#include "graphic.h"
double Function::plot(double x)
{
	switch (_type)
	{
	case FunctionType::Quadratic:
		double y = 0;
		for (unsigned int i = 0; i < _data.size(); i++)
		{
			y += pow(x, i) * _data[i];
		}
		return y;
	}
	return x;
}

double Plot::plot(double x)
{
	return (x);
}


Function::Function(std::vector<double> quadratic)
{
	_type = FunctionType::Quadratic;
	_data = quadratic;
}


Plot::Plot(std::vector<Vector2> data, std::string xLabel, std::string yLabel)
{
	this->xLabel = xLabel;
	this->yLabel = yLabel;
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

	float* verticies = new float[_data.size() * 2];

	for (unsigned int i = 0; i < _data.size(); i++)
	{
		verticies[i * 2] = _data.at(i).x;
		verticies[(i * 2) + 1] = _data.at(i).y;
	}
	_vd = new VertexData(verticies, _data.size() * 2, 2);
	delete[] verticies;
}

