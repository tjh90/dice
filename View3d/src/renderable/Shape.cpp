#include "pch.hpp"

#include "Shape.hpp"

#include "Shader.hpp"

using namespace dice::view3d;
using namespace dice::view3d::renderable;

Shape::Shape(const std::shared_ptr<Shader>& pShader,
             const glm::vec3& centre,
             const std::vector<float>& vertices,
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
        switch (i % sc_dimensions)
        {
            case 0:
                m_vertices[i] += centre.x;
                break;
            case 1:
                m_vertices[i] += centre.y;
                break;
            case 2:
                m_vertices[i] += centre.z;
                break;
        }
    }

    // Define vertex array.
    glGenVertexArrays(1, &m_vertexArrayId);
    glBindVertexArray(m_vertexArrayId);

    // Define vertex buffer.
    glGenBuffers(1, &m_vertexBufferId);
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferId);
    glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(float), m_vertices.data(), GL_DYNAMIC_DRAW);

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
