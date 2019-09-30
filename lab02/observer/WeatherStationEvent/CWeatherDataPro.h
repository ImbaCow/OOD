#pragma once
#include "pch.h"
#include "CObservable.h"

struct SWeatherProInfo
{
	double temperature;
	double humidity;
	double pressure;
	double windSpeed;
	double windAngle;
};

class CWeatherDataPro : public CObservable<SWeatherProInfo>
{
public:
	double GetTemperature() const;
	double GetHumidity() const;
	double GetPressure() const;
	double GetWindSpeed() const;
	double GetWindAngle() const;
	void MeasurementsChanged();
	void SetMeasurements(double temp, double humidity, double pressure, double windSpeed, double windAngle);

protected:
	SWeatherProInfo GetChangedData() const override;

private:
	double m_temperature;
	double m_humidity;
	double m_pressure;
	double m_windSpeed;
	double m_windAngle;
};
