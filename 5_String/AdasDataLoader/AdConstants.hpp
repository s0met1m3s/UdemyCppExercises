#pragma once

#include <cstdint>
#include <cstring>

constexpr std::int32_t INVALID_VEHICLE_ID = -1;
constexpr std::int32_t EGO_VEHICLE_ID = -2;

constexpr std::size_t NUM_VEHICLES_ON_LANE = 2;
constexpr float SPEED_ADAPTAION_FACTOR = 0.01F;
