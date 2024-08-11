#include <metal_stdlib>
using namespace metal;

// DOT : Dot product
kernel void dot(const device float* x [[buffer(0)]],
                const device float* y [[buffer(1)]],
                device float& result [[ buffer(2) ]],
                const uint id [[ thread_position_in_grid ]],
                const uint threadgroupID [[ threadgroup_position_in_grid]],
                const uint tid [[ thread_index_in_threadgroup ]])
{
    // TODO : implement metal dotproduct
    threadgroup_barrier(mem_flags::mem_threadgroup);
}

// AXPY : Constant times a vector plus a vector.
kernel void axpy(constant float& scale [[buffer(0)]],
                 device float* x [[buffer(1)]],
                 const device float* y [[buffer(2)]],
                 const uint id [[thread_position_in_grid]])
{
    x[id] = x[id] * scale + y[id];
}

// COPY : Copy vector into another one.
kernel void copy(const device float* x [[buffer(0)]],
                 device float* y [[buffer(1)]],
                 const uint id [[thread_position_in_grid]])
{
    y[id] = x[id];
}

// SCAL : Scaling a vector by a constant.
// result = ax
kernel void scal(constant float& scale [[buffer(0)]],
                 device float* x [[buffer(1)]],
                 const uint id [[thread_position_in_grid]])
{
    x[id] = x[id] * scale;
}

// SWAP : Swap two vectors
kernel void swap(device float* x [[buffer(0)]],
                 device float* y [[buffer(1)]],
                 const uint id [[thread_position_in_grid]])
{
    float temp = x[id];
    y[id] = x[id];
    x[id] = temp;
}
