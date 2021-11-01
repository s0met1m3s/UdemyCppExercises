#include <iostream>

#include "AdConstants.hpp"
#include "AdFunctions.hpp"
#include "AdTypes.hpp"

void initEgoVehicle(VehicleType &EgoVehicle)
{
    EgoVehicle.Id = -1;
    EgoVehicle.SpeedMps = 135.0F / 3.6F;
    EgoVehicle.LongitudinalDistanceM = 0.0F;
    EgoVehicle.Lane = LaneAssociationType::LANE_ASSOCIATION_CENTER;
}

void initVehicles(NeighbourVehiclesType &Vehicles)
{
    Vehicles.VehiclesLeftLane[0].Id = 0;
    Vehicles.VehiclesLeftLane[0].SpeedMps = 130.0F / 3.6F;
    Vehicles.VehiclesLeftLane[0].LongitudinalDistanceM = 80.0F;
    Vehicles.VehiclesLeftLane[0].Lane = LaneAssociationType::LANE_ASSOCIATION_LEFT;

    Vehicles.VehiclesLeftLane[1].Id = 1;
    Vehicles.VehiclesLeftLane[1].SpeedMps = 80.0F / 3.6F;
    Vehicles.VehiclesLeftLane[1].LongitudinalDistanceM = -20.0F;
    Vehicles.VehiclesLeftLane[1].Lane = LaneAssociationType::LANE_ASSOCIATION_LEFT;

    Vehicles.VehiclesCenterLane[0].Id = 2;
    Vehicles.VehiclesCenterLane[0].SpeedMps = 120.0F / 3.6F;
    Vehicles.VehiclesCenterLane[0].LongitudinalDistanceM = 50.0F;
    Vehicles.VehiclesCenterLane[0].Lane = LaneAssociationType::LANE_ASSOCIATION_CENTER;

    Vehicles.VehiclesCenterLane[1].Id = 3;
    Vehicles.VehiclesCenterLane[1].SpeedMps = 110.0F / 3.6F;
    Vehicles.VehiclesCenterLane[1].LongitudinalDistanceM = -50.0F;
    Vehicles.VehiclesCenterLane[1].Lane = LaneAssociationType::LANE_ASSOCIATION_CENTER;

    Vehicles.VehiclesRightLane[0].Id = 4;
    Vehicles.VehiclesRightLane[0].SpeedMps = 90.0F / 3.6F;
    Vehicles.VehiclesRightLane[0].LongitudinalDistanceM = 30.0F;
    Vehicles.VehiclesRightLane[0].Lane = LaneAssociationType::LANE_ASSOCIATION_RIGHT;


    Vehicles.VehiclesRightLane[1].Id = 5;
    Vehicles.VehiclesRightLane[1].SpeedMps = 130.0F / 3.6F;
    Vehicles.VehiclesRightLane[1].LongitudinalDistanceM = -30.0F;
    Vehicles.VehiclesRightLane[1].Lane = LaneAssociationType::LANE_ASSOCIATION_RIGHT;
}

void printVehicle(const VehicleType &Veh)
{
    if (EGO_VEHICLE_ID == Veh.Id)
    {
        std::cout << "ID: Ego VehicleType" << std::endl;
        std::cout << "Speed (m/s): " << Veh.SpeedMps << std::endl << std::endl;
    }
    else
    {
        std::cout << "ID: " << Veh.Id << std::endl;
        std::cout << "Speed (m/s): " << Veh.SpeedMps << std::endl;
        std::cout << "Distance: " << Veh.LongitudinalDistanceM << std::endl << std::endl;
    }
}

void printNeighborVehicles(const NeighbourVehiclesType &Vehicles)
{
    for (std::size_t i = 0; i < NUM_VEHICLES_ON_LANE; i++)
    {
        printVehicle(Vehicles.VehiclesLeftLane[i]);
    }

    for (std::size_t i = 0; i < NUM_VEHICLES_ON_LANE; i++)
    {
        printVehicle(Vehicles.VehiclesCenterLane[i]);
    }

    for (std::size_t i = 0; i < NUM_VEHICLES_ON_LANE; i++)
    {
        printVehicle(Vehicles.VehiclesRightLane[i]);
    }
}

bool checkValidGap(const VehicleType &FrontVehicle,
                   const VehicleType &RearVehicle,
                   const VehicleType &EgoVehicle)
{
    const float EgoSpeedKmh = EgoVehicle.SpeedMps * 3.6;
    const float MinDistanceM = EgoSpeedKmh / 2.0;
    const bool DistanceToFrontValid =
        std::abs(FrontVehicle.LongitudinalDistanceM) > MinDistanceM ? true : false;
    const bool DistanceToRearValid =
        std::abs(RearVehicle.LongitudinalDistanceM) > MinDistanceM ? true : false;

    return DistanceToFrontValid && DistanceToRearValid;
}

