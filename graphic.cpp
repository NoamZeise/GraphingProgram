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

