#ifndef Geometry_hpp
#define Geometry_hpp

#include <Eigen/Dense>

namespace Geometry
{

float area(const Eigen::Vector3f& x0,
           const Eigen::Vector3f& x1,
           const Eigen::Vector3f& x2);

float volume(const Eigen::Vector3f& x0,
             const Eigen::Vector3f& x1,
             const Eigen::Vector3f& x2,
             const Eigen::Vector3f& x3);

// TODO: calculate deformation gradient

} // namespace Geometry

#endif /* Geometry_hpp */

