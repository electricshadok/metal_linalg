#include "Solver.hpp"
#include <Eigen/Dense>

Solver::Solver() : gravity(0.0, -9.81, 0.0)
{
}

void Solver::initialize(const ObjectData& obj)
{
    system = std::make_shared<Assembly>(obj.numNodes());
}


/* https://colab.research.google.com/github/vincentbonnetcg/Numerical-Bric-a-Brac/blob/master/animation/implicit_time_integrator.ipynb#scrollTo=9628d9ad-fc35-4f35-84cf-d7772bae30d0
*/

void Solver::step(const float h, const ObjectData& obj)
{
    /* Assemble the system
     Implicit Step
     Solve :
         (M - h * df/dv - h^2 * df/dx) * deltaV = h * (f0 + h * df/dx * v0)
           A = (M - h^2 * df/dx)
           b = h * (f0 + h * df/dx * v0)
         => A * deltaV = b <=> deltaV = A^-1 * b
         deltaX = (v0 + deltaV) * h
         v = v + deltaV
         x = x + deltaX
    */
    // Apply gravity on nodes
    // TODO
    
    // Mass Matrix
    for (size_t i=0; i<obj.numNodes(); ++i)
    {
        Nodes::Mass m = obj.nodes.m[i];
        Eigen::Matrix3d massMatrix;
        massMatrix << m, 0.0, 0.0,
                      0.0, m, 0.0,
                      0.0, 0.0, m;
        system->addToMatrix(massMatrix, i, i);
    }
    
    // Update node velocities and positions
    // TODO

}
