#version 460 core

uniform vec4 colour = vec4(1.0f, 0.0f, 1.0f, 1.0f);

out vec4 FragmentColour;

void main()
{
   FragmentColour = colour;
};
