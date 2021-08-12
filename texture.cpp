#include "texture.h"

Texture::Texture(const char* path)
{
	Wrap_S = GL_REPEAT;
	Wrap_T = GL_REPEAT;
	Format = GL_RGB;
	glGenTextures(1, &ID);
	int nrChannels;
	unsigned char* data = stbi_load(path, &Width, &Height, &nrChannels, 0);
	if (!data)
	{
		stbi_image_free(data);
		std::cout << "failed to load texture at " << path << std::endl;
		return;
	}
	if (nrChannels == 1)
		Format = GL_RED;
	else if (nrChannels == 3)
		Format = GL_RGB;
	else if(nrChannels == 4)
		Format = GL_RGBA;

	glBindTexture(GL_TEXTURE_2D, ID);
	
	glTexImage2D(GL_TEXTURE_2D, 0, Format, Width, Height, 0, Format, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, Wrap_S);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, Wrap_T);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_2D, 0);
	stbi_image_free(data);
}

Texture::~Texture()
{
	glDeleteTextures(1, &ID);
}

void Texture::Bind()
{
	glBindTexture(GL_TEXTURE_2D, ID);
}