#include "Solver.hpp"
#include <Eigen/Dense>
#include "physics/system/LinearSolvers.hpp"

Solver::Solver() : gravity(0.0, -9.81, 0.0)
{
}

void Solver::initialize(const ObjectData& obj)
{
    system = std::make_shared<Assembly>(obj.numNodes());
}

/* https://colab.research.google.com/github/vincentbonnetcg/Numerical-Bric-a-Brac/blob/master/animation/implicit_time_integrator.ipynb#scrollTo=9628d9ad-fc35-4f35-84cf-d7772bae30d0
*/

void Solver::step(const float h, ObjectData& obj)
{
    /* Assemble the system
     Implicit Step
     Solve :
         (M - h * df/dv - h^2 * df/dx) * deltaV = h * (f0 + h * df/dx * v0)
           A = (M - h * df/dv - h^2 * df/dx)
           b = h * (f0 + h * df/dx * v0)
         => A * deltaV = b <=> deltaV = A^-1 * b
         deltaX = (v0 + deltaV) * h
         v = v + deltaV
         x = x + deltaX
    */
    
    // Set system to zero
    system->setZero();
    
    // Gather forces
    for (size_t i=0; i<obj.numNodes(); ++i)
    {
        obj.nodes.f[i].setZero();
        obj.nodes.f[i] = gravity * obj.nodes.m[i];
    }

    // Assemble A matrix
    for (size_t i=0; i<obj.numNodes(); ++i)
    {
        // Mass Matrix
        Mass m = obj.nodes.m[i];
        Eigen::Matrix3f massMatrix;
        massMatrix << m, 0.0, 0.0,
                      0.0, m, 0.0,
                      0.0, 0.0, m;
        system->addToMatrix(massMatrix, i, i);
    }
    
    // Assemble b vector
    for (size_t i=0; i<obj.numNodes(); ++i)
    {
        system->addToVector(obj.nodes.f[i] * h, i);
    }
    
    // Solve system
    CGSolver solver(PreconditionerType::None);
    std::vector<Eigen::Vector3f> solution(toVector3f(solver.solve(*system)));

    // Update node velocities and positions
    // TODO : update

}

std::vector<Eigen::Vector3f> Solver::toVector3f(const Eigen::VectorXf& solution)
{
    std::vector<Eigen::Vector3f> result;
    for (int i = 0; i < solution.size(); i += 3) {
        result.emplace_back(solution[i], solution[i + 1], solution[i + 2]);
    }
    return result;
}