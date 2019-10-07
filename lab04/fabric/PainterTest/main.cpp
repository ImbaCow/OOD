#pragma once
#include "pch.h"
#include "TestCanvas.h"
#include "CTriangle.h"
#include "CEllipse.h"
#include "CRectangle.h"
#include "CRegularPolygon.h"
#include "CShapeFactory.h"
#include "CDesigner.h"
#include "CPictureDraft.h"
#include "CPainter.h"

#define BOOST_TEST_MODULE PainterTest
#include <boost/test/unit_test.hpp>

#define EPSILION 1

template <typename T>
void ComparePair(const std::pair<T, T>& first, const std::pair<T, T>& second)
{
	BOOST_CHECK_CLOSE(first.first, second.first, EPSILION);
	BOOST_CHECK_CLOSE(first.second, second.second, EPSILION);
}

BOOST_AUTO_TEST_SUITE(PainterTest)

	BOOST_AUTO_TEST_SUITE(TestShape)
		BOOST_AUTO_TEST_CASE(TestTriangle)
		{
			CTriangle shape(Color::Green, { 1, 2 }, { 3, 4 }, { 5, 6 });
			BOOST_CHECK_EQUAL(shape.GetColor(), Color::Green);

			ComparePair(shape.GetVertex1(), { 1, 2 });
			ComparePair(shape.GetVertex2(), { 3, 4 });
			ComparePair(shape.GetVertex3(), { 5, 6 });

			std::shared_ptr<TestCanvas> canvas = std::make_shared<TestCanvas>();
			std::shared_ptr<ICanvas> canvasBase = canvas;
			shape.Draw(canvasBase);

			BOOST_CHECK_EQUAL(canvas->m_color, Color::Green);
			BOOST_CHECK_EQUAL(canvas->m_lineArr.size(), 3u);

			ComparePair(canvas->m_lineArr[0].first, { 1, 2 });
			ComparePair(canvas->m_lineArr[0].second, { 3, 4 });

			ComparePair(canvas->m_lineArr[1].first, { 3, 4 });
			ComparePair(canvas->m_lineArr[1].second, { 5, 6 });

			ComparePair(canvas->m_lineArr[2].first, { 5, 6 });
			ComparePair(canvas->m_lineArr[2].second, { 1, 2 });
		}
		BOOST_AUTO_TEST_CASE(TestEllipse)
		{
			CEllipse shape(Color::Green, { 1, 2 }, 3, 4);
			BOOST_CHECK_EQUAL(shape.GetColor(), Color::Green);

			BOOST_CHECK_CLOSE(shape.GetHeight(), 4, EPSILION);
			BOOST_CHECK_CLOSE(shape.GetWidth(), 3, EPSILION);
			ComparePair(shape.GetLeftTop(), { 1, 2 });

			std::shared_ptr<TestCanvas> canvas = std::make_shared<TestCanvas>();
			std::shared_ptr<ICanvas> canvasBase = canvas;
			shape.Draw(canvasBase);

			BOOST_CHECK_EQUAL(canvas->m_color, Color::Green);
			BOOST_CHECK_EQUAL(canvas->m_lineArr.size(), 0u);
			BOOST_CHECK_EQUAL(canvas->m_ellipseArr.size(), 1u);

			BOOST_CHECK_CLOSE(canvas->m_ellipseArr[0].height, 4, EPSILION);
			BOOST_CHECK_CLOSE(canvas->m_ellipseArr[0].width, 3, EPSILION);
			ComparePair(canvas->m_ellipseArr[0].leftTop, { 1, 2 });
		}
		BOOST_AUTO_TEST_CASE(TestRectangle)
		{
			CRectangle shape(Color::Black, { 1, 2 }, { 3, 4 });
			BOOST_CHECK_EQUAL(shape.GetColor(), Color::Black);

			ComparePair(shape.GetLeftTop(), { 1, 2 });
			ComparePair(shape.GetRightBottom(), { 3, 4 });

			std::shared_ptr<TestCanvas> canvas = std::make_shared<TestCanvas>();
			std::shared_ptr<ICanvas> canvasBase = canvas;
			shape.Draw(canvasBase);

			BOOST_CHECK_EQUAL(canvas->m_color, Color::Black);
			BOOST_CHECK_EQUAL(canvas->m_lineArr.size(), 4u);
			BOOST_CHECK_EQUAL(canvas->m_ellipseArr.size(), 0u);

			ComparePair(canvas->m_lineArr[0].first, { 1, 2 });
			ComparePair(canvas->m_lineArr[0].second, { 3, 2 });

			ComparePair(canvas->m_lineArr[1].first, { 1, 2 });
			ComparePair(canvas->m_lineArr[1].second, { 1, 4 });

			ComparePair(canvas->m_lineArr[2].first, { 3, 2 });
			ComparePair(canvas->m_lineArr[2].second, { 3, 4 });

			ComparePair(canvas->m_lineArr[3].first, { 1, 4 });
			ComparePair(canvas->m_lineArr[3].second, { 3, 4 });
		}
		BOOST_AUTO_TEST_CASE(TestPolygon)
		{
			CRegularPolygon shape(Color::Red, 5, { 2, 3 }, 4);

			ComparePair(shape.GetCenter(), { 2, 3 });
			BOOST_CHECK_EQUAL(shape.GetColor(), Color::Red);
			BOOST_CHECK_EQUAL(shape.GetVertexCount(), 5u);
			BOOST_CHECK_CLOSE(shape.GetRadius(), 4, EPSILION);

			std::shared_ptr<TestCanvas> canvas = std::make_shared<TestCanvas>();
			std::shared_ptr<ICanvas> canvasBase = canvas;
			shape.Draw(canvasBase);

			BOOST_CHECK_EQUAL(canvas->m_color, Color::Red);
			BOOST_CHECK_EQUAL(canvas->m_lineArr.size(), 5u);
		}
		BOOST_AUTO_TEST_CASE(TestPolygonError)
		{
			BOOST_CHECK_THROW(CRegularPolygon(Color::Red, 2, { 2, 3 }, 4), std::invalid_argument);
		}
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(TestFactory)
		BOOST_AUTO_TEST_CASE(TestFactoryTriangle)
		{
			CShapeFactory factory;
			std::shared_ptr<CShape> shape = factory.CreateShape("triangle 1 2 3 4 5 6 0");

			std::shared_ptr<TestCanvas> canvas = std::make_shared<TestCanvas>();
			std::shared_ptr<ICanvas> canvasBase = canvas;
			shape->Draw(canvasBase);

			BOOST_CHECK_EQUAL(canvas->m_color, Color::Green);
			BOOST_CHECK_EQUAL(canvas->m_lineArr.size(), 3u);

			ComparePair(canvas->m_lineArr[0].first, { 1, 2 });
			ComparePair(canvas->m_lineArr[0].second, { 3, 4 });

			ComparePair(canvas->m_lineArr[1].first, { 3, 4 });
			ComparePair(canvas->m_lineArr[1].second, { 5, 6 });

			ComparePair(canvas->m_lineArr[2].first, { 5, 6 });
			ComparePair(canvas->m_lineArr[2].second, { 1, 2 });
		}

		BOOST_AUTO_TEST_CASE(TestFactoryEllipse)
		{
			CShapeFactory factory;
			std::shared_ptr<CShape> shape = factory.CreateShape("ellipse 1 2 3 4 0");

			std::shared_ptr<TestCanvas> canvas = std::make_shared<TestCanvas>();
			std::shared_ptr<ICanvas> canvasBase = canvas;
			shape->Draw(canvasBase);

			BOOST_CHECK_EQUAL(canvas->m_color, Color::Green);
			BOOST_CHECK_EQUAL(canvas->m_lineArr.size(), 0u);
			BOOST_CHECK_EQUAL(canvas->m_ellipseArr.size(), 1u);

			BOOST_CHECK_CLOSE(canvas->m_ellipseArr[0].width, 3, EPSILION);
			BOOST_CHECK_CLOSE(canvas->m_ellipseArr[0].height, 4, EPSILION);
			ComparePair(canvas->m_ellipseArr[0].leftTop, { 1, 2 });
		}

		BOOST_AUTO_TEST_CASE(TestFactoryRectangle)
		{
			CShapeFactory factory;
			std::shared_ptr<CShape> shape = factory.CreateShape("rectangle 1 2 3 4 5");

			std::shared_ptr<TestCanvas> canvas = std::make_shared<TestCanvas>();
			std::shared_ptr<ICanvas> canvasBase = canvas;
			shape->Draw(canvasBase);

			BOOST_CHECK_EQUAL(canvas->m_color, Color::Black);
			BOOST_CHECK_EQUAL(canvas->m_lineArr.size(), 4u);
			BOOST_CHECK_EQUAL(canvas->m_ellipseArr.size(), 0u);

			ComparePair(canvas->m_lineArr[0].first, { 1, 2 });
			ComparePair(canvas->m_lineArr[0].second, { 3, 2 });

			ComparePair(canvas->m_lineArr[1].first, { 1, 2 });
			ComparePair(canvas->m_lineArr[1].second, { 1, 4 });

			ComparePair(canvas->m_lineArr[2].first, { 3, 2 });
			ComparePair(canvas->m_lineArr[2].second, { 3, 4 });

			ComparePair(canvas->m_lineArr[3].first, { 1, 4 });
			ComparePair(canvas->m_lineArr[3].second, { 3, 4 });
		}

		BOOST_AUTO_TEST_CASE(TestFactoryPolygon)
		{
			CShapeFactory factory;
			std::shared_ptr<CShape> shape = factory.CreateShape("polygon 5 1 2 4 1");

			std::shared_ptr<TestCanvas> canvas = std::make_shared<TestCanvas>();
			std::shared_ptr<ICanvas> canvasBase = canvas;
			shape->Draw(canvasBase);

			BOOST_CHECK_EQUAL(canvas->m_color, Color::Red);
			BOOST_CHECK_EQUAL(canvas->m_lineArr.size(), 5u);
		}

		BOOST_AUTO_TEST_CASE(TestFactoryError)
		{
			CShapeFactory factory;
			BOOST_CHECK_THROW(factory.CreateShape("triangle 1 2 5 6 0"), std::invalid_argument);
			BOOST_CHECK_THROW(factory.CreateShape("treangle 1 2 3 4 5 6 0"), std::invalid_argument);
		}
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(TestDraft)
		BOOST_AUTO_TEST_CASE(TestGetters)
		{
			std::vector<std::shared_ptr<CShape>> shapeArr;

			std::shared_ptr<CShape> shape1 = std::make_shared<CTriangle>(Color::Green, Point{ 1, 2 }, Point{ 3, 4 }, Point{ 5, 6 });
			std::shared_ptr<CShape> shape2 = std::make_shared<CEllipse>(Color::Green, Point{ 1, 2 }, 3, 4);
			shapeArr.push_back(shape1);
			shapeArr.push_back(shape2);
			CPictureDraft draft(shapeArr);

			BOOST_CHECK_EQUAL(draft.GetShapeCount(), 2u);
			BOOST_CHECK_EQUAL(draft.GetShape(0), shape1);
			BOOST_CHECK_EQUAL(draft.GetShape(1), shape2);
		}
		BOOST_AUTO_TEST_CASE(TestError)
		{
			std::vector<std::shared_ptr<CShape>> shapeArr;

			std::shared_ptr<CShape> shape1 = std::make_shared<CTriangle>(Color::Green, Point{ 1, 2 }, Point{ 3, 4 }, Point{ 5, 6 });
			std::shared_ptr<CShape> shape2 = std::make_shared<CEllipse>(Color::Green, Point{ 1, 2 }, 3, 4);
			shapeArr.push_back(shape1);
			shapeArr.push_back(shape2);
			CPictureDraft draft(shapeArr);

			BOOST_CHECK_THROW(draft.GetShape(2), std::out_of_range);
		}
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(TestDraw)
		BOOST_AUTO_TEST_CASE(TestDesigner)
		{
			std::shared_ptr<IShapeFactory> factory = std::make_shared<CShapeFactory>();
			CDesigner designer(factory);

			std::stringstream ss("triangle 1 2 3 4 5 6 0\nellipse 1 2 3 4 1");
			CPictureDraft draft = designer.CreateDraft(ss);

			BOOST_CHECK_EQUAL(draft.GetShapeCount(), 2u);
			BOOST_CHECK_EQUAL(draft.GetShape(0)->GetColor(), Color::Green);
			BOOST_CHECK_EQUAL(draft.GetShape(1)->GetColor(), Color::Red);

			std::shared_ptr<TestCanvas> canvas = std::make_shared<TestCanvas>();
			std::shared_ptr<ICanvas> canvasBase = canvas;
			draft.GetShape(0)->Draw(canvasBase);

			BOOST_CHECK_EQUAL(canvas->m_color, Color::Green);
			BOOST_CHECK_EQUAL(canvas->m_lineArr.size(), 3u);

			ComparePair(canvas->m_lineArr[0].first, { 1, 2 });
			ComparePair(canvas->m_lineArr[0].second, { 3, 4 });

			ComparePair(canvas->m_lineArr[1].first, { 3, 4 });
			ComparePair(canvas->m_lineArr[1].second, { 5, 6 });

			ComparePair(canvas->m_lineArr[2].first, { 5, 6 });
			ComparePair(canvas->m_lineArr[2].second, { 1, 2 });

			draft.GetShape(1)->Draw(canvasBase);

			BOOST_CHECK_EQUAL(canvas->m_color, Color::Red);
			BOOST_CHECK_EQUAL(canvas->m_ellipseArr.size(), 1u);

			ComparePair(canvas->m_ellipseArr[0].leftTop, { 1, 2 });
			BOOST_CHECK_CLOSE(canvas->m_ellipseArr[0].width, 3, EPSILION);
			BOOST_CHECK_CLOSE(canvas->m_ellipseArr[0].height, 4, EPSILION);
		}
		BOOST_AUTO_TEST_CASE(TestPainter)
		{
			std::shared_ptr<IShapeFactory> factory = std::make_shared<CShapeFactory>();
			CDesigner designer(factory);

			std::stringstream ss("triangle 1 2 3 4 5 6 0\nellipse 1 2 3 4 1");
			CPictureDraft draft = designer.CreateDraft(ss);

			std::shared_ptr<TestCanvas> canvas = std::make_shared<TestCanvas>();
			std::shared_ptr<ICanvas> canvasBase = canvas;

			CPainter painter;
			painter.DrawPicture(draft, canvasBase);

			BOOST_CHECK_EQUAL(canvas->m_color, Color::Red);
			BOOST_CHECK_EQUAL(canvas->m_lineArr.size(), 3u);

			ComparePair(canvas->m_lineArr[0].first, { 1, 2 });
			ComparePair(canvas->m_lineArr[0].second, { 3, 4 });

			ComparePair(canvas->m_lineArr[1].first, { 3, 4 });
			ComparePair(canvas->m_lineArr[1].second, { 5, 6 });

			ComparePair(canvas->m_lineArr[2].first, { 5, 6 });
			ComparePair(canvas->m_lineArr[2].second, { 1, 2 });

			BOOST_CHECK_EQUAL(canvas->m_ellipseArr.size(), 1u);
			ComparePair(canvas->m_ellipseArr[0].leftTop, { 1, 2 });
			BOOST_CHECK_CLOSE(canvas->m_ellipseArr[0].width, 3, EPSILION);
			BOOST_CHECK_CLOSE(canvas->m_ellipseArr[0].height, 4, EPSILION);
		}
	BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()