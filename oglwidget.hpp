#ifndef OGLWIDGET_HPP
#define OGLWIDGET_HPP

#include <QWidget>
#include <QOpenGLWidget>
#include <QOpenGLFunctions_4_3_Core>
#include <QMessageBox>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QDir>
/* GLM */
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.h"
#include "camera.h"
#include "kgfequ.h"

/*!
 * @class OGLWidget
 *
 * @brief Класс содержащий методы рендеринга и отображающий рендер на экран
 */
class OGLWidget : public QOpenGLWidget
{
private:
    QOpenGLFunctions_4_3_Core *ogl;
    Camera *camera;
    GLfloat lastX, lastY;
    KGFequation<GLfloat> *equation;

public:
    OGLWidget (QWidget *parent = 0);
    ~OGLWidget ();
    void drawGrid ();
    void drawSurface ();
    /* Контекст отрисовки */
    QOpenGLFunctions_4_3_Core *getOGL (void);
protected:
    void initializeGL ();
    void resizeGL (int w, int h);
    void paintGL ();

    /* События нажатия клавиш и движения мыши */
    void keyPressEvent (QKeyEvent *event);
    void mousePressEvent (QMouseEvent *event);
    void mouseReleaseEvent (QMouseEvent *event);
    QOpenGLContext *m_context;
};

#endif // OGLWIDGET_HPP
