#ifndef DICE_VIEW3D_RENDERER_HPP
#define DICE_VIEW3D_RENDERER_HPP

#include <GL/gl.h>

namespace dice::view3d
{

class IRenderable;
class Shader;

class Renderer
{
public:
    Renderer();

    void SetMode(GLenum mode);

    void Render(const IRenderable* pRenderable, const Shader& shader) const;

private:
    static constexpr GLenum sc_defaultMode = GL_FILL;
};

}

#endif