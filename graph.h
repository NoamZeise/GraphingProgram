#pragma once
#ifndef GRAPH_H
#define GRAPH_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "render.h"
#include "geometry.h"

class Graph
{
public:
	Graph(glm::vec2 position, glm::vec2 size);
	~Graph();
	void Render(Renderer* renderer);
	void Control(float dt, bool keys[1024]);

private:
	Vector2 _position;
	Vector2 _size;

	Vector2 graphPos = Vector2(0.0, 0.0);
	Vector2 graphScale = Vector2(5, 5);

	glm::vec2 fromGraphToScreen(Vector2 p);

	void horizontalLine(Renderer* renderer, double yPos, glm::vec3 colour, float width);
	void verticalLine(Renderer* renderer, double xPos, glm::vec3 colour, float width);
	void DrawGrid(Renderer* renderer);

	double roundUp(double number, double fixedBase);
	double roundDown(double number, double fixedBase);
};


#endif