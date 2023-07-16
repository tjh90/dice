#ifndef DICE_VIEW3D_CAMERA_HPP
#define DICE_VIEW3D_CAMERA_HPP

#include <glm/vec3.hpp>

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

    glm::mat4 GetView() const;

private:
    static const glm::vec3 sc_left;
    static const glm::vec3 sc_up;
    static const glm::vec3 sc_front;
    static const std::unordered_map<Direction, glm::vec3> sc_directionMap;

    glm::vec3 m_pos { 0.0f, 0.0f, 3.0f };

    float m_speed = 0.01f;
};

}

#endif
