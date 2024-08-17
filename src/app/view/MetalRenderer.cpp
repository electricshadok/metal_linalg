#include "MetalRenderer.hpp"
#include "Log.hpp"
#include "Transform.hpp"

typedef struct {
    vector_float4 position;
    vector_float4 color;
} Vertex;

typedef struct {
    matrix_float4x4 modelViewProjectionMatrix;
} Uniforms;

MetalRenderer::MetalRenderer():
    vertexBuffer(nullptr),
    indexBuffer(nullptr)
{
    device = MTL::CreateSystemDefaultDevice();
    
    setupMetal();
    setupCamera();
}

MetalRenderer::~MetalRenderer()
{
    device->release();
    commandQueue->release();
    pipelineState->release();
    uniformBuffer->release();
    
    if (vertexBuffer) {
        vertexBuffer->release();
    }
    
    if (indexBuffer) {
        indexBuffer->release();
    }
}

void MetalRenderer::setupMetal()
{
    MTL::Library* library = device->newDefaultLibrary();
    
    NS::String* vtxShader = NS::String::string("vertexShader", NS::ASCIIStringEncoding);
    NS::String* frgShader = NS::String::string("fragmentShader", NS::ASCIIStringEncoding);
    auto vertexFunction = library->newFunction(vtxShader);
    auto fragmentFunction = library->newFunction(frgShader);

    // Create a vertex descriptor
    MTL::VertexDescriptor* vertexDescriptor = MTL::VertexDescriptor::alloc()->init();
    vertexDescriptor->attributes()->object(0)->setFormat(MTL::VertexFormatFloat4);
    vertexDescriptor->attributes()->object(0)->setOffset(0);
    vertexDescriptor->attributes()->object(0)->setBufferIndex(0);

    vertexDescriptor->attributes()->object(1)->setFormat(MTL::VertexFormatFloat4);
    vertexDescriptor->attributes()->object(1)->setOffset(sizeof(vector_float4));
    vertexDescriptor->attributes()->object(1)->setBufferIndex(0);

    vertexDescriptor->layouts()->object(0)->setStride(sizeof(Vertex));
    vertexDescriptor->layouts()->object(0)->setStepFunction(MTL::VertexStepFunctionPerVertex);

    // Create a render pipeline descriptor
    MTL::RenderPipelineDescriptor* pipelineDescriptor = MTL::RenderPipelineDescriptor::alloc()->init();
    pipelineDescriptor->setVertexFunction(vertexFunction);
    pipelineDescriptor->setFragmentFunction(fragmentFunction);
    pipelineDescriptor->setVertexDescriptor(vertexDescriptor);
    pipelineDescriptor->colorAttachments()->object(0)->setPixelFormat(MTL::PixelFormatBGRA8Unorm);
    
    NS::Error* error = nullptr;
    pipelineState = device->newRenderPipelineState(pipelineDescriptor, &error);
    if (!pipelineState) {
        Log::error() << "Failed to create render pipeline state: " << error->localizedDescription()->utf8String();
        return;
    }
    
    commandQueue = device->newCommandQueue();
    vertexFunction->release();
    fragmentFunction->release();
    pipelineDescriptor->release();
    vertexDescriptor->release();
    library->release();
    
    uniformBuffer = device->newBuffer(sizeof(Uniforms), MTL::ResourceStorageModeShared);
}

