#include "geometry.h"

double Geometry::distance(Vector2 p1, Vector2 p2)
{
	return sqrt(((p1.x - p2.x) * (p1.x - p2.x)) + ((p1.y - p2.y) * (p1.y - p2.y)));
}


double Geometry::magnitide(Vector2 p)
{
	return sqrt((p.x * p.x) + (p.y * p.y));
}

double Geometry::dot(Vector2 p1, Vector2 p2)
{
	return (p1.x * p2.x) + (p1.y * p2.y);
}