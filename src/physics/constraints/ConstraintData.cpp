#include "ConstraintData.hpp"

ConstraintDataBase::ConstraintDataBase(size_t num_c, size_t size)
{
    size_t num_ids = num_c * size;
    size_t num_grad = num_c * size;
    size_t num_jac= num_c * size * size;

    _size = size;
    _k.resize(num_c);
    _kd.resize(num_c);
    _ids.resize(num_ids);
    _f.resize(num_grad);
    _dfdx.resize(num_jac);
    _dfdv.resize(num_jac);
}

size_t ConstraintDataBase::numConstraints() const
{
    return _k.size();
}

void ConstraintDataBase::setProperties(float stiffness, float damping)
{
    std::fill(_k.begin(), _k.end(), stiffness);
    std::fill(_kd.begin(), _kd.end(), damping);
}

void ConstraintDataBase::resetDerivatives()
{
    std::fill(_f.begin(), _f.end(), V3f::Zero());
    std::fill(_dfdx.begin(), _dfdx.end(), M33f::Zero());
    std::fill(_dfdv.begin(), _dfdv.end(), M33f::Zero());
}

template<size_t N>
ConstraintData<N>::ConstraintData(size_t c) : ConstraintDataBase(c, N)
{
    // Additional initialization (if needed)
}

// Explicit template instantiation for specific types
template struct ConstraintData<1>;
template struct ConstraintData<2>;
template struct ConstraintData<3>;
template struct ConstraintData<4>;
