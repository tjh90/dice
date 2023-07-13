#include "pch.hpp"

#include "Renderer.hpp"

#include "IRenderable.hpp"
#include "Shader.hpp"

using namespace dice::view3d;

Renderer::Renderer()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    SetMode(sc_defaultMode);
}

void Renderer::SetMode(GLenum mode)
{
    switch (mode)
    {
        case GL_LINE: // Fallthrough.
        case GL_FILL:
            glPolygonMode(GL_FRONT_AND_BACK, mode);
            break;
        default:
            // Do nothing.
            break;
    }
}

void Renderer::Render(const IRenderable* pRenderable, const Shader& shader) const
{
    if (!pRenderable)
    {
        return;
    }

    glUseProgram(shader.GetShaderProgram());
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, pRenderable->GetElementArrayBuffer());
    glDrawElements(GL_TRIANGLES, pRenderable->GetElementCount(), GL_UNSIGNED_INT, 0);
}
