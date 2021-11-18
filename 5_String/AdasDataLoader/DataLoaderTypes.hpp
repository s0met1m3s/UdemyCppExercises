#pragma once

#include <array>
#include <tuple>

#include "AdTypes.hpp"
#include "DataLoaderConstants.hpp"

using VehiclesData = std::array<std::array<VehicleType, NUM_ITERATIONS>, NUM_VEHICLES>;
using VehiclesInCycle = std::tuple<VehicleType, VehicleType, VehicleType, VehicleType, VehicleType, VehicleType>;
