#include "pch.hpp"

#include "renderable/Cube.hpp"

#include "Shader.hpp"

#include "renderable/Shape.hpp"

using namespace dice::view3d::renderable;

const std::vector<float> Cube::sc_vertices =
{
    -0.5f,  0.0f, -0.5f,
     0.5f,  0.0f, -0.5f,
     0.5f,  1.0f, -0.5f,
    -0.5f,  1.0f, -0.5f,
     0.5f,  1.0f,  0.5f,
    -0.5f,  1.0f,  0.5f,
    -0.5f,  0.0f,  0.5f,
     0.5f,  0.0f,  0.5f
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
    Shape(pShader, centre, sc_vertices, sc_indices)
{
}
