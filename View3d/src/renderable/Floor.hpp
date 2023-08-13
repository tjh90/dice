#ifndef DICE_VIEW3D_RENDERABLE_FLOOR_HPP
#define DICE_VIEW3D_RENDERABLE_FLOOR_HPP

#include <glm/vec3.hpp>

#include "Shader.hpp"

#include "renderable/Shape.hpp"

namespace dice::view3d::renderable
{

class Floor : public Shape
{
public:
    Floor(const std::shared_ptr<Shader>& pShader, const glm::vec3& centre);
private:
    static const std::vector<glm::vec3> sc_vertices;
    static const std::vector<unsigned int> sc_indices;
};

}

#endif