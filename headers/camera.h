#ifndef CAMERA_H
#define CAMERA_H

/***
 * Класс Камера
 * ВНИМАНИЕ! Управление мышью будет
 * работать некорректно, если НЕ задать Viewport
 * Например: glViewport(0, 0, width, height)
 * Иначе камера будет улетать
*/

#include <GL/gl.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

/** Направления движения камеры */
enum camera_Movement
{
    FORWARD, BACKWARD, LEFT, RIGHT
};

constexpr GLfloat YAW   = -65.85f,
                  PITCH = 56.45f,
                  SPEED = 0.2f,
                  SENS  = 0.05f;

/** Начальное положение камеры */
namespace COrig
{
    const glm::vec3 origPos   {23.103849f, -13.426983f, 18.367807f},
                    origFront {0.226110f, 0.833404f, -0.504294f},
                    origUp    {-0.075893f, 0.531200f, 0.843841f};
}

class Camera
{
public:
    glm::vec3 Position;
    glm::vec3 Front;
    glm::vec3 Up;
    glm::vec3 Right;
    glm::vec3 WorldUp;

    GLfloat Yaw;
    GLfloat Pitch;
    GLfloat moveSpeed;
    GLfloat mouseSens;

    Camera();
    Camera(glm::vec3 position,
           glm::vec3 up = COrig::origUp,
           GLfloat yaw = YAW,
           GLfloat pitch = PITCH);
    Camera(GLfloat posX, GLfloat posY, GLfloat posZ, GLfloat upX, GLfloat upY, GLfloat upZ, GLfloat yaw, GLfloat pitch);

    glm::mat4 getViewMatrix ();
    void keyboardMove (camera_Movement direction);
    void mouseMove (GLfloat xoffset, GLfloat yoffset);
    /** Возвращает камеру в исходное место */
    void rollBack ();

    /* Запрет */
    Camera(Camera const&) = delete;
    Camera(Camera &&) = delete;

private:
    void updateCameraVectors ();
};

#endif // CAMERA_H
