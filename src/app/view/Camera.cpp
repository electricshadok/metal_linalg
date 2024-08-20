#include "Camera.hpp"
#include "Transform.hpp"
#include <cmath>

Camera::Camera(simd::float3 position, simd::float3 up, float yaw, float pitch)
    : front(simd::float3{0.0f, 0.0f, -1.0f}), movementSpeed(2.5f), mouseSensitivity(0.1f)
{
    this->position = position;
    this->worldUp = up;
    this->yaw = yaw;
    this->pitch = pitch;
    updateCameraVectors();
}

simd::float4x4 Camera::getViewMatrix() const
{
    return matrix_look_at(position, position + front, up);
}

void Camera::processKeyboardInput(char direction, float deltaTime)
{
    // TODO: connect function to key events
    float velocity = movementSpeed * deltaTime;
    if (direction == 'W')
        position += front * velocity;
    if (direction == 'S')
        position -= front * velocity;
    if (direction == 'A')
        position -= right * velocity;
    if (direction == 'D')
        position += right * velocity;
}

void Camera::processMouseMovement(float xoffset, float yoffset, bool constrainPitch)
{
    // TODO: connect function to key events
    xoffset *= mouseSensitivity;
    yoffset *= mouseSensitivity;

    yaw += xoffset;
    pitch += yoffset;

    if (constrainPitch)
    {
        if (pitch > 89.0f)
            pitch = 89.0f;
        if (pitch < -89.0f)
            pitch = -89.0f;
    }

    updateCameraVectors();
}

void Camera::updateCameraVectors()
{
    simd::float3 front;
    front.x = cosf(yaw * M_PI / 180.0f) * cosf(pitch * M_PI / 180.0f);
    front.y = sinf(pitch * M_PI / 180.0f);
    front.z = sinf(yaw * M_PI / 180.0f) * cosf(pitch * M_PI / 180.0f);
    this->front = simd::normalize(front);

    right = simd::normalize(simd::cross(this->front, worldUp));
    up = simd::normalize(simd::cross(right, this->front));
}
