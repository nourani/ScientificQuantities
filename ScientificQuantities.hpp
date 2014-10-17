/*
 * ScientificQuantities.hpp
 * 	Inspired by:
 * 	- Stroustrup's 2012 talk (The idea of employing literals)
 * 	- http://www.codeproject.com/Articles/447922/Application-of-Cplusplus11-User-Defined-Literals-t (how to set up the classes and conversions)
 * 	- http://grahampentheny.com/archives/106 (explicit class declaration)
 *
 *  Created on: Feb 11, 2014
 *      Author: navid nourani-vatani
 *      Location: https://github.com/nourani/ScientificQuantities
 */

#ifndef SCIENTIFICQUANTITIES_HPP_
#define SCIENTIFICQUANTITIES_HPP_

#include <ostream>
#include <cmath>
#include <assert.h>
#include <stdexcept>
#include <vector>

namespace SciQ {

	// The Quantity class based on the SI BASE units:
	// https://en.wikipedia.org/wiki/International_System_of_Units#Units_and_prefixes
	// TODO: can we use a string literal? We can use this to define the unit as well as
	//		coping with quantities with similar base units
	template<int L, int M, int T, int EC, int TT, int AS, int LI>
	class Quantity {
	public:
		// Constructor with explicit declaration ensures that a UNIT is given during
		// variable initialization
		constexpr explicit Quantity( double val=0 )
		: value( val ) {
		}

		constexpr Quantity( const Quantity& x )
		: value( x.value ) {

		}

		// Conversion to a different unit
		constexpr double in( const Quantity& rhs ) {
			return value / rhs.value;
		}

		template<int L2, int M2, int T2, int EC2, int TT2, int AS2, int LI2>
		bool compType( const Quantity<L2, M2, T2, EC2, TT2, AS2, LI2>& rhs ) {
			return (L==L2 && M==M2 && T==T2 && EC==EC2 && TT==TT2 && AS==AS2 && LI==LI2);
		}

		// Get function
		constexpr double getValue() {
			return value;
		}

		// Operator overloading
		Quantity& operator+=( const Quantity& rhs ) {
			value += rhs.value;
			return *this;
		}

		Quantity& operator-=( const Quantity& rhs ) {
			value -= rhs.value;
			return *this;
		}

		// Overloading the double operator allows us to work with the class seamlessly with other packages and environments
		operator double() {
			return value;
		}

	private:
		double value;
	};




	// C++11 Physical quantity classes
	// Base units of the SI system
	using Length 		= Quantity<1,0,0,0,0,0,0>;
	using Mass 			= Quantity<0,1,0,0,0,0,0>;
	using Time 			= Quantity<0,0,1,0,0,0,0>;
	using Current		= Quantity<0,0,0,1,0,0,0>;
	using Temperature 	= Quantity<0,0,0,0,1,0,0>;
	using Substance		= Quantity<0,0,0,0,0,1,0>;
	using Luminous		= Quantity<0,0,0,0,0,0,1>;

