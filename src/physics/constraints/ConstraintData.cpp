#include "ConstraintData.hpp"

ConstraintDataBase::ConstraintDataBase(size_t num_c, size_t num_ids, size_t num_grad, size_t num_jac):
    k(num_c),
    kd(num_c),
    _ids(num_ids),
    _f(num_grad),
    _dfdx(num_jac),
    _dfdv(num_jac)
{
}

size_t ConstraintDataBase::numConstraints() const
{
    return k.size();
}

template<size_t N>
ConstraintData<N>::ConstraintData(size_t c) : ConstraintDataBase(c, c * N, c * N, c * N * N)
{
    // Additional initialization (if needed)
}

template<size_t N>
size_t ConstraintData<N>::size() const
{
    return N;
}

// Explicit template instantiation for specific types
template struct ConstraintData<1>;
template struct ConstraintData<2>;
template struct ConstraintData<3>;
template struct ConstraintData<4>;
