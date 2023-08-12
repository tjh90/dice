#include "pch.hpp"

#include "renderable/Tetrahedron.hpp"

#include "Shader.hpp"

#include "renderable/Shape.hpp"

using namespace dice::view3d::renderable;

const std::vector<float> Tetrahedron::sc_vertices =
{
    -0.5f,                 0.0f, -std::sqrt(3.0f)/6.0f,
     0.5f,                 0.0f, -std::sqrt(3.0f)/6.0f,
     0.0f,                 0.0f,  1.0f/std::sqrt(3.0f),
     0.0f, std::sqrt(6.0f)/3.0f,                  0.0f
};

const std::vector<unsigned int> Tetrahedron::sc_indices =
{
    0U, 1U, 2U,
    0U, 1U, 3U,
    0U, 2U, 3U,
    1U, 2U, 3U
};

Tetrahedron::Tetrahedron(const std::shared_ptr<Shader>& pShader, const glm::vec3& centre) :
    Shape(pShader, centre, sc_vertices, sc_indices)
{
}
