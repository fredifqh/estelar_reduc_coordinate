#ifndef BASICS_FUNCTIONS_HPP
#define BASICS_FUNCTIONS_HPP

using namespace std;

double ConvertRAToDegrees(double, double, double); // Function to convert Right Ascention (hours, minutes and seconds) to degrees
double ConvertDecToDegrees(double, double, double); // Function to convert Declination (degrees, minutes and seconds) to degrees
//std::vector<double> ConvertDegRAtoRAcoord(double, double); // Function to convert Degrees in hours, minutes and seconds
void UnitVector(double, double, double, double u[3]); // Function to get unit vector
void RestaVector(double x[3], double y[3], double s[3]); // Function to rest vectors
double RAinDeg(double, double);
double DEinDeg(double, double, double);

vector<double> ConvertRAtoCoord(double);
vector<double> ConvertDEtoCoord(double); 

#endif // BASICS_FUNCTIONS_HPP
