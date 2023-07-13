#ifndef DICE_VIEW3D_SHADERS_HPP
#define DICE_VIEW3D_SHADERS_HPP

#include <glad/glad.h>

namespace dice::view3d
{

class Shaders
{
public:
    static const GLchar* GetVertexShaderSource();
    static const GLchar* GetFragmentShaderSource();

private:
    static const GLchar* sc_vertexShaderSource;
    static const GLchar* sc_fragmentShaderSource;

    Shaders() = delete;
};

}

#endif