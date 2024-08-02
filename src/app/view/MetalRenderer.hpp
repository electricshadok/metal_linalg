#ifndef MetalRenderer_hpp
#define MetalRenderer_hpp

#include <QuartzCore/CAMetalLayer.h>
#include <QuartzCore/CAMetalDrawable.hpp>
#include <Metal/Metal.hpp>
#include <simd/simd.h>

class MetalRenderer
{
public:
    MetalRenderer();
    virtual ~MetalRenderer();
    
    void draw(CA::MetalDrawable* drawable);
    
private:
    void setupMetal();
    void setupVertices();
    void setupCamera();

    // Reference to the current GPU device
    MTL::Device* device;
    // Queue managing the execution of command buffers on the GPU
    MTL::CommandQueue* commandQueue;
    // Reference to the pipeline state object, which contains the graphics rendering pipeline's state
    MTL::RenderPipelineState* pipelineState;
    // Buffer containing vertex data
    MTL::Buffer* vertexBuffer;
    // Buffer containing index data
    MTL::Buffer* indexBuffer;
    // Buffer containing uniform data
    MTL::Buffer* uniformBuffer;
};

#endif /* MetalRenderer_hpp */
