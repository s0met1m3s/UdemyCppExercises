#include <iostream>

constexpr std::int32_t EGO_VEHICLE_ID = -1;

enum class LaneAssociation
{
    LANE_ASSOCIATION_UNKNOWN,
    LANE_ASSOCIATION_RIGHT,
    LANE_ASSOCIATION_CENTER,
    LANE_ASSOCIATION_LEFT
};

enum class VehicleType
{
    VEHICLE_TYPE_UNKNOWN,
    VEHICLE_TYPE_CAR,
    VEHICLE_TYPE_TRUCK,
    VEHICLE_TYPE_MOTORCYCLE,
};

struct Vehicle
{
    std::int32_t Id;
    LaneAssociation Lane;
    VehicleType Type;
    float SpeedMps;
    float LongitudinalDistanceM;
};

struct NeighbourVehicles
{
    Vehicle VehiclesLeftLane[2];
    Vehicle VehiclesCenterLane[2];
    Vehicle VehiclesRightLane[2];
};

void initEgoVehicle(Vehicle &);

void initVehicles(NeighbourVehicles &);

void printVehicle(const Vehicle &);

void printNeighborVehicles(const NeighbourVehicles &);

int main()
{
    Vehicle EgoVehicle = {};
    NeighbourVehicles Vehicles = {};

    initEgoVehicle(EgoVehicle);
    initVehicles(Vehicles);

    printVehicle(EgoVehicle);
    printNeighborVehicles(Vehicles);

    return 0;
}

void initEgoVehicle(Vehicle &EgoVehicle)
{
    EgoVehicle.Id = -1;
    EgoVehicle.SpeedMps = 135.0F / 3.6F;
    EgoVehicle.LongitudinalDistanceM = 0.0F;
    EgoVehicle.Type = VehicleType::VEHICLE_TYPE_CAR;
    EgoVehicle.Lane = LaneAssociation::LANE_ASSOCIATION_CENTER;
}

void initVehicles(NeighbourVehicles &Vehicles)
{
    Vehicles.VehiclesLeftLane[0].Id = 0;
    Vehicles.VehiclesLeftLane[0].SpeedMps = 130.0F / 3.6F;
    Vehicles.VehiclesLeftLane[0].LongitudinalDistanceM = 80.0F;
    Vehicles.VehiclesLeftLane[0].Type = VehicleType::VEHICLE_TYPE_CAR;
    Vehicles.VehiclesLeftLane[0].Lane = LaneAssociation::LANE_ASSOCIATION_LEFT;

    Vehicles.VehiclesLeftLane[1].Id = 1;
    Vehicles.VehiclesLeftLane[1].SpeedMps = 80.0F / 3.6F;
    Vehicles.VehiclesLeftLane[1].LongitudinalDistanceM = -20.0F;
    Vehicles.VehiclesLeftLane[1].Type = VehicleType::VEHICLE_TYPE_TRUCK;
    Vehicles.VehiclesLeftLane[1].Lane = LaneAssociation::LANE_ASSOCIATION_LEFT;

    Vehicles.VehiclesCenterLane[0].Id = 2;
    Vehicles.VehiclesCenterLane[0].SpeedMps = 120.0F / 3.6F;
    Vehicles.VehiclesCenterLane[0].LongitudinalDistanceM = 50.0F;
    Vehicles.VehiclesCenterLane[0].Type = VehicleType::VEHICLE_TYPE_CAR;
    Vehicles.VehiclesCenterLane[0].Lane = LaneAssociation::LANE_ASSOCIATION_CENTER;

    Vehicles.VehiclesCenterLane[1].Id = 3;
    Vehicles.VehiclesCenterLane[1].SpeedMps = 110.0F / 3.6F;
    Vehicles.VehiclesCenterLane[1].LongitudinalDistanceM = 50.0F;
    Vehicles.VehiclesCenterLane[1].Type = VehicleType::VEHICLE_TYPE_CAR;
    Vehicles.VehiclesCenterLane[1].Lane = LaneAssociation::LANE_ASSOCIATION_CENTER;

    Vehicles.VehiclesRightLane[0].Id = 4;
    Vehicles.VehiclesRightLane[0].SpeedMps = 90.0F / 3.6F;
    Vehicles.VehiclesRightLane[0].LongitudinalDistanceM = 30.0F;
    Vehicles.VehiclesRightLane[0].Type = VehicleType::VEHICLE_TYPE_MOTORCYCLE;
    Vehicles.VehiclesRightLane[0].Lane = LaneAssociation::LANE_ASSOCIATION_RIGHT;


    Vehicles.VehiclesRightLane[1].Id = 5;
    Vehicles.VehiclesRightLane[1].SpeedMps = 130.0F / 3.6F;
    Vehicles.VehiclesRightLane[1].LongitudinalDistanceM = 30.0F;
    Vehicles.VehiclesRightLane[1].Type = VehicleType::VEHICLE_TYPE_CAR;
    Vehicles.VehiclesRightLane[1].Lane = LaneAssociation::LANE_ASSOCIATION_RIGHT;
}

void printVehicle(const Vehicle &Veh)
{
    if (EGO_VEHICLE_ID == Veh.Id)
    {
        std::cout << "ID: Ego Vehicle" << std::endl;
        std::cout << "Speed (m/s): " << Veh.SpeedMps << std::endl << std::endl;
    }
    else
    {
        std::cout << "ID: " << Veh.Id << std::endl;
        std::cout << "Speed (m/s): " << Veh.SpeedMps << std::endl;
        std::cout << "Distance: " << Veh.LongitudinalDistanceM << std::endl << std::endl;
    }
}

void printNeighborVehicles(const NeighbourVehicles &Vehicles)
{
    for (std::size_t i = 0; i < 2; i++)
    {
        printVehicle(Vehicles.VehiclesLeftLane[i]);
    }

    for (std::size_t i = 0; i < 2; i++)
    {
        printVehicle(Vehicles.VehiclesCenterLane[i]);
    }

    for (std::size_t i = 0; i < 2; i++)
    {
        printVehicle(Vehicles.VehiclesRightLane[i]);
    }
}
