#pragma once

#ifndef GRAPHIC_H
#define GRAPHIC_H

#include <cmath>
#include <vector>

#include "geometry.h"
#include "vertex_data.h"

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

	Plot(std::vector<Vector2> data);

	~Plot()
	{
		delete _vd;
	}
	std::vector<Vector2>* getData()
	{
		return &_data;
	}

	VertexData* getVertexData()
	{
		return _vd;
	}
private:
	std::vector<Vector2> _data;
	std::vector<Vector2> _fullData;
	VertexData* _vd;
};




#endif