#include "pch.hpp"

#include "renderable/ShapeFactory.hpp"

#include "renderable/Shape.hpp"

#include <numbers>

using namespace dice::view3d;
using namespace dice::view3d::renderable;

const std::vector<glm::vec3> ShapeFactory::sc_cubeVertices =
{
    { -0.5f,  0.0f, -0.5f },
    {  0.5f,  0.0f, -0.5f },
    {  0.5f,  1.0f, -0.5f },
    { -0.5f,  1.0f, -0.5f },
    {  0.5f,  1.0f,  0.5f },
    { -0.5f,  1.0f,  0.5f },
    { -0.5f,  0.0f,  0.5f },
    {  0.5f,  0.0f,  0.5f }
};

const std::vector<unsigned int> ShapeFactory::sc_cubeIndices =
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

const std::vector<glm::vec3> ShapeFactory::sc_tetrahedronVertices =
{
    { -0.5f,                 0.0f, -std::sqrt(3.0f)/6.0f },
    {  0.5f,                 0.0f, -std::sqrt(3.0f)/6.0f },
    {  0.0f,                 0.0f,  1.0f/std::sqrt(3.0f) },
    {  0.0f, std::sqrt(6.0f)/3.0f,                  0.0f},
};

const std::vector<unsigned int> ShapeFactory::sc_tetrahedronIndices =
{
    0U, 1U, 2U,
    0U, 1U, 3U,
    0U, 2U, 3U,
    1U, 2U, 3U
};

std::unique_ptr<IRenderable> ShapeFactory::CreateCube(const std::shared_ptr<Shader>& pShader, const glm::vec3& centre)
{
    return std::make_unique<Shape>(pShader, centre, sc_cubeVertices, sc_cubeIndices);
}

std::unique_ptr<IRenderable> ShapeFactory::CreateCylinder(const std::shared_ptr<Shader>& pShader,
                                                          const glm::vec3& centre,
                                                          float radius,
                                                          float height)
{
    unsigned int totalVertexCount = 2 * (1 + sc_cylinderStripCount);

    std::vector<glm::vec3> vertices(totalVertexCount);
    vertices[0] = { 0.0f, 0.0f, 0.0f };
    vertices[1] = { 0.0f, height, 0.0f };

    unsigned int firstRadialVertexOffset = 2U;
    unsigned int aboveFirstRadialVertexOffset = firstRadialVertexOffset + sc_cylinderStripCount;

    float dTheta = 2 * std::numbers::pi / sc_cylinderStripCount;
    float theta = 0.0f;
    for (unsigned int i = 0; i < sc_cylinderStripCount; i++)
    {
        float x = radius * std::cos(theta);
        float z = radius * std::sin(theta);

        vertices[firstRadialVertexOffset + i] = { x, 0.0f, z };
        vertices[aboveFirstRadialVertexOffset + i] = { x, height, z };

        theta += dTheta;
    }

    std::vector<unsigned int> indices;
    for (unsigned int i = 0; i < sc_cylinderStripCount; i++)
    {
        unsigned int thisVertexIndex = firstRadialVertexOffset + i;
        unsigned int nextVertexIndex = firstRadialVertexOffset + (i + 1) % sc_cylinderStripCount;
        unsigned int aboveThisVertexIndex = aboveFirstRadialVertexOffset + i;
        unsigned int aboveNextVertexIndex = aboveFirstRadialVertexOffset + (i + 1) % sc_cylinderStripCount;

        std::vector<unsigned int> sectorIndices =
        {
                           0U,      thisVertexIndex,      nextVertexIndex, // Bottom circle sector.
              thisVertexIndex,      nextVertexIndex, aboveThisVertexIndex, // First vertical.
              nextVertexIndex, aboveThisVertexIndex, aboveNextVertexIndex, // Second vertical.
                           1U, aboveThisVertexIndex, aboveNextVertexIndex  // Top circle sector.
        };
        std::copy(sectorIndices.begin(), sectorIndices.end(), std::back_inserter(indices));
    }

    return std::make_unique<Shape>(pShader, centre, vertices, indices);
}

std::unique_ptr<IRenderable> ShapeFactory::CreateTetrahedron(const std::shared_ptr<Shader>& pShader,
                                                             const glm::vec3& centre)
{
    return std::make_unique<Shape>(pShader, centre, sc_tetrahedronVertices, sc_tetrahedronIndices);
}
