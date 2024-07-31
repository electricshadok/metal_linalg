#ifndef scal_hpp
#define scal_hpp

#include "FunctionOp.hpp"

namespace blas {

class scal: public InplaceFunctionOp
{
public:
    
    scal();
    
    scal& operator()(const GPUTensor& x, const float scale);
    
    virtual void setupEncoder(MTL::ComputeCommandEncoder& encoder) override;
    
    virtual void getNumThreadGroups(const MTL::Size& threadgroupSize,
                                    MTL::Size& numThreadgroups) const override;
    
protected:
    
    const GPUTensor* _x;
    float _scale;
};

} // namespace blas

#endif /* scal_hpp */