	// Derived SI units
	// TODO: How can we differentiate between
	//	- Angle vs SolidAngle and
	// 	- Luminous vs Luminous Flux and
	//	- Frequency vs Radioactivity??
	using Angle 		= Quantity<0,0,0,0,0,0,0>;
	using SolidAngle	= Quantity<0,0,0,0,0,0,0>;
	using Frequency 	= Quantity<0,0,-1,0,0,0,0>;
	using Force 		= Quantity<1,1,-2,0,0,0,0>;
	using Pressure		= Quantity<-1,1,-2,0,0,0,0>;
	using Energy		= Quantity<2,1,-2,0,0,0,0>;
	using Power			= Quantity<2,1,-3,0,0,0,0>;
	using Charge		= Quantity<0,0,1,1,0,0,0>;
	using Voltage		= Quantity<2,1,-3,-1,0,0,0>;
	using Capacitance	= Quantity<-2,-1,4,2,0,0,0>;
	using Resistance	= Quantity<2,1,-3,-2,0,0,0>;
	using Conductance	= Quantity<-2,-1,3,2,0,0,0>;
	using MagneticFlux	= Quantity<2,1,-2,-1,0,0,0>;
	using MagneticField = Quantity<0,1,-2,-2,0,0,0>;
	using Inductance	= Quantity<2,1,-2,-2,0,0,0>;
	using Temperature	= Quantity<0,0,0,0,1,0,0>;
	using LuminousFlux	= Quantity<0,0,0,0,0,0,1>;
	using Illuminance	= Quantity<-2,0,0,0,0,0,1>;
	using Radioactivity = Quantity<0,0,-1,0,0,0,0>;
	using AbsorbedDose 	= Quantity<2,0,-2,0,0,0,0>;
	using EquivalentDose= Quantity<2,0,-2,0,0,0,0>;
	using CatalyticActivity = Quantity<0,0,-1,0,0,1,0>;

	// Additional units for our purpose
	using Area 			= Quantity<2,0,0,0,0,0,0>;
	using Volume 		= Quantity<3,0,0,0,0,0,0>;
	using Speed 		= Quantity<1,0,-1,0,0,0,0>;
	using Acceleration 	= Quantity<1,0,-2,0,0,0,0>;


	// These are handy for the Convert functions to convert between units
	constexpr Length kilometre( 1e3 );
	constexpr Length metre( 1.0 );
	constexpr Length centimetre( 1e-2 );
	constexpr Length milimetre( 1e-3 );

	constexpr Mass kilogram( 1.0 );
	constexpr Mass gram( 1e-3 );
	constexpr Mass tonne( 1e3 );

	constexpr Area metre2( 1.0 );
	constexpr Area kilometre2( 1.0e6 );

	constexpr Time second( 1.0 );
	constexpr Time minute( 60 );
	constexpr Time hour( 60 * 24 );
	constexpr Time day( 24 * 60 * 24 );

	constexpr Temperature celcius( 273.15 );
	constexpr Temperature kelvin( 1.0 );
	constexpr Temperature fahrenheit( (1.0-32)*5/9+273.15 );

	constexpr Angle radian( 1.0 );
	constexpr Angle degree( M_PI / 180. );
	constexpr Angle gradian( 2 * M_PI / 400. ); // For c.lees!
	constexpr Angle turn( 2 * M_PI );
	constexpr Angle angleminute( M_PI/10800 );
	constexpr Angle anglesecond( M_PI/648000 );

	constexpr Volume litre( 0.001 );

	constexpr Pressure bar( 10e5 );
	constexpr Pressure atm( 101325 );

	// C++11 literals
	// NOTE: it is recommended to create own literals starting with _ as literals witout _
	//		may be defined by the system in the future and ours will be ignored then!
	constexpr Length operator"" _km(long double x) {return Length(x*1e3);}
	constexpr Length operator"" _km(unsigned long long x) {return Length(x*1e3);}
	constexpr Length operator"" _m(long double x) {return Length(x);}
	constexpr Length operator"" _m(unsigned long long x) {return Length(x);}
	constexpr Length operator"" _cm(long double x) {return Length(x/100.);}
	constexpr Length operator"" _cm(unsigned long long x) {return Length(x/100.);}
	constexpr Length operator"" _mm(long double x) {return Length(x/1.e3);}
	constexpr Length operator"" _mm(unsigned long long x) {return Length(x/1.e3);}
	constexpr Length operator"" _nm(long double x) {return Length(x/1.e6);}
	constexpr Length operator"" _nm(unsigned long long x) {return Length(x/1.e6);}

