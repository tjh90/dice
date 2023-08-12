#ifndef DICE_VIEW3D_APP_HPP
#define DICE_VIEW3D_APP_HPP

#include "Camera.hpp"
#include "Renderer.hpp"

#include "renderable/IRenderable.hpp"

class GLFWwindow;

namespace dice::view3d
{

class App
{
public:
    explicit App(GLFWwindow* pWnd, int width, int height);

    void RenderLoop();

private:
    GLFWwindow* m_pWnd;
    Renderer m_renderer;

    std::vector<std::unique_ptr<renderable::IRenderable>> m_renderables;

    Camera m_camera;

    static void ResizeCallback(GLFWwindow*, int width, int height);
    static void KeyboardCallback(GLFWwindow* window, int key, int, int action, int);

    void ProcessInput();
    void Render();
};

}

#endif
