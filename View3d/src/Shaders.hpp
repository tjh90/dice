#ifndef DICE_VIEW3D_SHADERS_HPP
#define DICE_VIEW3D_SHADERS_HPP

#include <filesystem>
#include <memory>

namespace dice::view3d
{

class Shader;

class Shaders
{
public:
    static Shaders* GetInstance();

    std::weak_ptr<Shader> GetCubeShader();

private:
    static const std::filesystem::path sc_cubeVertexShaderPath;
    static const std::filesystem::path sc_cubeFragmentShaderPath;

    static std::unique_ptr<Shaders> sc_pInstance;

    std::unordered_map<std::filesystem::path, std::string> m_shaderPathMap = { };

    Shaders() = default;

    const GLchar* LoadShader(const std::filesystem::path& shaderPath);

    std::shared_ptr<Shader> m_pCubeShader;
};

}

#endif