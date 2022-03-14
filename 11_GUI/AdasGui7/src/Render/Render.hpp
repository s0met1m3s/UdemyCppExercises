#pragma once

#include "DataLoader.hpp"

static constexpr const char *const LANE_NAMES[] = {
    "Left",
    "Center",
    "Right",
    "None",
};

static constexpr const char *const OBJECT_NAMES[] = {
    "Car",
    "Truck",
    "Motorbike",
    "None",
};

static constexpr const char *const VALUE_NAMES[] = {
    "long_velocity_mps",
    "lat_velocity_mps",
    "velocity_mps",
    "acceleration_mps2",
    "heading_deg",
    "rel_velocity_mps",
    "rel_acceleration_mps2",
};

void render_cycle(const VehicleInformationType &ego_vehicle,
                  const NeighborVehiclesType &vehicles,
                  const LanesInformationType &lanes,
                  const bool long_request,
                  const LaneAssociationType lat_request,
                  const std::uint32_t cycle_idx);
