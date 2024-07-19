#include "axpy.hpp"

#include <Foundation/Foundation.hpp>
#include <Metal/Metal.hpp>
#include <QuartzCore/QuartzCore.hpp>

namespace blas {

axpy::axpy() : x(nullptr), y(nullptr)
{
}

axpy& axpy::operator()(const GPUTensor& x, const GPUTensor& y, const float scale)
{
    this->x = &x;
    this->y = &y;
    _scale = scale;
    
    return *this;
}

void axpy::setupEncoder(MTL::ComputeCommandEncoder& encoder)
{
    // Set pipeline state to the encoder
    encoder.setComputePipelineState(_pipeline_state);
    
    // Setup the encoder
    NS::UInteger offset = 0;
    encoder.setBytes(&_scale, sizeof(_scale), 0);
    encoder.setBuffer(this->x->data(), offset, 1);
    encoder.setBuffer(this->y->data(), offset, 2);
}

void axpy::getNumThreadGroups(const MTL::Size& threadgroupSize,  MTL::Size& numThreadgroups) const
{
    // Determine how many thread groups are needed to cover the entire grid
    size_t size = this->x->shape();
    auto width = (size + (threadgroupSize.width-1)) / threadgroupSize.width;
    numThreadgroups = MTL::Size(width,
                                threadgroupSize.height,
                                threadgroupSize.depth);
}

} // namespace blas
