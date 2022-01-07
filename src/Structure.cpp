#include <vector>
#include <memory>
#include <math.h>
#include <iostream>

#include <Structure.hpp>

Bound::Bound(double stiffness, PhysVertex& vert1, PhysVertex& vert2) : k(stiffness), vert1(vert1), vert2(vert2) {
    length = (vert1.pos - vert2.pos).norm3d();
}

double Bound::forceMagnitude(){
    double current_length = (vert1.pos - vert2.pos).norm3d();

    double velocity_projection = (vert1.pos - vert2.pos).scalar_prod(vert1.vel - vert2.vel);

    return -k*(length - current_length) + 10.0*velocity_projection;

}


Structure::Structure() {
    // vertices initialization
    vertices.emplace_back(PhysVertex(1,-0.5,-0.5,-0.5));
    vertices.emplace_back(PhysVertex(1, 0.5,-0.5,-0.5));
    vertices.emplace_back(PhysVertex(1, 0.5,-0.5, 0.5));
    vertices.emplace_back(PhysVertex(1,-0.5,-0.5, 0.5));
    vertices.emplace_back(PhysVertex(1,-0.5, 0.5,-0.5));
    vertices.emplace_back(PhysVertex(1, 0.5, 0.5,-0.5));
    vertices.emplace_back(PhysVertex(1, 0.5, 0.5, 0.5));
    vertices.emplace_back(PhysVertex(1,-0.5, 0.5, 0.5));

    // bounds initializtion
    bounds.emplace_back(Bound(500, vertices[0], vertices[1]));
    bounds.emplace_back(Bound(500, vertices[0], vertices[3]));
    bounds.emplace_back(Bound(500, vertices[0], vertices[4]));
    bounds.emplace_back(Bound(500, vertices[0], vertices[6]));

    bounds.emplace_back(Bound(500, vertices[1], vertices[2]));
    bounds.emplace_back(Bound(500, vertices[1], vertices[5]));
    bounds.emplace_back(Bound(500, vertices[1], vertices[7]));

    bounds.emplace_back(Bound(500, vertices[2], vertices[3]));
    bounds.emplace_back(Bound(500, vertices[2], vertices[6]));
    bounds.emplace_back(Bound(500, vertices[2], vertices[4]));

    bounds.emplace_back(Bound(500, vertices[3], vertices[7]));
    bounds.emplace_back(Bound(500, vertices[3], vertices[5]));

    bounds.emplace_back(Bound(500, vertices[4], vertices[7]));
    bounds.emplace_back(Bound(500, vertices[4], vertices[5]));

    bounds.emplace_back(Bound(500, vertices[5], vertices[6]));

    bounds.emplace_back(Bound(500, vertices[6], vertices[7]));

};

void Structure::evalForces(double gravity){
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

void Structure::stepForward(double dt){
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

void Structure::getPositions(float* pos_array){
    for (int i = 0; i < vertices.size(); i++){
        pos_array[3*i] = vertices[i].pos[0];
        pos_array[3*i+1] = vertices[i].pos[1];
        pos_array[3*i+2] = vertices[i].pos[2];
    }
}
