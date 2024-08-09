#include "Solver.hpp"


void Solver::initialize(const Scene& scene)
{
    system = std::make_shared<Assembly>(scene.numNodes());
}

void Solver::step(const float dt, const Scene& scene)
{
   
    /* https://colab.research.google.com/github/vincentbonnetcg/Numerical-Bric-a-Brac/blob/master/animation/implicit_time_integrator.ipynb#scrollTo=9628d9ad-fc35-4f35-84cf-d7772bae30d0
    */
    /*
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
    // Mass Matrix
    for (const auto& obj : scene.objects)
    {
        for (size_t i=0; i<obj->numNodes(); ++i)
        {
            // TODO
        }
    }
}
