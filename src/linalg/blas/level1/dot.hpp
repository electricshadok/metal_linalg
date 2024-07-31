#ifndef dot_hpp
#define dot_hpp

#include "FunctionOp.hpp"

namespace blas {

class dot : FunctionOp
{
    dot();
    
    dot& operator()(const GPUTensor& x, const GPUTensor& y);
    
    virtual void setupEncoder(MTL::ComputeCommandEncoder& encoder) override;
    
    virtual void getNumThreadGroups(const MTL::Size& threadgroupSize,
                                    MTL::Size& numThreadgroups) const override;
    
protected:
    
    const GPUTensor* x;
    const GPUTensor* y;
};

} // namespace blas


#endif /* dot_hpp */
