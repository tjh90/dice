#ifndef DICE_VIEW3D_RENDERABLE_SHAPE_HPP
#define DICE_VIEW3D_RENDERABLE_SHAPE_HPP

#include <glm/vec3.hpp>

#include "Shader.hpp"

#include "renderable/IRenderable.hpp"

namespace dice::view3d
{

class Shader;

namespace renderable
{

class Shape : public IRenderable
{
public:
    Shape(const std::shared_ptr<Shader>& pShader,
          const glm::vec3& centre,
          const std::vector<float>& vertices,
          const std::vector<unsigned int>& elementIndices);
    virtual ~Shape();

    GLsizei GetElementCount() const override;
    std::shared_ptr<Shader> GetShader() override;
    void Bind() const override;

protected:
    static constexpr GLint sc_dimensions = 3;
    static constexpr GLsizei sc_stride = 3 * sizeof(float);

    void Initialise(const std::vector<float>& vertices, const std::vector<unsigned int>& elementIndices);

private:
    const std::shared_ptr<Shader> m_pShader;

    glm::vec3 m_centre;
    std::vector<float> m_vertices;
    std::vector<unsigned int> m_elementIndices;
    bool m_isInitialised = false;

    GLuint m_vertexArrayId = 0U;
    GLuint m_vertexBufferId = 0U;
    GLuint m_elementBufferId = 0U;
};

}
}

#endif