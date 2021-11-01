#include <cstring>
#include <iostream>
#include <numeric>

#include "AdFunctions.hpp"
#include "AdTypes.hpp"

int main()
{
    VehicleType EgoVehicle = {};
    NeighbourVehiclesType Vehicles = {};

    initEgoVehicle(EgoVehicle);
    initVehicles(Vehicles);

    printVehicle(EgoVehicle);
    printNeighborVehicles(Vehicles);

    GapType Gap =
        computeTargetGap(EgoVehicle, Vehicles, LaneAssociationType::LANE_ASSOCIATION_LEFT);
    printGap(Gap);

    printScene(EgoVehicle, Vehicles);

    std::cout << "Compute forward (1sec)?: ";
    char Input;
    std::cin >> Input;

    while (Input == 'y')
    {
        computeFutureState(EgoVehicle, Vehicles, 1);
        printScene(EgoVehicle, Vehicles);

        std::cout << "Compute forward (1sec)?: ";
        std::cin >> Input;
    }


    return 0;
}
