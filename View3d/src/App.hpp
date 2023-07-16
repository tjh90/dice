#ifndef DICE_VIEW3D_APP_HPP
#define DICE_VIEW3D_APP_HPP

#include "Camera.hpp"
#include "IRenderable.hpp"
#include "Renderer.hpp"

class GLFWwindow;

namespace dice::view3d
{

class Shaders;

class App
{
public:
    explicit App(GLFWwindow* pWnd, int width, int height);

    void RenderLoop();

private:
    GLFWwindow* m_pWnd;
    Renderer m_renderer;
    Shaders* m_pShaders;

    std::vector<std::unique_ptr<IRenderable>> m_renderables;

    Camera m_camera;

    static void ResizeCallback(GLFWwindow*, int width, int height);

    void ProcessInput();
    void Render();
};

}

#endif
