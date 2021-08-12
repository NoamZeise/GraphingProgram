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


Graph::~Graph()
{
	for (unsigned int i = 0; i < graphics.size(); i++)
	{
		delete graphics[i];
	}
}


void Graph::Render(Renderer* renderer)
{
	//draw grid background
	renderer->DrawSquare(glm::vec2(_position.x, _position.y), glm::vec2(_size.x, _size.y), 0.0, graphTheme.bgColour);

	DrawGrid(renderer);

	for (unsigned int i = 0; i < graphics.size(); i++)
		DrawGraphic(renderer, graphics[i], i);
	
}

void Graph::DrawGraphic(Renderer* renderer, Graphic* graphic, int num)
{
	Plot* plot = dynamic_cast<Plot*>(graphic);

	switch (num)
	{
	case 1:
		graphTheme.graphColour = glm::vec3(0.5f, 0.0f,0.0f);
		break;
	case 2:
		graphTheme.graphColour = glm::vec3(0.0f, 0.5f, 0.0f);
		break;
	case 3:
		graphTheme.graphColour = glm::vec3(0.0f, 0.0f, 0.5f);
		break;
	case 4:
		graphTheme.graphColour = glm::vec3(0.5f, 0.5f, 0.0f);
		break;
	case 5:
		graphTheme.graphColour = glm::vec3(0.5f, 0.0f, 0.5f);
		break;
	case 6:
		graphTheme.graphColour = glm::vec3(0.0f, 0.5f, 0.5f);
		break;
	default:
		graphTheme.graphColour = glm::vec3(0.0f);
		break;
	}

	if (plot == nullptr)
	{
		//plot data line
		Vector2 lastPos(graphPos.x, graphic->plot(graphPos.x));
		double step = (double)graphScale.x / 100.0;
		for (double x = graphPos.x; x <= graphPos.x + (graphScale.x * 1.0001); x += step)
		{
			if (x < graphPos.x)
				break;
			Vector2 thisPos(x, graphic->plot(x));
			renderer->DrawLine(fromGraphToScreen(lastPos), fromGraphToScreen(thisPos), graphTheme.graphColour, graphTheme.graphThickness);
			lastPos = thisPos;
		}
	}
	else
	{
		//plot data points
		renderer->DrawVertexPoints(plot->getVertexData(),
			glm::vec2(graphPos.x, graphPos.y),
			glm::vec2(graphScale.x, graphScale.y),
			glm::vec2(_position.x, _position.y),
			glm::vec2(_size.x, _size.y),
			graphTheme.graphColour,
			graphTheme.pointThickness);
	}

	//draw labels
	renderer->DrawString(
		graphic->xLabel,
		glm::vec2(_size.x / 2 + (num * (_size.x / 25)), _size.y - _size.x / 200),
		_size.x / 100,
		0,
		graphTheme.graphColour);

	renderer->DrawString(
		graphic->yLabel,
		glm::vec2(_size.x / 200, _size.y / 2 + (num * (_size.y / 30))),
		_size.x / 100,
		0,
		graphTheme.graphColour);
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

	//text
	renderer->DrawString("x:" + std::to_string(graphPos.x)
		+ "  y:" + std::to_string(graphPos.y)
		+ "  interval:1e" + std::to_string(xSize),
		glm::vec2(_size.x / 200, _size.y - _size.x / 200), _size.x / 100, 0, graphTheme.textColour);

}

void Graph::Control(float dt, bool keys[1024])
{
	double speed = 0.5;
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

bool Graph::withinScreen(Vector2 p)
{
	return !(
		p.x < graphPos.x ||
		p.x > graphPos.x + graphScale.x ||
		p.y < graphPos.y ||
		p.y > graphPos.y + graphScale.y);
}
bool Graph::crossesScreen(Vector2 p1, Vector2 p2)
{
	if (withinScreen(p1) || withinScreen(p2))
		return true;
	if (p1.x < graphPos.x && p2.x < graphPos.x)
		return false;
	if (p1.x > graphPos.x + graphScale.x && p2.x > graphPos.x + graphScale.x)
		return false;
	if (p1.y < graphPos.y && p2.y < graphScale.y)
		return false;
	if (p1.y > graphPos.y + graphScale.y && p2.y > graphPos.y + graphScale.y)
		return false;
	return true;
}

void Graph::horizontalLine(Renderer* renderer, double yPos, glm::vec3 colour, float width)
{
	if (yPos > graphPos.y && yPos < graphPos.y + graphScale.y)
	{
		yPos = fromGraphToScreen(Vector2(0.0f, yPos)).y;
		renderer->DrawLine(
			glm::vec2(_position.x, yPos),
			glm::vec2(_position.x + _size.x, yPos),
			colour, width);
	}
}

void Graph::verticalLine(Renderer* renderer, double xPos, glm::vec3 colour, float width)
{
	if (xPos > graphPos.x && xPos < graphPos.x + graphScale.x)
	{
		xPos = fromGraphToScreen(Vector2(xPos, 0)).x;
		renderer->DrawLine(
			glm::vec2(xPos, _position.y),
			glm::vec2(xPos, _position.y + _size.y),
			colour, width);
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

void Graph::AddGraphic(Graphic* graphic)
{
	graphics.push_back(graphic);
}

void Graph::RemoveGraphic(Graphic* graphic)
{
	for (unsigned int i = 0; i < graphics.size() ; i++)
	{
		if (graphics[i] == graphic)
		{
			graphics.erase(graphics.begin() + i);
			break;
		}
	}
}

void Graph::Zoom(double offset)
{
	double speed = 0.1;
	if (offset < 0)
	{
		graphScale.x +=  speed * graphScale.x;
		graphPos.x -=  speed * graphScale.x * 0.5f;
		graphScale.y += speed * graphScale.y;
		graphPos.y -= speed * graphScale.y * 0.5f;
	}
	if (offset > 0)
	{
		graphScale.x -= speed * graphScale.x;
		graphPos.x += speed * graphScale.x * 0.5f;
		graphScale.y -= speed * graphScale.y;
		graphPos.y += speed * graphScale.y * 0.5f;
	}
}