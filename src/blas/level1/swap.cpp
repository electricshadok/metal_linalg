#include "swap.hpp"

#include <Foundation/Foundation.hpp>
#include <Metal/Metal.hpp>
#include <QuartzCore/QuartzCore.hpp>

namespace blas {

swap::swap() : _x(nullptr)
{
}

swap& swap::operator()(GPUTensor& x, GPUTensor& y)
{
    _x = &x;
    _y = &y;
    
    return *this;
}


void swap::setupEncoder(MTL::ComputeCommandEncoder& encoder)
{
    // Set pipeline state to the encoder
    encoder.setComputePipelineState(_pipeline_state);
    
    // Setup the encoder
    NS::UInteger offset = 0;
    encoder.setBuffer(_x->data(), offset, 0);
    encoder.setBuffer(_out->data(), offset, 1);
}

void swap::getNumThreadGroups(const MTL::Size& threadgroupSize,  MTL::Size& numThreadgroups) const
{
    size_t size = _x->shape();
    numThreadgroups = MTL::Size((size + (threadgroupSize.width-1)) / threadgroupSize.width,
                                threadgroupSize.height,
                                threadgroupSize.depth);
}

} // namespace blas
