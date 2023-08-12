#ifndef DICE_VIEW3D_IRENDERABLE_HPP
#define DICE_VIEW3D_IRENDERABLE_HPP

#include <GL/gl.h>

namespace dice::view3d
{

class Shader;

class IRenderable
{
public:
    ~IRenderable() = default;

    virtual GLsizei GetElementCount() const = 0;
    virtual std::shared_ptr<Shader> GetShader() = 0;

    virtual void Bind() const = 0;
};

}

#endif
