#ifndef Geometry_hpp
#define Geometry_hpp

#include "physics/Common.hpp"

namespace Geometry
{

float area(const V3f& x0,
           const V3f& x1,
           const V3f& x2);

float volume(const V3f& x0,
             const V3f& x1,
             const V3f& x2,
             const V3f& x3);

// TODO: calculate deformation gradient

} // namespace Geometry

#endif /* Geometry_hpp */

