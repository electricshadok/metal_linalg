#include "scal.hpp"

#include <Foundation/Foundation.hpp>
#include <Metal/Metal.hpp>
#include <QuartzCore/QuartzCore.hpp>

namespace blas {

scal::scal() : _x(nullptr)
{
}

scal& scal::operator()(const GPUTensor& x, const float scale)
{
    _x = &x;
    _scale = scale;

    return *this;
}

void scal::setupEncoder(MTL::ComputeCommandEncoder& encoder)
{
    // Set pipeline state to the encoder
    encoder.setComputePipelineState(_pipeline_state);
    
    // Setup the encoder
    NS::UInteger offset = 0;
    encoder.setBytes(&_scale, sizeof(_scale), 0);
    encoder.setBuffer(_x->data(), offset, 1);
}

void scal::getNumThreadGroups(const MTL::Size& threadgroupSize,  MTL::Size& numThreadgroups) const
{
    // Determine how many thread groups are needed to cover the entire grid
    size_t size = _x->shape();
    auto width = (size + (threadgroupSize.width-1)) / threadgroupSize.width;
    numThreadgroups = MTL::Size(width,
                                threadgroupSize.height,
                                threadgroupSize.depth);
}

} // namespace blas

