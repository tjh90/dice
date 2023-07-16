#ifndef DICE_VIEW3D_APP_HPP
#define DICE_VIEW3D_APP_HPP

#include "IRenderable.hpp"
#include "Renderer.hpp"

class GLFWwindow;

namespace dice::view3d
{

class Shaders;

class App
{
public:
    explicit App(GLFWwindow* pWnd);

    void RenderLoop();

private:
    GLFWwindow* m_pWnd;
    Shaders* m_pShaders;

    Renderer m_renderer;
    std::vector<std::unique_ptr<IRenderable>> m_renderables;

    void ProcessInput();
    void Render();
};

}

#endif
