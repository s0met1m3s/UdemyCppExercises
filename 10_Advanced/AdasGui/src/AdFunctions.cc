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
    const float decrease = ego_vehicle.speed_mps * SPEED_ADAPTAION_FACTOR;

    if (ego_vehicle.speed_mps - decrease > 0.0F)
    {
        ego_vehicle.speed_mps -= decrease;
    }
}

const VehicleType *get_vehicle_array(const LaneAssociationType lane, const NeighborVehiclesType &vehicles)
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
    const VehicleType *vehicles_array = get_vehicle_array(ego_vehicle.lane, vehicles);

    if (vehicles_array == nullptr)
    {
        return ego_vehicle.lane;
    }

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
    const float minimal_distance = mps_to_kmh(ego_vehicle.speed_mps) / 5.0F;

    const float front_distance = front_vehicle.distance_m;
    const float rear_distance = std::abs(rear_vehicle.distance_m);

    if ((front_distance > minimal_distance) && (rear_distance > minimal_distance))
    {
        return true;
    }

    return false;
}

bool lateral_control(const NeighborVehiclesType &vehicles,
                     const LaneAssociationType lane_change_request,
                     VehicleType &ego_vehicle)
{
    if (lane_change_request == ego_vehicle.lane)
    {
        return false;
    }

    const VehicleType *vehicles_array = get_vehicle_array(lane_change_request, vehicles);

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
