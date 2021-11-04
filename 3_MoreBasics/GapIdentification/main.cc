#include <cstring>
#include <iostream>
#include <numeric>

#include "AdFunctions.hpp"
#include "AdTypes.hpp"

int main()
{
    VehicleType ego_vehicle{};
    NeighborVehiclesType Vehicles{};

    initego_vehicle(ego_vehicle);
    initVehicles(Vehicles);

    printVehicle(ego_vehicle);
    printneighbor_vehicles(Vehicles);

    GapType Gap =
        computetarget_gap(ego_vehicle, Vehicles, LaneAssociationType::LANE_ASSOCIATION_LEFT);
    printGap(Gap);

    printScene(ego_vehicle, Vehicles);

    std::cout << "Compute forward (1sec)?: ";
    char Input;
    std::cin >> Input;

    while (Input == 'y')
    {
        computefuture_state(ego_vehicle, Vehicles, 1);
        printScene(ego_vehicle, Vehicles);

        std::cout << "Compute forward (1sec)?: ";
        std::cin >> Input;
    }


    return 0;
}
