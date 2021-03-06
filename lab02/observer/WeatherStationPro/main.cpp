#include "pch.h"
#include "CDisplay.h"
#include "CStatsDisplay.h"

int main()
{
	CWeatherDataPro wd;

	CDisplay display;
	wd.RegisterObserver(display, 2);

	CStatsDisplay statsDisplay;
	wd.RegisterObserver(statsDisplay, 1);

	wd.SetMeasurements(3, 0.7, 760, 12, 0);
	wd.SetMeasurements(4, 0.8, 761, 15, 270);
	/*wd.SetMeasurements(10, 0.8, 761, 10, 180);
	wd.SetMeasurements(-10, 0.8, 761, 20, 270);*/
/*
	wd.RemoveObserver(statsDisplay);

	wd.SetMeasurements(10, 0.8, 761, 10, 180);
	.SetMeasurements(-10, 0.8, 761, 20, 270)*/
	system("pause");
	return 0;
}