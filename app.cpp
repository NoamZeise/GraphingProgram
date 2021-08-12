#include "app.h"

App::App(unsigned int width, unsigned int height)
{
	Width = width;
	Height = height;
	Init();
	for (unsigned int i = 0; i < 1024; i++)
	{
		keys[i] = false;
	}
	for (unsigned int i = 0; i < 7; i++)
	{
		buttons[i] = false;
	}
	graph = new Graph(glm::vec2(0, 0), glm::vec2(width, height));
}

App::~App()
{
	delete renderer;
	renderer = nullptr;
	delete graph;
	graph = nullptr;
	for (unsigned int i = 0; i < openCsvs.size(); i++)
	{
		delete openCsvs.at(i);
	}
}

void App::Init()
{
	renderer = new Renderer(Width, Height);
	
}

void App::Update(float dt)
{
	graph->Control(dt, keys);

	if (keys[GLFW_KEY_F1] && !dialogOpened)
	{
		char const* lFilterPatterns[1] = { "*.csv" };
		char const* selection = tinyfd_openFileDialog( // there is also a wchar_t version
			"Select data or function", // title
			std::filesystem::current_path().string().c_str(), // optional initial directory
			1, // number of filter patterns
			lFilterPatterns, // char const * lFilterPatterns[2] = { "*.txt", "*.jpg" };
			NULL, // optional filter description
			0 // forbid multiple selections
		);

		if (selection)
		{
			openCsvs.push_back(new Csv(selection));
			graph->AddGraphic(new Plot(openCsvs.at(openCsvs.size() - 1)->get2Col(1, 2)));
		}
		dialogOpened = true;
	}
	else if (keys[GLFW_KEY_F2] && !dialogOpened)
	{
		

		dialogOpened = true;
	}
}


void App::Render()
{
	graph->Render(renderer);
}

void App::Resize(int width, int height)
{
	this->Width = width;
	this->Height = height;
	renderer->Resize(width, height);
	graph->Resize(width, height);
}

void App::Scroll(double offset)
{
	graph->Zoom(offset);
}

void App::ProcessKeyboard(int key, bool pressed)
{
	keys[key] = pressed;
	dialogOpened = false;
}
void App::ProcessMouseBtn(int button, bool pressed)
{
	buttons[button] = pressed;
	dialogOpened = false;
}
void App::ProcessMouse(double xPos, double yPos)
{
	mousePos.x = xPos;
	mousePos.y = yPos;
	dialogOpened = false;
}


