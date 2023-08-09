#pragma once
#include <Structure.hpp>

class Cuboid : public Structure
{
public:
    Cuboid();
    Cuboid(vect3d_d center_pos, double mass, double stiffness, double length, double width, double height, uint n, uint m, uint p);
};
