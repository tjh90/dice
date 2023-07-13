#ifndef DICE_VIEW3D_APP_HPP
#define DICE_VIEW3D_APP_HPP

#include <memory>

#include "IRenderable.hpp"
#include "Renderer.hpp"
#include "Shader.hpp"

class GLFWwindow;

namespace dice::view3d
{

class App
{
public:
    explicit App(GLFWwindow* pWnd);

    void RenderLoop();

private:
    GLFWwindow* m_pWnd;

    Renderer m_renderer;

    std::unique_ptr<Shader> m_pShader;
    std::unique_ptr<IRenderable> m_pCube;

    void ProcessInput();
    void Render();
};

}

#endif
