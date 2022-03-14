#pragma once

#include "AdTypes.hpp"
#include "DataLoaderConstants.hpp"

void compute_velocities(const std::array<float, NUM_ITERATIONS> long_velocities_mps,
                        const std::array<float, NUM_ITERATIONS> lat_velocities_mps,
                        std::array<float, NUM_ITERATIONS> &velocities_mps);

void compute_heading_degrees(const std::array<float, NUM_ITERATIONS> long_velocities_mps,
                             const std::array<float, NUM_ITERATIONS> lat_velocities_mps,
                             std::array<float, NUM_ITERATIONS> &heading_degrees);

void compute_accelerations(const std::array<float, NUM_ITERATIONS> &velocities_mps,
                           std::array<float, NUM_ITERATIONS> &accelerations_mps2);
