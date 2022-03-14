#include <algorithm>
#include <iostream>
#include <vector>

#include "AdTypes.hpp"
#include "DataLoaderConstants.hpp"
#include "Perception.hpp"

void compute_velocities(const std::array<float, NUM_ITERATIONS> long_velocities_mps,
                        const std::array<float, NUM_ITERATIONS> lat_velocities_mps,
                        std::array<float, NUM_ITERATIONS> &velocities_mps)
{
    std::transform(long_velocities_mps.begin(),
                   long_velocities_mps.end(),
                   lat_velocities_mps.begin(),
                   velocities_mps.begin(),
                   [&](const auto v_long, const auto v_lat) {
                       return std::sqrt(std::pow(v_long, 2.0F) + std::pow(v_lat, 2.0F));
                   });
}

void compute_heading_degrees(const std::array<float, NUM_ITERATIONS> long_velocities_mps,
                             const std::array<float, NUM_ITERATIONS> lat_velocities_mps,
                             std::array<float, NUM_ITERATIONS> &heading_degrees)
{
    std::transform(
        long_velocities_mps.begin(),
        long_velocities_mps.end(),
        lat_velocities_mps.begin(),
        heading_degrees.begin(),
        [&](const auto v_long, const auto v_lat) { return (std::atan2(v_lat, v_long) / PI<float>)*180.0F; });
}

void compute_accelerations(const std::array<float, NUM_ITERATIONS> &velocities_mps,
                           std::array<float, NUM_ITERATIONS> &accelerations_mps2)
{
    accelerations_mps2[0] = 0.0F;

    for (std::size_t i = 1; i < NUM_ITERATIONS; ++i)
    {
        accelerations_mps2[i] = (velocities_mps[i] - velocities_mps[i - 1]) / CYCLE_TIME_S;
    }
}
