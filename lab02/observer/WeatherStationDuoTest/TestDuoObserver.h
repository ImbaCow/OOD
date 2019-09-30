#pragma once
#include "pch.h"
#include "CWeatherData.h"

class TestDuoObserver : public IObserver<const CWeatherData&>
{
public:
	virtual ~TestDuoObserver() = default;

	virtual void Update(const CWeatherData& data) override;
	const CWeatherData* GetLastData();

private:
	const CWeatherData* lastData;
};

void TestDuoObserver::Update(const CWeatherData& data)
{
	lastData = &data;
}

inline const CWeatherData* TestDuoObserver::GetLastData()
{
	return lastData;
}
