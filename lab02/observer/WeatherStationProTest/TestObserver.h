#pragma once
#include "CWeatherDataPro.h"

template <typename T>
class TestObserver : public IObserver<T>
{
public:
	virtual void Update(T const& data) override;
	virtual ~TestObserver() = default;

	T GetLastInfo() const
	{
		return lastInfo;
	}

private:
	T lastInfo;
};

template <typename T>
void TestObserver<T>::Update(const T& data)
{
	lastInfo = data;
}
