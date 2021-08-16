#include "ui_manager.h"

UIManager::UIManager(int width, int height)
{
	this->width = width;
	this->height = height;
	topMenu = new Menu(Vector2(0, 0), Vector2(width / 10, width / 60), true);
	importMenu = new DropMenu(btnNames.importCsv, false,
		topMenu->AddButton(btnNames.importCsv));

	topMenu->AddButton(btnNames.addFunction);
	topMenu->AddButton(btnNames.clearGraph);
	topMenu->AddButton(btnNames.exit);

	menus.push_back(topMenu);
	menus.push_back(importMenu);
}

UIManager::~UIManager()
{
	for (unsigned int i = 0; i < openCsvs.size(); i++)
	{
		delete openCsvs.at(i);
	}
	for (unsigned int i = 0; i < menus.size(); i++)
	{
		delete menus.at(i);
	}
	for (unsigned int i = 0; i < graphics.size(); i++)
	{
		delete graphics[i];
	}
}

bool UIManager::Update(Graph* graph, Input* input)
{
	paused = false;
	if (option)
	{
		paused = true;
		std::string output = option->Update(input);
		if (output != "")
		{
			std::vector<double> outAsDouble;
			std::string str = "";
			for (unsigned int i = 0; i < output.size(); i++)
			{
				if (output[i] == ',')
				{
					if (str != "")
					{
						try {
							double d = std::stod(str);
							outAsDouble.push_back(d);
						}
						catch (...)
						{}
					}
					str = "";
				}
				else
				{
					str += output[i];
				}
			}
			if (str != "")
			{
				try {
					double d = std::stod(str);
					outAsDouble.push_back(d);
				}
				catch (...)
				{}
			}

			std::string prt = option->Parent();

			if (prt.size() > 3)
			{
				if (prt.substr(0, 3) == "csv")
				{
					Csv* csv = openCsvs.at(std::stoi(prt.substr(3, 1)));
					if (csv)
					{

						if (outAsDouble.size() >= 2)
						{
							graphics.push_back(new Plot(csv->get2Col((int)outAsDouble.at(0), (int)outAsDouble.at(1)),
								csv->getColLabel((int)outAsDouble.at(0)), csv->getColLabel((int)outAsDouble.at(1))));
							graph->AddGraphic(graphics.at(graphics.size() - 1));
						}
					}
				}
				if (prt.substr(0, 4) == "poly")
				{
					if (outAsDouble.size() >= 1)
					{
						graphics.push_back(new Function(outAsDouble));
						graph->AddGraphic(graphics.at(graphics.size() - 1));
					}
				}
			}

			delete option;
			option = nullptr;
		}
	}
	else
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
				importMenu->DMenu.AddButton(csv->getName());
			}
		}
		else if (topMenu->WasClicked(btnNames.addFunction))
		{
			option = new Options("poly",
				"enter coefficients from x^0 on. like(1,0,1)"
				, width, height);
		}
		else if (topMenu->WasClicked(btnNames.exit))
		{
			return true;
		}
		else if (topMenu->WasClicked(btnNames.clearGraph))
		{
			for (unsigned int i = 0; i < graphics.size(); i++)
			{
				graph->RemoveGraphic(graphics.at(i));
				delete graphics.at(i);
			}
			graphics.clear();
		}
		else
		{
			for (unsigned int i = 0; i < openCsvs.size(); i++)
			{
				if (importMenu->DMenu.WasClicked(openCsvs.at(i)->getName()))
				{
					option = new Options("csv" + std::to_string(i),
						"chose two collumns like->(0,1) ,then hit enter. num:"
						+ std::to_string(openCsvs.at(i)->getCollNum()),
					width, height);
				}
			}
		}


		bool pressed = false;
		if (input->Buttons[GLFW_MOUSE_BUTTON_1] == GLFW_PRESS)
			pressed = true;

		for (unsigned int i = 0; i < menus.size(); i++)
		{
			menus.at(i)->Update(input->X, input->Y, pressed);
		}
	}
	return false;
}

void UIManager::Render(Renderer* renderer)
{
	if (option)
	{
		option->Render(renderer);
	}
	for (unsigned int i = 0; i < menus.size(); i++)
	{
		menus.at(i)->Render(renderer);
	}

}

void UIManager::Resize(int width, int height)
{
	this->width = width;
	this->height = height;
	topMenu->Resize(Vector2(0, 0), Vector2(width / 10, width / 60));
	importMenu->Resize();
	if (option)
		option->Resize(width, height);
}
