/*
 * ScientificQuantities.hpp
 * 	Inspired by:
 * 	- Stroustrup's 2012 talk (The idea of employing literals)
 * 	- http://www.codeproject.com/Articles/447922/Application-of-Cplusplus11-User-Defined-Literals-t (how to set up the classes and conversions)
 * 	- http://grahampentheny.com/archives/106 (explicit class declaration)
 *
 *  Created on: Feb 11, 2014
 *      Author: navid
 */

#ifndef SCIENTIFICQUANTITIES_HPP_
#define SCIENTIFICQUANTITIES_HPP_

#include <cmath>

namespace SciQ {

	// The Quantity class
	template<int M, int L, int T>
	class Quantity {
	public:
		constexpr explicit Quantity( double val )
					: value( val ) {
		}

		constexpr Quantity( const Quantity& x )
					: value( x.value ) {

		}
//    NOTE: We can't do these anymore because the class is constexpr
//    constexpr Quantity& operator+=(const Quantity& rhs)
//    {
//        value+=rhs.value;
//        return *this;
//    }
//
//    constexpr Quantity& operator-=(const Quantity& rhs)
//    {
//        value-=rhs.value;
//        return *this;
//    }

		constexpr double in( const Quantity& rhs ) {
			return value / rhs.value;
		}

		constexpr double getValue() {
			return value;
		}

	private:
		double value;
	};

	// extra functions to manipulate the Quantity object
	template<int M, int L, int T>
	std::ostream& operator<<( std::ostream& os, const Quantity<M, L, T>& q ) {
		std::string unit = "";
		if( M ) {
			if( M < 0 ) {
				if( !unit.size() )
					unit += "1";
				unit += "/";
			}
			unit += "kg";
			if( abs( M ) > 1 ) {
				unit += std::to_string( abs( M ) );
			}
		}
		if( L ) {
			if( L < 0 ) {
				if( !unit.size() )
					unit += "1";
				unit += "/";
			}
			unit += "m";
			if( abs( L ) > 1 ) {
				unit += std::to_string( abs( L ) );
			}
		}
		if( T ) {
			if( T < 0 ) {
				if( !unit.size() )
					unit += "1";
				unit += "/";
			}
			unit += "s";
			if( abs( T ) > 1 ) {
				unit += std::to_string( abs( T ) );
			}
		}
		if( M == 0 && L == 0 && T == 0 ) { // angles are dimensionless although m/m
			unit += "rad";
		}
		os << q.getValue() << unit;
		return os;
	}
	template<int M, int L, int T>
	Quantity<M, L, T> operator+( const Quantity<M, L, T>& lhs, const Quantity<M, L, T>& rhs ) {
		return Quantity<M, L, T>( lhs ) += rhs;
	}
	template<int M, int L, int T>
	Quantity<M, L, T> operator-( const Quantity<M, L, T>& lhs, const Quantity<M, L, T>& rhs ) {
		return Quantity<M, L, T>( lhs ) -= rhs;
	}
	template<int M1, int L1, int T1, int M2, int L2, int T2>
	Quantity<M1 + M2, L1 + L2, T1 + T2> operator*( const Quantity<M1, L1, T1>& lhs,
				const Quantity<M2, L2, T2>& rhs ) {
		return Quantity<M1 + M2, L1 + L2, T1 + T2>( lhs.getValue() * rhs.getValue() );
	}
	template<int M, int L, int T>
	Quantity<M, L, T> operator*( const double& lhs, const Quantity<M, L, T>& rhs ) {
		return Quantity<M, L, T>( lhs * rhs.getValue() );
	}

	template<int M1, int L1, int T1, int M2, int L2, int T2>
	Quantity<M1 - M2, L1 - L2, T1 - T2> operator/( const Quantity<M1, L1, T1>& lhs,
				const Quantity<M2, L2, T2>& rhs ) {
		return Quantity<M1 - M2, L1 - L2, T1 - T2>( lhs.getValue() / rhs.getValue() );
	}
	// TODO: does this make sense: Divide a number by a unit?
	//template<int M, int L, int T>
	//Quantity<-M, -L, -T> operator/( double x, const Quantity<M, L, T>& rhs ) {
	//	return Quantity<-M, -L, -T>( x / rhs.getValue() );
	//}

	template<int M, int L, int T>
	Quantity<M, L, T> operator/( const Quantity<M, L, T>& rhs, double x ) {
		return Quantity<M, L, T>( rhs.getValue() / x );
	}

	template<int M, int L, int T>
	bool operator==( const Quantity<M, L, T>& lhs, const Quantity<M, L, T>& rhs ) {
		return (lhs.getValue() == rhs.getValue());
	}

	template<int M, int L, int T>
	bool operator!=( const Quantity<M, L, T>& lhs, const Quantity<M, L, T>& rhs ) {
		return (lhs.getValue() != rhs.getValue());
	}

