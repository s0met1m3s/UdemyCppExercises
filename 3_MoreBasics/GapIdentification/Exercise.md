# Exercise

Implement the following functions:

```cpp
void init_ego_vehicle(VehicleType &ego_vehicle);

void init_vehicles(NeighborVehiclesType &vehicles);

void print_vehicle(const VehicleType &vehicle);

void print_neighbor_vehicles(const NeighborVehiclesType &vehicles);

bool check_valid_gap(const VehicleType &front_vehicle,
                     const VehicleType &rear_vehicle,
                     const VehicleType &ego_vehicle);

GapType compute_target_gap(const VehicleType &ego_vehicle,
                           const NeighborVehiclesType &vehicles,
                           const LaneAssociationType target_lane);

void print_gap(const GapType &gap);

void print_scene(const VehicleType &ego_vehicle, const NeighborVehiclesType &vehicles);

void compute_future_distance(VehicleType &vehicle,
                             const float ego_driven_distance,
                             const float seconds);

void compute_future_state(const VehicleType &ego_vehicle,
                          NeighborVehiclesType &vehicles,
                          const float seconds);
```

## Main Function

```cpp
int main()
{
    VehicleType ego_vehicle{};
    NeighborVehiclesType vehicles{};

    init_ego_vehicle(ego_vehicle);
    init_vehicles(vehicles);

    print_vehicle(ego_vehicle);
    print_neighbor_vehicles(vehicles);

    GapType gap =
        compute_target_gap(ego_vehicle, vehicles, LaneAssociationType::LANE_ASSOCIATION_LEFT);
    print_gap(gap);

    print_scene(ego_vehicle, vehicles);

    std::cout << "Compute forward (1sec)?: ";
    char Input;
    std::cin >> Input;

    while (Input == 'y')
    {
        compute_future_state(ego_vehicle, vehicles, 1);
        print_scene(ego_vehicle, vehicles);

        std::cout << "Compute forward (1sec)?: ";
        std::cin >> Input;
    }

    return 0;
}
```
