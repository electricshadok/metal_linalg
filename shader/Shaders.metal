#include <metal_stdlib>
using namespace metal;

struct VertexIn {
    float4 position [[attribute(0)]];
    float4 color [[attribute(1)]];
};

struct VertexOut {
    float4 position [[position]];
    float4 color;
};

struct Uniforms {
    float4x4 modelViewProjectionMatrix;
};

vertex VertexOut vertexShader(VertexIn in [[stage_in]], constant Uniforms& uniforms [[buffer(1)]]) {
    VertexOut out;
    out.position = uniforms.modelViewProjectionMatrix * in.position;
    out.color = in.color;
    return out;
}

fragment float4 fragmentShader(VertexOut in [[stage_in]]) {
    return in.color;
}
