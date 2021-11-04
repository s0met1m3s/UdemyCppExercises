#pragma once

#include <cstdint>

#include "AdTypes.hpp"

void initego_vehicle(VehicleType &);

void initVehicles(NeighborVehiclesType &);

void printVehicle(const VehicleType &);

void printneighbor_vehicles(const NeighborVehiclesType &);

bool checkvalid_gap(const VehicleType &, const VehicleType &, const VehicleType &);

GapType computetarget_gap(const VehicleType &,
                          const NeighborVehiclesType &,
                          const LaneAssociationType);

void printGap(const GapType &);

void printScene(const VehicleType &, const NeighborVehiclesType &);

void computefuture_distance(VehicleType &, const float, const std::uint32_t);

void computefuture_state(const VehicleType &, NeighborVehiclesType &, const std::uint32_t);
