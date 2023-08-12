#include "pch.hpp"

#include "Cube.hpp"

#include "Shader.hpp"

using namespace dice::view3d;

const std::vector<float> Cube::sc_vertices =
{
    -1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,
     1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f,
     1.0f, -1.0f,  1.0f
};

const std::vector<unsigned int> Cube::sc_indices =
{
    0U, 1U, 2U,
    0U, 2U, 3U,
    0U, 3U, 5U,
    0U, 5U, 6U,
    0U, 1U, 7U,
    0U, 6U, 7U,
    4U, 1U, 2U,
    4U, 1U, 7U,
    4U, 2U, 3U,
    4U, 3U, 5U,
    4U, 5U, 6U,
    4U, 6U, 7U
};

Cube::Cube(const std::shared_ptr<Shader>& pShader, const glm::vec3& centre) :
    m_pShader(pShader),
    m_centre(centre),
    m_vertices(sc_vertices)
{
    // Compute cube vertices.
    size_t vertexCount = m_vertices.size();
    for (size_t i = 0; i < vertexCount; i++)
    {
        switch (i % sc_dimensions)
        {
            case 0:
                m_vertices[i] += m_centre.x;
                break;
            case 1:
                m_vertices[i] += m_centre.y;
                break;
            case 2:
                m_vertices[i] += m_centre.z;
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
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sc_indices.size() * sizeof(unsigned int), sc_indices.data(), GL_DYNAMIC_DRAW);

    // Specify vertex buffer format.
    glVertexAttribPointer(0, sc_dimensions, GL_FLOAT, GL_FALSE, sc_stride, nullptr);
    glEnableVertexAttribArray(0);
}

Cube::~Cube()
{
    glDeleteVertexArrays(1, &m_vertexArrayId);
    glDeleteBuffers(1, &m_vertexBufferId);
    glDeleteBuffers(1, &m_elementBufferId);
}

GLsizei Cube::GetElementCount() const
{
    return static_cast<int>(sc_indices.size());
}

std::shared_ptr<Shader> Cube::GetShader()
{
    return m_pShader;
}

void Cube::Bind() const
{
    glBindVertexArray(m_vertexArrayId);
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferId);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_elementBufferId);
}
