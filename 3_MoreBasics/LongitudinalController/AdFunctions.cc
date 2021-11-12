#include <cmath>
#include <iostream>

#include "AdConstants.hpp"
#include "AdFunctions.hpp"
#include "AdTypes.hpp"

float kph_to_mps(const float kph)
{
    return kph / 3.6F;
}

float mps_to_kph(const float mps)
{
    return mps * 3.6F;
}

void init_ego_vehicle(VehicleType &ego_vehicle)
{
    ego_vehicle.id = EGO_VEHICLE_ID;
    ego_vehicle.speed_mps = kph_to_mps(120.0F);
    ego_vehicle.distance_m = 0.0F;
    ego_vehicle.lane = LaneAssociationType::CENTER;
}

void init_vehicle(VehicleType &vehicle,
                  const std::int32_t id,
                  const float speed_mps,
                  const float distance_m,
                  const LaneAssociationType lane)
{
    vehicle.id = id;
    vehicle.speed_mps = kph_to_mps(speed_mps);
    vehicle.distance_m = distance_m;
    vehicle.lane = lane;
}

void init_vehicles(NeighborVehiclesType &vehicles)
{
    init_vehicle(vehicles.vehicles_left_lane[0], 0, 130.0F, 80.0F, LaneAssociationType::LEFT);
    init_vehicle(vehicles.vehicles_left_lane[1], 1, 130.0F, -20.0F, LaneAssociationType::LEFT);
    init_vehicle(vehicles.vehicles_center_lane[0], 2, 122.0F, 70.0F, LaneAssociationType::CENTER);
    init_vehicle(vehicles.vehicles_center_lane[1], 3, 118.0F, -50.0F, LaneAssociationType::CENTER);
    init_vehicle(vehicles.vehicles_right_lane[0], 4, 100.0F, 30.0F, LaneAssociationType::RIGHT);
    init_vehicle(vehicles.vehicles_right_lane[1], 5, 80.0F, -30.0F, LaneAssociationType::RIGHT);
}

void print_vehicle(const VehicleType &vehicle)
{
    if (EGO_VEHICLE_ID == vehicle.id)
    {
        std::cout << "Ego Vehicle: \n";
        std::cout << "Speed (m/s): " << vehicle.speed_mps << "\n";
    }
    else
    {
        std::cout << "ID: " << vehicle.id << "\n";
        std::cout << "Speed (m/s): " << vehicle.speed_mps << "\n";
        std::cout << "Distance (m): " << vehicle.distance_m << "\n";
    }
}

void print_neighbor_vehicles(const NeighborVehiclesType &vehicles)
{
    print_vehicle(vehicles.vehicles_left_lane[0]);
    print_vehicle(vehicles.vehicles_left_lane[1]);
    print_vehicle(vehicles.vehicles_center_lane[0]);
    print_vehicle(vehicles.vehicles_center_lane[1]);
    print_vehicle(vehicles.vehicles_right_lane[0]);
    print_vehicle(vehicles.vehicles_right_lane[1]);
}

void print_vehicle_speed(const VehicleType &vehicle, const char *name)
{
    if (vehicle.id != INVALID_VEHICLE_ID)
    {
        std::cout.precision(3);
        std::cout << name << ": (" << vehicle.speed_mps << " mps) ";
    }
}

void print_scene(const VehicleType &ego_vehicle, const NeighborVehiclesType &vehicles)
{
    std::cout << "    \t  L    C    R  \n";

    std::size_t left_idx = 0;
    std::size_t center_idx = 0;
    std::size_t right_idx = 0;

    const std::int32_t offset_m = 10;

    for (std::int32_t i = 100; i >= -100; i -= offset_m)
    {
        const VehicleType &left_vehicle = vehicles.vehicles_left_lane[left_idx];
        const VehicleType &center_vehicle = vehicles.vehicles_center_lane[center_idx];
        const VehicleType &right_vehicle = vehicles.vehicles_right_lane[right_idx];

        char left_string[]{"   "};
        char center_string[]{"   "};
        char right_string[]{"   "};

        const float range_m = static_cast<float>(i);

        if ((range_m >= left_vehicle.distance_m) && (left_vehicle.distance_m > (range_m - offset_m)))
        {
            left_string[1] = 'V';
            left_idx++;
        }

        if ((range_m >= ego_vehicle.distance_m) && (ego_vehicle.distance_m > (range_m - offset_m)))
        {
            center_string[1] = 'E';
        }
        else if ((range_m >= center_vehicle.distance_m) && (center_vehicle.distance_m > (range_m - offset_m)))
        {
            center_string[1] = 'V';
            center_idx++;
        }

        if ((range_m >= right_vehicle.distance_m) && (right_vehicle.distance_m > (range_m - offset_m)))
        {
            right_string[1] = 'V';
            right_idx++;
        }

        std::cout << i << "\t| " << left_string << " |" << center_string << " |" << right_string << " |\n";
    }

    std::cout << "\n";
    print_vehicle_speed(ego_vehicle, "E");
    print_vehicle_speed(vehicles.vehicles_left_lane[0], "L1");
    print_vehicle_speed(vehicles.vehicles_left_lane[1], "L2");
    print_vehicle_speed(vehicles.vehicles_center_lane[0], "C1");
    print_vehicle_speed(vehicles.vehicles_center_lane[1], "C2");
    print_vehicle_speed(vehicles.vehicles_right_lane[0], "R1");
    print_vehicle_speed(vehicles.vehicles_right_lane[1], "R2");
    std::cout << "\n";
}

