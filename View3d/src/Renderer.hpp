#ifndef DICE_VIEW3D_RENDERER_HPP
#define DICE_VIEW3D_RENDERER_HPP

#include <GL/gl.h>

namespace dice::view3d
{

namespace renderable
{
class IRenderable;
}

class Renderer
{
public:
    static void Setup();
    static void SetMode(GLenum mode);
    static void ToggleMode();
    static void SetAspectRatio(float aspectRatio);

    static void Render(const std::vector<std::unique_ptr<renderable::IRenderable>>& renderables);

private:
    static constexpr GLenum sc_defaultMode = GL_FILL;

    static float s_aspectRatio;

    Renderer() = delete;

    static void Render(renderable::IRenderable* pRenderable);
};

}

#endif