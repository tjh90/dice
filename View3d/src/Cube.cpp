#include "pch.hpp"

#include "Cube.hpp"

#include "Shader.hpp"

using namespace dice::view3d;

Cube::Cube(const std::weak_ptr<Shader>& pShader) :
    m_pShader(pShader)
{
    // Define vertex array.
    glGenVertexArrays(1, &m_vertexArray);
    glBindVertexArray(m_vertexArray);

    // Define vertex buffer.
    glGenBuffers(1, &m_vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(float), m_vertices.data(), GL_DYNAMIC_DRAW);

    // Define element buffer.
    glGenBuffers(1, &m_elementArrayBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_elementArrayBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(unsigned int), m_indices.data(), GL_DYNAMIC_DRAW);

    // Specify vertex buffer format.
    glVertexAttribPointer(0, sc_dimensions, GL_FLOAT, GL_FALSE, sc_stride, nullptr);
    glEnableVertexAttribArray(0);
}

Cube::~Cube()
{
    glDeleteVertexArrays(1, &m_vertexArray);
    glDeleteBuffers(1, &m_vertexBuffer);
    glDeleteBuffers(1, &m_elementArrayBuffer);
}

GLuint Cube::GetElementArrayBuffer() const
{
    return m_elementArrayBuffer;
}

GLsizei Cube::GetElementCount() const
{
    return static_cast<int>(m_indices.size());
}

std::weak_ptr<Shader> Cube::GetShader() const
{
    return m_pShader;
}
