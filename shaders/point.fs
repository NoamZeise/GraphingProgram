#version 330 core

out vec4 colour;

uniform vec3 spriteColour;

void main()
{
    colour = vec4(spriteColour, 1.0);
}