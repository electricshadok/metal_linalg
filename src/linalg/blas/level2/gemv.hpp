#ifndef gemv_hpp
#define gemv_hpp

#include "FunctionOp.hpp"

namespace blas {

class gemv : FunctionOp
{
    gemv();
    
    gemv& operator()(const GPUTensor& a, const GPUTensor& y);
    
    virtual void setupEncoder(MTL::ComputeCommandEncoder& encoder) override;
    
    virtual void getNumThreadGroups(const MTL::Size& threadgroupSize,
                                    MTL::Size& numThreadgroups) const override;
    
protected:
    
    const GPUTensor* a;
    const GPUTensor* x;
};

} // namespace blas


#endif /* gemv_hpp */
