#include "headers/camera.h"

Camera::Camera ()
    : moveSpeed(SPEED), mouseSens(SENS)
{
    this->Position = COrig::origPos;
    this->Front    = COrig::origFront;
    this->Up       = COrig::origUp;
    this->WorldUp  = this->Up;
    this->Yaw      = YAW;
    this->Pitch    = PITCH;
}

Camera::Camera(glm::vec3 position,
               glm::vec3 up,
               GLfloat yaw,
               GLfloat pitch)
    : Front(COrig::origFront),
      moveSpeed(SPEED),
      mouseSens(SENS)
{
    this->Position = position;
    this->WorldUp  = up;
    this->Yaw      = yaw;
    this->Pitch    = pitch;
    this->updateCameraVectors();
}

Camera::Camera(GLfloat posX, GLfloat posY, GLfloat posZ,
               GLfloat upX, GLfloat upY, GLfloat upZ,
               GLfloat yaw, GLfloat pitch)
    : Front(COrig::origFront),
      moveSpeed(SPEED),
      mouseSens(SENS)
{
    this->Position = glm::vec3(posX, posY, posZ);
    this->WorldUp  = glm::vec3(upX, upY, upZ);
    this->Yaw      = yaw;
    this->Pitch    = pitch;
    this->updateCameraVectors();
}

glm::mat4 Camera::getViewMatrix ()
{
    return glm::lookAt(this->Position, this->Position + this->Front, this->Up);
}

void Camera::keyboardMove (camera_Movement direction)
{
    switch (direction)
    {
    case FORWARD:
        this->Position += this->Front * moveSpeed;
        break;
    case BACKWARD:
        this->Position -= this->Front * moveSpeed;
        break;
    case LEFT:
        this->Position -= this->Right * moveSpeed;
        break;
    case RIGHT:
        this->Position += this->Right * moveSpeed;
        break;
    default:
        break;
    }
}

void Camera::mouseMove (GLfloat xoffset, GLfloat yoffset)
{
    xoffset *= this->mouseSens;
    yoffset *= this->mouseSens;

    this->Yaw   += xoffset;
    this->Pitch += yoffset;

    if (this->Pitch > 89.f)
    {
        this->Pitch = 89.f;
    }
    if (this->Pitch < -89.f)
    {
        this->Pitch = -89.f;
    }
    this->updateCameraVectors();
}

void Camera::rollBack ()
{
    this->Position = COrig::origPos;
    this->Front    = COrig::origFront;
    this->Up       = COrig::origUp;
}

void Camera::updateCameraVectors ()
{
    glm::vec3 front(-1.f);

    front.x = cos(glm::radians(this->Yaw)) * cos(glm::radians(this->Pitch));
    front.y = sin(glm::radians(this->Pitch));
    front.z = sin(glm::radians(this->Yaw)) * cos(glm::radians(this->Pitch));
    this->Front = glm::normalize(front);

    this->Right = glm::normalize( glm::cross(this->Front, this->WorldUp) );
    this->Up    = glm::normalize( glm::cross(this->Right, this->Front) );
}
