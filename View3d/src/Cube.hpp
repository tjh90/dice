#ifndef DICE_VIEW3D_CUBE_HPP
#define DICE_VIEW3D_CUBE_HPP

#include <glad/glad.h>
#include <GL/gl.h>

#include <vector>

#include "IRenderable.hpp"

namespace dice::view3d
{

class Cube : public IRenderable
{
public:
    Cube();
    ~Cube();

    GLuint GetElementArrayBuffer() const override;
    GLsizei GetElementCount() const override;

private:
    static constexpr GLint sc_dimensions = 3;
    static constexpr GLsizei sc_stride = 3 * sizeof(float);

    std::vector<float> m_vertices =
    {
        -0.5f, -0.5f,  0.0f,
         0.5f, -0.5f,  0.0f,
         0.5f,  0.5f,  0.0f,
        -0.5f,  0.5f,  0.0f
    };

    std::vector<unsigned int> m_indices =
    {
        0U, 1U, 2U, 0U, 2U, 3U
    };

    GLuint m_vertexArray = 0U;
    GLuint m_vertexBuffer = 0U;
    GLuint m_elementArrayBuffer = 0U;
};

}

#endif