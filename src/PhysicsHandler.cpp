#include <PhysicsHandler.hpp>
#include <iostream>

void PhysicsHandler::setEnviroment(ptr_vec<Structure>& structures,
                                   ptr_vec<Surface>&   surfaces,
                                   double              gravity){
    this->structures = structures;
    this->surfaces   = surfaces;
    this->gravity    = gravity;
};

void PhysicsHandler::bound(std::shared_ptr<Surface> surface, PhysVertex& vertex){
    vertex.surface = surface;
};

void PhysicsHandler::unbound(PhysVertex& vertex){
    vertex.surface = nullptr;
};

void PhysicsHandler::makeTimeStep(double dt){
    
    findContacts();

    for (auto structure : structures){
        structure->evalForces(gravity);
        structure->stepForward(dt);
    }
}


void PhysicsHandler::findContacts(){
    for (auto& surface : surfaces)
        for (auto& structure : structures)
            for (auto& vertex : structure->getVertices()){
                double height = surface->a * vertex.x + 
                                surface->b * vertex.y +
                                surface->c * vertex.z +
                                surface->d;
                double orientation = surface->a * vertex.vx +
                                     surface->b * vertex.vy +
                                     surface->c * vertex.vz;
                //std::cout << surface->a << " " << surface->b << " " << surface->c << " " << surface->d << std::endl;
                //std::cout << height << std::endl;
                if ((height < 0) and (orientation < 0)) {
                    bound(surface, vertex);
                } else {
                    unbound(vertex);
                }
            }
}