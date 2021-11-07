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
    vehicles.vehicles_leftLane[0].Id = 0;
    vehicles.vehicles_leftLane[0].speed_mps = 130.0F / 3.6F;
    vehicles.vehicles_leftLane[0].longitudinal_distanceM = 80.0F;
    vehicles.vehicles_leftLane[0].Lane = LaneAssociationType::LANE_ASSOCIATION_LEFT;

    vehicles.vehicles_leftLane[1].Id = 1;
    vehicles.vehicles_leftLane[1].speed_mps = 80.0F / 3.6F;
    vehicles.vehicles_leftLane[1].longitudinal_distanceM = -20.0F;
    vehicles.vehicles_leftLane[1].Lane = LaneAssociationType::LANE_ASSOCIATION_LEFT;

    vehicles.vehicles_centerLane[0].Id = 2;
    vehicles.vehicles_centerLane[0].speed_mps = 120.0F / 3.6F;
    vehicles.vehicles_centerLane[0].longitudinal_distanceM = 50.0F;
    vehicles.vehicles_centerLane[0].Lane = LaneAssociationType::LANE_ASSOCIATION_CENTER;

    vehicles.vehicles_centerLane[1].Id = 3;
    vehicles.vehicles_centerLane[1].speed_mps = 110.0F / 3.6F;
    vehicles.vehicles_centerLane[1].longitudinal_distanceM = -50.0F;
    vehicles.vehicles_centerLane[1].Lane = LaneAssociationType::LANE_ASSOCIATION_CENTER;

    vehicles.vehicles_rightLane[0].Id = 4;
    vehicles.vehicles_rightLane[0].speed_mps = 90.0F / 3.6F;
    vehicles.vehicles_rightLane[0].longitudinal_distanceM = 30.0F;
    vehicles.vehicles_rightLane[0].Lane = LaneAssociationType::LANE_ASSOCIATION_RIGHT;

    vehicles.vehicles_rightLane[1].Id = 5;
    vehicles.vehicles_rightLane[1].speed_mps = 130.0F / 3.6F;
    vehicles.vehicles_rightLane[1].longitudinal_distanceM = -30.0F;
    vehicles.vehicles_rightLane[1].Lane = LaneAssociationType::LANE_ASSOCIATION_RIGHT;
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
    print_vehicle(vehicles.vehicles_leftLane[0]);
    print_vehicle(vehicles.vehicles_leftLane[1]);

    print_vehicle(vehicles.vehicles_centerLane[0]);
    print_vehicle(vehicles.vehicles_centerLane[1]);

    print_vehicle(vehicles.vehicles_rightLane[0]);
    print_vehicle(vehicles.vehicles_rightLane[1]);
}

bool check_valid_gap(const VehicleType &front_vehicle,
                     const VehicleType &rear_vehicle,
                     const VehicleType &ego_vehicle)
{
    const float ego_speed_kmh = ego_vehicle.speed_mps * 3.6F;
    const float min_distance_m = ego_speed_kmh / 2.0F;
    const bool distance_tofront_valid =
        std::abs(front_vehicle.longitudinal_distanceM) > min_distance_m ? true : false;
    const bool distance_torear_valid =
        std::abs(rear_vehicle.longitudinal_distanceM) > min_distance_m ? true : false;

    return (distance_tofront_valid && distance_torear_valid);
}

GapType compute_target_gap(const VehicleType &ego_vehicle,
                           const NeighborVehiclesType &vehicles,
                           const LaneAssociationType target_lane)
{
    GapType gap{};

    switch (target_lane)
    {
    case LaneAssociationType::LANE_ASSOCIATION_LEFT:
    {
        const VehicleType &front_vehicle = vehicles.vehicles_leftLane[0];
        const VehicleType &rear_vehicle = vehicles.vehicles_leftLane[1];
        const float gap_lengthM =
            front_vehicle.longitudinal_distanceM - rear_vehicle.longitudinal_distanceM;

        gap.length_m = gap_lengthM;
        gap.valid_flag = check_valid_gap(front_vehicle, rear_vehicle, ego_vehicle);
        gap.Lane = LaneAssociationType::LANE_ASSOCIATION_LEFT;
        break;
    }
    case LaneAssociationType::LANE_ASSOCIATION_RIGHT:
    {
        const VehicleType &front_vehicle = vehicles.vehicles_rightLane[0];
        const VehicleType &rear_vehicle = vehicles.vehicles_rightLane[1];
        float gap_lengthM =
            front_vehicle.longitudinal_distanceM - rear_vehicle.longitudinal_distanceM;

        gap.length_m = gap_lengthM;
        gap.valid_flag = check_valid_gap(front_vehicle, rear_vehicle, ego_vehicle);
        gap.Lane = LaneAssociationType::LANE_ASSOCIATION_RIGHT;
        break;
    }
    case LaneAssociationType::LANE_ASSOCIATION_UNKNOWN:
    case LaneAssociationType::LANE_ASSOCIATION_CENTER:
    default:
    {
        break;
    }
    }

    return gap;
}

void print_gap(const GapType &gap)
{
    std::cout << "Lane: " << static_cast<std::int32_t>(gap.Lane) << std::endl;
    std::cout << "length_m: " << gap.length_m << std::endl;
    std::cout << "valid_flag: " << gap.valid_flag << std::endl << std::endl;
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
        const VehicleType &left_vehicle = vehicles.vehicles_leftLane[left_idx];
        const VehicleType &center_vehicle = vehicles.vehicles_centerLane[center_idx];
        const VehicleType &right_vehicle = vehicles.vehicles_rightLane[right_idx];

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

    compute_future_distance(vehicles.vehicles_leftLane[0], ego_driven_distance, seconds);
    compute_future_distance(vehicles.vehicles_leftLane[1], ego_driven_distance, seconds);

    compute_future_distance(vehicles.vehicles_centerLane[0], ego_driven_distance, seconds);
    compute_future_distance(vehicles.vehicles_centerLane[1], ego_driven_distance, seconds);

    compute_future_distance(vehicles.vehicles_rightLane[0], ego_driven_distance, seconds);
    compute_future_distance(vehicles.vehicles_rightLane[1], ego_driven_distance, seconds);
}
