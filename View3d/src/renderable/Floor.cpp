#include "pch.hpp"

#include "renderable/Floor.hpp"

#include "Shader.hpp"

#include "renderable/Shape.hpp"

using namespace dice::view3d::renderable;

const std::vector<glm::vec3> Floor::sc_vertices =
{
    { -1000.0f,  0.0f, -1000.0f },
    {  1000.0f,  0.0f, -1000.0f },
    {  1000.0f,  0.0f,  1000.0f },
    {  -1000.0f,  0.0f, 1000.0f }
};

const std::vector<unsigned int> Floor::sc_indices =
{
    0U, 1U, 2U,
    0U, 2U, 3U
};

Floor::Floor(const std::shared_ptr<Shader>& pShader, const glm::vec3& centre) :
    Shape(pShader, centre, sc_vertices, sc_indices)
{
}
