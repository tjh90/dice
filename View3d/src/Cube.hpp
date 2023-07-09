#ifndef DICE_VIEW3D_CUBE_HPP
#define DICE_VIEW3D_CUBE_HPP

#include <vector>

#include <glad/glad.h>
#include <GL/gl.h>

namespace dice::view3d
{

struct Point
{
    float x;
    float y;
    float z;

    static void Unpack(const std::vector<Point>& points, std::vector<float>& pointBuffer);
};

class Cube
{
public:
    Cube();
    ~Cube();

    void Render();

private:
    std::vector<Point> m_vertices =
    {
        { -0.5f, -0.5f, 0.0f },
        { 0.5f, -0.5f, 0.0f },
        { 0.5f,  0.5f, 0.0f }
    };

    std::vector<float> m_vertexBuffer;

    std::vector<unsigned int> m_indices =
    {
        0, 1, 2
    };

    GLuint m_vao = 0U;
    GLuint m_vbo = 0U;
    GLuint m_shaderProgram = 0U;
};

}

#endif