#pragma once
#include "pch.h"
#include "CCoffee.h"
#include "CDoublePortion.h"
#include "CMilkshake.h"
#include "CChocolate.h"
#include "CCream.h"
#include "СLiquor.h"
#include "CSyrup.h"

#define BOOST_TEST_MODULE BeverageTest
#include <boost/test/unit_test.hpp>

using namespace std;

BOOST_AUTO_TEST_SUITE(BeverageTest)
	BOOST_AUTO_TEST_CASE(TestDoublePortion)
	{
		/*CCoffee coffee();
		CDoublePortion beverage(move(coffee));

		auto coffee = make_unique<CCoffee>()

		BOOST_CHECK_EQUAL(130, beverage.GetCost());
		BOOST_CHECK_EQUAL("2x of Coffee", beverage->GetDescription());*/
	}
BOOST_AUTO_TEST_SUITE_END()