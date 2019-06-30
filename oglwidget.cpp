#include "oglwidget.hpp"

OGLWidget::OGLWidget (QWidget *parent)
    : QOpenGLWidget (parent)
{
    m_context = new QOpenGLContext;
    m_context->create();

    /* Установка формата, иначе segfault */
    QSurfaceFormat format;
    format.setDepthBufferSize(24);
    format.setStencilBufferSize(8);
    format.setSamples(3); // Сглаживает линни
    format.setVersion(4, 3);
    format.setProfile(QSurfaceFormat::CoreProfile);
    this->setFormat(format);

    /* Фокус на виджете, чтобы команды управления работали */
    this->setFocus(Qt::MouseFocusReason);
    this->setMouseTracking(true);

    camera = new Camera();
    lastX = width()  / 2.f;
    lastY = height() / 2.f;

    std::function<GLfloat(GLfloat)> F = [] (GLfloat arg) -> GLfloat
    {
        return exp( log((1 / 3.0) * fabs(arg)) );
    };

    equation = new KGFequation<GLfloat>(F, 2000, 0.005f, 20);
}

OGLWidget::~OGLWidget()
{
    delete camera;
    delete equation;
}

void OGLWidget::initializeGL ()
{
    /* Инициализация Qt OpenGL функций */
    ogl = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_4_3_Core>();

    /* Цвет экрана очистки */
    ogl->glClearColor(0.2f, 0.3f, 0.5f, 1);

    /* viewport важен для правильного перемещения */
    ogl->glViewport(0, 0, width(), height());

    /* Z-буфер для того, чтобы грани не перекрывали друг друга */
    ogl->glEnable(GL_DEPTH_TEST);
}

void OGLWidget::paintGL ()
{
    /* Очистка буфферов */
    ogl->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    drawSurface();
    drawGrid();

    this->update();
}

void OGLWidget::resizeGL (int w, int h)
{
    glViewport(0, 0, w, h);
}

void OGLWidget::keyPressEvent (QKeyEvent *event)
{
    switch (event->key())
    {
    case Qt::Key_W:
        camera->keyboardMove(FORWARD);
        break;
    case Qt::Key_S:
        camera->keyboardMove(BACKWARD);
        break;
    case Qt::Key_A:
        camera->keyboardMove(LEFT);
        break;
    case Qt::Key_D:
        camera->keyboardMove(RIGHT);
        break;
    case Qt::Key_N:
        equation->nextIter();
        break;
    case Qt::Key_R:
        camera->rollBack();
        this->lastX = this->width() / 2.f;
        this->lastY = this->height() / 2.f;
        break;
    case Qt::Key_P:
        QMessageBox::information(this, "Info", QString("Iter: %1").arg(equation->getCurrentIter()));
        break;
    default:
        break;
    }
}

void OGLWidget::mousePressEvent(QMouseEvent *event)
{
    this->lastX = event->x();
    this->lastY = event->y();
}

void OGLWidget::mouseReleaseEvent(QMouseEvent *event)
{
    GLfloat xoffset = event->x() - lastX,
            yoffset = lastY - event->y();
    camera->mouseMove(xoffset, yoffset);
}

