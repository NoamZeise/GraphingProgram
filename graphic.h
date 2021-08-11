#pragma once

#ifndef GRAPHIC_H
#define GRAPHIC_H

#include <cmath>
#include <vector>

#include "geometry.h"

class Graphic
{
public:
	virtual double plot(double x) = 0;
protected:

private:

};

enum FunctionType
{
	None,
	Quadratic,
	Sinusoidal
};

class Function : public Graphic
{
public:
	double plot(double x) override;
	
	Function(std::vector<double> quadratic);
private:
	FunctionType _type = FunctionType::None;
	std::vector<double> _data;
};

class Plot : public Graphic
{
public:
	double plot(double x) override;

	Plot(std::vector<Vector2> data)
	{
		_fullData = data;
		for (int i = 0; i < _fullData.size(); i++)
		{
			bool found = false;
			for (int j = 0; j < _data.size(); j++)
			{
				if (_data.at(j) == _fullData.at(i))
				{
					found = true;
					break;
				}
			}
			if (!found)
				_data.push_back(_fullData.at(i));
		}
	}
	std::vector<Vector2>* getData()
	{
		return &_data;
	}
private:
	std::vector<Vector2> _data;
	std::vector<Vector2> _fullData;
};




#endif