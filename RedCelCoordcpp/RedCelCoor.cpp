#include <bits/stdc++.h>
#include "RedCelCoor.hpp"	
#include "functions.hpp"
#include "constant.hpp"

#include "sofa.h"
#include "sofam.h"

using namespace std;

double e[3] = {};
double p[3] = {};
double q[3] = {};
double E[3] = {};	
double v[3] = {}; 
double m[3] = {}; 
double n[3] = {};
double z[3] = {};

vector<double> P = vector<double>(3);

double EB[3] = {-0.170461291, 0.887837737, 0.384890537}; // vector baricentro-Tierra
double SB[3] = {-0.003241859, 0.001221246, 0.000530395}; // vector baricentro-Sol

void ProperMotion(double hourRA, double minuteRA, double secondRA,  \
                  double degreDec, double minuteDec, double secondDec,\
                  double muAlpha, double muDelta, double radialVelocity, 
                  double paralaxe, double tempo, double TT, double p3[3])
{
    double	RA = ConvertRAToDegrees(hourRA, minuteRA, secondRA)*PI/180; // RA in radians
    double	DEC = ConvertDecToDegrees(degreDec, minuteDec, secondDec)*PI/180; // Declination in radians

	//cout << setprecision (10) << "Initial Righ Ascention in degrees = " << RA*180/PI << "\n" << "Initial Declination in degrees = " << DEC*180/PI << "\n";

	m[0] = cos(DEC)*cos(RA);
	m[1] = cos(DEC)*sin(RA);
	m[2] = sin(DEC);

	n[0] = -1*sin(RA);
	n[1] = cos(RA);
	n[2] = 0;

	z[0] = -1*sin(DEC)*cos(RA);
	z[1] = -1*sin(DEC)*sin(RA);
	z[2] = cos(DEC);
	
	v[0] = m[0] + f*tempo*(A*radialVelocity*paralaxe*m[0] + muAlpha*n[0] + muDelta*z[0]);
	v[1] = m[1] + f*tempo*(A*radialVelocity*paralaxe*m[1] + muAlpha*n[1] + muDelta*z[1]);
	v[2] = m[2] + f*tempo*(A*radialVelocity*paralaxe*m[2] + muAlpha*n[2] + muDelta*z[2]);

	//cout << setprecision (15) << P[0] << "  " << P[1] << "  " << P[2] << "\n";

	P[0] = v[0] - 3.5973e-06*EB[0];
	P[1] = v[1] - 3.5973e-06*EB[1];
	P[2] = v[2] - 3.5973e-06*EB[2];

	UnitVector(P[0], P[1], P[2], p); // 
	RestaVector(EB, SB, E); 
	UnitVector(E[0], E[1], E[2], e); // vector unitary de E
	cout << setprecision (15) << E[0] << "  " << E[1] << "  " << E[2] << "\n";

						//Ligh Deflection// 
	/* 
	Call function  iauLd to get light deflection from software tools  
	iauLd ( bm, p, q, e, em, dlim, p1 );
	*/
	double bm = 1; // mass of the gravitating body (solar masses)
	double em = 0.983337930; // distance from body to observer (au)
	double dlim = 6e-06; // deflection limiter (Note 4)
	double p1[3]; // direction from observer to source (unit vector)
	// q = p  because the star is located too long, the distance from body to source and the distance from observer to source are the same
	iauLd( bm, p, p, e, em, dlim, p1); 
	cout << setprecision(10) << "p1 = " << p1[0] << "  " << p1[1] << "  " << p1[2] << "\n";

						//Aberration// 
	/*
	Call function  iauAb to get Aberration from software tools 
	iauAb ( pnat, v, s, bm1, ppr );
	*/
	double vc = 0.005775518331;                                                                                                                   
	double bm1; // reciprocal of Lorenz factor
	double v[3] = {-0.017229052*vc, -0.002753491*vc, -0.001193498*vc}; //observer barycentric velocity in units of c
	double s = 0.983337930; // distance between the Sun and the observer (au)
	bm1 = pow((1 - (v[0]*v[0] + v[1]*v[1] + v[2]*v[2])),0.5); 
	double ppr[3];
	// pnat = p1 
	iauAb (p1, v, s, bm1, ppr);
	std::cout <<  std::setprecision(10) << "p2 = " << ppr[0] << "  "<< ppr[1] << "  " << ppr[2] << "\n";

			 //matrix of precession-nutation including frame bias// 
	/*
	Call function  iauPnm06a from software tools to get matrix of precesion and nutation and bias frame
	iauPnm06a(date1, date2, rnpb);
	*/
	double date1, date2;
 	double rnpb[3][3];
 	date1 = T0;
 	date2 = TT - T0;
	iauPnm06a(date1, date2, rnpb);
	//double p3[3];
	iauRxp(rnpb, ppr, p3); // product of r−matrix and pv−vector to get the state vector p3
	std::cout <<  std::setprecision(10) << "p3 = " << p3[0] << "  "<< p3[1] << "  " << p3[2] << "\n";

				// Getting right ascention from state vector p3 //
	double x = p3[0];
	double y = p3[1];
	double ra;
	ra = RAinDeg(x, y);

				// Getting declination from state vector p3 //
	double de;
	de = DEinDeg(p3[0], p3[1], p3[2]);
	
				// Transforming Right Ascension //
	vector<double>  RightAscencion;
	RightAscencion = ConvertRAtoCoord(ra);
	cout << setprecision(10) << "Right Ascension = " << RightAscencion[0] << "  "<< RightAscencion[1] << "  " << RightAscencion[2] << "\n";

	
	vector<double>  Declination;
	Declination = ConvertDEtoCoord(de);
	cout << setprecision(10) << "Declination = " << Declination[0] << "  "<< Declination[1] << "  " << Declination[2] << "\n";
} 
