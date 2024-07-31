#include "Compute.hpp"
#include "Tensor.hpp"
#include "Log.hpp"
#include "axpy.hpp"
#include "scal.hpp"
#include "linalg/blas/level1/dot.hpp"
#include "copy.hpp"
#include "app/view/MetalRenderer.hpp"

class Problem
{
public:
    Problem(const size_t size);
public:
    CPUTensor x, y;
    
};

Problem::Problem(const size_t size) : x(size), y(size)
{
    for (int i=0; i < size; ++i)
    {
        x.data()[i] = static_cast<float>(i);
        y.data()[i] = static_cast<float>(i * 2);
    }
}

/*int main(int argc, const char * argv[])
{
    // Initialize data on CPU
    Problem problem(10000000);

    // Prepare object and function
    Compute compute = Compute();
    auto device = compute.getDevice();
    blas::axpy axpy;
    blas::scal scal;
    blas::copy copy;
    compute.registerFunction(axpy, "axpy");
    compute.registerFunction(scal, "scal");
    compute.registerFunction(copy, "copy");

    GPUTensor px(device, problem.x);
    GPUTensor py(device, problem.y);
    GPUTensor out(device);
    
    // (x.2 + y) * 3
    compute(axpy(px, py, 2.0f));
    compute(scal(px, 3.0f));
    compute(copy(px, out));
    
    // Print result
    CPUTensor res;
    res.syncWith(out);
    for (int i = 0; i < 10; ++i)
    {
        Log::info() << problem.x.data()[i] << "," << problem.y.data()[i] << "=" << res.data()[i];
    }
    
    // Test Metal renderer
    MetalRenderer render;

    return 0;
}*/

