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

	Length l1 = 10_m;
	Time t1 = 60_s;
	Speed sp1 = l1/t1;
	Acceleration a2 = sp1/t1;

	cout << "travelling " << l1 << " in " << t1 <<
				" results in a velocity of " << sp1 << ". The acceleration is not " <<
				a2 << endl;

	cout << t1 << " in minutes = " << t1.in(minute) << endl;
	cout << l1 << " in km = " << l1.in(kilometre) << endl;

	Area a1 = l1*(5*l1);
	cout << l1 << " * (5*" << l1 << ") = " << a1 << "; in km2 = " << a1.in(kilometer2) << endl;

	Angle a3 = 3*3.1415926_rad;
	cout << a3 << " in deg: " << a3.in(degree) << " = " << a3.in(turn) << " turns" << endl;
	Angle a4 = 90_deg;
	cout << a4 << " in grad: " << a4.in(gradian) << " (c.lees!!!)" << endl;

	return 0;
}
