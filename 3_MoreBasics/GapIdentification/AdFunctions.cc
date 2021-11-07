#include <iostream>

#include "AdConstants.hpp"
#include "AdFunctions.hpp"
#include "AdTypes.hpp"

void init_ego_vehicle(VehicleType &ego_vehicle)
{
    ego_vehicle.Id = -1;
    ego_vehicle.speed_mps = 135.0F / 3.6F;
    ego_vehicle.longitudinal_distanceM = 0.0F;
    ego_vehicle.Lane = LaneAssociationType::LANE_ASSOCIATION_CENTER;
}

void init_vehicles(NeighborVehiclesType &vehicles)
{
    vehicles.vehicles_left_lane[0].Id = 0;
    vehicles.vehicles_left_lane[0].speed_mps = 130.0F / 3.6F;
    vehicles.vehicles_left_lane[0].longitudinal_distanceM = 80.0F;
    vehicles.vehicles_left_lane[0].Lane = LaneAssociationType::LANE_ASSOCIATION_LEFT;

    vehicles.vehicles_left_lane[1].Id = 1;
    vehicles.vehicles_left_lane[1].speed_mps = 80.0F / 3.6F;
    vehicles.vehicles_left_lane[1].longitudinal_distanceM = -20.0F;
    vehicles.vehicles_left_lane[1].Lane = LaneAssociationType::LANE_ASSOCIATION_LEFT;

    vehicles.vehicles_center_lane[0].Id = 2;
    vehicles.vehicles_center_lane[0].speed_mps = 120.0F / 3.6F;
    vehicles.vehicles_center_lane[0].longitudinal_distanceM = 50.0F;
    vehicles.vehicles_center_lane[0].Lane = LaneAssociationType::LANE_ASSOCIATION_CENTER;

    vehicles.vehicles_center_lane[1].Id = 3;
    vehicles.vehicles_center_lane[1].speed_mps = 110.0F / 3.6F;
    vehicles.vehicles_center_lane[1].longitudinal_distanceM = -50.0F;
    vehicles.vehicles_center_lane[1].Lane = LaneAssociationType::LANE_ASSOCIATION_CENTER;

    vehicles.vehicles_right_lane[0].Id = 4;
    vehicles.vehicles_right_lane[0].speed_mps = 90.0F / 3.6F;
    vehicles.vehicles_right_lane[0].longitudinal_distanceM = 30.0F;
    vehicles.vehicles_right_lane[0].Lane = LaneAssociationType::LANE_ASSOCIATION_RIGHT;

    vehicles.vehicles_right_lane[1].Id = 5;
    vehicles.vehicles_right_lane[1].speed_mps = 130.0F / 3.6F;
    vehicles.vehicles_right_lane[1].longitudinal_distanceM = -30.0F;
    vehicles.vehicles_right_lane[1].Lane = LaneAssociationType::LANE_ASSOCIATION_RIGHT;
}

void print_vehicle(const VehicleType &vehicle)
{
    if (EGO_VEHICLE_ID == vehicle.Id)
    {
        std::cout << "ID: Ego VehicleType" << std::endl;
        std::cout << "Speed (m/s): " << vehicle.speed_mps << std::endl << std::endl;
    }
    else
    {
        std::cout << "ID: " << vehicle.Id << std::endl;
        std::cout << "Speed (m/s): " << vehicle.speed_mps << std::endl;
        std::cout << "Distance: " << vehicle.longitudinal_distanceM << std::endl << std::endl;
    }
}

void print_neighbor_vehicles(const NeighborVehiclesType &vehicles)
{
    print_vehicle(vehicles.vehicles_left_lane[0]);
    print_vehicle(vehicles.vehicles_left_lane[1]);

    print_vehicle(vehicles.vehicles_center_lane[0]);
    print_vehicle(vehicles.vehicles_center_lane[1]);

    print_vehicle(vehicles.vehicles_right_lane[0]);
    print_vehicle(vehicles.vehicles_right_lane[1]);
}

void print_scene(const VehicleType &ego_vehicle, const NeighborVehiclesType &vehicles)
{
    std::cout << "    \t   L    C    R  \n";

    std::size_t left_idx = 0;
    std::size_t center_idx = 0;
    std::size_t right_idx = 0;

    const std::int32_t Offset = 20;

    for (std::int32_t i = 100; i >= -100; i -= Offset)
    {
        const VehicleType &left_vehicle = vehicles.vehicles_left_lane[left_idx];
        const VehicleType &center_vehicle = vehicles.vehicles_center_lane[center_idx];
        const VehicleType &right_vehicle = vehicles.vehicles_right_lane[right_idx];

        char left_string[]{"   "};
        char center_string[]{"   "};
        char right_string[]{"   "};

        float range_m = static_cast<float>(i);

        if ((range_m >= left_vehicle.longitudinal_distanceM) &&
            (left_vehicle.longitudinal_distanceM > (range_m - Offset)))
        {
            std::strncpy(left_string, " V ", 4);
            left_idx++;
        }

        if ((range_m >= center_vehicle.longitudinal_distanceM) &&
            (center_vehicle.longitudinal_distanceM > (range_m - Offset)))
        {
            std::strncpy(center_string, " V ", 4);
            center_idx++;
        }
        else if ((range_m >= ego_vehicle.longitudinal_distanceM) &&
                 (ego_vehicle.longitudinal_distanceM > (range_m - Offset)))
        {
            std::strncpy(center_string, " E ", 4);
        }

        if ((range_m >= right_vehicle.longitudinal_distanceM) &&
            (right_vehicle.longitudinal_distanceM > (range_m - Offset)))
        {
            std::strncpy(right_string, " V ", 4);
            right_idx++;
        }

        std::cout << i << "\t| " << left_string << " |" << center_string << " |" << right_string
                  << " |\n";
    }

    std::cout << std::endl;
}

void compute_future_distance(VehicleType &vehicle,
                             const float ego_driven_distance,
                             const float seconds)
{
    const float front_leftdriven_distance = vehicle.speed_mps * seconds;
    vehicle.longitudinal_distanceM += front_leftdriven_distance - ego_driven_distance;
}

void compute_future_state(const VehicleType &ego_vehicle,
                          NeighborVehiclesType &vehicles,
                          const float seconds)
{
    const float ego_driven_distance = ego_vehicle.speed_mps * seconds;

    compute_future_distance(vehicles.vehicles_left_lane[0], ego_driven_distance, seconds);
    compute_future_distance(vehicles.vehicles_left_lane[1], ego_driven_distance, seconds);

    compute_future_distance(vehicles.vehicles_center_lane[0], ego_driven_distance, seconds);
    compute_future_distance(vehicles.vehicles_center_lane[1], ego_driven_distance, seconds);

    compute_future_distance(vehicles.vehicles_right_lane[0], ego_driven_distance, seconds);
    compute_future_distance(vehicles.vehicles_right_lane[1], ego_driven_distance, seconds);
}
