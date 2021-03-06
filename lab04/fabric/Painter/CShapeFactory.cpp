#pragma once
#include "pch.h"
#include "CShapeFactory.h"

template <typename T>
T GetArg(std::istream& argsStream)
{
	T arg;
	if (!(argsStream >> arg))
	{
		throw std::logic_error("Not enough arguments");
	}
	return arg;
}

template <>
Color GetArg(std::istream& argsStream)
{
	int arg = GetArg<int>(argsStream);
	return static_cast<Color>(arg);
}

std::shared_ptr<CTriangle> MakeTriangle(std::istream& argsStream)
{
	Point vertex1 = { GetArg<double>(argsStream), GetArg<double>(argsStream) };
	Point vertex2 = { GetArg<double>(argsStream), GetArg<double>(argsStream) };
	Point vertex3 = { GetArg<double>(argsStream), GetArg<double>(argsStream) };
	Color color = GetArg<Color>(argsStream);

	return std::make_shared<CTriangle>(color, vertex1, vertex2, vertex3);
}

std::shared_ptr<CRectangle> MakeRectangle(std::istream& argsStream)
{
	Point leftTop = { GetArg<double>(argsStream), GetArg<double>(argsStream) };
	Point rightBottom = { GetArg<double>(argsStream), GetArg<double>(argsStream) };
	Color color = GetArg<Color>(argsStream);

	return std::make_shared<CRectangle>(color, leftTop, rightBottom);
}

std::shared_ptr<CRegularPolygon> MakePolygon(std::istream& argsStream)
{
	size_t vertexCount = GetArg<size_t>(argsStream);
	Point center = { GetArg<double>(argsStream), GetArg<double>(argsStream) };
	double radius = GetArg<double>(argsStream);
	Color color = GetArg<Color>(argsStream);

	return std::make_shared<CRegularPolygon>(color, vertexCount, center, radius);
}

std::shared_ptr<CEllipse> MakeEllipse(std::istream& argsStream)
{
	Point leftTop = { GetArg<double>(argsStream), GetArg<double>(argsStream) };
	double width = GetArg<double>(argsStream);
	double height = GetArg<double>(argsStream);
	Color color = GetArg<Color>(argsStream);

	return std::make_shared<CEllipse>(color, leftTop, width, height);
}

const std::string TRIANGLE_NAME = "triangle";
const std::string RECTANGLE_NAME = "rectangle";
const std::string ELLIPSE_NAME = "ellipse";
const std::string POLYGON_NAME = "polygon";

CShapeFactory::CShapeFactory()
{
	m_shapeGeneratorsMap[TRIANGLE_NAME] = MakeTriangle;
	m_shapeGeneratorsMap[RECTANGLE_NAME] = MakeRectangle;
	m_shapeGeneratorsMap[ELLIPSE_NAME] = MakeEllipse;
	m_shapeGeneratorsMap[POLYGON_NAME] = MakePolygon;
}

std::shared_ptr<CShape> CShapeFactory::CreateShape(const std::string& description)
{
	std::istringstream args(description);
	std::string shapeName;

	try
	{
		args >> shapeName;
		auto shapeIt = m_shapeGeneratorsMap.find(shapeName);
		if (shapeIt == m_shapeGeneratorsMap.end())
		{
			throw std::invalid_argument("Unhandled shape: " + shapeName + " given");
		}

		return shapeIt->second(args);
	}
	catch (const std::exception& ex)
	{
		throw std::invalid_argument("Error while parsing " + shapeName + " arguments: " + ex.what());
	}
}
