#include "Camera.h"
Camera::Camera(glm::vec3 position, glm::vec3 up, GLfloat yaw, GLfloat pitch, GLfloat movespeed, GLfloat turnspeed) : position(position), worldUp(up), yaw(yaw), pitch(pitch), movementSpeed(movespeed), turnSpeed(turnspeed)
{
    front = glm::vec3(.0f, .0f, -1.0f);
    this->update();
}

void Camera::update()
{
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

    front = glm::normalize(front);
    right = glm::normalize(glm::cross(front, worldUp));
    up = glm::normalize(glm::cross(right, front));
}

void Camera::keyControl(bool *keys, GLfloat deltaTime)
{
    auto velocity = movementSpeed * deltaTime;
    if (keys[GLFW_KEY_W])
    {
        position += front * velocity;
    }
    if (keys[GLFW_KEY_S])
    {
        position -= front * velocity;
    }
    if (keys[GLFW_KEY_A])
    {
        position -= right * velocity;
    }
    if (keys[GLFW_KEY_D])
    {
        position += right * velocity;
    }
}
glm::mat4 Camera::calculateViewMatrix()
{
    return glm::lookAt(position,
                       position + front,
                       up);
}

void Camera::mouseControl(glm::vec2 change)
{
    change *= turnSpeed;

    yaw += change.x;
    pitch += change.y;

    if(pitch>89.0f) pitch=89.0f;
    this->update();
}