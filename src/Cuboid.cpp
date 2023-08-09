#include <vector>
#include <Structure.hpp>

#include <Cuboid.hpp>


Cuboid::Cuboid()
{
    // vertices initialization
    vertices.emplace_back(PhysVertex(0.1,-0.5,-0.5,-0.5));
    vertices.emplace_back(PhysVertex(0.1, 0.5,-0.5,-0.5));
    vertices.emplace_back(PhysVertex(0.1, 0.5,-0.5, 0.5));
    vertices.emplace_back(PhysVertex(0.1,-0.5,-0.5, 0.5));
    vertices.emplace_back(PhysVertex(0.1,-0.5, 0.5,-0.5));
    vertices.emplace_back(PhysVertex(0.1, 0.5, 0.5,-0.5));
    vertices.emplace_back(PhysVertex(0.1, 0.5, 0.5, 0.5));
    vertices.emplace_back(PhysVertex(0.1,-0.5, 0.5, 0.5));

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

    // vertex indices assignment

    vertex_indices = {
        0,1,2,  // 1  triangle
        1,2,3,  // 2  triangle
        4,5,6,  // 3  triangle
        5,6,7,  // 4  triangle
        0,1,4,  // 5  triangle
        1,4,5,  // 6  triangle
        2,3,6,  // 7  triangle
        3,6,7,  // 8  triangle
        0,3,4,  // 9  triangle
        3,4,7,  // 10 triangle
        1,2,5,  // 11 triangle
        2,5,6   // 12 triangle
    };
}

