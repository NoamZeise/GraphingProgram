#include "app.h"

App::App(unsigned int width, unsigned int height)
{
	Width = width;
	Height = height;
	Init();
}

App::~App()
{
	delete renderer;
	delete graph;
	delete uiManager;
}

void App::Init()
{
	graph = new Graph(Vector2(0, 0), Vector2(Width, Height));
	uiManager = new UIManager(Width, Height);
	renderer = new Renderer(Width, Height);
}

void App::Update(float dt)
{
	graph->Control(dt, &input);
	if (uiManager->Update(graph, &input))
		shouldClose = true;

	input.offset = 0;
}



void App::Render()
{
	graph->Render(renderer);
	uiManager->Render(renderer);
}

void App::Resize(int width, int height)
{
	this->Width = width;
	this->Height = height;
	renderer->Resize(width, height);
	graph->Resize(width, height);
	uiManager->Resize(width, height);
}

void App::Scroll(double offset)
{
	input.offset = offset;
}

void App::ProcessKeyboard(int key, bool pressed)
{
	input.Keys[key] = pressed;
}
void App::ProcessMouseBtn(int button, bool pressed)
{
	input.Buttons[button] = pressed;
}
void App::ProcessMouse(double xPos, double yPos)
{
	input.X = xPos;
	input.Y = yPos;
}

bool App::ShouldClose()
{
	return shouldClose;
}


