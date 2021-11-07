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
    float speed_mps;
    float longitudinal_distanceM;
};

struct NeighborVehiclesType
{
    VehicleType vehicles_leftLane[NUM_VEHICLES_ON_LANE];
    VehicleType vehicles_centerLane[NUM_VEHICLES_ON_LANE];
    VehicleType vehicles_rightLane[NUM_VEHICLES_ON_LANE];
};

struct GapType
{
    float length_m;
    LaneAssociationType Lane;
    bool valid_flag;
};
