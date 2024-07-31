#include "FunctionOp.hpp"
#include "Log.hpp"

#include <Foundation/Foundation.hpp>
#include <Metal/Metal.hpp>
#include <QuartzCore/QuartzCore.hpp>


FunctionOp::FunctionOp() : _func(nullptr),  _out(nullptr)
{
}

bool FunctionOp::registerFunction(MTL::Library* library, const char* name)
{
    MTL::Device* device = library->device();

    NS::String* function_name = NS::String::string(name, NS::ASCIIStringEncoding);
    this->_func = library->newFunction(function_name);

    if (!this->_func) {
        Log::error() << name << " NOT found";
        return false;
    }

    NS::Error* error = nullptr;
    this->_pipeline_state = device->newComputePipelineState(this->_func, &error);
    if (!this->_pipeline_state) {
        Log::error() << "Failed to create pipeline state: " << error->localizedDescription()->utf8String();
        return false;
    }

    Log::info() << name << " register";
    return true;
}

InplaceFunctionOp::InplaceFunctionOp() : FunctionOp()
{
}
