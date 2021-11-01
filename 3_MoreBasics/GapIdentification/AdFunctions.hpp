#pragma once

#include <cstdint>

#include "AdTypes.hpp"

void initEgoVehicle(VehicleType &);

void initVehicles(NeighbourVehiclesType &);

void printVehicle(const VehicleType &);

void printNeighborVehicles(const NeighbourVehiclesType &);

bool checkValidGap(const VehicleType &, const VehicleType &, const VehicleType &);

GapType computeTargetGap(const VehicleType &,
                         const NeighbourVehiclesType &,
                         const LaneAssociationType);

void printGap(const GapType &);

void printScene(const VehicleType &, const NeighbourVehiclesType &);

void computeFutureDistance(VehicleType &, const float, const std::uint32_t);

void computeFutureState(const VehicleType &, NeighbourVehiclesType &, const std::uint32_t);