void MetalRenderer::setMesh(const ObjectData& obj)
{
    // Convert vertices
    std::vector<Vertex> vertices(obj.nodes.p.size());
    for (size_t i = 0; i < obj.nodes.p.size(); ++i) {
        vertices[i].position = {obj.nodes.p[i][0], obj.nodes.p[i][1], obj.nodes.p[i][2], 1.0f};
        vertices[i].color = {0.5f, 0.5f, 0.5f, 1.0f};
    }
    
    // Convert indices
    std::vector<uint16_t> indices(obj.connectivity.triangles.size() * 3);
    for (size_t i = 0; i < obj.connectivity.triangles.size(); ++i) {
        indices[i * 3 + 0] = obj.connectivity.triangles[i][0];
        indices[i * 3 + 1] = obj.connectivity.triangles[i][1];
        indices[i * 3 + 2] = obj.connectivity.triangles[i][2];
    }

    // Create buffers
    if (vertexBuffer) vertexBuffer->release();
    if (indexBuffer) indexBuffer->release();
    
    // Create buffers
    vertexBuffer = device->newBuffer(vertices.data(), vertices.size() * sizeof(Vertex), MTL::ResourceStorageModeShared);
    indexBuffer = device->newBuffer(indices.data(), indices.size() * sizeof(uint16_t), MTL::ResourceStorageModeShared);
}

void MetalRenderer::updateMesh(const ObjectData& obj)
{
    if (!vertexBuffer) return;

    // Convert vertices
    std::vector<Vertex> vertices(obj.nodes.p.size());
    for (size_t i = 0; i < obj.nodes.p.size(); ++i) {
        vertices[i].position = {obj.nodes.p[i][0], obj.nodes.p[i][1], obj.nodes.p[i][2], 1.0f};
        vertices[i].color = {0.5f, 0.5f, 0.5f, 1.0f};
    }
    
    memcpy(vertexBuffer->contents(), vertices.data(), vertices.size() * sizeof(Vertex));
}

void MetalRenderer::setupCamera()
{
    // Setup the perspective projection matrix
    float aspect = 800.0f / 600.0f;
    float fovy = M_PI / 4.0f; // 45 degrees field of view
    float nearZ = 0.1f;
    float farZ = 100.0f;
    matrix_float4x4 projectionMatrix = matrix_perspective(fovy, aspect, nearZ, farZ);

    // Setup the view matrix (simple translation for now)
    vector_float3 eye = {0.0f, 0.0f, -5.0f};
    vector_float3 center = {0.0f, 0.0f, 0.0f};
    vector_float3 up = {0.0f, 1.0f, 0.0f};
    matrix_float4x4 viewMatrix = matrix_look_at(eye, center, up);
    
    Uniforms uniforms;
    uniforms.modelViewProjectionMatrix = simd_mul(projectionMatrix, viewMatrix);

    memcpy(uniformBuffer->contents(), &uniforms, sizeof(uniforms));
}

void MetalRenderer::draw(CA::MetalDrawable* drawable)
{
    MTL::RenderPassDescriptor* passDescriptor = MTL::RenderPassDescriptor::alloc()->init();
    passDescriptor->colorAttachments()->object(0)->setTexture(drawable->texture());
    passDescriptor->colorAttachments()->object(0)->setLoadAction(MTL::LoadActionClear);
    passDescriptor->colorAttachments()->object(0)->setClearColor(MTL::ClearColor::Make(0.0, 0.0, 1.0, 1.0));
    passDescriptor->colorAttachments()->object(0)->setStoreAction(MTL::StoreActionStore);

    MTL::CommandBuffer* commandBuffer = commandQueue->commandBuffer();
    MTL::RenderCommandEncoder* renderEncoder = commandBuffer->renderCommandEncoder(passDescriptor);

    renderEncoder->setTriangleFillMode(MTL::TriangleFillModeLines);
    renderEncoder->setRenderPipelineState(pipelineState);
    renderEncoder->setVertexBuffer(uniformBuffer, 0, 1);
    
    if (vertexBuffer and indexBuffer)
    {
        renderEncoder->setVertexBuffer(vertexBuffer, 0, 0);
        renderEncoder->drawIndexedPrimitives(MTL::PrimitiveType::PrimitiveTypeTriangle, indexBuffer->length() / sizeof(uint16_t), MTL::IndexType::IndexTypeUInt16, indexBuffer, 0);
    }

    renderEncoder->endEncoding();
    commandBuffer->presentDrawable(drawable);
    commandBuffer->commit();
    
    passDescriptor->release();
}
