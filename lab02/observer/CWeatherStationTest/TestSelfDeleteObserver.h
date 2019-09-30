#pragma once
#include "CWeatherData.h"

class TestSelfDeleteObserver : public IObserver<SWeatherInfo>
{
public:
	TestSelfDeleteObserver(CObservable<SWeatherInfo>& data);
	virtual ~TestSelfDeleteObserver() = default;

	virtual void Update(SWeatherInfo const& data);
	SWeatherInfo GetLastInfo()
	{
		return lastInfo;
	}

private:
	CObservable<SWeatherInfo>& data;
	SWeatherInfo lastInfo;
};

TestSelfDeleteObserver::TestSelfDeleteObserver(CObservable<SWeatherInfo>& data)
	: data(data)
{
}

inline void TestSelfDeleteObserver::Update(const SWeatherInfo& info)
{
	lastInfo = info;
	data.RemoveObserver(*this);
}
