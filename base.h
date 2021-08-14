#pragma once
#ifndef BASE_H
#define BASE_H


#include <string>
#include "geometry.h"
#include "render.h"

class Base
{
public:
	Base(Vector2 pos, Vector2 size)
	{
		this->_Position = pos;
		this->_Size = size;
	}
	Base() {}
	virtual void Resize(Vector2 pos, Vector2 size)
	{
		this->_Position = pos;
		this->_Size = size;
	}
	virtual void Update(double xPos, double yPos, bool pressed) = 0;
	virtual void Render(Renderer* renderer) = 0;

	Vector2 getPosition() { return _Position; }
	Vector2 getSize() { return _Size; }
protected:
	Vector2 _Position;
	Vector2 _Size;
};



#endif