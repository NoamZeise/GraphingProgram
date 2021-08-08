#version 330 core
in vec2 TexCoords;
out vec4 colour;

uniform vec3 spriteColour;

void main()
{
    colour = vec4(spriteColour, 1.0);
}