	constexpr Mass operator"" _tonne(long double x) {return Mass(x*1e3);}
	constexpr Mass operator"" _tonne(unsigned long long x) {return Mass(x*1e3);}
	constexpr Mass operator"" _kg(long double x) {return Mass(x);}
	constexpr Mass operator"" _kg(unsigned long long x) {return Mass(x);}
	constexpr Mass operator"" _g(long double x) {return Mass(x/1000.);}
	constexpr Mass operator"" _g(unsigned long long x) {return Mass(x/1000.);}

	constexpr Time operator"" _s(long double x) {return Time(x);}
	constexpr Time operator"" _s(unsigned long long x) {return Time(x);}
	constexpr Time operator"" _sec(long double x) {return Time(x);}
	constexpr Time operator"" _sec(unsigned long long x) {return Time(x);}
	constexpr Time operator"" _min(long double x) {return Time(x*60);}
	constexpr Time operator"" _min(unsigned long long x) {return Time(x*60);}
	constexpr Time operator"" _hr(long double x) {return Time(x*60*24);}
	constexpr Time operator"" _hr(unsigned long long x) {return Time(x*60*24);}
	constexpr Time operator"" _hour(long double x) {return Time(x*60*24);}
	constexpr Time operator"" _hour(unsigned long long x) {return Time(x*60*24);}
	constexpr Frequency operator"" _Hz(long double x) {return Frequency(x);}
	constexpr Frequency operator"" _Hz(unsigned long long x) {return Frequency(x);}

	constexpr Current operator"" _A(long double x) {return Current(x);}
	constexpr Current operator"" _A(unsigned long long x) {return Current(x);}
	constexpr Energy operator"" _J(long double x) {return Energy(x);}
	constexpr Energy operator"" _J(unsigned long long x) {return Energy(x);}
	constexpr Power operator"" _W(long double x) {return Power(x);}
	constexpr Power operator"" _W(unsigned long long x) {return Power(x);}
	constexpr Charge operator"" _C(long double x) {return Charge(x);}
	constexpr Charge operator"" _C(unsigned long long x) {return Charge(x);}
	constexpr Voltage operator"" _V(long double x) {return Voltage(x);}
	constexpr Voltage operator"" _V(unsigned long long x) {return Voltage(x);}
	constexpr Capacitance operator"" _F(long double x) {return Capacitance(x);}
	constexpr Capacitance operator"" _F(unsigned long long x) {return Capacitance(x);}
	constexpr Resistance operator"" _Ohm(long double x) {return Resistance(x);}
	constexpr Resistance operator"" _Ohm(unsigned long long x) {return Resistance(x);}
	constexpr Conductance operator"" _S(long double x) {return Conductance(x);}
	constexpr Conductance operator"" _S(unsigned long long x) {return Conductance(x);}
	constexpr Inductance operator"" _H(long double x) {return Inductance(x);}
	constexpr Inductance operator"" _H(unsigned long long x) {return Inductance(x);}

	constexpr Temperature operator"" _K(long double x) {return Temperature(x);}
	constexpr Temperature operator"" _K(unsigned long long x) {return Temperature(x);}
	constexpr Temperature operator"" _degC(long double x) {return Temperature(x-273.15);}
	constexpr Temperature operator"" _degC(unsigned long long x) {return Temperature(x-273.15);}

	constexpr Substance operator"" _mol(long double x) {return Substance(x);}
	constexpr Substance operator"" _mol(unsigned long long x) {return Substance(x);}
	constexpr Radioactivity operator"" _Bq(long double x) {return Radioactivity(x);}
	constexpr Radioactivity operator"" _Bq(unsigned long long x) {return Radioactivity(x);}
	constexpr AbsorbedDose operator"" _Gy(long double x) {return AbsorbedDose(x);}
	constexpr AbsorbedDose operator"" _Gy(unsigned long long x) {return AbsorbedDose(x);}
	constexpr EquivalentDose operator"" _Sv(long double x) {return EquivalentDose(x);}
	constexpr EquivalentDose operator"" _Sv(unsigned long long x) {return EquivalentDose(x);}
	constexpr CatalyticActivity operator"" _kat(long double x) {return CatalyticActivity(x);}
	constexpr CatalyticActivity operator"" _kat(unsigned long long x) {return CatalyticActivity(x);}

