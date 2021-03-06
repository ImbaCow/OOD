#pragma once
#include "pch.h"
#include "WeatherStationDuo.h"
#include "TestDuoObserver.h"

#define BOOST_TEST_MODULE WeatherDuoTest
#include <boost/test/unit_test.hpp>

using namespace std;

BOOST_AUTO_TEST_SUITE(WeatherDuoTest)
	BOOST_AUTO_TEST_SUITE(WeatherStationDuoTest)
		BOOST_AUTO_TEST_CASE(DuoTest)
		{
			WeatherStationDuo duoData;
			TestDuoObserver obs1;
			TestDuoObserver obs2;
			duoData.GetInData().RegisterObserver(obs1, 1);
			duoData.GetOutData().RegisterObserver(obs2, 1);

			duoData.GetInData().SetMeasurements(1, 1, 1);
			BOOST_CHECK_EQUAL(obs1.GetLastData(), &duoData.GetInData());
			BOOST_CHECK_EQUAL(obs1.GetLastData()->GetHumidity(), 1);
			BOOST_CHECK_EQUAL(obs1.GetLastData()->GetTemperature(), 1);
			BOOST_CHECK_EQUAL(obs1.GetLastData()->GetHumidity(), 1);

			duoData.GetOutData().SetMeasurements(2, 2, 2);
			BOOST_CHECK_EQUAL(obs2.GetLastData(), &duoData.GetOutData());
			BOOST_CHECK_EQUAL(obs2.GetLastData()->GetHumidity(), 2);
			BOOST_CHECK_EQUAL(obs2.GetLastData()->GetTemperature(), 2);
			BOOST_CHECK_EQUAL(obs2.GetLastData()->GetHumidity(), 2);
		}
		BOOST_AUTO_TEST_CASE(DuoSelfTest)
		{
			WeatherStationDuo duoData;
			TestDuoObserver obs;
			duoData.GetInData().RegisterObserver(obs, 1);
			duoData.GetOutData().RegisterObserver(obs, 1);

			duoData.GetInData().SetMeasurements(1, 1, 1);
			BOOST_CHECK_EQUAL(obs.GetLastData(), &duoData.GetInData());
			BOOST_CHECK_EQUAL(obs.GetLastData()->GetHumidity(), 1);
			BOOST_CHECK_EQUAL(obs.GetLastData()->GetTemperature(), 1);
			BOOST_CHECK_EQUAL(obs.GetLastData()->GetHumidity(), 1);

			duoData.GetOutData().SetMeasurements(2, 2, 2);
			BOOST_CHECK_EQUAL(obs.GetLastData(), &duoData.GetOutData());
			BOOST_CHECK_EQUAL(obs.GetLastData()->GetHumidity(), 2);
			BOOST_CHECK_EQUAL(obs.GetLastData()->GetTemperature(), 2);
			BOOST_CHECK_EQUAL(obs.GetLastData()->GetHumidity(), 2);
		}
	BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()