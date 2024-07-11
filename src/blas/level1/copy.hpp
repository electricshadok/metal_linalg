#ifndef copy_hpp
#define copy_hpp

#include "FunctionOp.hpp"

namespace blas {

class copy: public FunctionOp
{
public:
    
    copy();
    
    copy& operator()(const GPUTensor& x, GPUTensor& out);
    
    virtual void setupEncoder(MTL::ComputeCommandEncoder& encoder) override;
    
    virtual void getNumThreadGroups(const MTL::Size& threadgroupSize,
                                    MTL::Size& numThreadgroups) const override;
    
protected:
    
    const GPUTensor* _x;
};

} // namespace blas


#endif /* copy_hpp */
