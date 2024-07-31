#ifndef Camera_hpp
#define Camera_hpp

#include <simd/simd.h>

class Camera
{
public:
    Camera(simd::float3 position, simd::float3 up, float yaw, float pitch);
    simd::float4x4 getViewMatrix() const;
    void processKeyboardInput(char direction, float deltaTime);
    void processMouseMovement(float xoffset, float yoffset, bool constrainPitch = true);

    
private:
    void updateCameraVectors();
    
    simd::float3 position;
    simd::float3 front;
    simd::float3 up;
    simd::float3 right;
    simd::float3 worldUp;
    float yaw;
    float pitch;

    float movementSpeed;
    float mouseSensitivity;
};

#endif /* Camera_hpp */
