#ifndef compute_hpp
#define compute_hpp

#include "FunctionOp.hpp"
#include "Tensor.hpp"

#include <chrono>

namespace MTL {
    // forward declaration for MTL
    class Device;
    class Library;
    class CommandQueue;
    class CommandBuffer;
    class ComputeCommandEncoder;
    class Function;
    class Size;
}

struct Status
{
    Status(std::chrono::milliseconds duration, GPUTensor* result)
    {
        this->duration = duration;
        this->result = result;
    }
    
    std::chrono::milliseconds duration;
    GPUTensor* result;
};

class Compute
{
public:
    Compute();
    virtual ~Compute();
    
    void printDeviceCapabilities();

    void registerFunction(FunctionOp& func, const char* name);
    
    Status execute(FunctionOp& func);
    
    MTL::Device* getDevice() { return device; }

    Status operator()(FunctionOp& func);
    
protected:
    // Reference to the current GPU device
    MTL::Device* device;
    // Library containing a collection of compute kernels
    MTL::Library* library;
    // Queue managing the execution of command buffers on the GPU
    MTL::CommandQueue* commandQueue;
    // Buffer for storing commands that will be executed by the GPU
    MTL::CommandBuffer* commandBuffer;
    // Encoder for configuring compute commands within a command buffer
    MTL::ComputeCommandEncoder* encoder;

};

#endif /* compute_hpp */



