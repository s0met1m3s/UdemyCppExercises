#pragma once

#include <cstdint>
#include <string>
#include <string_view>

#include "AdTypes.hpp"

float kph_to_mps(const float kph);

float mps_to_kph(const float mps);

std::string &get_ego_string(const VehicleType &ego_vehicle,
                            std::string &left_string,
                            std::string &center_string,
                            std::string &right_string);

void print_vehicle(const VehicleType &vehicle);

void print_neighbor_vehicles(const NeighborVehiclesType &vehicles);

bool check_vehicle_in_tile(const VehicleType *const vehicle, const float range_m, const float offset_m);

bool check_vehicle_out_of_range(const VehicleType *const vehicle);

void print_scene(const VehicleType &ego_vehicle, const NeighborVehiclesType &vehicles);

void print_vehicle_speed(const VehicleType &vehicle, const std::string_view name);

void compute_future_distance(VehicleType &vehicle, const float ego_driven_distance, const float seconds);

void compute_future_state(const VehicleType &ego_vehicle,
                          NeighborVehiclesType &vehicles,
                          const float seconds);

void longitudinal_control(const VehicleType &front_vehicle, VehicleType &ego_vehicle);

const std::array<VehicleType, NUM_VEHICLES_ON_LANE> &get_vehicle_array(
    const LaneAssociationType lane,
    const NeighborVehiclesType &vehicles);

LaneAssociationType get_lane_change_request(const VehicleType &ego_vehicle,
                                            const NeighborVehiclesType &vehicles);

bool lateral_control(const LaneAssociationType lane_change_request, VehicleType &ego_vehicle);