GapType computeTargetGap(const VehicleType &EgoVehicle,
                         const NeighbourVehiclesType &Vehicles,
                         const LaneAssociationType TargetLane)
{
    GapType Gap = {};

    switch (TargetLane)
    {
    case LaneAssociationType::LANE_ASSOCIATION_LEFT:
    {
        const VehicleType &FrontVehicle = Vehicles.VehiclesLeftLane[0];
        const VehicleType &RearVehicle = Vehicles.VehiclesLeftLane[1];
        const float GapLengthM =
            FrontVehicle.LongitudinalDistanceM - RearVehicle.LongitudinalDistanceM;


        Gap.LengthM = GapLengthM;
        Gap.ValidFlag = checkValidGap(FrontVehicle, RearVehicle, EgoVehicle);
        Gap.Lane = LaneAssociationType::LANE_ASSOCIATION_LEFT;
        break;
    }
    case LaneAssociationType::LANE_ASSOCIATION_RIGHT:
    {
        const VehicleType &FrontVehicle = Vehicles.VehiclesRightLane[0];
        const VehicleType &RearVehicle = Vehicles.VehiclesRightLane[1];
        float GapLengthM = FrontVehicle.LongitudinalDistanceM - RearVehicle.LongitudinalDistanceM;

        Gap.LengthM = GapLengthM;
        Gap.ValidFlag = checkValidGap(FrontVehicle, RearVehicle, EgoVehicle);
        Gap.Lane = LaneAssociationType::LANE_ASSOCIATION_RIGHT;
        break;
    }
    case LaneAssociationType::LANE_ASSOCIATION_UNKNOWN:
    case LaneAssociationType::LANE_ASSOCIATION_CENTER:
    default:
    {
        break;
    }
    }

    return Gap;
}

void printGap(const GapType &Gap)
{
    std::cout << "Lane: " << static_cast<std::int32_t>(Gap.Lane) << std::endl;
    std::cout << "LengthM: " << Gap.LengthM << std::endl;
    std::cout << "ValidFlag: " << Gap.ValidFlag << std::endl << std::endl;
}

void printScene(const VehicleType &EgoVehicle, const NeighbourVehiclesType &Vehicles)
{
    std::cout << "    \t   L    C    R  \n";

    std::size_t LeftIdx = 0;
    std::size_t CenterIdx = 0;
    std::size_t RightIdx = 0;

    const std::int32_t Offset = 20;

    for (std::int32_t i = 100; i >= -100; i -= Offset)
    {
        const VehicleType &LeftVehicle = Vehicles.VehiclesLeftLane[LeftIdx];
        const VehicleType &CenterVehicle = Vehicles.VehiclesCenterLane[CenterIdx];
        const VehicleType &RightVehicle = Vehicles.VehiclesRightLane[RightIdx];

        char LeftString[] = "   ";
        char CenterString[] = "   ";
        char RightString[] = "   ";

        if ((i >= LeftVehicle.LongitudinalDistanceM) &&
            (LeftVehicle.LongitudinalDistanceM > (i - Offset)))
        {
            std::strncpy(LeftString, " V ", 4);
            LeftIdx++;
        }

        if ((i >= CenterVehicle.LongitudinalDistanceM) &&
            (CenterVehicle.LongitudinalDistanceM > (i - Offset)))
        {
            std::strncpy(CenterString, " V ", 4);
            CenterIdx++;
        }
        else if ((i >= EgoVehicle.LongitudinalDistanceM) &&
                 (EgoVehicle.LongitudinalDistanceM > (i - Offset)))
        {
            std::strncpy(CenterString, " E ", 4);
        }

        if ((i >= RightVehicle.LongitudinalDistanceM) &&
            (RightVehicle.LongitudinalDistanceM > (i - Offset)))
        {
            std::strncpy(RightString, " V ", 4);
            RightIdx++;
        }

        std::cout << i << "\t| " << LeftString << " |" << CenterString << " |" << RightString
                  << " |\n";
    }

    std::cout << std::endl;
}

void computeFutureDistance(VehicleType &Vehicle,
                           const float EgoDrivenDistance,
                           const std::uint32_t Seconds)
{
    const float FrontLeftDrivenDistance = Vehicle.SpeedMps * Seconds;
    Vehicle.LongitudinalDistanceM += FrontLeftDrivenDistance - EgoDrivenDistance;
}

void computeFutureState(const VehicleType &EgoVehicle,
                        NeighbourVehiclesType &Vehicles,
                        const std::uint32_t Seconds)
{
    const float EgoDrivenDistance = EgoVehicle.SpeedMps * Seconds;

    computeFutureDistance(Vehicles.VehiclesLeftLane[0], EgoDrivenDistance, Seconds);
    computeFutureDistance(Vehicles.VehiclesLeftLane[1], EgoDrivenDistance, Seconds);

    computeFutureDistance(Vehicles.VehiclesCenterLane[0], EgoDrivenDistance, Seconds);
    computeFutureDistance(Vehicles.VehiclesCenterLane[1], EgoDrivenDistance, Seconds);

    computeFutureDistance(Vehicles.VehiclesRightLane[0], EgoDrivenDistance, Seconds);
    computeFutureDistance(Vehicles.VehiclesRightLane[1], EgoDrivenDistance, Seconds);
}