	template<int M, int L, int T>
	bool operator<=( const Quantity<M, L, T>& lhs, const Quantity<M, L, T>& rhs ) {
		return lhs.getValue() <= rhs.getValue();
	}
	template<int M, int L, int T>
	bool operator>=( const Quantity<M, L, T>& lhs, const Quantity<M, L, T>& rhs ) {
		return lhs.getValue() >= rhs.getValue();
	}
	template<int M, int L, int T>
	bool operator<( const Quantity<M, L, T>& lhs, const Quantity<M, L, T>& rhs ) {
		return lhs.getValue() < rhs.getValue();
	}
	template<int M, int L, int T>
	bool operator>( const Quantity<M, L, T>& lhs, const Quantity<M, L, T>& rhs ) {
		return lhs.getValue() > rhs.getValue();
	}

	// C++11 Physical quantity classes
	// Base unitsof the MLT system
	using Mass = Quantity<1,0,0>;
	using Length = Quantity<0,1,0>;
	using Time = Quantity<0,0,1>;
	// Derived units
	using Area = Quantity<0,2,0>;
	using Volume = Quantity<0,3,0>;
	using Speed = Quantity<0,1,-1>;
	using Acceleration = Quantity<0,1,-2>;
	using Frequency = Quantity<0,0,-1>;
	using Force = Quantity<1,1,-2>;
	using Pressure = Quantity<1,-1,-2>;
	using Angle = Quantity<0,0,0>;

	// These are handy for the Convert member function to convert between units
	constexpr Mass kilogram( 1.0 );
	constexpr Mass gram( 1.0e-3 );

	constexpr Length kilometre( 1e3 );
	constexpr Length kilometer( 1e3 );
	constexpr Length metre( 1.0 );
	constexpr Length meter( 1.0 );
	constexpr Length centimetre( 0.01 );
	constexpr Length centimeter( 0.01 );
	constexpr Length milimetre( 0.01 );
	constexpr Length milimeter( 0.01 );

	constexpr Area metre2( 1.0 );
	constexpr Area meter2( 1.0 );
	constexpr Area kilometre2( 1.0e6 );
	constexpr Area kilometer2( 1.0e6 );

	constexpr Time second( 1.0 );
	constexpr Time minute( 60 );
	constexpr Time hour( 60 * 24 );
	constexpr Time day( 24 * 60 * 24 );

	constexpr Angle radian( 1.0 );
	constexpr Angle degree( M_PI / 180. );
	constexpr Angle gradian( 2 * M_PI / 400. ); // For c.lees!
	constexpr Angle turn( 2 * M_PI );

// C++11 literals
// NOTE: it is recommended to create own literals starting with _ as literals witout _
//		may be defined by the system in the future and ours will be ignored then!
constexpr Mass operator"" _kg(long double x) {return Mass(x);}
constexpr Mass operator"" _kg(unsigned long long x) {return Mass(x);}
constexpr Mass operator"" _g(long double x) {return Mass(x/1000.);}
constexpr Mass operator"" _g(unsigned long long x) {return Mass(x/1000.);}

constexpr Length operator"" _km(long double x) {return Length(x*1000.);}
constexpr Length operator"" _km(unsigned long long x) {return Length(x*1000);}
constexpr Length operator"" _m(long double x) {return Length(x);}
constexpr Length operator"" _m(unsigned long long x) {return Length(x);}
constexpr Length operator"" _cm(long double x) {return Length(x/100.);}
constexpr Length operator"" _cm(unsigned long long x) {return Length(x/100.);}
constexpr Length operator"" _mm(long double x) {return Length(x/1000.);}
constexpr Length operator"" _mm(unsigned long long x) {return Length(x/1000.);}

constexpr Time operator"" _s(long double x) {return Time(x);}
constexpr Time operator"" _s(unsigned long long x) {return Time(x);}
constexpr Time operator"" _min(long double x) {return Time(x*60);}
constexpr Time operator"" _min(unsigned long long x) {return Time(x*60);}
constexpr Time operator"" _hr(long double x) {return Time(x*60*24);}
constexpr Time operator"" _hr(unsigned long long x) {return Time(x*60*24);}

constexpr Speed operator"" _mps(long double x) {return Speed(x);}
constexpr Speed operator"" _mps(unsigned long long x) {return Speed(x);}
constexpr Speed operator"" _kmph(long double x) {return Speed(x*1000./3600.);}
constexpr Speed operator"" _kmph(unsigned long long x) {return Speed(x*1000./3600.);}

constexpr Angle operator"" _rad(long double x) {return Angle(x);}
constexpr Angle operator"" _rad(unsigned long long x) {return Angle(x);}
constexpr Angle operator"" _deg(long double x) {return Angle(x/180.*M_PI);}
constexpr Angle operator"" _deg(unsigned long long x) {return Angle(x/180.*M_PI);}

}
	// namespace SciQ;

// conversion macro
#define ConvertTo(_x, _y) (_x).Convert(1.0_##_y)

#endif /* SCIENTIFICQUANTITIES_HPP_ */
