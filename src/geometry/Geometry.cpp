#include "Geometry.hpp"


namespace Geometry
{

float area(const V3f& x0,
           const V3f& x1,
           const V3f& x2)
{
    V3f v1 = x1 - x0;
    V3f v2 = x2 - x0;
    V3f crossProduct = v1.cross(v2);
    
    float area = 0.5f * crossProduct.norm();
    return area;
}

float volume(const V3f& x0,
             const V3f& x1,
             const V3f& x2,
             const V3f& x3)
{
    V3f v1 = x1 - x0;
    V3f v2 = x2 - x0;
    V3f v3 = x3 - x0;

    // Calculate the volume from the scalar triple product
    float volume = std::abs(v1.dot(v2.cross(v3))) / 6.0f;

    return volume;
}

V3f normal(const V3f& x0,
           const V3f& x1,
           const V3f& x2)
{
    V3f v1 = x1 - x0;
    V3f v2 = x2 - x0;
    V3f normal = v1.cross(v2).normalized();
    return normal;
}


} // namespace Geometry
