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

void Shader::SetColour(unsigned int r, unsigned int g, unsigned int b)
{
    m_colour = { NormaliseColour(r), NormaliseColour(g), NormaliseColour(b), 1.0f };
}

float Shader::NormaliseColour(unsigned int pixel)
{
    return (pixel % 256) / 256;
}

const glm::mat4& Shader::GetProjection() const
{
    return m_projection;
}

void Shader::SetProjection(const glm::mat4& projection)
{
    m_projection = projection;
}

const glm::mat4& Shader::GetTransform() const
{
    return m_transform;
}

void Shader::SetTransform(const glm::mat4& transform)
{
    m_transform = transform;
}
