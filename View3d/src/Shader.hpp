#ifndef DICE_VIEW3D_SHADER_HPP
#define DICE_VIEW3D_SHADER_HPP

#include <glad/glad.h>
#include <GL/gl.h>
#include <glm/glm.hpp>

namespace dice::view3d
{

class Shader
{
public:
    static const GLchar* sc_colourName;
    static const GLchar* sc_projectionName;
    static const GLchar* sc_transformName;

    Shader(const GLchar* vertexShaderSrc, const GLchar* fragmentShaderSrc);
    Shader(const Shader& other) = delete;
    ~Shader();

    Shader& operator=(const Shader& other) = delete;

    GLuint GetShaderId() const;

    const Colour& GetColour() const;
    void SetColour(const Colour& colour);

    const glm::mat4& GetTransform() const;
    void SetTransform(const glm::mat4& transform);

private:
    GLuint m_id = 0U;

    glm::vec4 m_colour { 1.0f };

    glm::mat4 m_projection { 1.0f };
    glm::mat4 m_transform { 1.0f };

    static float NormaliseColour(unsigned int pixel);
};

}

#endif
