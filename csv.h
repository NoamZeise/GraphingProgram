#pragma once
#ifndef CSV_H
#define CSV_H

#include <fstream>
#include <string>
#include <vector>

class Csv
{
public:
	Csv(const char* filename)
	{
		std::ifstream file(filename);
		if (file.is_open())
		{
			std::string line;
			while (std::getline(file, line))
			{
				if (collumns == 0)
				{
					std::string value = "";
					for (unsigned int i = 0; i < line.size(); i++)
					{
						if (line[i] == ',')
						{
							collumns++;
							titles.push_back(value);
							value = "";
						}
						else
						{
							value += line[i];
						}
					}
					collumns++;
					titles.push_back(value);
				}
				else
				{
					rows++;
					std::string value = "";
					for (unsigned int i = 0; i < line.size(); i++)
					{
						if (line[i] == ',')
						{
							if(value != "")
								data.push_back(value);
							else
								data.push_back("0");
							value = "";
						}
						else
						{
							value += line[i];
						}
					}
					if (value != "")
						data.push_back(value);
					else
						data.push_back("0");
				}
			}
			file.close();
		}

	}

	std::vector<Vector2> get2Col()
	{
		int getColls[] { 1, 2 };
		std::vector<Vector2> colData;
		int collumn = 1;
		int row = 1;
		Vector2 p(0, 0);
		for (int i = 0; i < data.size(); i++)
		{
			if (collumn == getColls[0])
			{
				p.x = std::stod(data.at(i));
			}
			if (collumn == getColls[1])
			{
				//std::cout << data.at(i) << std::endl;
				//std::cout << data.size() << std::endl;
				//std::cout << i << std::endl;
				p.y = std::stod(data.at(i));
				colData.push_back(p);
				row++;
				if (row >= rows)
					break;
			}
			collumn++;
			if (collumn >= collumns)
				collumn = 0;
		}
		return colData;
	}

private:
	int collumns = 0;
	int rows = 0;
	std::vector<std::string> titles;
	std::vector<std::string> data;
};



#endif