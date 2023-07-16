#ifndef DICE_VIEW3D_RENDERER_HPP
#define DICE_VIEW3D_RENDERER_HPP

#include <GL/gl.h>

namespace dice::view3d
{

class IRenderable;

class Renderer
{
public:
    Renderer();

    void SetMode(GLenum mode);
    static void SetAspectRatio(float aspectRatio);

    void Render(const std::vector<std::unique_ptr<IRenderable>>& renderables) const;

private:
    static constexpr GLenum sc_defaultMode = GL_FILL;

    static float s_aspectRatio;

    void Render(IRenderable* pRenderable) const;
};

}

#endif