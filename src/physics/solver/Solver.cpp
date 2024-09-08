#include "Solver.hpp"
#include <Eigen/Dense>
#include "physics/system/LinearSolvers.hpp"

Solver::Solver() : gravity(0.0, -9.81, 0.0)
{
}

void Solver::initialize(const SolverData& data)
{
    ObjectData& obj = *data.obj;
    system = std::make_shared<Assembly>(obj.numNodes());
}

/* https://colab.research.google.com/github/vincentbonnetcg/Numerical-Bric-a-Brac/blob/master/animation/implicit_time_integrator.ipynb#scrollTo=9628d9ad-fc35-4f35-84cf-d7772bae30d0
*/

void Solver::step(const float h, SolverData& data)
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
    ObjectData& obj = *data.obj;
    
    // Initialize system
    system = std::make_shared<Assembly>(obj.numNodes());

    // Reset external forces/accelerations
    for (size_t i=0; i<obj.numNodes(); ++i)
    {
        obj.nodes.f[i].setZero();
        obj.nodes.f[i] = gravity * obj.nodes.m[i];
    }

    // Calculate constraints derivatives
    for (auto& ctn : data.ctns)
    {
        ctn->updateDerivatives(obj);
    }
    
    // Assemble system
    assembleGlobalMatrix(h, data);
    assembleGlobalVector(h, data);
    
    // Solve system to get velocity deltas
    CGSolver solver(PreconditionerType::None);
    std::vector<Eigen::Vector3f> dv(toVector3f(solver.solve(*system)));
    
    // Compute position deltas
    std::vector<Eigen::Vector3f> dx(dv.size());
    for (size_t i=0; i < dx.size();++i)
    {
        dx[i] = (obj.nodes.vel[i] + dv[i]) * h;
    }
    
    // Update states
    for (size_t i=0; i < dx.size();++i)
    {
        obj.nodes.vel[i] += dv[i];
        obj.nodes.p[i] += dx[i];
    }
}

void Solver::assembleGlobalMatrix(const float h, const SolverData& data)
{
    // Assemble the matrix A
    // A = (M - h * df/dv - h^2 * df/dx)
    
    ObjectData& obj = *data.obj;

    // Add mass matrix (M)
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
    
    // Add (- h * df/dv - h^2 * df/dx)
    for (auto& ctn : data.ctns)
    {
        for (size_t i=0; i < ctn->numConstraints(); ++i)
        {
            // TODO - add equation above
        }
    }
}

void Solver::assembleGlobalVector(const float h, const SolverData& data)
{
    // Assemble the vector b
    // b = h * (f0 + h * df/dx * v0)
    
    ObjectData& obj = *data.obj;
    
    // Add (h * f0)
    for (size_t i=0; i<obj.numNodes(); ++i)
    {
        system->addToVector(obj.nodes.f[i] * h, i);
    }
    
    // Add (h * h * df/dx * v0)
    for (auto& ctn : data.ctns)
    {
        size_t ctn_size = ctn->size();
        // TODO - add equation above
    }
}



std::vector<Eigen::Vector3f> Solver::toVector3f(const Eigen::VectorXf& solution)
{
    std::vector<Eigen::Vector3f> result;
    for (int i = 0; i < solution.size(); i += 3) {
        result.emplace_back(solution[i], solution[i + 1], solution[i + 2]);
    }
    return result;
}
