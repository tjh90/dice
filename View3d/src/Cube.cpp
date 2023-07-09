#include "Cube.hpp"

#include <stdexcept>

using namespace dice::view3d;

void Point::Unpack(const std::vector<Point>& points, std::vector<float>& pointBuffer)
{
    size_t pointsCount = points.size();
    std::vector<float> buff(3 * pointsCount);
    for (size_t i = 0; i < pointsCount; i += 3)
    {
        const Point& point = points[i];
        pointBuffer[i] = point.x;
        pointBuffer[i + 1] = point.y;
        pointBuffer[i + 2] = point.z;
    }
}

const char* vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";
const char* fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\n\0";

Cube::Cube() :
    m_vertexBuffer(m_vertices.size())
{
    // Vertex shader.
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);

    // Fragment shader.
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);

    GLint success = 0;

    // Create shader program and add shaders.
    m_shaderProgram = glCreateProgram();
    std::vector<GLuint> shaders = { vertexShader, fragmentShader };
    for (GLuint shader : shaders)
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (GL_TRUE != success)
        {
            GLsizei logLength = 0;
            GLchar errMsg[1024];
            glGetShaderInfoLog(shader, 1024, &logLength, errMsg);
            throw new std::runtime_error(errMsg);
        }

        glAttachShader(m_shaderProgram, shader);
    }

    glLinkProgram(m_shaderProgram);
    glGetProgramiv(m_shaderProgram, GL_LINK_STATUS, &success);
    if (GL_TRUE != success)
    {
        GLsizei logLength = 0;
        GLchar errMsg[1024];
        glGetProgramInfoLog(m_shaderProgram, 1024, &logLength, errMsg);
        throw new std::runtime_error(errMsg);
    }

    //for (GLuint shader : shaders)
    //{
    //    glDeleteShader(shader);
    //}

    float vertices[] = {
        -0.5f, -0.5f, 0.0f, // left
         0.5f, -0.5f, 0.0f, // right
         0.0f,  0.5f, 0.0f  // top
    };

    glGenVertexArrays(1, &m_vao);
    glGenBuffers(1, &m_vbo);
    glBindVertexArray(m_vao);

    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    //Point::Unpack(m_vertices, m_vertexBuffer);

    glBufferData(GL_ARRAY_BUFFER, m_vertexBuffer.size() * sizeof(float), vertices, GL_STATIC_DRAW);

    // Specify vertex buffer format.
    glUseProgram(m_shaderProgram);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
}

Cube::~Cube()
{
    glDeleteVertexArrays(1, &m_vao);
    glDeleteBuffers(1, &m_vbo);
    glDeleteProgram(m_shaderProgram);
}

void Cube::Render()
{
    glBindVertexArray(m_vao);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}
