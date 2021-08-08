#pragma once
#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include "stb_image.h"

static class ResourceManager
{
public:
	static unsigned char* loadTextureData(const char* path, int* width, int* height, int* nrChannels);
};




#endif