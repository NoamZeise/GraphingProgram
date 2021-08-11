#version 330 core
in vec2 TexCoords;
out vec4 colour;

uniform sampler2D image;
uniform vec3 spriteColour;
uniform bool enableTexture;
uniform bool enableFont;

void main()
{
    if(enableTexture)
        colour = vec4(spriteColour, 1.0) * texture(image, TexCoords);
    else if(enableFont)
        {
           vec4 sampled = vec4(1.0, 1.0, 1.0, texture(image, TexCoords).r);
          colour = vec4(spriteColour, 1.0) * sampled;
        }
    else
        colour = vec4(spriteColour, 1.0);
}