#pragma once
#include "pch.h"

enum Color
{
	Green,
	Red,
	Blue,
	Yellow,
	Pink,
	Black
};

typedef std::pair<double, double> Point;

class ICanvas
{
public:
	virtual ~ICanvas() = default;

	virtual void SetColor(Color color) = 0;
	virtual void DrawLine(const Point& from, const Point& to) = 0;
	virtual void DrawEllipse(const Point& leftTop, double width, double height) = 0;
};
