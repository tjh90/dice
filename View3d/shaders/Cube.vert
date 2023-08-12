#version 460 core

layout (location = 0) in vec3 position;

uniform mat4 projection;
uniform mat4 transform;

void main()
{
   gl_Position = projection * transform * vec4(position.x, position.y, position.z, 1.0f);
};
