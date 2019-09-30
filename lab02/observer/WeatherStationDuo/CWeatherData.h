#pragma once
#include "pch.h"
#include "CObservable.h"

class CWeatherData : public CObservable<const CWeatherData&>
{
public:
	double GetTemperature() const;
	double GetHumidity() const;
	double GetPressure() const;
	void MeasurementsChanged();
	void SetMeasurements(double temp, double humidity, double pressure);

protected:
	const CWeatherData& GetChangedData() const override;

private:
	double m_temperature;
	double m_humidity;
	double m_pressure;
};