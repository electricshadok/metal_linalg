#include "App.hpp"
#include "physics/objects/CubeMesh.hpp"
#include "physics/constraints/DistanceConstraint.hpp"

App::App()
{
    data = std::make_shared<SolverData>();
    data->obj = std::make_shared<CubeMesh>();
    size_t numEdges = data->obj->numEdges();
    
    const float stiffness = 10000.0;
    const float damping = 0.0;

    // Distance constraint
    auto distance_ctn(std::make_shared<DistanceConstraint>(numEdges));
    distance_ctn->setupConstraint(*data->obj, stiffness, damping);
    data->ctns.push_back(distance_ctn);
    
    // Anchor distance constraint on the top
    auto anchor_distance_ctn(std::make_shared<AnchorDistanceConstraint>(4));
    // 0,1,4,5 are the node ids of top face for the cube
    anchor_distance_ctn->setupZeroAnchor(0, *data->obj, 0);
    anchor_distance_ctn->setupZeroAnchor(1, *data->obj, 1);
    anchor_distance_ctn->setupZeroAnchor(2, *data->obj, 4);
    anchor_distance_ctn->setupZeroAnchor(3, *data->obj, 5);
    data->ctns.push_back(anchor_distance_ctn);

    // TODO: add AreaConstraint
    // TODO: add VolumeConstraint
    // TODO: add BendingConstraint
    
    // Set solver and render
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
    solver->step(1.0/600.0, *data);
    renderer->updateMesh(*data->obj);
}
