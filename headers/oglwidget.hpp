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
#include "datastorage.h"

/*!
 * @class OGLWidget
 *
 * @brief Класс содержащий методы рендеринга и отображающий рендер на экран
 */
class OGLWidget : public QOpenGLWidget
{
private:
    int surfVertSize{}, gridVertSize{};
    GLfloat lastX, lastY;
    QOpenGLFunctions_4_3_Core *ogl;
    Camera *camera;
    GLfloat* surfVertices;
    GLfloat* gridVertices;
    KGFequation<GLfloat> *equation;
    DataStorage *ds;

public:
    OGLWidget (QWidget *parent = nullptr);
    ~OGLWidget ();
    void drawGrid ();
    void drawSurface ();
    void setDataStorage (DataStorage *dspointer);

protected:
    void initializeGL () override;
    void resizeGL (int w, int h) override;
    void paintGL () override;
    void updateArrays ();
    void clearArrays ();

    /* События нажатия клавиш и движения мыши */
    void keyPressEvent (QKeyEvent *event) override;
    void mousePressEvent (QMouseEvent *event) override;
    void mouseReleaseEvent (QMouseEvent *event) override;
    QOpenGLContext *m_context;
};

#endif // OGLWIDGET_HPP
