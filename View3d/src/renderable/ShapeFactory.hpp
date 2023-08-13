#ifndef DICE_VIEW3D_RENDERABLE_SHAPEFACTORY_HPP
#define DICE_VIEW3D_RENDERABLE_SHAPEFACTORY_HPP

#include <glm/vec3.hpp>

#include "renderable/Shape.hpp"

#include <memory>
#include <vector>

namespace dice::view3d
{

class Shader;

namespace renderable
{

class ShapeFactory
{
public:
    static std::unique_ptr<IRenderable> CreateCube(const std::shared_ptr<Shader>& pShader,
                                                   const glm::vec3& centre);
    static std::unique_ptr<IRenderable> CreateCylinder(const std::shared_ptr<Shader>& pShader,
                                                       const glm::vec3& centre,
                                                       float radius,
                                                       float height);
    static std::unique_ptr<IRenderable> CreateTetrahedron(const std::shared_ptr<Shader>& pShader,
                                                          const glm::vec3& centre);

private:
    static const std::vector<glm::vec3> sc_cubeVertices;
    static const std::vector<unsigned int> sc_cubeIndices;

    static const std::vector<glm::vec3> sc_tetrahedronVertices;
    static const std::vector<unsigned int> sc_tetrahedronIndices;

    static constexpr unsigned int sc_cylinderStripCount = 100U;

    ShapeFactory() = delete;
};

}
}

#endif