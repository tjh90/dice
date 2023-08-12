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

    virtual GLuint GetElementArrayBuffer() const = 0;
    virtual GLsizei GetElementCount() const = 0;

    virtual std::shared_ptr<Shader> GetShader() = 0;
};

}

#endif
