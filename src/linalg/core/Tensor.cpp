#include "Tensor.hpp"

#include <Metal/Metal.hpp>


TensorBase::TensorBase(size_t size)
{
    setShape(size);
}

GPUTensor::GPUTensor(MTL::Device* device, size_t size): TensorBase(size)
{
    _data = nullptr;
    _device = device;
    allocate();
}

GPUTensor::GPUTensor(MTL::Device* device, CPUTensor& tensor)
{
    _data = nullptr;
    _device = device;
    syncWith(tensor);
}

GPUTensor::~GPUTensor()
{
    if (_data != nullptr) {
        _data->release();
        _data = nullptr;
    }
}

void GPUTensor::allocate()
{
    // Release GPU memory
    if (_data != nullptr) {
        _data->release();
        _data = nullptr;
    }
    if (_size == 0) {
        return;
    }

    _data = _device->newBuffer(_size * sizeof(float), MTL::ResourceStorageModeShared);
}

void GPUTensor::syncWith(CPUTensor& tensor)
{
    setShape(tensor.shape());
    
    if (_data != nullptr) {
        _data->release();
    }
    _data =  _device->newBuffer(tensor.data(), _size * sizeof(float), MTL::ResourceStorageModeShared);
}

CPUTensor::CPUTensor(size_t size): TensorBase(size)
{
    _data = nullptr;
    allocate();
}

CPUTensor::~CPUTensor()
{
    if (_data != nullptr) {
        delete[] _data;
        _data = nullptr;
    }
}

void CPUTensor::allocate()
{
    if (_data != nullptr) {
        delete[] _data;
        _data = nullptr;
    }
    
    if (_size == 0) {
        return;
    }
    _data = new float[_size];
}

void CPUTensor::syncWith(GPUTensor& tensor)
{
    // Allocate memory
    setShape(tensor.shape());
    allocate();
    
    // Copy content
    float* content = static_cast<float*>(tensor.data()->contents());
    std::memcpy(_data, content, _size * sizeof(float));
}
