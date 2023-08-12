#include "pch.hpp"

#include "Renderer.hpp"

#include "IRenderable.hpp"
#include "Shader.hpp"

using namespace dice::view3d;

float Renderer::s_aspectRatio = 1.0f;

Renderer::Renderer()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);
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

void Renderer::SetAspectRatio(float aspectRatio)
{
    s_aspectRatio = aspectRatio;
}

void Renderer::Render(const std::vector<std::unique_ptr<IRenderable>>& renderables) const
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for (const std::unique_ptr<IRenderable>& pRenderable : renderables)
    {
        Render(pRenderable.get());
    }
}

void Renderer::Render(IRenderable* pRenderable) const
{
    std::shared_ptr<Shader> pShader = pRenderable ? pRenderable->GetShader() : nullptr;
    if (!pShader)
    {
        return;
    }

    GLuint shaderId = pShader->GetShaderId();
    glUseProgram(shaderId);

    // Projection.
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), s_aspectRatio, 0.1f, 100.0f);
    GLint projectionLoc = glGetUniformLocation(shaderId, Shader::sc_projectionName);
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

    // Transform.
    glm::mat4 transform = pShader->GetTransform();
    GLint transformLoc = glGetUniformLocation(shaderId, Shader::sc_transformName);
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, pRenderable->GetElementArrayBuffer());
    glDrawElements(GL_TRIANGLES, pRenderable->GetElementCount(), GL_UNSIGNED_INT, 0);
}
