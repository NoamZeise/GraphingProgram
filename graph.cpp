#include "graph.h"

Graph::Graph(glm::vec2 position, glm::vec2 size)
{
	_position = Vector2(position.x, position.y);
	_size = Vector2(size.x, size.y);
	if (_size.x > _size.y)
		graphScale.y = (graphScale.x / _size.x) * _size.y;
	else
		graphScale.x = (graphScale.y / _size.y) * _size.x;
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
	//draw grid background
	renderer->DrawSquare(glm::vec2(_position.x, _position.y), glm::vec2(_size.x, _size.y), 0.0, graphTheme.bgColour);

	DrawGrid(renderer);
	
	Vector2 lastPos(graphPos.x, sin(graphPos.x) * 1.0);
	double step = (double)graphScale.x / 100.0;
	for (double x = graphPos.x; x < (double)graphPos.x + (double)graphScale.x; x+= step)
	{
		if (x < graphPos.x)
			break;
		Vector2 thisPos(x, sin(x) * 1.0);
		renderer->DrawLine(fromGraphToScreen(lastPos), fromGraphToScreen(thisPos), graphTheme.graphColour, graphTheme.graphThickness);
		lastPos = thisPos;
	}
}

void Graph::DrawGrid(Renderer* renderer)
{
	int xSize(1), ySize(1);
	double scale = Math::max(graphScale.x, graphScale.y);
	if (scale > 5)
	{
		xSize = (int)log10(scale / 3);
		ySize = (int)log10(scale / 3);
	}
	else
	{
		xSize = (int)log10(scale / 3) - 1;
		ySize = (int)log10(scale / 3) - 1;
	}

	//draw vertical grid lines
	double interval = pow(10.0, (double)xSize);
	double min = roundUp(graphPos.x, interval) - graphPos.x;
	double max = (graphPos.x - roundDown(graphPos.x, interval)) + graphScale.x + interval;
	for (double x = min; x < max; x += interval)
	{
		verticalLine(renderer, (x + graphPos.x),graphTheme.gridColour, graphTheme.gridThickness);
	}
	verticalLine(renderer, 0, graphTheme.originColour, graphTheme.originThickness);
	
	//draw horizontal grid lines
	interval = pow(10.0, (double)ySize);
	min = roundUp(graphPos.y, interval) - graphPos.y;
	max = (graphPos.y - roundDown(graphPos.y, interval)) + graphScale.y + interval;
	for (double y = min; y < max; y += interval)
	{
		horizontalLine(renderer, (y + graphPos.y), graphTheme.gridColour, graphTheme.gridThickness);
	}
	horizontalLine(renderer, 0, graphTheme.originColour, graphTheme.originThickness);
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
	if (yPos > graphPos.y && yPos < graphPos.y + graphScale.y)
	{
		yPos = fromGraphToScreen(Vector2(0.0f, yPos)).y;
		renderer->DrawLine(glm::vec2(_position.x, yPos), glm::vec2(_position.x + _size.x, yPos), colour, width);
	}
}


void Graph::verticalLine(Renderer* renderer, double xPos, glm::vec3 colour, float width)
{
	if (xPos > graphPos.x && xPos < graphPos.x + graphScale.x)
	{
		xPos = fromGraphToScreen(Vector2(xPos, 0)).x;
		renderer->DrawLine(glm::vec2(xPos, _position.y), glm::vec2(xPos, _position.y + _size.y), colour, width);
	}
}


void Graph::Resize(double width, double height)
{
	_size = Vector2(width, height);
	if (_size.x > _size.y)
		graphScale.y = (graphScale.x / _size.x) * _size.y;
	else
		graphScale.x = (graphScale.y / _size.y) * _size.x;

}

void Graph::Reposition(Vector2 position)
{
	_position = Vector2(position.x, position.y);
}