#pragma once
#include <memory>
#include <Structure.hpp>

template <class T>
using ptr_vec = std::vector<std::shared_ptr<T>>;

class PhysicsHandler {
    

    PhysicsHandler() = default;
    PhysicsHandler(PhysicsHandler&) = delete;
    PhysicsHandler operator=(PhysicsHandler&) = delete;

    ptr_vec<Structure> structures;
    ptr_vec<Surface> surfaces;
    double gravity;

public:

    static PhysicsHandler& getInstance(){
        static PhysicsHandler object;
        return object;
    };

    void setEnviroment(ptr_vec<Structure>&, ptr_vec<Surface>&, double);

    void makeTimeStep(double);
    void findContacts();
    void bound(std::shared_ptr<Surface>, PhysVertex&);
    void unbound(PhysVertex&);
};