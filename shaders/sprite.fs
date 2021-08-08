#version 330 core
in vec2 TexCoords;
out vec4 colour;

uniform sampler2D image;
uniform vec3 spriteColour;
uniform bool enableTexture;

void main()
{
    if(enableTexture)
        colour = vec4(spriteColour, 1.0) * texture(image, TexCoords);
    else
        colour = vec4(spriteColour, 1.0);
}