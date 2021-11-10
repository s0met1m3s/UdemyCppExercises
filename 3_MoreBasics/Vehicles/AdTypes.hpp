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
    VehicleType vehicles_left_lane[NUM_VEHICLES_ON_LANE];
    VehicleType vehicles_center_lane[NUM_VEHICLES_ON_LANE];
    VehicleType vehicles_right_lane[NUM_VEHICLES_ON_LANE];
};
