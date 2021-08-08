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
	void Resize(double width, double height);
	void Reposition(Vector2 position);

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

	struct theme
	{
		glm::vec3 bgColour = glm::vec3(0.8);
		glm::vec3 graphColour = glm::vec3(0.0);
		float graphThickness = 3.0f;
		glm::vec3 gridColour = glm::vec3(0.6);
		float gridThickness = 1.0f;
		glm::vec3 originColour = glm::vec3(0.2);
		float originThickness = 1.5f;

	};
	theme graphTheme;
};


#endif