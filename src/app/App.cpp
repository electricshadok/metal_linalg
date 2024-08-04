#include "App.hpp"
#include "physics/objects/CubeMesh.hpp"

App::App()
{
    scene = new Scene();
    renderer = new MetalRenderer();
    
    auto cube = std::make_shared<CubeMesh>();
    scene->addObject(cube);
    renderer->setMesh(*cube);
}

App::~App() 
{
    delete renderer;
    delete scene;
}


void App::draw(CA::MetalDrawable* drawable)
{
    renderer->draw(drawable);
}
