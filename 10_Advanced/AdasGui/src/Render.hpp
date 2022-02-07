#pragma once

#include <string_view>

#include "DataLoader.hpp"

void render_cycle(const VehicleType &ego_vehicle, const NeighborVehiclesType &vehicles);

void plot_solid_line(const float border, std::string_view label);

void plot_dashed_lines(const float border, std::string_view label);

void plot_ego_vehicle(const VehicleType &ego_vehicle, std::string_view label);

void plot_lane_vehicles(const std::array<VehicleType, 2> &vehicles,
                        const float offset_m,
                        std::string_view label_front,
                        std::string_view label_rear);

void plot_lanes(const VehicleType &ego_vehicle, const NeighborVehiclesType &vehicles);

void plot_vehicle_in_table(const VehicleType &vehicle, std::string_view position_name);

void plot_table(const VehicleType &ego_vehicle, const NeighborVehiclesType &vehicles);

void plot_cycle_number(const std::size_t cycle);
