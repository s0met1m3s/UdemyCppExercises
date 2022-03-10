# Exercises

## Example

![Example](./media/Lanes.gif)

### Intro

The previously called *speed_mps* is now called *velocity_mps*.  
Speed is just the rate of change of distance for a certain amount of time.  
Velocity is the same but in addation it can be seen as a vector.

The following vehicle properties are added:

- Lateral velocity ($\frac{m}{s}$)
- Longitudinal velocity ($\frac{m}{s}$)
- Heading degree ($\in [-180, 180]$)
- Acceleration ($\frac{m}{s^2}$)

From the data, or so to say from out "radars" and "cameras", we will only recieve the lat. and long velcoity.  
Hence, we have to compute the acceleration (direction independent) and the acceleration by hand.

To compute the velocity we can use the lateral and long. velcotiy:  
$v = \sqrt{v_{long}^2 + v_{lat}^2}$

To compute the heading degree we can use the following formula:  
$d = \frac{\arctan2(v_{long}, v_{lat})}{\pi} * 360$

Here is a small introduction to the vehicle heading: [link](http://street.umn.edu/VehControl/javahelp/HTML/Definition_of_Vehicle_Heading_and_Steeing_Angle.htm)  
I also created a small python script to compute some heading values on your own.

This is the new vehicle struct:

```cpp
struct VehicleInformationType
{
    std::int32_t id;
    float width;
    float height;

    LaneAssociationType lane;
    ObjectClassType object_class;

    float long_velocity_mps;
    float lat_velocity_mps;
    float velocity_mps;
    float acceleration_mps2;

    float heading_deg;

    float long_distance_m;
    float lat_distance_m;
};
```

### Exercise 1

Update the data loader code:

- Compute the
  - Velocity
  - Heading degree
  - Acceleration
