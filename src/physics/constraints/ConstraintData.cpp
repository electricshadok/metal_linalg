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
