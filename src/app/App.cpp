#include "App.hpp"
#include "physics/objects/CubeMesh.hpp"

App::App()
{
    data = std::make_shared<SolverData>();
    data->obj = std::make_shared<CubeMesh>();
    solver = std::make_shared<Solver>();
    renderer = std::make_shared<MetalRenderer>();
    renderer->setMesh(*data->obj);
    solver->initialize(*data);
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
