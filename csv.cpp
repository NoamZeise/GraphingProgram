#include "csv.h"

Csv::Csv(const char* filename)
{
	datasetName = filename;
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
std::vector<Vector2> Csv::get2Col(int xCol, int yCol)
{

	std::vector<Vector2> colData;

	if (xCol >= collumns || yCol >= collumns)
		return colData;

	//check for non-numeric collumns
	for (int i = 0; i < collumns; i++)
	{
		try { std::stod(data.at(i)); }
		catch(...)
		{
			if (i == xCol || i == yCol)
				return colData;
		}
	}

	int collumn = 0;
	int row = 0;
	bool invalidP = false;
	Vector2 p(0, 0);
	for (int i = 0; i < data.size(); i++)
	{
		if (collumn == xCol)
		{
			if (data.at(i) != "")
				p.x = std::stod(data.at(i));
			else 
				invalidP = true;
		}
		if (collumn == yCol)
		{
			if (data.at(i) != "")
				p.y = std::stod(data.at(i));
			else
				invalidP = true;
		}
		collumn++;
		if (collumn >= collumns)
		{
			row++;
			if (row >= rows)
				break;
			collumn = 0;
			if (!invalidP)
				colData.push_back(p);
		}
	}
	return colData;
}

std::string Csv::getColLabel(int col)
{
	if(col < titles.size())
		return titles[col];
	return std::to_string(col);
}

std::string Csv::getName()
{
	std::string name = datasetName;
	name = name.substr(name.find_last_of('\\') + 1);
	return name;
}