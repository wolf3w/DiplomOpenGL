#ifndef OGLWIDGET_HPP
#define OGLWIDGET_HPP

#include <QWidget>
#include <QOpenGLWidget>
#include <QOpenGLFunctions_4_3_Core>
#include <QMessageBox>
#include <QKeyEvent>
#include <QMouseEvent>
/* GLM */
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.h"
#include "camera.h"
#include "kgfequ.h"

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
