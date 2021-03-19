#include "headers/shader.h"

Shader::Shader (QOpenGLFunctions_4_3_Core* argFun,
                const GLchar* vertPath, const GLchar* fragPath)
{
    /* Инициализация функций */
    ogl_ = argFun;

    std::string vertTmpCode, fragTmpCode;
    std::ifstream vShaderFile, fShaderFile;

    /* Проверка файлов на исключения */
    vShaderFile.exceptions(std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::badbit);

    try
    {
        vShaderFile.open(vertPath);
        fShaderFile.open(fragPath);
        /* Создаем потоки для считывания */
        std::stringstream vShaderStream, fShaderStream;
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        /* Закроем файлы */
        vShaderFile.close();
        fShaderFile.close();
        /* Конвертируем из потока в строку */
        vertTmpCode = vShaderStream.str();
        fragTmpCode = fShaderStream.str();
    }
    catch (std::ifstream::failure e)
    {
        std::cout << "[Считывание шейдеров]: Ошибка" << std::endl;
    }

    /* Перевод из string в GLchar* */
    const GLchar *vertCode = vertTmpCode.c_str(),
                 *fragCode = fragTmpCode.c_str();

    /* Компиляция шейдеров и программы */
    GLuint vertex, fragment;
    GLint succes;
    GLchar info[512];

    /* Компилируем вершинный шейдер */
    vertex = ogl_->glCreateShader(GL_VERTEX_SHADER);
    ogl_->glShaderSource(vertex, 1, &vertCode, nullptr);
    ogl_->glCompileShader(vertex);

    /* Проверка на ошибки при компиляции верш. шейдера */
    ogl_->glGetShaderiv(vertex, GL_COMPILE_STATUS, &succes);
    if (!succes)
    {
        ogl_->glGetShaderInfoLog(vertex, 512, nullptr, info);
        std::cout << "Vertex Shader Error: " << info << std::endl;
    }

    /* Теперь фрагментый шейдер */
    fragment = ogl_->glCreateShader(GL_FRAGMENT_SHADER);
    ogl_->glShaderSource(fragment, 1, &fragCode, nullptr);
    ogl_->glCompileShader(fragment);

    /* Проверка на ошибки при компиляции */
    ogl_->glGetShaderiv(fragment, GL_COMPILE_STATUS, &succes);
    if (!succes)
    {
        ogl_->glGetShaderInfoLog(fragment, 512, nullptr, info);
        std::cout << "Fragment Shader Error: " << info << std::endl;
    }

    /* Создаем шейдерную программу */
    program_ = ogl_->glCreateProgram();
    /* Привяжем к программе шейдеры */
    ogl_->glAttachShader(program_, vertex);
    ogl_->glAttachShader(program_, fragment);
    ogl_->glLinkProgram(program_);

    /* Удалим шейдеры, т.к. уже привязаны к программе */
    ogl_->glDeleteShader(vertex);
    ogl_->glDeleteShader(fragment);
}

void Shader::Use()
{
    ogl_->glUseProgram(program_);
}
