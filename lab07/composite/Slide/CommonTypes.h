#pragma once
#include "pch.h"

struct Point
{
	double x;
	double y;
};

struct Rect
{
	Point leftTop;
	double width;
	double height;
};

typedef uint32_t RGBAColor;