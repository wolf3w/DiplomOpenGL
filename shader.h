#ifndef SHADER_H
#define SHADER_H

#include <fstream>
#include <sstream>
#include <iostream>
#include <QOpenGLFunctions_4_3_Core>

class Shader
{
private:
    QOpenGLFunctions_4_3_Core *ogl_;

public:
    GLuint program_;
    /* Конструктор шейдера */
    /* argFun - инициализированные функции OGL для Qt */
    /* vertPath - путь до кода с вершинным шейдером */
    /* fragPath - путь до кода с фрагментным шейдером */
    Shader (QOpenGLFunctions_4_3_Core *argFun, const GLchar* vertPath,
            const GLchar* fragPath);

    /* Используем программу */
    void Use ();
};

#endif // SHADER_H
