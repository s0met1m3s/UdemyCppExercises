#pragma once

#include <cstdint>

#include "AdConstants.hpp"

enum class LaneAssociationType
{
    LANE_ASSOCIATION_UNKNOWN,
    LANE_ASSOCIATION_RIGHT,
    LANE_ASSOCIATION_CENTER,
    LANE_ASSOCIATION_LEFT
};

struct VehicleType
{
    std::int32_t Id;
    LaneAssociationType Lane;
    float SpeedMps;
    float LongitudinalDistanceM;
};

struct NeighbourVehiclesType
{
    VehicleType VehiclesLeftLane[NUM_VEHICLES_ON_LANE];
    VehicleType VehiclesCenterLane[NUM_VEHICLES_ON_LANE];
    VehicleType VehiclesRightLane[NUM_VEHICLES_ON_LANE];
};

struct GapType
{
    float LengthM;
    LaneAssociationType Lane;
    bool ValidFlag;
};
