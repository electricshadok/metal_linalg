#include "ConstraintData.hpp"

template<size_t N>
ConstraintData<N>::ConstraintData(size_t c)
    : k(c),
      ids(c * N),
      f(c * N),
      dxdf(c * N * N),
      dvdf(c * N * N)
{
    // Additional initialization (if needed)
}

template<size_t N>
size_t ConstraintData<N>::size() const
{
    return k.size();
}

// Explicit template instantiation for specific types
template struct ConstraintData<1>;
template struct ConstraintData<2>;
template struct ConstraintData<3>;
template struct ConstraintData<4>;
