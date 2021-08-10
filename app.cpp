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
	
}

void App::Init()
{
	Shader shader("shaders/sprite.vs", "shaders/sprite.fs");

	shader.Use();

	//configure sprite shader
	glm::mat4 proj = glm::ortho(0.0f, static_cast<float>(Width), static_cast<float>(Height), 0.0f, -1.0f, 1.0f);
	glm::mat4 view = glm::mat4(1.0f);
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, 0.0f));

	glUniform1i(shader.Location("image"), 0);
	glUniformMatrix4fv(shader.Location("projection"), 1, GL_FALSE, &proj[0][0]);
	glUniformMatrix4fv(shader.Location("view"), 1, GL_FALSE, &view[0][0]);

	renderer = new Renderer(shader);
	
}

void App::Update(float dt)
{
	graph->Control(dt, keys);

	if (keys[GLFW_KEY_F1])
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
			//std::cout << selection << std::endl;
			Csv file(selection);
			//file.get2Col();
			graph->AddGraphic(new Plot(file.get2Col()));
		}
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


