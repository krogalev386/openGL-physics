#include <vector>
#include <memory>
#include <math.h>
#include <iostream>

#include <Structure.hpp>

Bound::Bound(double stiffness, PhysVertex& vert1, PhysVertex& vert2) : k(stiffness), vert1(vert1), vert2(vert2)
{
    length = (vert1.pos - vert2.pos).norm3d();
}

double Bound::forceMagnitude()
{
    double current_length = (vert1.pos - vert2.pos).norm3d();

    double velocity_projection = (vert1.pos - vert2.pos).scalar_prod(vert1.vel - vert2.vel);

    return -k*(length - current_length) + 40.0*velocity_projection;
}


Structure::Structure()
{}

std::vector<uint> Structure::getIndices()
{
    return vertex_indices;
}

void Structure::evalForces(double gravity)
{
    for (auto& vertex : vertices){
        vertex.force[0] = 0;
        vertex.force[1] = 0;
        vertex.force[2] = gravity*vertex.mass;
        //std::cout << "CHECK:" << &vertex << " " << vertex.mass << " " << vertex.fx << " " << vertex.fy << " " << vertex.fz << std::endl;
    }
    for (auto& bound : bounds){
        PhysVertex& vert1 = bound.vert1;
        PhysVertex& vert2 = bound.vert2;

        double x, y, z; // direction unit vector from second vertex to first one
        vect3d_d direction = vert2.pos - vert1.pos;
        direction = direction/direction.norm3d();

        double forceMagn = bound.forceMagnitude();
        vert1.force += direction*forceMagn;
        vert2.force -= direction*forceMagn;
    }
};

void Structure::stepForward(double dt)
{
    for (auto& vert : vertices){
        bool shouldMove = (vert.surface == nullptr);
        if (vert.surface){
            double result = vert.surface->normal_vect.scalar_prod(vert.vel);
            shouldMove = result > 0;
        }

        vert.pos += vert.vel*dt;
        vert.vel += vert.force*(dt/vert.mass);

        if (!shouldMove){
            vert.vel = -vert.vel;
        }
    }
};

std::vector<float> Structure::getPositions()
{
    std::vector<float> pos_array(3*vertices.size());
    for (int i = 0; i < vertices.size(); i++){
        pos_array[3*i] = vertices[i].pos[0];
        pos_array[3*i+1] = vertices[i].pos[1];
        pos_array[3*i+2] = vertices[i].pos[2];
    }
    return pos_array;
}
