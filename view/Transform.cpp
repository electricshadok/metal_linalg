#include "Transform.hpp"


matrix_float4x4 matrix_perspective(float fovyRadians, float aspect, float nearZ, float farZ) 
{
    float yScale = 1 / tanf(fovyRadians * 0.5);
    float xScale = yScale / aspect;
    float zRange = farZ - nearZ;
    float zScale = -(farZ + nearZ) / zRange;
    float wzScale = -2 * farZ * nearZ / zRange;
    matrix_float4x4 m = {{
        { xScale, 0, 0, 0 },
        { 0, yScale, 0, 0 },
        { 0, 0, zScale, -1 },
        { 0, 0, wzScale, 0 }
    }};
    return m;
}

matrix_float4x4 matrix_translation(float x, float y, float z) 
{
    matrix_float4x4 m = {{
        { 1, 0, 0, 0 },
        { 0, 1, 0, 0 },
        { 0, 0, 1, 0 },
        { x, y, z, 1 }
    }};
    return m;
}

matrix_float4x4 matrix_rotation(float angle, vector_float3 axis) 
{
    axis = simd::normalize(axis);
    float ct = cosf(angle);
    float st = sinf(angle);
    float ci = 1 - ct;
    float x = axis.x, y = axis.y, z = axis.z;
    matrix_float4x4 m = {{
        { ct + x*x*ci, x*y*ci - z*st, x*z*ci + y*st, 0 },
        { y*x*ci + z*st, ct + y*y*ci, y*z*ci - x*st, 0 },
        { z*x*ci - y*st, z*y*ci + x*st, ct + z*z*ci, 0 },
        { 0, 0, 0, 1 }
    }};
    return m;
}

matrix_float4x4 matrix_look_at(vector_float3 eye, vector_float3 center, vector_float3 up) 
{
    vector_float3 f = simd::normalize(center - eye);
    vector_float3 s = simd::normalize(simd::cross(f, up));
    vector_float3 u = simd::cross(s, f);
    
    matrix_float4x4 m = {{
        { s.x, u.x, -f.x, 0 },
        { s.y, u.y, -f.y, 0 },
        { s.z, u.z, -f.z, 0 },
        { -simd::dot(s, eye), -simd::dot(u, eye), simd::dot(f, eye), 1 }
    }};
    return m;
}
