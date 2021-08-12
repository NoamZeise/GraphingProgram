#include "csv.h"

Csv::Csv(const char* filename)
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
						data.push_back(value);
						value = "";
					}
					else
					{
						value += line[i];
					}
				}
				data.push_back(value);
			}
		}
		file.close();
	}

}

std::vector<Vector2> Csv::get2Col(int col1, int col2)
{
	if (col1 > col2)
	{
		int temp = col1;
		col1 = col2;
		col2 = temp;
	}
	std::vector<Vector2> colData;
	int collumn = 1;
	int row = 1;
	bool invalidP = false;
	Vector2 p(0, 0);
	for (int i = 0; i < data.size(); i++)
	{
		if (collumn == col1)
		{
			if (data.at(i) != "")
				p.x = std::stod(data.at(i));
			else
				invalidP = true;
		}
		if (collumn == col2)
		{
			if (data.at(i) != "" && !invalidP)
			{
				p.y = std::stod(data.at(i));
				colData.push_back(p);
			}
			else
				invalidP = false;
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