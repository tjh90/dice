#include "pch.hpp"

#include "Shape.hpp"

#include "Shader.hpp"

using namespace dice::view3d;
using namespace dice::view3d::renderable;

Shape::Shape(const std::shared_ptr<Shader>& pShader,
             const glm::vec3& centre,
             const std::vector<glm::vec3>& vertices,
             const std::vector<unsigned int>& elementIndices) :
    m_pShader(pShader),
    m_centre(centre),
    m_vertices(vertices),
    m_elementIndices(elementIndices)
{
    // Compute vertices.
    size_t vertexCount = m_vertices.size();
    for (size_t i = 0; i < vertexCount; i++)
    {
        m_vertices[i].x += centre.x;
        m_vertices[i].y += centre.y;
        m_vertices[i].z += centre.z;
    }

    // Define vertex array.
    glGenVertexArrays(1, &m_vertexArrayId);
    glBindVertexArray(m_vertexArrayId);

    // Define vertex buffer.
    glGenBuffers(1, &m_vertexBufferId);
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferId);
    GLsizeiptr bufferSize = m_vertices.size() * sc_dimensions * sizeof(float);
    glBufferData(GL_ARRAY_BUFFER, bufferSize, m_vertices.data(), GL_DYNAMIC_DRAW);

    // Define element buffer.
    glGenBuffers(1, &m_elementBufferId);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_elementBufferId);
    GLsizeiptr elementBufferSize = m_elementIndices.size() * sizeof(unsigned int);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, elementBufferSize, m_elementIndices.data(), GL_DYNAMIC_DRAW);

    // Specify vertex buffer format.
    glVertexAttribPointer(0, sc_dimensions, GL_FLOAT, GL_FALSE, sc_stride, nullptr);
    glEnableVertexAttribArray(0);

    m_isInitialised = true;
}

Shape::~Shape()
{
    glDeleteVertexArrays(1, &m_vertexArrayId);
    glDeleteBuffers(1, &m_vertexBufferId);
    glDeleteBuffers(1, &m_elementBufferId);
}

GLsizei Shape::GetElementCount() const
{
    return m_isInitialised ? static_cast<int>(m_elementIndices.size()) : 0;
}

std::shared_ptr<Shader> Shape::GetShader()
{
    return m_pShader;
}

void Shape::Bind() const
{
    if (m_isInitialised)
    {
        glBindVertexArray(m_vertexArrayId);
        glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferId);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_elementBufferId);
    }
}
