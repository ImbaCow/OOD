#pragma once
#include "pch.h"
#include "TestSelfDeleteObserver.h"
#include "CWeatherData.h"
#include "TestPriorityObserver.h"
#include "TestObserver.h"

#define BOOST_TEST_MODULE WeatherTest
#include <boost/test/unit_test.hpp>

using namespace std;

BOOST_AUTO_TEST_SUITE(WeatherTest)
	BOOST_AUTO_TEST_SUITE(WeatherStationTest)
		BOOST_AUTO_TEST_CASE(SelfDeleteTest)
		{
			CWeatherData data;
			TestSelfDeleteObserver testObs1(data);
			TestObserver<SWeatherInfo> obs;
			TestSelfDeleteObserver testObs2(data);
			data.RegisterObserver(testObs1, 1u);
			data.RegisterObserver(obs, 1u);
			data.RegisterObserver(testObs2, 1u);

			BOOST_CHECK_NO_THROW(data.SetMeasurements(1, 1, 1));
		}
		BOOST_AUTO_TEST_CASE(PriorityTest)
		{
			CWeatherData data;
			vector<const TestPriorityObserver*> dataArr;
			TestPriorityObserver testObs1(&dataArr);
			TestPriorityObserver testObs2(&dataArr);
			data.RegisterObserver(testObs1, 2u);
			data.RegisterObserver(testObs2, 1u);

			BOOST_CHECK_NO_THROW(data.SetMeasurements(1, 1, 1));

			BOOST_CHECK_EQUAL(dataArr.size(), 2u);
			BOOST_CHECK_EQUAL(dataArr[0], &testObs2);
			BOOST_CHECK_EQUAL(dataArr[1], &testObs1);
		}
		BOOST_AUTO_TEST_CASE(EqualPriorityTest)
		{
			CWeatherData data;
			vector<const TestPriorityObserver*> dataArr;
			TestPriorityObserver testObs1(&dataArr);
			TestPriorityObserver testObs2(&dataArr);
			data.RegisterObserver(testObs1, 1u);
			data.RegisterObserver(testObs2, 1u);

			BOOST_CHECK_NO_THROW(data.SetMeasurements(1, 1, 1));

			BOOST_CHECK_EQUAL(dataArr.size(), 2u);
			if (&testObs1 < &testObs2)
			{
				BOOST_CHECK_EQUAL(dataArr[0], &testObs1);
				BOOST_CHECK_EQUAL(dataArr[1], &testObs2);
			}
			else
			{
				BOOST_CHECK_EQUAL(dataArr[0], &testObs2);
				BOOST_CHECK_EQUAL(dataArr[1], &testObs1);
			}
		}
		BOOST_AUTO_TEST_CASE(ReplceSelfObserverWithPriorityTest)
		{
			CWeatherData data;
			vector<const TestPriorityObserver*> dataArr;
			TestPriorityObserver testObs1(&dataArr);
			data.RegisterObserver(testObs1, 2);
			data.RegisterObserver(testObs1, 2);
			data.RegisterObserver(testObs1, 1);
			data.RegisterObserver(testObs1, 1);

			BOOST_CHECK_NO_THROW(data.SetMeasurements(1, 1, 1));

			BOOST_CHECK_EQUAL(dataArr.size(), 2u);
			BOOST_CHECK_EQUAL(dataArr[0], &testObs1);
			BOOST_CHECK_EQUAL(dataArr[1], &testObs1);
		}
	BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()