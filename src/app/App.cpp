#include "App.hpp"
#include "physics/objects/CubeMesh.hpp"
#include "physics/constraints/DistanceConstraint.hpp"

App::App()
{
    data = std::make_shared<SolverData>();
    data->obj = std::make_shared<CubeMesh>();
    size_t numEdges = data->obj->numEdges();
    data->ctns.push_back(std::make_shared<DistanceConstraint>(numEdges));
    // TODO: add AreaConstraint
    // TODO: add VolumeConstraint
    // TODO: add BendingConstraint
    const float stiffness = 10.0;
    const float damping = 0.0;
    data->ctns[0]->setupConstraint(*data->obj, stiffness, damping);

    solver = std::make_shared<Solver>();
    solver->initialize(*data);
    
    renderer = std::make_shared<MetalRenderer>();
    renderer->setMesh(*data->obj);
}

void App::draw(CA::MetalDrawable* drawable)
{
    renderer->draw(drawable);
}

void App::step()
{
    solver->step(1.0/60.0, *data);
    renderer->updateMesh(*data->obj);
}
