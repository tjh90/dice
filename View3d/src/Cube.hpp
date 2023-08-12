#ifndef DICE_VIEW3D_CUBE_HPP
#define DICE_VIEW3D_CUBE_HPP

#include <glm/vec3.hpp>

#include "IRenderable.hpp"
#include "Shader.hpp"

namespace dice::view3d
{

class Shader;

class Cube : public IRenderable
{
public:
    Cube(const std::shared_ptr<Shader>& pShader, const glm::vec3& centre);
    ~Cube();

    GLsizei GetElementCount() const override;
    std::shared_ptr<Shader> GetShader() override;
    void Bind() const override;

private:
    static constexpr GLint sc_dimensions = 3;
    static constexpr GLsizei sc_stride = 3 * sizeof(float);

    static const std::vector<float> sc_vertices;
    static const std::vector<unsigned int> sc_indices;

    const std::shared_ptr<Shader> m_pShader;

    glm::vec3 m_centre;
    std::vector<float> m_vertices;

    GLuint m_vertexArrayId = 0U;
    GLuint m_vertexBufferId = 0U;
    GLuint m_elementBufferId = 0U;
};

}

#endif