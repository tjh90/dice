#ifndef DICE_VIEW3D_SHADER_HPP
#define DICE_VIEW3D_SHADER_HPP

#include <glad/glad.h>
#include <GL/gl.h>

namespace dice::view3d
{

class Shader
{
public:
    Shader(const GLchar* vertexShaderSrc, const GLchar* fragmentShaderSrc);
    ~Shader();

    GLuint GetShaderProgram() const;

private:
    GLuint m_shaderProgram = 0U;
};

}

#endif
