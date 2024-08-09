#include "App.hpp"
#include "physics/objects/CubeMesh.hpp"

App::App()
{
    scene = new Scene();
    solver = new Solver();
    renderer = new MetalRenderer();
    
    auto cube = std::make_shared<CubeMesh>();
    scene->addObject(cube);
    renderer->setMesh(*cube);
    solver->initialize(*scene);
}

App::~App() 
{
    delete renderer;
    delete solver;
    delete scene;
}


void App::draw(CA::MetalDrawable* drawable)
{
    renderer->draw(drawable);
}

void App::step()
{
    solver->step(1.0/60.0, *scene);
}
