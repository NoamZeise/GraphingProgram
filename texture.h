#pragma once

#ifndef TEXTURE_H
#define TEXTURE_H


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