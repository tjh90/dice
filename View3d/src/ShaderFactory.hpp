#ifndef DICE_VIEW3D_SHADERS_HPP
#define DICE_VIEW3D_SHADERS_HPP

#include <filesystem>
#include <memory>

namespace dice::view3d
{

class Shader;

class ShaderFactory
{
public:
    std::shared_ptr<Shader> CreateCubeShader();

private:
    static const std::filesystem::path sc_cubeVertexShaderPath;
    static const std::filesystem::path sc_cubeFragmentShaderPath;

    std::unordered_map<std::filesystem::path, std::string> m_shaderPathMap = { };

    const GLchar* LoadShader(const std::filesystem::path& shaderPath);
};

}

#endif