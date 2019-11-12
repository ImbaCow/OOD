#pragma once 
#include "catch2/catch.hpp"
#include "CommonTypes.h"

constexpr double DOUBLE_EPS = 0.00001;

using namespace Catch::Matchers::Floating;

inline void RequireDoubleEquality(double actual, double expected)
{
	REQUIRE_THAT(actual, WithinAbsMatcher(expected, DOUBLE_EPS));
}

inline void CheckDoubleEquality(double actual, double expected)
{
	CHECK_THAT(actual, WithinAbsMatcher(expected, DOUBLE_EPS));
}

inline void RequirePointEquality(const Point& actual, const Point& expected)
{
	RequireDoubleEquality(actual.x, expected.x);
	RequireDoubleEquality(actual.y, expected.y);
}

inline void CheckPointEquality(const Point& actual, const Point& expected)
{
	CheckDoubleEquality(actual.x, expected.x);
	CheckDoubleEquality(actual.y, expected.y);
}