#ifndef DICE_VIEW3D_APP_HPP
#define DICE_VIEW3D_APP_HPP

#include <memory>

class GLFWwindow;

namespace dice::view3d
{

class Cube;

class App
{
public:
    App();
    ~App();

    void RenderLoop();

private:
    static constexpr int sc_openGlMajorVersion = 4;
    static constexpr int sc_openGlMinorVersion = 6;

    static constexpr int sc_viewportSizeX = 1024;
    static constexpr int sc_viewportSizeY = 768;

    GLFWwindow* m_pWnd = nullptr;

    std::unique_ptr<Cube> m_pCube;

    void ProcessInput();
    void Render();
};

}

#endif
