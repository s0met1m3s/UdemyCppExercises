#pragma once

#include <cstdint>
#include <string_view>

#include "AdTypes.hpp"

float kph_to_mps(const float kph);

float mps_to_kph(const float mps);

void longitudinal_control(const VehicleInformationType &front_vehicle, VehicleInformationType &ego_vehicle);

const std::array<VehicleInformationType, NUM_VEHICLES_ON_LANE> &get_vehicle_array(
    const LaneAssociationType lane,
    const NeighborVehiclesType &vehicles);

LaneAssociationType get_lane_change_request(const VehicleInformationType &ego_vehicle,
                                            const NeighborVehiclesType &vehicles);

bool lateral_control(const LaneAssociationType lane_change_request, VehicleInformationType &ego_vehicle);