	constexpr Luminous operator"" _cd(long double x) {return Luminous(x);}
	constexpr Luminous operator"" _cd(unsigned long long x) {return Luminous(x);}
	constexpr LuminousFlux operator"" _lm(long double x) {return LuminousFlux(x);}
	constexpr LuminousFlux operator"" _lm(unsigned long long x) {return LuminousFlux(x);}
	constexpr Illuminance operator"" _lx(long double x) {return Illuminance(x);}
	constexpr Illuminance operator"" _lx(unsigned long long x) {return Illuminance(x);}

	constexpr Angle operator"" _rad(long double x) {return Angle(x);}
	constexpr Angle operator"" _rad(unsigned long long x) {return Angle(x);}
	constexpr Angle operator"" _deg(long double x) {return Angle(x/180.*M_PI);}
	constexpr Angle operator"" _deg(unsigned long long x) {return Angle(x/180.*M_PI);}

	constexpr Force operator"" _N(long double x) {return Force(x);}
	constexpr Force operator"" _N(unsigned long long x) {return Force(x);}
	constexpr Pressure operator"" _Pa(long double x) {return Pressure(x);}
	constexpr Pressure operator"" _Pa(unsigned long long x) {return Pressure(x);}
	constexpr Pressure operator"" _bar(long double x) {return Pressure(x*10e5);}
	constexpr Pressure operator"" _bar(unsigned long long x) {return Pressure(x*10e5);}
	constexpr Pressure operator"" _atm(long double x) {return Pressure(x*101325);}
	constexpr Pressure operator"" _atm(unsigned long long x) {return Pressure(x*101325);}

	constexpr MagneticFlux operator"" _Wb(long double x) {return MagneticFlux(x);}
	constexpr MagneticFlux operator"" _Wb(unsigned long long x) {return MagneticFlux(x);}
	constexpr MagneticField operator"" _T(long double x) {return MagneticField(x);}
	constexpr MagneticField operator"" _T(unsigned long long x) {return MagneticField(x);}

	constexpr Area operator"" _m2(long double x) {return Area(x);}
	constexpr Area operator"" _m2(unsigned long long x) {return Area(x);}
	constexpr Volume operator"" _m3(long double x) {return Volume(x);}
	constexpr Volume operator"" _m3(unsigned long long x) {return Volume(x);}

	constexpr Speed operator"" _mps(long double x) {return Speed(x);}
	constexpr Speed operator"" _mps(unsigned long long x) {return Speed(x);}
	constexpr Speed operator"" _kmph(long double x) {return Speed(x*1000./3600.);}
	constexpr Speed operator"" _kmph(unsigned long long x) {return Speed(x*1000./3600.);}

	/*
	 * Global operator overloads for the Quantity class
	 */
	template<int L, int M, int T, int EC, int TT, int AS, int LI>
	std::ostream& operator<<( std::ostream& os, const Quantity<L, M, T, EC, TT, AS, LI>& q ) {
        const std::vector<std::string> base_units {
            "m", "kg", "s", "A", "K", "mol", "cd"
        } ;
        const std::vector<int> exponents { 
            L, M, T, EC, TT, AS, LI
        } ;
        os << q.getValue() ;
        for(int i=0; i<exponents.size(); ++i) {
            if (0 == exponents[i]) {
                continue ;
            } 
            if (1 == exponents[i]) {
                os << " " << base_units[i] ; 
            } else {
                os << " " << base_units[i] << "^" << exponents[i] ;
            }
        }
        return os ; 
	}

