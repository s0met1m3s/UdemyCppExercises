#include <iostream>

#include "AdConstants.hpp"
#include "AdFunctions.hpp"
#include "AdTypes.hpp"

void initego_vehicle(VehicleType &ego_vehicle)
{
    ego_vehicle.Id = -1;
    ego_vehicle.speed_mps = 135.0F / 3.6F;
    ego_vehicle.longitudinal_distanceM = 0.0F;
    ego_vehicle.Lane = LaneAssociationType::LANE_ASSOCIATION_CENTER;
}

void initVehicles(NeighborVehiclesType &Vehicles)
{
    Vehicles.vehicles_leftLane[0].Id = 0;
    Vehicles.vehicles_leftLane[0].speed_mps = 130.0F / 3.6F;
    Vehicles.vehicles_leftLane[0].longitudinal_distanceM = 80.0F;
    Vehicles.vehicles_leftLane[0].Lane = LaneAssociationType::LANE_ASSOCIATION_LEFT;

    Vehicles.vehicles_leftLane[1].Id = 1;
    Vehicles.vehicles_leftLane[1].speed_mps = 80.0F / 3.6F;
    Vehicles.vehicles_leftLane[1].longitudinal_distanceM = -20.0F;
    Vehicles.vehicles_leftLane[1].Lane = LaneAssociationType::LANE_ASSOCIATION_LEFT;

    Vehicles.vehicles_centerLane[0].Id = 2;
    Vehicles.vehicles_centerLane[0].speed_mps = 120.0F / 3.6F;
    Vehicles.vehicles_centerLane[0].longitudinal_distanceM = 50.0F;
    Vehicles.vehicles_centerLane[0].Lane = LaneAssociationType::LANE_ASSOCIATION_CENTER;

    Vehicles.vehicles_centerLane[1].Id = 3;
    Vehicles.vehicles_centerLane[1].speed_mps = 110.0F / 3.6F;
    Vehicles.vehicles_centerLane[1].longitudinal_distanceM = -50.0F;
    Vehicles.vehicles_centerLane[1].Lane = LaneAssociationType::LANE_ASSOCIATION_CENTER;

    Vehicles.vehicles_rightLane[0].Id = 4;
    Vehicles.vehicles_rightLane[0].speed_mps = 90.0F / 3.6F;
    Vehicles.vehicles_rightLane[0].longitudinal_distanceM = 30.0F;
    Vehicles.vehicles_rightLane[0].Lane = LaneAssociationType::LANE_ASSOCIATION_RIGHT;


    Vehicles.vehicles_rightLane[1].Id = 5;
    Vehicles.vehicles_rightLane[1].speed_mps = 130.0F / 3.6F;
    Vehicles.vehicles_rightLane[1].longitudinal_distanceM = -30.0F;
    Vehicles.vehicles_rightLane[1].Lane = LaneAssociationType::LANE_ASSOCIATION_RIGHT;
}

void printVehicle(const VehicleType &Veh)
{
    if (EGO_VEHICLE_ID == Veh.Id)
    {
        std::cout << "ID: Ego VehicleType" << std::endl;
        std::cout << "Speed (m/s): " << Veh.speed_mps << std::endl << std::endl;
    }
    else
    {
        std::cout << "ID: " << Veh.Id << std::endl;
        std::cout << "Speed (m/s): " << Veh.speed_mps << std::endl;
        std::cout << "Distance: " << Veh.longitudinal_distanceM << std::endl << std::endl;
    }
}

void printneighbor_vehicles(const NeighborVehiclesType &Vehicles)
{
    for (std::size_t i = 0; i < NUM_VEHICLES_ON_LANE; i++)
    {
        printVehicle(Vehicles.vehicles_leftLane[i]);
    }

    for (std::size_t i = 0; i < NUM_VEHICLES_ON_LANE; i++)
    {
        printVehicle(Vehicles.vehicles_centerLane[i]);
    }

    for (std::size_t i = 0; i < NUM_VEHICLES_ON_LANE; i++)
    {
        printVehicle(Vehicles.vehicles_rightLane[i]);
    }
}

bool checkvalid_gap(const VehicleType &front_vehicle,
                    const VehicleType &rear_vehicle,
                    const VehicleType &ego_vehicle)
{
    const float ego_speedKmh = ego_vehicle.speed_mps * 3.6;
    const float min_distanceM = ego_speedKmh / 2.0;
    const bool distance_tofront_valid =
        std::abs(front_vehicle.longitudinal_distanceM) > min_distanceM ? true : false;
    const bool distance_torear_valid =
        std::abs(rear_vehicle.longitudinal_distanceM) > min_distanceM ? true : false;

    return distance_tofront_valid && distance_torear_valid;
}

