#include <vector>
#include <memory>
#include <math.h>
#include <vect3d.hpp>

struct Surface {
    Surface(double a, double b, double c, double d) : normal_vect(a, b, c), d(d) {};
    vect3d_d normal_vect;
    double d; // plane equation a*x + b*y + c*z + d = 0, or (r,N) + d = 0 where N = (a, b, c) - normal vector
};

struct PhysVertex {
    PhysVertex(double mass, double x, double y, double z) : mass(mass), pos(x, y, z) {};
    double mass;
    vect3d_d pos;
    vect3d_d vel;
    vect3d_d force;
    std::shared_ptr<Surface> surface;
};

struct Bound {
    Bound(double stiffness, PhysVertex& vert1, PhysVertex& vert2);
    double forceMagnitude();
    double k;
    double length;
    PhysVertex &vert1, &vert2;
};

class Structure {

    std::vector<PhysVertex> vertices;
    std::vector<Bound> bounds;

public:

    Structure();
    void getPositions(float*);
    void evalForces(double);
    void stepForward(double);
    std::vector<PhysVertex>& getVertices() { return vertices; };
};