#ifndef App_hpp
#define App_hpp

#include "physics/Scene.hpp"
#include "app/view/MetalRenderer.hpp"

class App
{
public:
    App();
    ~App();
    
    void draw(CA::MetalDrawable* drawable);

private:
    Scene* scene;
    MetalRenderer* renderer;
};

// TODO
// https://chatgpt.com/c/832409e5-0f10-48b5-9230-c25fe72bb164


#endif /* App_hpp */
