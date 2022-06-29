/*
Author: Danilo Nascimento
E-mail: me@daniloonspace.com

This calculator is for Ground Station Visibility Estimation
Consider using a slant angle of 0, 5 or 10 depending on the location if there are buildings or mountains blocking the view
*/

#include <iostream>

#define _USE_MATH_DEFINES // Define before including to use math constants like m_pi , e...
#include <math.h>
using namespace std;

#define DEG2RAD M_PI/180.0 // Deg to radians
#define RAD2DEG 180.0/M_PI

// in SI units
const double Me = 5.972e+24; // Earth mass
const double Re = 6371000;  // Earth radius [m]
const double G = 6.67e-11;  // Universal constant of gravitation

double getOrbitalVelocity(double orbitHeight); // Tangencial Velocity in m/s
double getOrbitalPeriod(double orbitVelocity, double orbitAltitude); // Period in secs

int main()
{
    // std::cout << "Hello World!\n";

    double satHeight;

    cout << "\nSatellite Altitude [km]: ";
    cin >> satHeight;
    satHeight = Re + satHeight * 1000; // convert to Meters & height relative to the center of mass

    double slantAngle;
    cout << "\nSlant Angle [deg]: "; // 0, 5 , 10 deg
    cin >> slantAngle;
   // slantAngle *= DEG2RAD; // Convert to radians

    double orbitalVelocity = getOrbitalVelocity(satHeight);
    double orbitalPeriod = getOrbitalPeriod(orbitalVelocity,satHeight); 


    // Calculating the Geocentric Semi Angle
    double geocentricSemiAngle;
    double alpha;
    double theta = (90.0 + slantAngle)*DEG2RAD;
    alpha = asin((Re * sin(theta) / satHeight));
    alpha *= RAD2DEG;

    geocentricSemiAngle = 180.0 - (90.0 + slantAngle) - alpha;
   // geocentricSemiAngle *= DEG2RAD; // deg to rad

    double visibilityArc = (2*geocentricSemiAngle) * satHeight;

    double angularVelocity = orbitalVelocity / satHeight; // Angular velocity Of CubeSat

    double visibilityWindow = (2 * geocentricSemiAngle*DEG2RAD) / angularVelocity; // in secs


    cout << "\nResults" << endl;
    cout << "Satellite Height: " << (satHeight - Re) / 1000 << " km" << endl; // convert to km above MSL
    cout << "Slant Angle: " << slantAngle << " Deg" << endl;
    cout << "Geocentrical Semi-Angle: " << geocentricSemiAngle << " deg" << endl; // convert to deg
    cout << "Geocentrical Angle: " << 2*geocentricSemiAngle << " deg" << endl; // convert to deg
    cout << "Satellite Orbital Velocity: " << orbitalVelocity * 0.001 << " km/s" << endl; // convert to km/s
    cout << "Satellite Period: " << orbitalPeriod / 60.0 << " mins" << endl; // convert to mins
    cout << "Visibility Window: " << visibilityWindow / 60.0 << " mins" << endl; // convert to mins

    

}

double getOrbitalVelocity(double orbitHeight) {
    double velocity;

    velocity = sqrt((G * Me) / orbitHeight);

    return velocity;

}

double getOrbitalPeriod(double orbitVelocity, double orbitAltitude){
    double period;

    period = (2 * M_PI * (orbitAltitude)) / orbitVelocity;

    return period;

}

