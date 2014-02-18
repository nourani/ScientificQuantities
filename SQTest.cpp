/*
 * main.cpp
 *
 *  Created on: Feb 11, 2014
 *      Author: navid
 */

#include <iostream>

#include "ScientificQuantities.hpp"

using namespace SciQ;
using namespace std;

int main( int argc, char ** argv ) {

	cout << "The base SI units are: " << endl
				<< "\tLength:              " << Length(1) << endl
				<< "\tMass:                " << Mass(1) << endl
				<< "\tTime:                " << Time(1) << endl
				<< "\tCurrent:             " << Current(1) << endl
				<< "\tTemperature:         " << Temperature(1) << endl
				<< "\tAmount of Substance: " << Substance(1) << endl
				<< "\tLuminous intensity:  " << Luminous(1) << endl;

	cout << endl << "The derived SI units are: " << endl
				<< "\tAngle:               " << Angle(1) << endl
				<< "\tSolidAngle:          " << SolidAngle(1) << endl
				<< "\tFrequency:           " << Frequency(1) << endl
				<< "\tForce:               " << Force(1) << endl
				<< "\tPressure:            " << Pressure(1) << endl
				<< "\tEnergy:              " << Energy(1) << endl
				<< "\tPower:               " << Power(1) << endl
				<< "\tCharge:              " << Charge(1) << endl
				<< "\tVoltage:             " << Voltage(1) << endl
				<< "\tCapacitance:         " << Capacitance(1) << endl
				<< "\tResistance:          " << Resistance(1) << endl
				<< "\tConductance:         " << Conductance(1) << endl
				<< "\tMagnetic Flux:       " << MagneticFlux(1) << endl
				<< "\tMagnetic Field:      " << MagneticField(1) << endl
				<< "\tInductance:          " << Inductance(1) << endl
				<< "\tLuminous Flux:       " << LuminousFlux(1) << endl
				<< "\tIlluminance:         " << Illuminance(1) << endl
				<< "\tRadioactivity:       " << Radioactivity(1) << endl
				<< "\tAbsorbed dose:       " << AbsorbedDose(1) << endl
				<< "\tEquivalent dose:     " << EquivalentDose(1) << endl
				<< "\tCatalytic activity:  " << CatalyticActivity(1) << endl;

	cout << endl << "Some additional units defined are: " << endl
				<< "\tArea:                " << Area(1) << endl
				<< "\tVolume:              " << Volume(1) << endl
				<< "\tSpeed:               " << Speed(1) << endl
				<< "\tAcceleration:        " << Acceleration(1) << endl;

	cout << endl << "The following conversions are supported: " << endl
				<< "\t kilometre:   " << kilometre << endl
				<< "\t metre:       " << metre << endl
				<< "\t centimetre:  " << centimetre << endl
				<< "\t milimetre:   " << milimetre << endl
				<< "\t tonne:       " << tonne << endl
				<< "\t kilogram:    " << kilogram << endl
				<< "\t gram:        " << gram << endl
				<< "\t kilometre2:  " << kilometre2 << endl
				<< "\t metre2:      " << metre2 << endl
				<< "\t second:      " << second << endl
				<< "\t minute:      " << minute << endl
				<< "\t hour:        " << hour << endl
				<< "\t day:         " << day << endl
				<< "\t kelvin:      " << kelvin << endl
				<< "\t celcius:     " << celcius << endl
				<< "\t fahrenhein:  " << fahrenheit << endl
				<< "\t radian:      " << radian << endl
				<< "\t degree:      " << degree << endl
				<< "\t gradian:     " << gradian << endl
				<< "\t turn:        " << turn << endl
				<< "\t angleminute: " << angleminute << endl
				<< "\t anglesecond: " << anglesecond << endl
				<< "\t litre:       " << litre << endl
				<< "\t bar:         " << bar << endl
				<< "\t atm:         " << atm << endl;

	cout << endl << "The following units are available: " << endl
				<< "\t_km, _m, _cm, _mm, _nm" << endl
				<< "\t_tonne, _kg, _g" << endl
				<< "\t_s, _sec, _min, _hr, _hour, _Hz" << endl
				<< "\t_A, _J, _V, _W, _C, _F, _Ohm, _S, _H" << endl
				<< "\t_K, _degC" << endl
				<< "\t_mol, _Bq, _Gy, _kat" << endl
				<< "\t_cd, _lm, _lx" << endl
				<< "\t_rad, _deg" << endl
				<< "\t_N, _Pa, _bar, _atm" << endl
				<< "\t_Wb, _T" << endl
				<< "\t_m2, _m3" << endl
				<< "\t_mps, kmph" << endl;

	cout << endl << "Example usage:" << endl;
	Length l1 = 100_m;
	Time t1 = 60_s;
	Speed sp1 = l1 / t1;
	cout << "\n\tTravelling " << l1 << " in " << t1 << " results in a velocity of " << sp1 << "."
				<< endl;
	Acceleration a2 = 100_m / 10_s / 10_s;
	cout << "\n\tIf the acceleration was " << a2 << " then after " << t1
				<< " we would be traveling at " << a2 * t1 << endl;

	Frequency f1 = 1. / t1;
	cout << "\n\tIf the duration between two flashes is " << t1 << " then the light is flashing at "
				<< f1 << endl;

	Area a1 = l1 * l1;
	Volume v1 = a1 * l1;
	cout << "\n\t(" << l1 << " * " << l1 << ") = " << a1 << "; in km2 = " << a1.in( kilometre2 )
				<< endl;

	Angle a3 = M_PI*radian;
	a3 = 3. * a3;
	Angle a4 = 90_deg + 2_rad;
	cout << "\n\t" << t1 << " in minutes = " << t1.in( minute ) << endl;
	cout << "\n\t" << l1 << " in km = " << l1.in( kilometre ) << endl;
	cout << "\n\t" << a3 << " in deg: " << a3.in( degree ) << " = " << a3.in( turn ) << " turns"
				<< endl;
	cout << "\n\t" << a4 << " in grad: " << a4.in( gradian ) << " (c.lees!!!)" << endl;

	double l = l1;
	cout << "\n\tAssigning a length (" << l1 << ") to a double: " << l << endl;

	return 0;
}