Cuboid::Cuboid(vect3d_d center_pos, double mass, double stiffness, double length, double width, double height, uint n, uint m, uint p)
{
    auto ind_map = [&](uint i, uint j, uint k)
    {
        return (k*(m+1)*(n+1) + j*(n+1) + i);
    };

    double delta_x = length / n;
    double delta_y = width / m;
    double delta_z = height / p;

    // vertices initialization
    for (uint k = 0; k < p+1; k++)
        for (uint j = 0; j < m+1; j++)
            for (uint i = 0; i < n+1; i++)
                vertices.emplace_back(PhysVertex(mass,delta_x*i,delta_y*j,delta_y*k));

    // bounds initializtion
    for (uint i = 1; i < n+1; i++)
        for (uint j = 1; j < m+1; j++)
            for (uint k = 1; k < p+1; k++)
            {
                // along x axis:
                bounds.emplace_back(Bound(stiffness, vertices[ind_map(i-1,j  ,k  )], vertices[ind_map(i  ,j  ,k  )]));
                bounds.emplace_back(Bound(stiffness, vertices[ind_map(i-1,j-1,k-1)], vertices[ind_map(i  ,j-1,k-1)]));
                bounds.emplace_back(Bound(stiffness, vertices[ind_map(i-1,j  ,k-1)], vertices[ind_map(i  ,j  ,k-1)]));
                bounds.emplace_back(Bound(stiffness, vertices[ind_map(i-1,j-1,k  )], vertices[ind_map(i  ,j-1,k  )]));

                // along y axis:
                bounds.emplace_back(Bound(stiffness, vertices[ind_map(i  ,j-1,k  )], vertices[ind_map(i  ,j  ,k  )]));
                bounds.emplace_back(Bound(stiffness, vertices[ind_map(i  ,j-1,k-1)], vertices[ind_map(i  ,j  ,k-1)]));
                bounds.emplace_back(Bound(stiffness, vertices[ind_map(i-1,j-1,k  )], vertices[ind_map(i-1,j  ,k  )]));
                bounds.emplace_back(Bound(stiffness, vertices[ind_map(i-1,j-1,k-1)], vertices[ind_map(i-1,j  ,k-1)]));

                // along y axis:
                bounds.emplace_back(Bound(stiffness, vertices[ind_map(i  ,j  ,k  )], vertices[ind_map(i  ,j  ,k-1)]));
                bounds.emplace_back(Bound(stiffness, vertices[ind_map(i  ,j-1,k  )], vertices[ind_map(i  ,j-1,k-1)]));
                bounds.emplace_back(Bound(stiffness, vertices[ind_map(i-1,j  ,k  )], vertices[ind_map(i-1,j  ,k-1)]));
                bounds.emplace_back(Bound(stiffness, vertices[ind_map(i-1,j-1,k  )], vertices[ind_map(i-1,j-1,k-1)]));

                // diagonal bounds:
                bounds.emplace_back(Bound(stiffness, vertices[ind_map(i  ,j  ,k  )], vertices[ind_map(i-1,j-1,k-1)]));
                bounds.emplace_back(Bound(stiffness, vertices[ind_map(i  ,j  ,k-1)], vertices[ind_map(i-1,j-1,k  )]));
                bounds.emplace_back(Bound(stiffness, vertices[ind_map(i  ,j-1,k  )], vertices[ind_map(i-1,j  ,k-1)]));
                bounds.emplace_back(Bound(stiffness, vertices[ind_map(i-1,j  ,k  )], vertices[ind_map(i  ,j-1,k-1)]));

            }

    // vertex indices assignment

    // x surface:
    for (uint j = 1; j < m+1; j++)
        for (uint k = 1; k < p+1; k++)
        {
            // x = 0:
            vertex_indices.emplace_back(ind_map(0,j-1,k-1));
            vertex_indices.emplace_back(ind_map(0,j-1,k  ));
            vertex_indices.emplace_back(ind_map(0,j  ,k-1));
            vertex_indices.emplace_back(ind_map(0,j  ,k  ));

            vertex_indices.emplace_back(ind_map(0,j-1,k-1));
            vertex_indices.emplace_back(ind_map(0,j  ,k-1));
            vertex_indices.emplace_back(ind_map(0,j-1,k  ));
            vertex_indices.emplace_back(ind_map(0,j  ,k  ));

            // x = length
            vertex_indices.emplace_back(ind_map(n,j-1,k-1));
            vertex_indices.emplace_back(ind_map(n,j-1,k  ));
            vertex_indices.emplace_back(ind_map(n,j  ,k-1));
            vertex_indices.emplace_back(ind_map(n,j  ,k  ));

            vertex_indices.emplace_back(ind_map(n,j-1,k-1));
            vertex_indices.emplace_back(ind_map(n,j  ,k-1));
            vertex_indices.emplace_back(ind_map(n,j-1,k  ));
            vertex_indices.emplace_back(ind_map(n,j  ,k  ));
        }
    // y surface
    for (uint i = 1; i < n+1; i++)
        for (uint k = 1; k < p+1; k++)
        {
            // y = 0
            vertex_indices.emplace_back(ind_map(i-1,0,k-1));
            vertex_indices.emplace_back(ind_map(i-1,0,k  ));
            vertex_indices.emplace_back(ind_map(i  ,0,k-1));
            vertex_indices.emplace_back(ind_map(i  ,0,k  ));

            vertex_indices.emplace_back(ind_map(i-1,0,k-1));
            vertex_indices.emplace_back(ind_map(i  ,0,k-1));
            vertex_indices.emplace_back(ind_map(i-1,0,k  ));
            vertex_indices.emplace_back(ind_map(i  ,0,k  ));

            // y = width
            vertex_indices.emplace_back(ind_map(i-1,m,k-1));
            vertex_indices.emplace_back(ind_map(i-1,m,k  ));
            vertex_indices.emplace_back(ind_map(i  ,m,k-1));
            vertex_indices.emplace_back(ind_map(i  ,m,k  ));

            vertex_indices.emplace_back(ind_map(i-1,m,k-1));
            vertex_indices.emplace_back(ind_map(i  ,m,k-1));
            vertex_indices.emplace_back(ind_map(i-1,m,k  ));
            vertex_indices.emplace_back(ind_map(i  ,m,k  ));

        }
    // z surface
    for (uint i = 1; i < n+1; i++)
        for (uint j = 1; j < m+1; j++)
        {
            // z = 0
            vertex_indices.emplace_back(ind_map(i-1,j-1,0));
            vertex_indices.emplace_back(ind_map(i-1,j  ,0));
            vertex_indices.emplace_back(ind_map(i  ,j-1,0));
            vertex_indices.emplace_back(ind_map(i  ,j  ,0));

            vertex_indices.emplace_back(ind_map(i  ,j  ,0));
            vertex_indices.emplace_back(ind_map(i-1,j  ,0));
            vertex_indices.emplace_back(ind_map(i  ,j-1,0));
            vertex_indices.emplace_back(ind_map(i-1,j-1,0));

            // z = height
            vertex_indices.emplace_back(ind_map(i-1,j-1,p));
            vertex_indices.emplace_back(ind_map(i-1,j  ,p));
            vertex_indices.emplace_back(ind_map(i  ,j-1,p));
            vertex_indices.emplace_back(ind_map(i  ,j  ,p));

            vertex_indices.emplace_back(ind_map(i  ,j  ,p));
            vertex_indices.emplace_back(ind_map(i-1,j  ,p));
            vertex_indices.emplace_back(ind_map(i  ,j-1,p));
            vertex_indices.emplace_back(ind_map(i-1,j-1,p));
        }

    // move cube to position defined by center_pos:

    vect3d_d shift = center_pos - vect3d_d(length/2, width/2, height/2);
    for (auto& vertex : vertices)
    {
        vertex.pos = vertex.pos + shift;
    }
}
