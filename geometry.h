#pragma once
#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
struct Vector2
{
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

	bool operator==(Vector2 p2)
	{
		return (x == p2.x) && (y == p2.y);
	}

	Vector2 operator+(Vector2 p2)
	{
		return Vector2(x + p2.x, y + p2.y);
	}

};
static class Geometry
{
public:
	static double distance(Vector2 p1, Vector2 p2);
	static double magnitide(Vector2 p);
	static double dot(Vector2 p1, Vector2 p2);
};

static class Math
{
public:
	static inline double max(double x, double y)
	{
		return x > y ? x : y;
	}
	static inline double min(double x, double y)
	{
		return x < y ? x : y;
	}
};





#endif