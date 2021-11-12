#pragma once

#include <cstdint>

#include "AdTypes.hpp"

void init_ego_vehicle(VehicleType &ego_vehicle);

void init_vehicles(NeighborVehiclesType &vehicles);

void print_vehicle(const VehicleType &vehicle);

void print_neighbor_vehicles(const NeighborVehiclesType &vehicles);

void print_scene(const VehicleType &ego_vehicle, const NeighborVehiclesType &vehicles);

void compute_future_distance(VehicleType &vehicle, const float ego_driven_distance, const float seconds);

void compute_future_state(const VehicleType &ego_vehicle, NeighborVehiclesType &vehicles, const float seconds);

void longitudinal_control(const VehicleType &front_vehicle, const VehicleType &rear_vehicle, VehicleType &ego_vehicle);
