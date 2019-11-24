#include "pch.h"
#include "CStyle.h"
#include "CRectangleShape.h"
#include "TestUtils.h"

using namespace std;

SCENARIO("Style can change properties")
{
	GIVEN("default style")
	{
		CStyle style;

		REQUIRE(style.IsEnabled().has_value());
		REQUIRE_FALSE(style.IsEnabled().value());
		REQUIRE_THROWS_AS(style.GetColor(), std::logic_error);

		WHEN("enable")
		{
			style.Enable(true);

			THEN("style isenabled is true and color is undefined")
			{
				CHECK(style.IsEnabled().has_value());
				CHECK(style.IsEnabled().value());
				CHECK_FALSE(style.GetColor().has_value());
			}

			AND_WHEN("set color")
			{
				style.SetColor(0xFF00FF0F);

				THEN("color is defined")
				{
					CHECK(style.GetColor().has_value());
					CHECK(style.GetColor().value() == 0xFF00FF0F);
				}
			}

			AND_WHEN("disable")
			{
				style.Enable(false);

				THEN("color is undefined")
				{
					CHECK(style.IsEnabled().has_value());
					CHECK_FALSE(style.IsEnabled().value());
					CHECK_THROWS_AS(style.GetColor(), std::logic_error);
				}
			}
		}
	}

	GIVEN("initialized style")
	{
		CStyle style(0x00FF00F0);

		REQUIRE(style.IsEnabled().has_value());
		REQUIRE(style.IsEnabled().value());

		REQUIRE(style.GetColor().has_value());
		REQUIRE(style.GetColor().value() == 0x00FF00F0);

		WHEN("disable and then enable")
		{
			style.Enable(false);
			style.Enable(true);

			THEN("style color is old value")
			{
				CHECK(style.GetColor().has_value());
				CHECK(style.GetColor().value() == 0x00FF00F0);
			}
		}
	}
}

SCENARIO("Shape style cannot be nullptr")
{
	GIVEN("nullptr style")
	{
		unique_ptr<IStyle> stylePtr = nullptr;

		THEN("shape initialization throw error")
		{
			CHECK_THROWS_AS(CRectangleShape({ { .0, .0 }, .0, .0 }, move(stylePtr), make_unique<CLineStyle>()), std::invalid_argument);
		}
	}
}