#pragma once

#include "DataLoader.hpp"

void render_cycle(const VehicleInformationType &ego_vehicle,
                  const NeighborVehiclesType &vehicles,
                  const LanesInformationType &lanes);

void plot_lanes(const VehicleInformationType &ego_vehicle,
                const NeighborVehiclesType &vehicles,
                const LanesInformationType &lanes);

void plot_table(const VehicleInformationType &ego_vehicle, const NeighborVehiclesType &vehicles);
