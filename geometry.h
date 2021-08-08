#pragma once
#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
class Vector2
{
public:
	double x;
	double y;
	Vector2()
	{
		x = 0.0;
		y = 0.0;
	}
	Vector2(double x, double y)
	{
		this->x = x;
		this->y = y;
	}

};
static class Geometry
{
public:
	static double distance(Vector2 p1, Vector2 p2);
	static double magnitide(Vector2 p);
	static double dot(Vector2 p1, Vector2 p2);
};





#endif