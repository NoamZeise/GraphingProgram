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

	topMenu = new Menu(glm::vec2(0, 0), glm::vec2(width / 10, width / 60), true);
	topMenu->AddButton(btnNames.importCsv);
	topMenu->AddButton(btnNames.addFunction);

	topMenu->AddButton(btnNames.exit);
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

	MenuControls();
}

void App::MenuControls()
{
	if (topMenu->WasClicked(btnNames.importCsv))
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
			Csv* csv = new Csv(selection);
			openCsvs.push_back(csv);
			graph->AddGraphic(new Plot(csv->get2Col(0, 1), csv->getColLabel(0), csv->getColLabel(1)));
		}
	}
	else if (topMenu->WasClicked(btnNames.addFunction))
	{
		std::vector<double> v = { 0, 0.1, 0.1, 0.1 };
		graph->AddGraphic(new Function(v));
	}
	else if (topMenu->WasClicked(btnNames.exit))
	{
		shouldClose = true;
	}


	bool pressed = false;
	if (buttons[GLFW_MOUSE_BUTTON_1] == GLFW_PRESS)
		pressed = true;

	topMenu->Update(mousePos.x, mousePos.y, pressed);
}


void App::Render()
{
	graph->Render(renderer);
	topMenu->Render(renderer);
}

void App::Resize(int width, int height)
{
	this->Width = width;
	this->Height = height;
	renderer->Resize(width, height);
	graph->Resize(width, height);
	topMenu->Resize(glm::vec2(0, 0), glm::vec2(width / 10, width / 60));
}

void App::Scroll(double offset)
{
	graph->Zoom(offset);
}

void App::ProcessKeyboard(int key, bool pressed)
{
	keys[key] = pressed;
}
void App::ProcessMouseBtn(int button, bool pressed)
{
	buttons[button] = pressed;
}
void App::ProcessMouse(double xPos, double yPos)
{
	mousePos.x = xPos;
	mousePos.y = yPos;

	bool pressed = false;
	if (buttons[GLFW_MOUSE_BUTTON_1] == GLFW_PRESS)
		pressed = true;
}

bool App::ShouldClose()
{
	return shouldClose;
}


