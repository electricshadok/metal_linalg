#include "dot.hpp"

#include <Foundation/Foundation.hpp>
#include <Metal/Metal.hpp>
#include <QuartzCore/QuartzCore.hpp>

namespace blas {

dot::dot() : x(nullptr), y(nullptr)
{
}

dot& dot::operator()(const GPUTensor& x, const GPUTensor& y)
{
    this->x = &x;
    this->y = &y;
    
    return *this;
}

void dot::setupEncoder(MTL::ComputeCommandEncoder& encoder)
{
    // TODO : implement dot::setupEncoder
}

void dot::getNumThreadGroups(const MTL::Size& threadgroupSize, MTL::Size& numThreadgroups) const
{
    // TODO : implement dot::getNumThreadGroups
}

} // namespace blas
