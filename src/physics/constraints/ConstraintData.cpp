#include "ConstraintData.hpp"

ConstraintDataBase::ConstraintDataBase(size_t num_c, size_t num_ids, size_t num_grad, size_t num_jac):
    k(num_c),
    ids(num_ids),
    f(num_grad),
    dxdf(num_jac),
    dvdf(num_jac)
{
}

size_t ConstraintDataBase::size() const
{
    return k.size();
}

template<size_t N>
ConstraintData<N>::ConstraintData(size_t c) : ConstraintDataBase(c, c * N, c * N, c * N * N)
{
    // Additional initialization (if needed)
}

// Explicit template instantiation for specific types
template struct ConstraintData<1>;
template struct ConstraintData<2>;
template struct ConstraintData<3>;
template struct ConstraintData<4>;
