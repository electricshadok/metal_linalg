#ifndef gemm_hpp
#define gemm_hpp

#include "FunctionOp.hpp"

namespace blas {

class gemm : FunctionOp
{
    gemm();
    
    gemm& operator()(const GPUTensor& x, const GPUTensor& y);
    
    virtual void setupEncoder(MTL::ComputeCommandEncoder& encoder) override;
    
    virtual void getNumThreadGroups(const MTL::Size& threadgroupSize,
                                    MTL::Size& numThreadgroups) const override;
    
protected:
    
    const GPUTensor* x;
    const GPUTensor* y;
};

} // namespace blas


#endif /* gemm_hpp */
