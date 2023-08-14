#include "pch.hpp"

#include "App.hpp"

#include "Shader.hpp"
#include "ShaderFactory.hpp"
#include "Timer.hpp"

#include "renderable/Floor.hpp"
#include "renderable/ShapeFactory.hpp"

using namespace dice::view3d;
using namespace dice::view3d::renderable;

#ifdef DEBUG
std::ofstream g_log = std::ofstream("./log.log");
void LogCallback(GLenum source,
                 GLenum type,
                 GLuint id,
                 GLenum severity,
                 GLsizei length,
                 const GLchar* msg,
                 const void* userParam);
#endif

App::App(GLFWwindow* pWnd, int width, int height) :
    m_pWnd(pWnd)
{
#ifdef DEBUG
    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(LogCallback, 0);
#endif

    // Set up viewport size with a callback.
    glfwSetFramebufferSizeCallback(pWnd, ResizeCallback);
    ResizeCallback(pWnd, width, height);

    // Set up keyboard callback.
    glfwSetKeyCallback(pWnd, KeyboardCallback);

    Renderer::Setup();

    // Create floor.
    ShaderFactory shaderFactory;
    Colour floorColour = ShaderFactory::CreateColour(8U, 32U, 8U);
    std::shared_ptr<Shader> pFloorShader = shaderFactory.CreateSimpleShader(&floorColour);
    std::unique_ptr<IRenderable> pFloor = std::make_unique<Floor>(pFloorShader, glm::vec3 { 0.0f });
    m_renderables.push_back(std::move(pFloor));

    // Create cubes.
    std::vector<Colour> cubeColours =
    {
        ShaderFactory::CreateColour(128U, 0U, 0U),
        ShaderFactory::CreateColour(0U, 128, 0U)
    };
    std::vector<glm::vec3> cubeCentres = { { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 4.0f } };
    size_t count = std::min(cubeColours.size(), cubeCentres.size());
    for (size_t i = 0; i < count; i++)
    {
        std::shared_ptr<Shader> pCubeShader = shaderFactory.CreateSimpleShader(&cubeColours[i]);
        std::unique_ptr<IRenderable> pCube = ShapeFactory::CreateCube(pCubeShader, cubeCentres[i]);
        m_renderables.push_back(std::move(pCube));
    }

    // Create tetrahedron.
    Colour tetrahedronColour = ShaderFactory::CreateColour(0U, 0U, 128U);
    std::shared_ptr<Shader> pTetrahedronShader = shaderFactory.CreateSimpleShader(&tetrahedronColour);
    std::unique_ptr<IRenderable> pTetrahedron = ShapeFactory::CreateTetrahedron(pTetrahedronShader,
                                                                                glm::vec3 { 2.0f, 0.0f, 2.0f });
    m_renderables.push_back(std::move(pTetrahedron));

    // Create cylinder.
    Colour cylinderColour = ShaderFactory::CreateColour(192U, 128U, 0U);
    std::shared_ptr<Shader> pCylinderShader = shaderFactory.CreateSimpleShader(&cylinderColour);
    std::unique_ptr<IRenderable> pCylinder = ShapeFactory::CreateCylinder(pCylinderShader,
                                                                          glm::vec3 { -2.0f, 0.0f, 2.0f },
                                                                          0.5f,
                                                                          0.5f);
    m_renderables.push_back(std::move(pCylinder));
}

void App::ResizeCallback(GLFWwindow*, int width, int height)
{
    Renderer::SetAspectRatio((1.0f * width) / height);
    glViewport(0, 0, width, height);
}

void App::KeyboardCallback(GLFWwindow* pWnd, int key, int, int action, int)
{
    bool isPressed = GLFW_PRESS == action;
    if (isPressed)
    {
        switch(key)
        {
            case GLFW_KEY_ESCAPE:
                glfwSetWindowShouldClose(pWnd, true);
                break;
            case GLFW_KEY_SPACE:
                glClearColor(0.5f, 1.0f, 1.0f, 1.0f);
                break;
            case GLFW_KEY_M:
                Renderer::ToggleMode();
                break;
            case GLFW_KEY_EQUAL:
                Camera::ChangeSpeedFactor(true);
                break;
            case GLFW_KEY_MINUS:
                Camera::ChangeSpeedFactor(false);
                break;
            default:
                break;
        }
    }
}

void App::RenderLoop()
{
    while (!glfwWindowShouldClose(m_pWnd))
    {
        Timer::GetInstance().Update();

        ProcessInput();

        Renderer::Render(m_renderables);

        glfwSwapBuffers(m_pWnd);
        glfwPollEvents();
    }
}

void App::ProcessInput()
{
    // Movement.
    std::vector<Camera::Direction> directions;
    if (GLFW_PRESS == glfwGetKey(m_pWnd, GLFW_KEY_W))
    {
        directions.push_back(Camera::Direction::FORWARD);
    }
    if (GLFW_PRESS == glfwGetKey(m_pWnd, GLFW_KEY_S))
    {
        directions.push_back(Camera::Direction::BACK);
    }
    if (GLFW_PRESS == glfwGetKey(m_pWnd, GLFW_KEY_A))
    {
        directions.push_back(Camera::Direction::LEFT);
    }
    if (GLFW_PRESS == glfwGetKey(m_pWnd, GLFW_KEY_D))
    {
        directions.push_back(Camera::Direction::RIGHT);
    }
    if (GLFW_PRESS == glfwGetKey(m_pWnd, GLFW_KEY_E))
    {
        directions.push_back(Camera::Direction::UP);
    }
    if (GLFW_PRESS == glfwGetKey(m_pWnd, GLFW_KEY_Q))
    {
        directions.push_back(Camera::Direction::DOWN);
    }
    m_camera.Move(directions);

    glm::mat4 view = m_camera.GetView();
    for (const auto& pRenderable : m_renderables)
    {
        std::shared_ptr<Shader> pShader = pRenderable ? pRenderable->GetShader() : nullptr;
        if (pShader)
        {
            pShader->SetTransform(view);
        }
    }
}

#ifdef DEBUG
void LogCallback(GLenum,
                 GLenum type,
                 GLuint,
                 GLenum severity,
                 GLsizei,
                 const GLchar* msg,
                 const void*)
{
    std::string severityStr;
    switch(severity)
    {
        case GL_DEBUG_SEVERITY_HIGH:
            severityStr = "HIGH";
            break;
        case GL_DEBUG_SEVERITY_MEDIUM:
            severityStr = "MED";
            break;
        case GL_DEBUG_SEVERITY_LOW:
            severityStr = "LOW";
            break;
        case GL_DEBUG_SEVERITY_NOTIFICATION:
            severityStr = "INFO";
            break;
        default:
            severityStr = "UNKNOWN";
            break;
    }

    std::string typeStr;
    switch(type)
    {
        case GL_DEBUG_TYPE_ERROR:
            typeStr = "ERROR";
            break;
        case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
            typeStr = "DEPRECATED";
            break;
        case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
            typeStr = "UB";
            break;
        case GL_DEBUG_TYPE_PERFORMANCE:
            typeStr = "PERFORMANCE";
            break;
        default:
            typeStr = "OTHER";
            break;
    }

    g_log << "[" << severityStr << "] <<" << typeStr << ">>    " << msg << std::endl;
}
#endif
