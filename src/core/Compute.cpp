#include "Compute.hpp"

#define NS_PRIVATE_IMPLEMENTATION
#define CA_PRIVATE_IMPLEMENTATION
#define MTL_PRIVATE_IMPLEMENTATION
#include <Foundation/Foundation.hpp>
#include <Metal/Metal.hpp>
#include <QuartzCore/QuartzCore.hpp>

#include "Log.hpp"

Compute::Compute()
{
    device = MTL::CreateSystemDefaultDevice();
    library = device->newDefaultLibrary();
    commandQueue = device->newCommandQueue();
    commandBuffer = nullptr;
    encoder = nullptr;

    printDeviceCapabilities();
}

Compute::~Compute()
{
    if (encoder) {
        encoder->release();
    }
    if (commandBuffer) {
        commandBuffer->release();
    }

    commandQueue->release();
    library->release();
    device->release();
}


void Compute::printDeviceCapabilities()
{
    Log::info() << "--- Device infos ---";
    
    const char* device_name = device->name()->utf8String();
    Log::info() << "Device Name: " << device_name;
    
    MTL::Size max_threads = device->maxThreadsPerThreadgroup();
    Log::info() << "Max threads per group: " << max_threads.width << "," << max_threads.height << "," << max_threads.depth;

    // Note: Direct querying for the "maximum number of threadgroups" is not straightforward because it depends on various factors such as the compute kernel's resource usage.
    // However, you can determine the maximum number of threads per threadgroup and other limits related to threadgroup dimensions directly.
}


void Compute::registerFunction(FunctionOp& func, const char* name)
{
    func.registerFunction(this->library, name);
}

Status Compute::execute(FunctionOp& func)
{
    std::chrono::time_point start = std::chrono::high_resolution_clock::now();
    
    commandBuffer = commandQueue->commandBuffer();
    encoder = commandBuffer->computeCommandEncoder();
    
    if (!func.inPlace())
    {
        func.getOutput()->allocate();
    }
    func.setupEncoder(*encoder);

    // Run the kernel
    MTL::Size threadgroupSize = MTL::Size(256, 1, 1);
    MTL::Size numThreadgroups;
    func.getNumThreadGroups(threadgroupSize, numThreadgroups);
    encoder->dispatchThreadgroups(numThreadgroups, threadgroupSize);
    encoder->endEncoding();

    // Commit the command buffer and wait for it to complete
    commandBuffer->commit();
    commandBuffer->waitUntilCompleted();

    std::chrono::time_point stop = std::chrono::high_resolution_clock::now();
    std::chrono::milliseconds duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    return Status(duration, func.getOutput());
}

Status Compute::operator()(FunctionOp& func)
{
    return execute(func);
}