void compute_future_distance(VehicleType &vehicle, const float ego_driven_distance, const float seconds)
{
    const float driven_distance = vehicle.speed_mps * seconds;
    vehicle.distance_m += driven_distance - ego_driven_distance;

    if (std::abs(vehicle.distance_m) >= MAX_VIEW_RANGE_M)
    {
        vehicle.id = INVALID_VEHICLE_ID;
    }
}

void compute_future_state(const VehicleType &ego_vehicle, NeighborVehiclesType &vehicles, const float seconds)
{
    const float ego_driven_distance = ego_vehicle.speed_mps * seconds;

    compute_future_distance(vehicles.vehicles_left_lane[0], ego_driven_distance, seconds);
    compute_future_distance(vehicles.vehicles_left_lane[1], ego_driven_distance, seconds);
    compute_future_distance(vehicles.vehicles_center_lane[0], ego_driven_distance, seconds);
    compute_future_distance(vehicles.vehicles_center_lane[1], ego_driven_distance, seconds);
    compute_future_distance(vehicles.vehicles_right_lane[0], ego_driven_distance, seconds);
    compute_future_distance(vehicles.vehicles_right_lane[1], ego_driven_distance, seconds);
}

void longitudinal_control(const VehicleType &front_vehicle, const VehicleType &rear_vehicle, VehicleType &ego_vehicle)
{
    auto rear_vehicle_to_close = false;
    auto front_vehicle_to_close = false;

    auto minimal_distance = mps_to_kph(ego_vehicle.speed_mps) / 2.0F;

    const auto font_distance_abs = std::abs(front_vehicle.distance_m);
    const auto rear_distance_abs = std::abs(rear_vehicle.distance_m);

    if (front_vehicle.id != INVALID_VEHICLE_ID && font_distance_abs < minimal_distance)
    {
        front_vehicle_to_close = true;
    }

    if (rear_vehicle.id != INVALID_VEHICLE_ID && rear_distance_abs < minimal_distance)
    {
        rear_vehicle_to_close = true;
    }

    if (!front_vehicle_to_close && !rear_vehicle_to_close)
    {
        return;
    }

    if (rear_vehicle_to_close && !front_vehicle_to_close)
    {
        // increase speed
        const auto increase = ego_vehicle.speed_mps * SPEED_ADAPTATION_MPS;

        if (ego_vehicle.speed_mps + increase < MAX_VEHICLE_SPEED_MPS)
        {
            ego_vehicle.speed_mps += increase;
        }
    }
    else if (!rear_vehicle_to_close && front_vehicle_to_close)
    {
        // decrease speed
        const auto decrease = ego_vehicle.speed_mps * SPEED_ADAPTATION_MPS;

        if (ego_vehicle.speed_mps - decrease < MAX_VEHICLE_SPEED_MPS)
        {
            ego_vehicle.speed_mps -= decrease;
        }
    }
    else
    {
        // big issue ;)
        if (rear_vehicle_to_close && rear_vehicle_to_close && (font_distance_abs < rear_distance_abs))
        {
            // decrease speed
            const auto decrease = ego_vehicle.speed_mps * SPEED_ADAPTATION_MPS;

            if (ego_vehicle.speed_mps - decrease < MAX_VEHICLE_SPEED_MPS)
            {
                ego_vehicle.speed_mps -= decrease;
            }
        }
        else if (rear_vehicle_to_close && rear_vehicle_to_close && (rear_distance_abs < font_distance_abs))
        {
            // increase speed
            const auto increase = ego_vehicle.speed_mps * SPEED_ADAPTATION_MPS;

            if (ego_vehicle.speed_mps + increase < MAX_VEHICLE_SPEED_MPS)
            {
                ego_vehicle.speed_mps += increase;
            }
        }
    }
}
