#pragma once
#include "pch.h"
#include "CWeatherData.h"

class TestPriorityObserver : public IObserver<SWeatherInfo>
{
public:
	TestPriorityObserver(std::vector<const TestPriorityObserver*>* dataArr);
	virtual ~TestPriorityObserver() = default;

	virtual void Update(SWeatherInfo const& data) override;

	SWeatherInfo GetLastInfo() const
	{
		return lastInfo;
	}

private:
	std::vector<const TestPriorityObserver*>* dataArr;
	SWeatherInfo lastInfo;
};

inline TestPriorityObserver::TestPriorityObserver(std::vector<const TestPriorityObserver*>* dataArr)
	: dataArr(dataArr)
{
}

void TestPriorityObserver::Update(SWeatherInfo const& data)
{
	lastInfo = data;
	dataArr->push_back(this);
}
