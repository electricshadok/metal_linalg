#include "Geometry.hpp"


namespace Geometry
{

float area(const Eigen::Vector3f& x0,
           const Eigen::Vector3f& x1,
           const Eigen::Vector3f& x2)
{
    Eigen::Vector3f v1 = x1 - x0;
    Eigen::Vector3f v2 = x2 - x0;
    Eigen::Vector3f crossProduct = v1.cross(v2);
    
    float area = 0.5f * crossProduct.norm();
    return area;
}

float volume(const Eigen::Vector3f& x0,
             const Eigen::Vector3f& x1,
             const Eigen::Vector3f& x2,
             const Eigen::Vector3f& x3)
{
    Eigen::Vector3f v1 = x1 - x0;
    Eigen::Vector3f v2 = x2 - x0;
    Eigen::Vector3f v3 = x3 - x0;

    // Calculate the volume from the scalar triple product
    float volume = std::abs(v1.dot(v2.cross(v3))) / 6.0f;

    return volume;
}


} // namespace Geometry
