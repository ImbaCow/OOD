#pragma once
#include "pch.h"
#include "CModernCanvasAdapter.h"

#define BOOST_TEST_MODULE AdapterTest
#include <boost/test/unit_test.hpp>

using namespace std;

BOOST_AUTO_TEST_SUITE(TestObjectAdapter)
	BOOST_AUTO_TEST_CASE(TestDefautValues)
	{
		ostringstream out;
		CModernCanvasAdapter adapter(out);

		adapter.LineTo(1, 1);
		adapter.EndDraw();

		BOOST_CHECK_EQUAL(out.str(), R"(<draw>
  <line fromX="0" fromY="0" toX="1" toY="1">
    <color r="0" g="0" b="0" a="1" />
  </line>
</draw>
)");
	}
	BOOST_AUTO_TEST_CASE(TestSetColor)
	{
		ostringstream out;
		CModernCanvasAdapter adapter(out);

		adapter.SetColor(0xFF00FF00);
		adapter.LineTo(1, 1);

		adapter.SetColor(0x80808080);
		adapter.LineTo(2, 2);
		adapter.EndDraw();

		BOOST_CHECK_EQUAL(out.str(), R"(<draw>
  <line fromX="0" fromY="0" toX="1" toY="1">
    <color r="1" g="0" b="1" a="0" />
  </line>
  <line fromX="1" fromY="1" toX="2" toY="2">
    <color r="0.501961" g="0.501961" b="0.501961" a="0.501961" />
  </line>
</draw>
)");
	}
	BOOST_AUTO_TEST_CASE(TestUsePainter)
	{
		ostringstream out;
		CModernCanvasAdapter adapter(out);
		shape_drawing_lib::CCanvasPainter painter(adapter);

		shape_drawing_lib::CTriangle triangle({ 10, 15 }, { 100, 200 }, { 150, 250 }, 0x80808080);
		shape_drawing_lib::CRectangle rectangle({ 30, 40 }, 18, 24, 0xFFFFFFFF);

		painter.Draw(triangle);
		painter.Draw(rectangle);
		adapter.EndDraw();

		BOOST_CHECK_EQUAL(out.str(), R"(<draw>
  <line fromX="10" fromY="15" toX="100" toY="200">
    <color r="0.501961" g="0.501961" b="0.501961" a="0.501961" />
  </line>
  <line fromX="100" fromY="200" toX="150" toY="250">
    <color r="0.501961" g="0.501961" b="0.501961" a="0.501961" />
  </line>
  <line fromX="150" fromY="250" toX="10" toY="15">
    <color r="0.501961" g="0.501961" b="0.501961" a="0.501961" />
  </line>
  <line fromX="30" fromY="40" toX="48" toY="40">
    <color r="1" g="1" b="1" a="1" />
  </line>
  <line fromX="48" fromY="40" toX="48" toY="64">
    <color r="1" g="1" b="1" a="1" />
  </line>
  <line fromX="48" fromY="64" toX="48" toY="64">
    <color r="1" g="1" b="1" a="1" />
  </line>
  <line fromX="48" fromY="64" toX="48" toY="40">
    <color r="1" g="1" b="1" a="1" />
  </line>
</draw>
)");
	}

	struct CoutRedirect
	{
		CoutRedirect(std::streambuf* new_buffer)
			: old(std::cout.rdbuf(new_buffer))
		{
		}

		~CoutRedirect()
		{
			std::cout.rdbuf(old);
		}

	private:
		std::streambuf* old;
	};
	BOOST_AUTO_TEST_CASE(TestUseOldCanvas)
	{
		ostringstream out;

		{
			CoutRedirect guard(out.rdbuf());
			graphics_lib::CCanvas simpleCanvas;
			shape_drawing_lib::CCanvasPainter painter(simpleCanvas);

			shape_drawing_lib::CTriangle triangle({ 10, 15 }, { 100, 200 }, { 150, 250 }, 0x80808080);
			shape_drawing_lib::CRectangle rectangle({ 30, 40 }, 18, 24, 0xFFFFFFFF);

			painter.Draw(triangle);
			painter.Draw(rectangle);
		}
		BOOST_CHECK_EQUAL(out.str(), R"(SetColor (#80808080)
MoveTo (10, 15)
LineTo (100, 200)
LineTo (150, 250)
LineTo (10, 15)
SetColor (#ffffffff)
MoveTo (30, 40)
LineTo (48, 40)
LineTo (48, 64)
LineTo (48, 64)
LineTo (48, 40)
)");
	}
BOOST_AUTO_TEST_SUITE_END()
