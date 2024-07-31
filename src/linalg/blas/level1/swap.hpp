#ifndef swap_hpp
#define swap_hpp

#include "FunctionOp.hpp"

namespace blas {

class swap : FunctionOp
{
    swap();
    
    swap& operator()(GPUTensor& x, GPUTensor& y);
    
    virtual void setupEncoder(MTL::ComputeCommandEncoder& encoder) override;
    
    virtual void getNumThreadGroups(const MTL::Size& threadgroupSize,
                                    MTL::Size& numThreadgroups) const override;
    
protected:
    
    const GPUTensor* _x;
    const GPUTensor* _y;
};

} // namespace blas

#endif /* swap_hpp */
