#pragma once

#include <array>
#include <cstdint>

#include "AdConstants.hpp"

enum class LaneAssociationType
{
    LEFT,
    RIGHT,
    CENTER,
    NONE,
};

struct VehicleType
{
    std::int32_t id;
    LaneAssociationType lane;
    float speed_mps;
    float distance_m;
};

struct NeighborVehiclesType
{
    std::array<VehicleType, NUM_VEHICLES_ON_LANE> vehicles_left_lane;
    std::array<VehicleType, NUM_VEHICLES_ON_LANE> vehicles_center_lane;
    std::array<VehicleType, NUM_VEHICLES_ON_LANE> vehicles_right_lane;
};

struct Polynomial3rdDegreeType
{
    float x3;
    float x2;
    float x1;
    float x0;
};

struct LaneType
{
    Polynomial3rdDegreeType left_polynomial;
    Polynomial3rdDegreeType right_polynomial;
};

struct LanesType
{
    LaneType left_lane;
    LaneType center_lane;
    LaneType right_lane;
};
