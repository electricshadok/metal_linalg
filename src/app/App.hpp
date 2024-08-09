#ifndef App_hpp
#define App_hpp

#include "physics/Scene.hpp"
#include "physics/solver/Solver.hpp"
#include "app/view/MetalRenderer.hpp"

class App
{
public:
    App();
    ~App();
    
    void draw(CA::MetalDrawable* drawable);
    
    void step();

private:
    Scene* scene;
    Solver* solver;
    MetalRenderer* renderer;
};

#endif /* App_hpp */
