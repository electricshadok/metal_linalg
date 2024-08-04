#include "App.hpp"

App::App() 
{
    scene = new Scene();
    renderer = new MetalRenderer();
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
