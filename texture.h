#pragma once

#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad/glad.h>
#include <iostream>
#include "stb_image.h"

class Texture
{
public:
	unsigned int ID;
    int Width, Height;
	unsigned int Format;
	unsigned int Wrap_S;
	unsigned int Wrap_T;
	Texture(const char* path);
	~Texture();
	void Bind();
};


#endif