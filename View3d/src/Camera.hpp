#ifndef DICE_VIEW3D_CAMERA_HPP
#define DICE_VIEW3D_CAMERA_HPP

#include <glm/vec3.hpp>

#include <memory>

namespace dice::view3d
{

class Camera
{
public:
    enum class Direction
    {
        UP,
        DOWN,
        LEFT,
        RIGHT,
        FORWARD,
        BACK
    };

    void Move(const std::vector<Direction>& directions);

    static void ChangeSpeedFactor(bool increaseSpeed);

    glm::mat4 GetView() const;

private:
    static constexpr float sc_speedIncrement = 1.0f;
    static float s_speedFactor;

    glm::vec3 m_left { 1.0f, 0.0f, 0.0f };
    glm::vec3 m_up { 0.0f, 1.0f, 0.0f };
    glm::vec3 m_front { 0.0f, 0.0f, 1.0f };

    glm::vec3 m_pos { 0.0f, 0.5f, -3.0f };
};

}

#endif
