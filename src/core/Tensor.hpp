#ifndef Tensor_hpp
#define Tensor_hpp

#include <stddef.h>

namespace MTL {
    // forward declaration for MTL
    class Buffer;
    class Device;
}

class TensorBase
{
public:
    
    TensorBase(size_t size = 0);
    
    void setShape(size_t size) {_size = size;}
    size_t shape() const {return  _size;}
    
protected:
    
    size_t _size;
};

class CPUTensor;

class GPUTensor : public TensorBase
{
public:
    GPUTensor(MTL::Device* device, size_t size = 0);
    GPUTensor(MTL::Device* device, CPUTensor& tensor);
    virtual ~GPUTensor();
    
    void allocate();

    MTL::Buffer* data() { return _data; };
    const MTL::Buffer* data() const {return _data; };
    
    void syncWith(CPUTensor& tensor);
    
protected:
    
    MTL::Device* _device;
    MTL::Buffer* _data;
};

class CPUTensor : public TensorBase
{
public:
    CPUTensor(size_t size = 0);
    virtual ~CPUTensor();
    
    void allocate();

    float* data() { return _data; };
    const float* data() const {return _data; };
    
    void syncWith(GPUTensor& tensor);
    
protected:
    float* _data;
};



#endif