void OGLWidget::drawSurface ()
{
    /* Нужен полный путь */
    GLchar *pathVert = "/home/wolf3w/DiplomOpenGL/vshader.vert",
           *pathFrag = "/home/wolf3w/DiplomOpenGL/fshader.frag";

    Shader surfShader(ogl, pathVert, pathFrag);

    /* Получение массивов */
    QVector<GLfloat> tmpVert = equation->getSurface();
    GLfloat vertices[tmpVert.size()];

    for (int i = 0; i < tmpVert.size(); i++)
    {
        vertices[i] = tmpVert[i];
    }

    /* Создание и привязка буферов VBO и VAO */
    GLuint surfVAO, surfVBO;

    ogl->glGenVertexArrays(1, &surfVAO);
    ogl->glGenBuffers(1, &surfVBO);

    ogl->glBindVertexArray(surfVAO);
    ogl->glBindBuffer(GL_ARRAY_BUFFER, surfVBO);
    ogl->glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    /* Установка смещения для выбора из vertices */
    ogl->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*) 0);
    ogl->glEnableVertexAttribArray(0);

    /* Трансформация */
    glm::mat4 model, view, projection;

    model = glm::mat4(1.f);
    view  = camera->getViewMatrix();
    projection = glm::perspective(45.0f, (GLfloat)width() / (GLfloat)height(), 0.1f, 100.0f);

    GLint modelLoc  = ogl->glGetUniformLocation(surfShader.program_, "model"),
          viewLoc   = ogl->glGetUniformLocation(surfShader.program_, "view"),
          projecLoc = ogl->glGetUniformLocation(surfShader.program_, "projection");

    ogl->glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    ogl->glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    ogl->glUniformMatrix4fv(projecLoc, 1, GL_FALSE, glm::value_ptr(projection));

    /* Установка цвета */
    GLint colorLoc = ogl->glGetUniformLocation(surfShader.program_, "objColor");
    glm::vec3 colorSurf {1.0f, 0.5f, 0.31f};
    ogl->glUniform3fv(colorLoc, 1, glm::value_ptr(colorSurf));

    /* Наконец-то отрисовка */
    ogl->glDrawArrays(GL_TRIANGLES, 0, tmpVert.size());
    surfShader.Use();

    /* Отвязка и чистка */
    ogl->glBindVertexArray(0);
    ogl->glBindBuffer(GL_ARRAY_BUFFER, 0);
    ogl->glDeleteVertexArrays(1, &surfVAO);
    ogl->glDeleteBuffers(1, &surfVBO);
    ogl->glDeleteProgram(surfShader.program_);
    tmpVert.clear();
}

void OGLWidget::drawGrid ()
{
    GLchar *pathVert = "/home/wolf3w/DiplomOpenGL/vshader.vert",
           *pathFrag = "/home/wolf3w/DiplomOpenGL/fshader.frag";

    Shader gridSh(ogl, pathVert, pathFrag);

    QVector<GLfloat> gridTmp = equation->getGrid();
    GLfloat gridVertices[gridTmp.size()];

    for (GLint i = 0; i < gridTmp.size(); i++)
    {
        gridVertices[i] = gridTmp[i];
    }

    GLuint gridVAO, gridVBO;

    ogl->glGenVertexArrays(1, &gridVAO);
    ogl->glGenBuffers(1, &gridVBO);
    ogl->glBindVertexArray(gridVAO);
    ogl->glBindBuffer(GL_ARRAY_BUFFER, gridVBO);
    ogl->glBufferData(GL_ARRAY_BUFFER, sizeof(gridVertices), gridVertices, GL_STATIC_DRAW);

    ogl->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*) 0);
    ogl->glEnableVertexAttribArray(0);

    glm::mat4 model, view, projection;

    model = glm::mat4(1.f);
    view  = camera->getViewMatrix();
    projection = glm::perspective(45.0f, (GLfloat)width() / (GLfloat)height(), 0.1f, 100.0f);

    GLint modelLoc  = ogl->glGetUniformLocation(gridSh.program_, "model"),
          viewLoc   = ogl->glGetUniformLocation(gridSh.program_, "view"),
          projecLoc = ogl->glGetUniformLocation(gridSh.program_, "projection");

    ogl->glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    ogl->glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    ogl->glUniformMatrix4fv(projecLoc, 1, GL_FALSE, glm::value_ptr(projection));

    glm::vec3 gridColor {0.f, 0.f, 0.f};
    GLint grColorLoc = ogl->glGetUniformLocation(gridSh.program_, "objColor");
    ogl->glUniform3fv(grColorLoc, 1, glm::value_ptr(gridColor));

    ogl->glDrawArrays(GL_LINES, 0, gridTmp.size());
    gridSh.Use();

    ogl->glBindVertexArray(0);
    ogl->glBindBuffer(GL_ARRAY_BUFFER, 0);
    ogl->glDeleteVertexArrays(1, &gridVAO);
    ogl->glDeleteBuffers(1, &gridVBO);
    ogl->glDeleteProgram(gridSh.program_);
    gridTmp.clear();
}
