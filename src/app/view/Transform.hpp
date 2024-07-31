#ifndef Transform_hpp
#define Transform_hpp

#include <simd/simd.h>


matrix_float4x4 matrix_perspective(float fovyRadians, float aspect, float nearZ, float farZ);

matrix_float4x4 matrix_translation(float x, float y, float z);

matrix_float4x4 matrix_rotation(float angle, vector_float3 axis);

matrix_float4x4 matrix_look_at(vector_float3 eye, vector_float3 center, vector_float3 up);


#endif /* Transform_hpp */
