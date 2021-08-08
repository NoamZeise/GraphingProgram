#include "graph.h"

Graph::Graph(glm::vec2 position, glm::vec2 size)
{
	_position = Vector2(position.x, position.y);
	_size = Vector2(size.x, size.y);
}

double Graph::roundUp(double number, double fixedBase) {
	if (fixedBase != 0 && number != 0) {
		double sign = number > 0 ? 1 : -1;
		number *= sign;
		number /= fixedBase;
		double fixedPoint = ceil(number);
		number = fixedPoint * fixedBase;
		number *= sign;
	}
	return number;
}

double Graph::roundDown(double number, double fixedBase) {
	if (fixedBase != 0 && number != 0) {
		double sign = number > 0 ? 1 : -1;
		number *= sign;
		number /= fixedBase;
		double fixedPoint = floor(number);
		number = fixedPoint * fixedBase;
		number *= sign;
	}
	return number;
}


void Graph::Render(Renderer* renderer)
{
	renderer->DrawSquare(glm::vec2(_position.x, _position.y), glm::vec2(_size.x, _size.y), 0.0, glm::vec3(0.8, 0.8, 0.8));

	DrawGrid(renderer);
	
	Vector2 lastPos(graphPos.x, sin(graphPos.x) * 1.0);
	double step = (double)graphScale.x / 100.0;
	for (double x = graphPos.x; x < (double)graphPos.x + (double)graphScale.x; x+= step)
	{
		if (x < graphPos.x)
			break;
		Vector2 thisPos(x, sin(x) * 1.0);
		renderer->DrawLine(fromGraphToScreen(lastPos), fromGraphToScreen(thisPos), glm::vec3(0.0), 3.0);
		lastPos = thisPos;
	}
	

}

void Graph::DrawGrid(Renderer* renderer)
{
	int xSize(1), ySize(1);

	if (graphScale.x > 5)
		xSize = (int)log10(graphScale.x / 3);
	else
		xSize = (int)log10(graphScale.x / 3) - 1;
	if (graphScale.y > 5)
		ySize = (int)log10(graphScale.y / 3);
	else
		ySize = (int)log10(graphScale.y / 3) - 1;

	double size = pow(10.0, (double)xSize);
	double limit = roundUp(graphPos.x, size) - graphPos.x;
	double flr = roundDown(graphPos.x, size);
	double tempX = graphPos.x - flr;
	double maxX = tempX + graphScale.x;

	for (double x = limit; x < maxX; x += size)
	{
		verticalLine(renderer, (x + graphPos.x), glm::vec3(0.6), 1.0);
	}
	verticalLine(renderer, 0, glm::vec3(0.2), 1.5);
	
	size = pow(10.0, (double)ySize);
	limit = roundUp(graphPos.y, size) - graphPos.y;
	flr = roundDown(graphPos.y, size);
	double tempY = graphPos.y - flr;
	double maxY = tempY + graphScale.y;
	for (double y = limit; y < maxY; y += size)
	{
		horizontalLine(renderer, (y + graphPos.y), glm::vec3(0.6), 1.0);
	}
	
	horizontalLine(renderer, 0, glm::vec3(0.2), 1.5);
}

void Graph::Control(float dt, bool keys[1024])
{
	double speed = 1.0;
	if (keys[GLFW_KEY_W])
	{
		graphPos.y += (double)dt * speed * graphScale.y;
	}
	if (keys[GLFW_KEY_A])
	{
		graphPos.x -= (double)dt * speed * graphScale.x;
	}
	if (keys[GLFW_KEY_S])
	{
		graphPos.y -= (double)dt * speed * graphScale.y;
	}
	if (keys[GLFW_KEY_D])
	{
		graphPos.x += (double)dt * speed * graphScale.x;
	}
	if (keys[GLFW_KEY_MINUS])
	{
		graphScale.x += (double)dt * speed * graphScale.x;
		graphPos.x -= (double)dt * speed * graphScale.x * 0.5f;
		graphScale.y += (double)dt * speed * graphScale.y;
		graphPos.y -= (double)dt * speed * graphScale.y * 0.5f;
	}
	if (keys[GLFW_KEY_EQUAL])
	{
		graphScale.x -= (double)dt * speed * graphScale.x;
		graphPos.x += (double)dt * speed * graphScale.x * 0.5f;
		graphScale.y -= (double)dt * speed * graphScale.y;
		graphPos.y += (double)dt * speed * graphScale.y * 0.5f;
	}

}


glm::vec2 Graph::fromGraphToScreen(Vector2 p)
{
	p.x -= graphPos.x;
	p.y -= graphPos.y;

	p.x /= graphScale.x;
	p.y /= graphScale.y;

	p.x *= _size.x;
	p.y *= _size.y;

	p.y = _size.y - p.y;

	p.x += _position.x;
	p.y += _position.y;
	return glm::vec2(p.x, p.y);
}


void Graph::horizontalLine(Renderer* renderer, double yPos, glm::vec3 colour, float width)
{
	yPos = fromGraphToScreen(Vector2(0.0f, yPos)).y;
	renderer->DrawLine(glm::vec2(_position.x, yPos), glm::vec2(_position.x + _size.x, yPos) , colour, width);
}


void Graph::verticalLine(Renderer* renderer, double xPos, glm::vec3 colour, float width)
{
	xPos = fromGraphToScreen(Vector2(xPos, 0)).x;
	renderer->DrawLine(glm::vec2(xPos, _position.y), glm::vec2(xPos, _position.y + _size.y), colour, width);
}