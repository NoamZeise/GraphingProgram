#pragma once
#ifndef CSV_H
#define CSV_H

#include <fstream>
#include <string>
#include <vector>

#include "geometry.h";

class Csv
{
public:
	Csv(const char* filename);
	std::vector<Vector2> get2Col(int col1, int col2);
private:
	int collumns = 0;
	int rows = 0;
	std::vector<std::string> titles;
	std::vector<std::string> data;
};



#endif