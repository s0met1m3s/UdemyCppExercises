#include <algorithm>
#include <array>
#include <cmath>

#include "Units.hpp"
#include "utils.hpp"

constexpr static std::size_t NUM_ENTRIES = 3;
constexpr static std::uint32_t TIME_SPAN_MS = 50;

void compute_velocities(
    const std::array<float, NUM_ENTRIES> long_velocities_mps,
    const std::array<float, NUM_ENTRIES> lat_velocities_mps,
    std::array<float, NUM_ENTRIES> &velocities_mps);

void compute_heading_degrees(
    const std::array<float, NUM_ENTRIES> long_velocities_mps,
    const std::array<float, NUM_ENTRIES> lat_velocities_mps,
    std::array<float, NUM_ENTRIES> &heading_degrees);

void compute_accelerations(const std::array<float, NUM_ENTRIES> &velocities_mps,
                           std::array<float, NUM_ENTRIES> &accelerations_mps2);

void compute_rel_velocities(
    const std::array<float, NUM_ENTRIES> &velocities_mps,
    const std::array<float, NUM_ENTRIES> &ego_velocities_mps,
    std::array<float, NUM_ENTRIES> &rel_velocities_mps);

void compute_rel_accelerations(
    const std::array<float, NUM_ENTRIES> &accelerations_mps2,
    const std::array<float, NUM_ENTRIES> &ego_accelerations_mps2,
    std::array<float, NUM_ENTRIES> &rel_accelerations_mps2);

int main()
{
    const auto ego_velocities_mps =
        std::array<float, NUM_ENTRIES>{25.0F, 25.6F, 26.2F};
    const auto ego_accelerations_mps2 =
        std::array<float, NUM_ENTRIES>{0.0F, 0.6F, 0.6F};

    const auto long_velocities_mps =
        std::array<float, NUM_ENTRIES>{23.0F, 25.0F, 27.0F};
    const auto lat_velocities_mps =
        std::array<float, NUM_ENTRIES>{1.0F, 1.2F, 1.1F};

    auto velocities_mps = std::array<float, NUM_ENTRIES>{};
    auto heading_degrees = std::array<float, NUM_ENTRIES>{};
    auto accelerations_mps2 = std::array<float, NUM_ENTRIES>{};
    auto rel_velocities_mps = std::array<float, NUM_ENTRIES>{};
    auto rel_accelerations_mps2 = std::array<float, NUM_ENTRIES>{};

    compute_velocities(long_velocities_mps, lat_velocities_mps, velocities_mps);
    compute_heading_degrees(long_velocities_mps,
                            lat_velocities_mps,
                            heading_degrees);
    compute_accelerations(velocities_mps, accelerations_mps2);
    compute_rel_velocities(long_velocities_mps,
                           ego_velocities_mps,
                           rel_velocities_mps);
    compute_rel_accelerations(accelerations_mps2,
                              ego_accelerations_mps2,
                              rel_accelerations_mps2);

    std::cout << "velocities_mps: \n";
    print_array(velocities_mps);
    std::cout << "heading_degrees: \n";
    print_array(heading_degrees);
    std::cout << "accelerations_mps2: \n";
    print_array(accelerations_mps2);
    std::cout << "rel_velocities_mps: \n";
    print_array(rel_velocities_mps);
    std::cout << "rel_accelerations_mps2: \n";
    print_array(rel_accelerations_mps2);
}

void compute_velocities(
    const std::array<float, NUM_ENTRIES> long_velocities_mps,
    const std::array<float, NUM_ENTRIES> lat_velocities_mps,
    std::array<float, NUM_ENTRIES> &velocities_mps)
{
    std::transform(long_velocities_mps.begin(),
                   long_velocities_mps.end(),
                   lat_velocities_mps.begin(),
                   velocities_mps.begin(),
                   [&](const auto v_long, const auto v_lat) {
                       return std::sqrt(std::pow(v_long, 2.0F) +
                                        std::pow(v_lat, 2.0F));
                   });
}

void compute_heading_degrees(
    const std::array<float, NUM_ENTRIES> long_velocities_mps,
    const std::array<float, NUM_ENTRIES> lat_velocities_mps,
    std::array<float, NUM_ENTRIES> &heading_degrees)
{
    std::transform(long_velocities_mps.begin(),
                   long_velocities_mps.end(),
                   lat_velocities_mps.begin(),
                   heading_degrees.begin(),
                   [&](const auto v_long, const auto v_lat) {
                       return (std::atan2(v_lat, v_long) / PI<float>)*180.0F;
                   });
}

void compute_accelerations(const std::array<float, NUM_ENTRIES> &velocities_mps,
                           std::array<float, NUM_ENTRIES> &accelerations_mps2)
{
    accelerations_mps2[0] = 0.0F;

    for (std::size_t i = 1; i < NUM_ENTRIES; ++i)
    {
        accelerations_mps2[i] =
            (velocities_mps[i] - velocities_mps[i - 1]) / TIME_SPAN_MS;
    }
}

void compute_rel_velocities(
    const std::array<float, NUM_ENTRIES> &velocities_mps,
    const std::array<float, NUM_ENTRIES> &ego_velocities_mps,
    std::array<float, NUM_ENTRIES> &rel_velocities_mps)
{
    std::transform(
        velocities_mps.begin(),
        velocities_mps.end(),
        ego_velocities_mps.begin(),
        rel_velocities_mps.begin(),
        [&](const auto v_veh, const auto v_ego) { return v_ego - v_veh; });
}

void compute_rel_accelerations(
    const std::array<float, NUM_ENTRIES> &accelerations_mps2,
    const std::array<float, NUM_ENTRIES> &ego_accelerations_mps2,
    std::array<float, NUM_ENTRIES> &rel_accelerations_mps2)
{
    std::transform(
        accelerations_mps2.begin(),
        accelerations_mps2.end(),
        ego_accelerations_mps2.begin(),
        rel_accelerations_mps2.begin(),
        [&](const auto a_veh, const auto a_ego) { return a_ego - a_veh; });
}
