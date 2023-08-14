#include "pch.hpp"

#include "Shader.hpp"

using namespace dice::view3d;

const GLchar* Shader::sc_colourName = "colour";
const GLchar* Shader::sc_projectionName = "projection";
const GLchar* Shader::sc_transformName = "transform";

Shader::Shader(const GLchar* vertexShaderSrc, const GLchar* fragmentShaderSrc)
{
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSrc, nullptr);
    glCompileShader(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSrc, nullptr);
    glCompileShader(fragmentShader);

    // Check for shader compile errors.
    for (GLuint shaderId : { vertexShader, fragmentShader })
    {
        int success = GL_FALSE;
        glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);
        if (success != GL_TRUE)
        {
            throw std::runtime_error("Error compiling shader");
        }
    }

    m_id = glCreateProgram();
    glAttachShader(m_id, vertexShader);
    glAttachShader(m_id, fragmentShader);
    glLinkProgram(m_id);

    // Check for link errors.
    int success = GL_FALSE;
    glGetProgramiv(m_id, GL_LINK_STATUS, &success);
    if (success != GL_TRUE)
    {
        throw std::runtime_error("Error linking shaders");
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

Shader::~Shader()
{
    glDeleteProgram(m_id);
}

GLuint Shader::GetShaderId() const
{
    return m_id;
}

const Colour& Shader::GetColour() const
{
    return m_colour;
}

void Shader::SetColour(const Colour& colour)
{
    m_colour = colour;
}

const glm::mat4& Shader::GetTransform() const
{
    return m_transform;
}

void Shader::SetTransform(const glm::mat4& transform)
{
    m_transform = transform;
}