	template<int L, int M, int T, int EC, int TT, int AS, int LI>
	Quantity<L, M, T, EC, TT, AS, LI> operator+( const Quantity<L, M, T, EC, TT, AS, LI>& lhs,
				const Quantity<L, M, T, EC, TT, AS, LI>& rhs ) {
		return Quantity<L, M, T, EC, TT, AS, LI>( lhs ) += rhs;
	}
	template<int L, int M, int T, int EC, int TT, int AS, int LI>
	Quantity<L, M, T, EC, TT, AS, LI> operator-(
				const Quantity<L, M, T, EC, TT, AS, LI>& lhs,
				const Quantity<L, M, T, EC, TT, AS, LI>& rhs ) {
		return Quantity<L, M, T, EC, TT, AS, LI>( lhs ) -= rhs;
	}
	template<int L1, int M1, int T1, int EC1, int TT1, int AS1, int LI1, int L2, int M2, int T2,
	int EC2, int TT2, int AS2, int LI2>
	Quantity<M1 + M2, L1 + L2, T1 + T2, EC1 + EC2, TT1 + TT2, AS1 + AS2, LI1 + LI2> operator*(
				const Quantity<M1, L1, T1, EC1, TT1, AS1, LI1>& lhs,
				const Quantity<M2, L2, T2, EC2, TT2, AS2, LI2>& rhs ) {
		return Quantity<M1 + M2, L1 + L2, T1 + T2, EC1 + EC2, TT1 + TT2, AS1 + AS2, LI1 + LI2>(
					lhs.getValue() * rhs.getValue() );
	}
	template<int L1, int M1, int T1, int EC1, int TT1, int AS1, int LI1, int L2, int M2, int T2,
	int EC2, int TT2, int AS2, int LI2>
	Quantity<M1 - M2, L1 - L2, T1 - T2, EC1 - EC2, TT1 - TT2, AS1 - AS2, LI1 - LI2> operator/(
				const Quantity<M1, L1, T1, EC1, TT1, AS1, LI1>& lhs,
				const Quantity<M2, L2, T2, EC2, TT2, AS2, LI2>& rhs ) {
		return Quantity<M1 - M2, L1 - L2, T1 - T2, EC1 - EC2, TT1 - TT2, AS1 - AS2, LI1 - LI2>(
					lhs.getValue() / rhs.getValue() );
	}
	// TODO: How can we enforce during compile that the types of the values being compared are the same?
	template<int L1, int M1, int T1, int EC1, int TT1, int AS1, int LI1, int L2, int M2, int T2,
	int EC2, int TT2, int AS2, int LI2>
	bool operator==( const Quantity<L1, M1, T1, EC1, TT1, AS1, LI1>& lhs,
				const Quantity<L2, M2, T2, EC2, TT2, AS2, LI2>& rhs ) {
		assert( L1 == L2 && M1 == M2 && T1 == T2 && EC1 == EC2 && TT1 == TT2 && AS1 == AS2 && LI1 == LI2 );
		return (lhs.getValue() == rhs.getValue());
	}
	template<int L1, int M1, int T1, int EC1, int TT1, int AS1, int LI1, int L2, int M2, int T2,
	int EC2, int TT2, int AS2, int LI2>
	bool operator!=( const Quantity<L1, M1, T1, EC1, TT1, AS1, LI1>& lhs,
				const Quantity<L2, M2, T2, EC2, TT2, AS2, LI2>& rhs ) {
		assert( L1 == L2 && M1 == M2 && T1 == T2 && EC1 == EC2 && TT1 == TT2 && AS1 == AS2 && LI1 == LI2 );
		return (lhs.getValue() != rhs.getValue());
	}
	template<int L1, int M1, int T1, int EC1, int TT1, int AS1, int LI1, int L2, int M2, int T2,
	int EC2, int TT2, int AS2, int LI2>
	bool operator<=( const Quantity<L1, M1, T1, EC1, TT1, AS1, LI1>& lhs,
				const Quantity<L2, M2, T2, EC2, TT2, AS2, LI2>& rhs ) {
		assert( L1 == L2 && M1 == M2 && T1 == T2 && EC1 == EC2 && TT1 == TT2 && AS1 == AS2 && LI1 == LI2 );
		return (lhs.getValue() <= rhs.getValue());
	}
	template<int L1, int M1, int T1, int EC1, int TT1, int AS1, int LI1, int L2, int M2, int T2,
	int EC2, int TT2, int AS2, int LI2>
	bool operator>=( const Quantity<L1, M1, T1, EC1, TT1, AS1, LI1>& lhs,
				const Quantity<L2, M2, T2, EC2, TT2, AS2, LI2>& rhs ) {
		assert( L1 == L2 && M1 == M2 && T1 == T2 && EC1 == EC2 && TT1 == TT2 && AS1 == AS2 && LI1 == LI2 );
		return (lhs.getValue() >= rhs.getValue());
	}
	template<int L1, int M1, int T1, int EC1, int TT1, int AS1, int LI1, int L2, int M2, int T2,
	int EC2, int TT2, int AS2, int LI2>
	bool operator<( const Quantity<L1, M1, T1, EC1, TT1, AS1, LI1>& lhs,
				const Quantity<L2, M2, T2, EC2, TT2, AS2, LI2>& rhs ) {
		assert( L1 == L2 && M1 == M2 && T1 == T2 && EC1 == EC2 && TT1 == TT2 && AS1 == AS2 && LI1 == LI2 );
		return (lhs.getValue() < rhs.getValue());
	}
	template<int L1, int M1, int T1, int EC1, int TT1, int AS1, int LI1, int L2, int M2, int T2,
	int EC2, int TT2, int AS2, int LI2>
	bool operator>( const Quantity<L1, M1, T1, EC1, TT1, AS1, LI1>& lhs,
				const Quantity<L2, M2, T2, EC2, TT2, AS2, LI2>& rhs ) {
		assert( L1 == L2 && M1 == M2 && T1 == T2 && EC1 == EC2 && TT1 == TT2 && AS1 == AS2 && LI1 == LI2 );
		return (lhs.getValue() > rhs.getValue());
	}


