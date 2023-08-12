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
    static Colour CreateColour(unsigned int r, unsigned int g, unsigned int b);

    std::shared_ptr<Shader> CreateCubeShader(const Colour* pColour = nullptr);

private:
    static constexpr Colour sc_defaultColour = { 0.75, 0.75 , 0.75, 1.0 };

    static const std::filesystem::path sc_cubeVertexShaderPath;
    static const std::filesystem::path sc_cubeFragmentShaderPath;

    std::unordered_map<std::filesystem::path, std::string> m_shaderPathMap = { };

    static float NormaliseColour(unsigned int pixel);

    const GLchar* LoadShader(const std::filesystem::path& shaderPath);
};

}

#endif