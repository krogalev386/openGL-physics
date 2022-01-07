#include <vector>
#include <memory>
#include <math.h>
#include <iostream>

#include <Structure.hpp>

inline double norm3d(double x, double y, double z){
    return sqrt(x*x + y*y + z*z);
}

Bound::Bound(double stiffness, PhysVertex& vert1, PhysVertex& vert2) : k(stiffness), vert1(vert1), vert2(vert2) {
    length = norm3d((vert1.x - vert2.x),(vert1.y - vert2.y),(vert1.z - vert2.z));
}

double Bound::forceMagnitude(){
    double current_length = norm3d((vert1.x - vert2.x),(vert1.y - vert2.y),(vert1.z - vert2.z));

    double velocity_projection = (vert1.vx - vert2.vx)*(vert1.x - vert2.x)
                               + (vert1.vy - vert2.vy)*(vert1.y - vert2.y)
                               + (vert1.vz - vert2.vz)*(vert1.z - vert2.z);

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
        vertex.fx = 0;
        vertex.fy = 0;
        vertex.fz = gravity*vertex.mass;
        //std::cout << "CHECK:" << &vertex << " " << vertex.mass << " " << vertex.fx << " " << vertex.fy << " " << vertex.fz << std::endl;
    }
    for (auto& bound : bounds){
        PhysVertex& vert1 = bound.vert1;
        PhysVertex& vert2 = bound.vert2;

        double x, y, z; // direction unit vector from second vertex to first one
        x = (vert2.x - vert1.x);
        y = (vert2.y - vert1.y);
        z = (vert2.z - vert1.z);

        double norm = norm3d(x,y,z);
        x = x/norm; y = y/norm; z = z/norm;

        double forceMagn = bound.forceMagnitude();
        vert1.fx += x*forceMagn;
        vert1.fy += y*forceMagn;
        vert1.fz += z*forceMagn;
        vert2.fx -= x*forceMagn;
        vert2.fy -= y*forceMagn;
        vert2.fz -= z*forceMagn;
        //std::cout << vert2.mass << " " << &vert2 << " " << vert2.fx << " " << vert2.fy << " " << vert2.fz << std::endl;
    }
};

void Structure::stepForward(double dt){
    for (auto& vert : vertices){
        bool shouldMove = (vert.surface == nullptr);
        if (vert.surface){
            vect3d_d vertex_vel(vert.vx, vert.vy, vert.vz);
            double result = vert.surface->normal_vect.scalar_prod(vertex_vel);
            shouldMove = result > 0;
        }
        vert.x += vert.vx*dt;
        vert.y += vert.vy*dt;
        vert.z += vert.vz*dt;

        vert.vx += vert.fx*dt/vert.mass;
        vert.vy += vert.fy*dt/vert.mass;
        vert.vz += vert.fz*dt/vert.mass;
        if (!shouldMove){
            vert.vx = -vert.vx;
            vert.vy = -vert.vy;
            vert.vz = -vert.vz;
        }
        //std::cout << "STEPFORWARD:" << vert.x << " " << vert.y << " " << vert.z << std::endl;
    }
};

void Structure::getPositions(float* pos_array){
    for (int i = 0; i < vertices.size(); i++){
        pos_array[3*i] = vertices[i].x;
        pos_array[3*i+1] = vertices[i].y;
        pos_array[3*i+2] = vertices[i].z;
    }
}
