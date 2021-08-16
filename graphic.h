#pragma once

#ifndef GRAPHIC_H
#define GRAPHIC_H

#include <cmath>
#include <vector>
#include <string>

#include "geometry.h"
#include "vertex_data.h"

typedef double (*graphicFunc)(double);

class Graphic
{
public:
	virtual double plot(double x) = 0;
	std::string xLabel = "x";
	std::string yLabel = "y";
protected:

private:

};

enum class FunctionType
{
	None,
	Polynomial,
	PassedFunc,
	Sinusoidal
};

class Function : public Graphic
{
public:
	double plot(double x) override;

	Function(std::vector<double> polynomial);
	Function(graphicFunc func);

private:
	FunctionType _type = FunctionType::None;
	graphicFunc func = nullptr;
	std::vector<double> _data;
};

class Plot : public Graphic
{
public:
	double plot(double x) override;

	Plot(std::vector<Vector2> data, std::string xLabel, std::string yLabel);

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