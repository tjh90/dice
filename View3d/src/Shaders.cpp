#include "pch.hpp"

#include "Shaders.hpp"

using namespace dice::view3d;

const GLchar* Shaders::sc_vertexShaderSource = "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
        "}\0";
const GLchar* Shaders::sc_fragmentShaderSource = "#version 330 core\n"
        "out vec4 FragColor;\n"
        "void main()\n"
        "{\n"
        "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
        "}\n\0";

const GLchar* Shaders::GetVertexShaderSource()
{
    return sc_vertexShaderSource;
}

const GLchar* Shaders::GetFragmentShaderSource()
{
    return sc_fragmentShaderSource;
}
