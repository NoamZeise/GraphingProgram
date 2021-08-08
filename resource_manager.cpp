#include "resource_manager.h"
#include "stb_image.h"

static unsigned char* ResourceManager::loadTextureData(const char* path, int* width, int* height, int* nrChannels)
{
	unsigned char* data = stbi_load(path, width, height, nrChannels, 0);
	return data;
}