	// Global operator overloading with typename Type
	template<typename Type, int L, int M, int T, int EC, int TT, int AS, int LI>
	Quantity<L, M, T, EC, TT, AS, LI> operator*( const Quantity<L, M, T, EC, TT, AS, LI>& lhs,
				const Type rhs ) {
		return Quantity<L, M, T, EC, TT, AS, LI>( lhs.getValue() * rhs );
	}
	template<typename Type, int L, int M, int T, int EC, int TT, int AS, int LI>
	Quantity<L, M, T, EC, TT, AS, LI> operator*( const Type lhs,
				const Quantity<L, M, T, EC, TT, AS, LI>& rhs ) {
		return Quantity<L, M, T, EC, TT, AS, LI>( lhs * rhs.getValue() );
	}
	template<typename Type, int L, int M, int T, int EC, int TT, int AS, int LI>
	Quantity<L, M, T, EC, TT, AS, LI> operator/( const Quantity<L, M, T, EC, TT, AS, LI>& lhs,
				const Type rhs ) {
		return Quantity<L, M, T, EC, TT, AS, LI>( lhs.getValue() / rhs );
	}
	template<typename Type, int L, int M, int T, int EC, int TT, int AS, int LI>
	Quantity<-L, -M, -T, -EC, -TT, -AS, -LI> operator/( const Type lhs,
				const Quantity<L, M, T, EC, TT, AS, LI>& rhs ) {
		return Quantity<-L, -M, -T, -EC, -TT, -AS, -LI>( lhs / rhs.getValue() );
	}

}
// namespace SciQ;

// conversion macro
#define ConvertTo(_x, _y) (_x).Convert(1.0_##_y)

#endif /* SCIENTIFICQUANTITIES_HPP_ */
