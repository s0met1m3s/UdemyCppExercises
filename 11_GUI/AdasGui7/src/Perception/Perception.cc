#include <algorithm>
#include <array>
#include <iostream>

#include "AdTypes.hpp"
#include "DataLoaderConstants.hpp"
#include "DataLoaderTypes.hpp"
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

void compute_rel_velocities(const std::array<float, NUM_ITERATIONS> &velocities_mps,
                            const std::array<float, NUM_ITERATIONS> &ego_velocities_mps,
                            std::array<float, NUM_ITERATIONS> &rel_velocities_mps)
{
    std::transform(velocities_mps.begin(),
                   velocities_mps.end(),
                   ego_velocities_mps.begin(),
                   rel_velocities_mps.begin(),
                   [&](const auto v_veh, const auto v_ego) { return v_ego - v_veh; });
}

void compute_rel_accelerations(const std::array<float, NUM_ITERATIONS> &accelerations_mps2,
                               const std::array<float, NUM_ITERATIONS> &ego_accelerations_mps2,
                               std::array<float, NUM_ITERATIONS> &rel_accelerations_mps2)
{
    std::transform(accelerations_mps2.begin(),
                   accelerations_mps2.end(),
                   ego_accelerations_mps2.begin(),
                   rel_accelerations_mps2.begin(),
                   [&](const auto a_veh, const auto a_ego) { return a_ego - a_veh; });
}

void compute_ego_kinematics(EgoVehicleLogData &ego_data)
{
    compute_velocities(ego_data.long_velocities_mps, ego_data.lat_velocities_mps, ego_data.velocities_mps);
    compute_heading_degrees(ego_data.long_velocities_mps, ego_data.lat_velocities_mps, ego_data.heading_degs);
    compute_accelerations(ego_data.velocities_mps, ego_data.accelerations_mps2);
}

void compute_vehicle_kinematics(const EgoVehicleLogData &ego_data, VehicleLogData &vehicle_data)
{
    compute_velocities(vehicle_data.long_velocities_mps,
                       vehicle_data.lat_velocities_mps,
                       vehicle_data.velocities_mps);
    compute_heading_degrees(vehicle_data.long_velocities_mps,
                            vehicle_data.lat_velocities_mps,
                            vehicle_data.heading_degs);
    compute_accelerations(vehicle_data.velocities_mps, vehicle_data.accelerations_mps2);
    compute_rel_velocities(vehicle_data.velocities_mps,
                           ego_data.velocities_mps,
                           vehicle_data.rel_velocities_mps);
    compute_rel_accelerations(vehicle_data.accelerations_mps2,
                              ego_data.accelerations_mps2,
                              vehicle_data.rel_accelerations_mps2);
}
