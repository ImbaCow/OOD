#pragma once
#include "pch.h"
#include "CObservable.h"

struct SWeatherInfo
{
	double temperature;
	double humidity;
	double pressure;
};

class CWeatherData : public CObservable<SWeatherInfo>
{
public:
	double GetTemperature() const;
	double GetHumidity() const;
	double GetPressure() const;
	void MeasurementsChanged();
	void SetMeasurements(double temp, double humidity, double pressure);

protected:
	SWeatherInfo GetChangedData() const override;

private:
	double m_temperature;
	double m_humidity;
	double m_pressure;
};
