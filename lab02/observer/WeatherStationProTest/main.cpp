#pragma once
#include "pch.h"
#include "CStatsValue.h"
#include "CAngleStatsValue.h"
#include "CWeatherDataPro.h"
#include "TestObserver.h"

#define BOOST_TEST_MODULE WeatherProTest
#include <boost/test/unit_test.hpp>

using namespace std;

BOOST_AUTO_TEST_SUITE(WeatherProTest)
	BOOST_AUTO_TEST_SUITE(WeatherStationProTest)
		BOOST_AUTO_TEST_CASE(ProTest)
		{
			CWeatherDataPro data;
			TestObserver<SWeatherProInfo> obs;
			data.RegisterObserver(obs, 1);

			data.SetMeasurements(1, 2, 3, 4, 5);
			BOOST_CHECK_EQUAL(obs.GetLastInfo().temperature, 1);
			BOOST_CHECK_EQUAL(obs.GetLastInfo().humidity, 2);
			BOOST_CHECK_EQUAL(obs.GetLastInfo().pressure, 3);
			BOOST_CHECK_EQUAL(obs.GetLastInfo().windSpeed, 4);
			BOOST_CHECK_EQUAL(obs.GetLastInfo().windAngle, 5);
		}
		BOOST_AUTO_TEST_CASE(ProTestValue)
		{
			CStatsValue numValue;
			BOOST_CHECK(!numValue.GetAvgValue().has_value());
			BOOST_CHECK(!numValue.GetMaxValue().has_value());
			BOOST_CHECK(!numValue.GetMinValue().has_value());

			numValue.AddValue(12);
			BOOST_CHECK(numValue.GetAvgValue().has_value());
			BOOST_CHECK(numValue.GetMaxValue().has_value());
			BOOST_CHECK(numValue.GetMinValue().has_value());
			BOOST_CHECK_EQUAL(numValue.GetAvgValue().value(), 12);
			BOOST_CHECK_EQUAL(numValue.GetMaxValue().value(), 12);
			BOOST_CHECK_EQUAL(numValue.GetMinValue().value(), 12);

			numValue.AddValue(-6);
			BOOST_CHECK(numValue.GetAvgValue().has_value());
			BOOST_CHECK(numValue.GetMaxValue().has_value());
			BOOST_CHECK(numValue.GetMinValue().has_value());
			BOOST_CHECK_EQUAL(numValue.GetAvgValue().value(), 3);
			BOOST_CHECK_EQUAL(numValue.GetMaxValue().value(), 12);
			BOOST_CHECK_EQUAL(numValue.GetMinValue().value(), -6);

			numValue.AddValue(99);
			BOOST_CHECK(numValue.GetAvgValue().has_value());
			BOOST_CHECK(numValue.GetMaxValue().has_value());
			BOOST_CHECK(numValue.GetMinValue().has_value());
			BOOST_CHECK_EQUAL(numValue.GetAvgValue().value(), 35);
			BOOST_CHECK_EQUAL(numValue.GetMaxValue().value(), 99);
			BOOST_CHECK_EQUAL(numValue.GetMinValue().value(), -6);

			CAngleStatsValue angleValue;
		}
		BOOST_AUTO_TEST_CASE(ProTestAngleValue)
		{
			CAngleStatsValue numValue;
			BOOST_CHECK(!numValue.GetAvgValue().has_value());

			numValue.AddValue(0);
			BOOST_CHECK(numValue.GetAvgValue().has_value());
			BOOST_CHECK_EQUAL(numValue.GetAvgValue().value(), 0);

			numValue.AddValue(720);
			BOOST_CHECK(numValue.GetAvgValue().has_value());
			BOOST_CHECK_EQUAL(numValue.GetAvgValue().value(), 0);

			numValue.AddValue(180);
			BOOST_CHECK(numValue.GetAvgValue().has_value());
			BOOST_CHECK_EQUAL(numValue.GetAvgValue().value(), 60);

			numValue.AddValue(-540);
			BOOST_CHECK(numValue.GetAvgValue().has_value());
			BOOST_CHECK_EQUAL(numValue.GetAvgValue().value(), 90);

			CAngleStatsValue angleValue;
		}
	BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()