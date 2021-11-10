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
