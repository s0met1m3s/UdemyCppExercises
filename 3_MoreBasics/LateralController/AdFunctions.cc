#include <iostream>

#include "AdConstants.hpp"
#include "AdFunctions.hpp"
#include "AdTypes.hpp"

float kph_to_mps(const float kph)
{
    return kph / 3.6F;
}

float mps_to_kmh(const float mps)
{
    return mps * 3.6F;
}

void init_ego_vehicle(VehicleType &ego_vehicle)
{
    ego_vehicle.id = EGO_VEHICLE_ID;
    ego_vehicle.speed_mps = kph_to_mps(135.0F);
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
    init_vehicle(vehicles.vehicles_left_lane[1], 1, 80.0F, -20.0F, LaneAssociationType::LEFT);
    init_vehicle(vehicles.vehicles_center_lane[0], 2, 80.0F, 50.0F, LaneAssociationType::CENTER);
    init_vehicle(vehicles.vehicles_center_lane[1], 3, 120.0F, -50.0F, LaneAssociationType::CENTER);
    init_vehicle(vehicles.vehicles_right_lane[0], 4, 110.0F, 30.0F, LaneAssociationType::RIGHT);
    init_vehicle(vehicles.vehicles_right_lane[1], 5, 90.0F, -30.0F, LaneAssociationType::RIGHT);
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
        char *ego_string = nullptr;

        const float range_m = static_cast<float>(i);

        switch (ego_vehicle.lane)
        {
        case LaneAssociationType::LEFT:
        {
            ego_string = left_string;
            break;
        }
        case LaneAssociationType::CENTER:
        {
            ego_string = center_string;
            break;
        }
        case LaneAssociationType::RIGHT:
        {
            ego_string = right_string;
            break;
        }
        default:
        {
            break;
        }
        }

        if ((ego_string != nullptr) && (range_m >= ego_vehicle.distance_m) &&
            (ego_vehicle.distance_m > (range_m - offset_m)))
        {
            ego_string[1] = 'E';
        }

        if ((range_m >= left_vehicle.distance_m) && (left_vehicle.distance_m > (range_m - offset_m)))
        {
            left_string[1] = 'V';
            left_idx++;
        }

        if ((range_m >= center_vehicle.distance_m) && (center_vehicle.distance_m > (range_m - offset_m)))
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
    std::cout << "\n";
}

void print_vehicle_speed(const VehicleType &vehicle, const char *name)
{
    std::cout.precision(3);
    std::cout << name << ": (" << vehicle.speed_mps << " mps)";
}

void compute_future_distance(VehicleType &vehicle, const float ego_driven_distance, const float seconds)
{
    const float driven_distance = vehicle.speed_mps * seconds;
    vehicle.distance_m += driven_distance - ego_driven_distance;
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

void decrease_speed(VehicleType &ego_vehicle)
{
    const float decrease = ego_vehicle.speed_mps * SPEED_ADAPTATION_FACTOR;

    if (ego_vehicle.speed_mps - decrease > 0.0F)
    {
        ego_vehicle.speed_mps -= decrease;
    }
}

const VehicleType *get_lane_vehicles(const LaneAssociationType lane, const NeighborVehiclesType &vehicles)
{
    const VehicleType *vehicles_array = nullptr;

    switch (lane)
    {
    case LaneAssociationType::LEFT:
    {
        vehicles_array = vehicles.vehicles_left_lane;
        break;
    }
    case LaneAssociationType::CENTER:
    {
        vehicles_array = vehicles.vehicles_center_lane;
        break;
    }
    case LaneAssociationType::RIGHT:
    {
        vehicles_array = vehicles.vehicles_right_lane;
        break;
    }
    default:
    {
        break;
    }
    }

    return vehicles_array;
}

LaneAssociationType longitudinal_control(const NeighborVehiclesType &vehicles, VehicleType &ego_vehicle)
{
    const VehicleType *vehicles_array = get_lane_vehicles(ego_vehicle.lane, vehicles);

    const VehicleType &front_vehicle = vehicles_array[0];
    const VehicleType &rear_vehicle = vehicles_array[1];

    const float minimal_distance = mps_to_kmh(ego_vehicle.speed_mps) / 2.0F;
    const float crash_distance = mps_to_kmh(ego_vehicle.speed_mps) / 4.0F;

    const float front_distance = front_vehicle.distance_m;
    const float rear_distance = std::abs(rear_vehicle.distance_m);

    bool front_vehicle_too_close = false;

    bool front_vehicle_very_close = false;
    bool rear_vehicle_very_close = false;

    if (front_distance < minimal_distance)
    {
        front_vehicle_too_close = true;
    }

    if (front_distance < crash_distance)
    {
        front_vehicle_very_close = true;
    }

    if (rear_distance < crash_distance)
    {
        rear_vehicle_very_close = true;
    }

    if (front_vehicle_too_close)
    {
        decrease_speed(ego_vehicle);
    }

    if (front_vehicle_very_close || rear_vehicle_very_close)
    {
        return get_lane_change_request(ego_vehicle, front_distance, rear_distance);
    }

    return ego_vehicle.lane;
}

LaneAssociationType get_lane_change_request(const VehicleType &ego_vehicle,
                                            const float front_distance,
                                            const float rear_distance)
{
    const bool left_lane_change = (front_distance < rear_distance);

    if (left_lane_change)
    {
        switch (ego_vehicle.lane)
        {
        case LaneAssociationType::LEFT:
        {
            return ego_vehicle.lane;
            break;
        }
        case LaneAssociationType::CENTER:
        {
            return LaneAssociationType::LEFT;
            break;
        }
        case LaneAssociationType::RIGHT:
        {
            return LaneAssociationType::CENTER;
            break;
        }
        default:
        {
            return ego_vehicle.lane;
            break;
        }
        }
    }
    else
    {
        switch (ego_vehicle.lane)
        {
        case LaneAssociationType::LEFT:
        {
            return LaneAssociationType::CENTER;
            break;
        }
        case LaneAssociationType::CENTER:
        {
            return LaneAssociationType::RIGHT;
            break;
        }
        case LaneAssociationType::RIGHT:
        {
            return ego_vehicle.lane;
            break;
        }
        default:
        {
            return ego_vehicle.lane;
            break;
        }
        }
    }
}

bool gap_is_valid(const VehicleType &front_vehicle, const VehicleType &rear_vehicle, const VehicleType &ego_vehicle)
{
    const float front_distance = front_vehicle.distance_m;
    const float rear_distance = std::abs(rear_vehicle.distance_m);
    const float minimal_distance = mps_to_kmh(ego_vehicle.speed_mps) / 3.0F;

    if (front_distance > minimal_distance && rear_distance > minimal_distance)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool lateral_control(const NeighborVehiclesType &vehicles,
                     const LaneAssociationType lane_change_request,
                     VehicleType &ego_vehicle)
{
    if (lane_change_request == ego_vehicle.lane)
    {
        return false;
    }

    const VehicleType *vehicles_array = get_lane_vehicles(ego_vehicle.lane, vehicles);

    if (vehicles_array == nullptr)
    {
        return false;
    }

    const bool valid = gap_is_valid(vehicles_array[0], vehicles_array[1], ego_vehicle);

    if (valid)
    {
        ego_vehicle.lane = lane_change_request;

        return true;
    }

    return false;
}
