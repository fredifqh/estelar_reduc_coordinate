#include <bits/stdc++.h>
#include "constant.hpp"

using namespace std;

double declina;
double intparthourRA, intpartminuteRA, intparthourDE, intpartminuteDE;
vector<double> RAf = vector<double>(3);
vector<double> DEf = vector<double>(3);

// Function to convert Right ascension to degrees
double ConvertRAToDegrees(double x, double y, double z)
{
	return (x + y/60  + z/3600)*15;
}

// Function to convert Declination to degrees
double ConvertDecToDegrees(double a, double b, double c)
{
	if (a >= 0){
		declina = (a + b/60  + c/3600);
	}

	if (a < 0){
		declina = -1*(abs(a) + b/60  + c/3600);	
	}

	return declina;
}

// Implementing function to calculate unit vector

void UnitVector(double x, double y, double z, double u[3])
{
	u[0] = x/sqrt(pow(x,2) + pow(y,2) + pow(z,2));
	u[1] = y/sqrt(pow(x,2) + pow(y,2) + pow(z,2));
	u[2] = z/sqrt(pow(x,2) + pow(y,2) + pow(z,2));
}

// Implementing function to add two vectors

void RestaVector(double x[3], double y[3], double s[3])
{
	s[0] = x[0] - y[0];
	s[1] = x[1] - y[1];
	s[2] = x[2] - y[2];
}

// Function to get Right ascencion in degrees from state vector p3

double RAinDeg(double x, double y)
{
	double ra = atan2(y, x)*180/PI;

	if(ra < 0){
		ra += 360;
	}
	return ra;
}

// Function to get declination in degrees from state vector p3

double DEinDeg(double dex, double dey, double dez)
{
	dey = sqrt(pow(dex, 2) + pow(dey, 2));
	double de = atan2(dez, dey)*180/PI;
	return de;
}

// Functions to convert from RA and Declination in degrees to (hour, minute, second) and (°, ', ") respetively

vector<double> ConvertRAtoCoord(double RAinDegree) 
{	
	double fracHourRA = modf(RAinDegree/15,  &intparthourRA);
	RAf[0] = intparthourRA;   // RA hours
	double fracMinuRA = modf(fracHourRA*60,  &intpartminuteRA);
	RAf[1] = intpartminuteRA; // RA minutes
 	RAf[2] = fracMinuRA*60;   // RA seconds
 	return RAf;
}

vector<double> ConvertDEtoCoord(double DEinDegree) 
{
	if (DEinDegree < 0)
	{
		double fracHourDE = modf(DEinDegree, &intparthourDE);
		DEf[0] = intparthourDE;   // DE hours
		double fracMinuDE = modf(fracHourDE*60, &intpartminuteDE);
		DEf[1] = intpartminuteDE; // DE minutes
	 	DEf[2] = fracMinuDE*60;   // DE seconds
	}

 	else
 	{
		double fracHourDE = modf(abs(DEinDegree), &intparthourDE);
		DEf[0] = -1*intparthourDE;   // DE hours
		double fracMinuDE = modf(fracHourDE*60, &intpartminuteDE);
		DEf[1] = intpartminuteDE; // DE minutes
	 	DEf[2] = fracMinuDE*60;   // DE seconds
 	}
return DEf;
}

