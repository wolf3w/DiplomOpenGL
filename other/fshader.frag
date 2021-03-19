#version 430 core

//in vec3 ourColor;
out vec4 color;
uniform vec3 objColor;

void main()
{
    color = vec4(objColor, 1.0f);
}
