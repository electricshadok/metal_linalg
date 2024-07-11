#ifndef axpy_hpp
#define axpy_hpp

#include "FunctionOp.hpp"

namespace blas {

class axpy: public InplaceFunctionOp
{
public:
    
    axpy();
    
    axpy& operator()(const GPUTensor& x, const GPUTensor& y, const float scale);
    
    virtual void setupEncoder(MTL::ComputeCommandEncoder& encoder) override;
    
    virtual void getNumThreadGroups(const MTL::Size& threadgroupSize,
                                    MTL::Size& numThreadgroups) const override;
    
protected:
    
    const GPUTensor* x;
    const GPUTensor* y;
    float _scale;
};

} // namespace blas


#endif /* axpy_hpp */
