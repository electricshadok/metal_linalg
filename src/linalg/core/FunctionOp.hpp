#ifndef kernel_op_hpp
#define kernel_op_hpp

#include "Tensor.hpp"


namespace MTL {
    // forward declaration for MTL namespace
    class Buffer;
    class ComputePipelineState;
    class ComputeCommandEncoder;
    class Device;
    class Function;
    class Library;
    class Size;
}


class FunctionOp
{
public:
    
    FunctionOp();
    virtual ~FunctionOp() {};
    
    virtual void setupEncoder(MTL::ComputeCommandEncoder& encoder) = 0;
    
    virtual void getNumThreadGroups(const MTL::Size& threadgroupSize,  MTL::Size& numThreadgroups) const = 0;
    
    GPUTensor* getOutput() { return _out;}
    
    bool registerFunction(MTL::Library* library, const char* name);
    
    virtual bool inPlace() { return false; }
    
protected:

    GPUTensor* _out;
    MTL::Function* _func;
    MTL::ComputePipelineState* _pipeline_state;
};


class InplaceFunctionOp : public FunctionOp
{
public:
    
    InplaceFunctionOp();
    virtual ~InplaceFunctionOp() {};
    
    virtual bool inPlace() { return true; }
};



#endif /* kernel_op_hpp */