GapType computetarget_gap(const VehicleType &ego_vehicle,
                          const NeighborVehiclesType &Vehicles,
                          const LaneAssociationType target_lane)
{
    GapType Gap{};

    switch (target_lane)
    {
    case LaneAssociationType::LANE_ASSOCIATION_LEFT:
    {
        const VehicleType &front_vehicle = Vehicles.vehicles_leftLane[0];
        const VehicleType &rear_vehicle = Vehicles.vehicles_leftLane[1];
        const float gap_lengthM =
            front_vehicle.longitudinal_distanceM - rear_vehicle.longitudinal_distanceM;


        Gap.length_m = gap_lengthM;
        Gap.valid_flag = checkvalid_gap(front_vehicle, rear_vehicle, ego_vehicle);
        Gap.Lane = LaneAssociationType::LANE_ASSOCIATION_LEFT;
        break;
    }
    case LaneAssociationType::LANE_ASSOCIATION_RIGHT:
    {
        const VehicleType &front_vehicle = Vehicles.vehicles_rightLane[0];
        const VehicleType &rear_vehicle = Vehicles.vehicles_rightLane[1];
        float gap_lengthM =
            front_vehicle.longitudinal_distanceM - rear_vehicle.longitudinal_distanceM;

        Gap.length_m = gap_lengthM;
        Gap.valid_flag = checkvalid_gap(front_vehicle, rear_vehicle, ego_vehicle);
        Gap.Lane = LaneAssociationType::LANE_ASSOCIATION_RIGHT;
        break;
    }
    case LaneAssociationType::LANE_ASSOCIATION_UNKNOWN:
    case LaneAssociationType::LANE_ASSOCIATION_CENTER:
    default:
    {
        break;
    }
    }

    return Gap;
}

void printGap(const GapType &Gap)
{
    std::cout << "Lane: " << static_cast<std::int32_t>(Gap.Lane) << std::endl;
    std::cout << "length_m: " << Gap.length_m << std::endl;
    std::cout << "valid_flag: " << Gap.valid_flag << std::endl << std::endl;
}

void printScene(const VehicleType &ego_vehicle, const NeighborVehiclesType &Vehicles)
{
    std::cout << "    \t   L    C    R  \n";

    std::size_t left_idx = 0;
    std::size_t center_idx = 0;
    std::size_t right_idx = 0;

    const std::int32_t Offset = 20;

    for (std::int32_t i = 100; i >= -100; i -= Offset)
    {
        const VehicleType &left_vehicle = Vehicles.vehicles_leftLane[left_idx];
        const VehicleType &center_vehicle = Vehicles.vehicles_centerLane[center_idx];
        const VehicleType &right_vehicle = Vehicles.vehicles_rightLane[right_idx];

        char left_string[] = "   ";
        char center_string[] = "   ";
        char right_string[] = "   ";

        if ((i >= left_vehicle.longitudinal_distanceM) &&
            (left_vehicle.longitudinal_distanceM > (i - Offset)))
        {
            std::strncpy(left_string, " V ", 4);
            left_idx++;
        }

        if ((i >= center_vehicle.longitudinal_distanceM) &&
            (center_vehicle.longitudinal_distanceM > (i - Offset)))
        {
            std::strncpy(center_string, " V ", 4);
            center_idx++;
        }
        else if ((i >= ego_vehicle.longitudinal_distanceM) &&
                 (ego_vehicle.longitudinal_distanceM > (i - Offset)))
        {
            std::strncpy(center_string, " E ", 4);
        }

        if ((i >= right_vehicle.longitudinal_distanceM) &&
            (right_vehicle.longitudinal_distanceM > (i - Offset)))
        {
            std::strncpy(right_string, " V ", 4);
            right_idx++;
        }

        std::cout << i << "\t| " << left_string << " |" << center_string << " |" << right_string
                  << " |\n";
    }

    std::cout << std::endl;
}

void computefuture_distance(VehicleType &Vehicle,
                            const float ego_drivenDistance,
                            const std::uint32_t Seconds)
{
    const float front_leftdriven_distance = Vehicle.speed_mps * Seconds;
    Vehicle.longitudinal_distanceM += front_leftdriven_distance - ego_drivenDistance;
}

void computefuture_state(const VehicleType &ego_vehicle,
                         NeighborVehiclesType &Vehicles,
                         const std::uint32_t Seconds)
{
    const float ego_drivenDistance = ego_vehicle.speed_mps * Seconds;

    computefuture_distance(Vehicles.vehicles_leftLane[0], ego_drivenDistance, Seconds);
    computefuture_distance(Vehicles.vehicles_leftLane[1], ego_drivenDistance, Seconds);

    computefuture_distance(Vehicles.vehicles_centerLane[0], ego_drivenDistance, Seconds);
    computefuture_distance(Vehicles.vehicles_centerLane[1], ego_drivenDistance, Seconds);

    computefuture_distance(Vehicles.vehicles_rightLane[0], ego_drivenDistance, Seconds);
    computefuture_distance(Vehicles.vehicles_rightLane[1], ego_drivenDistance, Seconds);
}
