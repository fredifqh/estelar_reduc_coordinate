/*Client Code: client code, is the one that includes the main function. 
This file should be stored by the name main.cpp*/

#include <bits/stdc++.h>
#include "RedCelCoor.hpp"
#include "constant.hpp"
using namespace std;

int main(int argc, char const *argv[])
{
	ios_base::sync_with_stdio(0); // These lines make input and output more efficient
	cin.tie(0);

	string program_name = argv[0];
    double hourRA = atof(argv[1]);  
	double minuteRA = atof(argv[2]);  
   	double secondRA = atof(argv[3]); 
    double degreDec = atof(argv[4]); 
    double minuteDec = atof(argv[5]);     
    double secondDec = atof(argv[6]); 
    double muAlpha = atof(argv[7]);
    double muDelta = atof(argv[8]);
    double radialVelocity = atof(argv[9]);
    double paralaxe = atof(argv[10]);
    double tempo = atof(argv[11]);
    double TT = atof(argv[12]);
    double p4[3];
		
    ProperMotion(hourRA, minuteRA, secondRA, degreDec, minuteDec, secondDec, muAlpha, muDelta, radialVelocity, paralaxe, tempo, TT, p4);
}
