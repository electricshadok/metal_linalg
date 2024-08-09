#ifndef App_hpp
#define App_hpp

#include "physics/objects/ObjectData.hpp"
#include "physics/solver/Solver.hpp"
#include "app/view/MetalRenderer.hpp"
#include <memory>

class App
{
public:
    App();
    
    void draw(CA::MetalDrawable* drawable);
    
    void step();

private:
    std::shared_ptr<ObjectData> data;
    std::shared_ptr<Solver> solver;
    std::shared_ptr<MetalRenderer> renderer;
};

#endif /* App_hpp */
