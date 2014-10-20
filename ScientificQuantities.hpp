/*
 * ScientificQuantities.hpp
 *      Inspired by:
 *      - Stroustrup's 2012 talk (The idea of employing literals)
 *      - http://www.codeproject.com/Articles/447922/Application-of-Cplusplus11-User-Defined-Literals-t (how to set up the classes and conversions)
 *      - http://grahampentheny.com/archives/106 (explicit class declaration)
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
#include <array>

namespace SciQ {
    /**
     * Number of base units. 
     *
     * See http://physics.nist.gov/cuu/Units/units.html
     */
    constexpr int NUM_BASE_UNITS = 7 ;

    /**
     * This template is used to specify names of fundamental units of a
     * specific Quantity, T. For example, the fundamental unit of
     * Quantity<1,0,0,0,0,0,0> (i.e. Length) can be specified to be "m". This
     * information will be used when an instance of this Quantity<> is
     * displayed using operator<<(). Fundamental units of several quantities
     * are defined later in this file and users of this header may add
     * fundamental units for their own custom quantities. However, the same
     * quantity may not have two different fundamental units (this compiler
     * will catch this). If a quantity does not have an explicitly defined
     * FundamentalUnit then it will still be printed using a generic version
     * of operator<<() that simply displays its value and dimensionality.
     */
    template<typename T>
    struct FundamentalUnit 
    {} ;

    /**
     * Representation of a physical/scientific quantity using a combination of
     * seven base quantities: length (L), mass (M), temperature (T), electric
     * current (EC), thermodynamic temperature (TT), amount of substance (AS),
     * and luminous intensity (LI). See
     * [this](http://physics.nist.gov/cuu/Units/units.html) page for more
     * information. 
     *
     * \todo Can we use a string literal? We can use this to define the unit as
     * well as coping with quantities with similar base units
     * 
     * \see 
     * - [International System of Units: Units and Prefixes](https://en.wikipedia.org/wiki/International_System_of_Units#Units_and_prefixes)
     * - [SI Base Units](http://physics.nist.gov/cuu/Units/units.html)
     * - [Application of C++11 User-Defined Literals to Handling Scientific Quantities, Number Representation and String Manipulation](http://www.codeproject.com/Articles/447922/Application-of-Cplusplus11-User-Defined-Literals-t)
     * - [Fixing it once and for all: Enforcing units of measure in C++11](http://grahampentheny.com/archives/106)
     *
     */
    template<int L, int M, int T, int EC, int TT, int AS, int LI>
    class Quantity {
    public:
        /**
         * The type of the current Quantity. 
         */
        using Type = Quantity<L, M, T, EC, TT, AS, LI> ;

        /**
         * The fundamental unit corresponding to the current quantity. 
         */
        using FundamentalUnitType = FundamentalUnit<Type> ;

        /**
         * Explicit constructor to make sure that a unit is given during 
         * variable initialization. Creates a quantity with the specified
         * value (default: 0) in its fundamental unit. 
         */
        constexpr explicit Quantity( double val=0 ) 
        : value( val ) {
        }

        /**
         * Create a copy of the specified quantity. 
         */
        constexpr Quantity( const Quantity& x )
        : value( x.value ) {
        }

        /**
         * Get the value of the current quantity in units of the specified 
         * quantity, \c rhs. For example:
         *
         * \code
         * Length a = 1000.0 * meter ; 
         * std::cout << a.in(kilometer) << std::endl ;
         * \endcode
         *
         * The above code will display "1" as \c a equal 1000 m and this
         * value equals 1 km. 
         */
        constexpr double in( const Quantity& rhs ) {
            return value / rhs.value;
        }

        /**
         * Check if two different instantiations of this template correspond
         * to compatible physical values. In other works, all base unit 
         * exponents for both instantiations are indentical.
         *
         * \todo Not sure if we need this.
         */
        template<int L2, int M2, int T2, int EC2, int TT2, int AS2, int LI2>
        bool compType( const Quantity<L2, M2, T2, EC2, TT2, AS2, LI2>& rhs ) {
            return (L==L2 && M==M2 && T==T2 && EC==EC2 && TT==TT2 && AS==AS2 && LI==LI2);
        }

        /**
         * Get the value of the current quantity in its fundamental SI unit.
         */
        constexpr double getValue() {
            return value;
        }

        /**
         * Add the specified quantity, \c rhs, to this quantity. The value of
         * this quantity is updated.
         */
        Quantity& operator+=( const Quantity& rhs ) {
            value += rhs.value;
            return *this;
        }

        /**
         * Subtract the specified quantity, \c rhs, from this quantity. The 
         * value of this quantity is updated.
         */
        Quantity& operator-=( const Quantity& rhs ) {
            value -= rhs.value;
            return *this;
        }

        /**
         * Convert this quantity into a double. This is the same as calling
         * getValue(). Overloading the double operator allows us to work with
         * the class seamlessly with other packages and environments.
         */
        operator double() {
            return value;
        }
    private:
        /**
         * Value of this quantity in its fundamental SI units.
         */
        double value;
    };

    //
    // Arithmetic operators for Quantity<> instances.
    //
    template<int L, int M, int T, int EC, int TT, int AS, int LI>
    Quantity<L, M, T, EC, TT, AS, LI> 
    operator+( const Quantity<L, M, T, EC, TT, AS, LI>& lhs,
               const Quantity<L, M, T, EC, TT, AS, LI>& rhs ) {
        return Quantity<L, M, T, EC, TT, AS, LI>( lhs ) += rhs;
    }

    template<int L, int M, int T, int EC, int TT, int AS, int LI>
    Quantity<L, M, T, EC, TT, AS, LI> 
    operator-( const Quantity<L, M, T, EC, TT, AS, LI>& lhs,
               const Quantity<L, M, T, EC, TT, AS, LI>& rhs ) {
        return Quantity<L, M, T, EC, TT, AS, LI>( lhs ) -= rhs;
    }
    template<int L1, int M1, int T1, int EC1, int TT1, int AS1, int LI1, 
             int L2, int M2, int T2, int EC2, int TT2, int AS2, int LI2>
    Quantity<M1+M2, L1+L2, T1+T2, EC1+EC2, TT1+TT2, AS1+AS2, LI1+LI2> 
    operator*( const Quantity<M1, L1, T1, EC1, TT1, AS1, LI1>& lhs,
               const Quantity<M2, L2, T2, EC2, TT2, AS2, LI2>& rhs ) {
        using ResultType = Quantity<M1+M2, L1+L2, T1+T2, EC1+EC2, TT1+TT2, AS1+AS2, LI1+LI2> ;
        return ResultType( lhs.getValue() * rhs.getValue() );
    }
    template<int L1, int M1, int T1, int EC1, int TT1, int AS1, int LI1, 
             int L2, int M2, int T2, int EC2, int TT2, int AS2, int LI2>
    Quantity<M1-M2, L1-L2, T1-T2, EC1-EC2, TT1-TT2, AS1-AS2, LI1-LI2>
    operator/( const Quantity<M1, L1, T1, EC1, TT1, AS1, LI1>& lhs,
               const Quantity<M2, L2, T2, EC2, TT2, AS2, LI2>& rhs ) {
        using ResultType = Quantity<M1-M2, L1-L2, T1-T2, EC1-EC2, TT1-TT2, AS1-AS2, LI1-LI2> ;
        return ResultType( lhs.getValue() / rhs.getValue() );
    }
    template<int L1, int M1, int T1, int EC1, int TT1, int AS1, int LI1, 
             int L2, int M2, int T2, int EC2, int TT2, int AS2, int LI2>
    bool operator==( const Quantity<L1, M1, T1, EC1, TT1, AS1, LI1>& lhs,
                     const Quantity<L2, M2, T2, EC2, TT2, AS2, LI2>& rhs ) {
        static_assert( L1 == L2 && M1 == M2 && T1 == T2 && EC1 == EC2 && TT1 == TT2 && AS1 == AS2 && LI1 == LI2, 
                       "Type of values being compared must be same.");
        return (lhs.getValue() == rhs.getValue());
    }
    template<int L1, int M1, int T1, int EC1, int TT1, int AS1, int LI1, 
             int L2, int M2, int T2, int EC2, int TT2, int AS2, int LI2>
    bool operator!=( const Quantity<L1, M1, T1, EC1, TT1, AS1, LI1>& lhs,
                     const Quantity<L2, M2, T2, EC2, TT2, AS2, LI2>& rhs ) {
        static_assert( L1 == L2 && M1 == M2 && T1 == T2 && EC1 == EC2 && TT1 == TT2 && AS1 == AS2 && LI1 == LI2, 
                       "Type of values being compared must be same.");
        return (lhs.getValue() != rhs.getValue());
    }
    template<int L1, int M1, int T1, int EC1, int TT1, int AS1, int LI1, 
             int L2, int M2, int T2, int EC2, int TT2, int AS2, int LI2>
    bool operator<=( const Quantity<L1, M1, T1, EC1, TT1, AS1, LI1>& lhs,
                     const Quantity<L2, M2, T2, EC2, TT2, AS2, LI2>& rhs ) {
        static_assert( L1 == L2 && M1 == M2 && T1 == T2 && EC1 == EC2 && TT1 == TT2 && AS1 == AS2 && LI1 == LI2, 
                       "Type of values being compared must be same.");
        return (lhs.getValue() <= rhs.getValue());
    }
    template<int L1, int M1, int T1, int EC1, int TT1, int AS1, int LI1, 
             int L2, int M2, int T2, int EC2, int TT2, int AS2, int LI2>
    bool operator>=( const Quantity<L1, M1, T1, EC1, TT1, AS1, LI1>& lhs,
                     const Quantity<L2, M2, T2, EC2, TT2, AS2, LI2>& rhs ) {
        static_assert( L1 == L2 && M1 == M2 && T1 == T2 && EC1 == EC2 && TT1 == TT2 && AS1 == AS2 && LI1 == LI2, 
                       "Type of values being compared must be same.");
        return (lhs.getValue() >= rhs.getValue());
    }
    template<int L1, int M1, int T1, int EC1, int TT1, int AS1, int LI1, 
             int L2, int M2, int T2, int EC2, int TT2, int AS2, int LI2>
    bool operator<( const Quantity<L1, M1, T1, EC1, TT1, AS1, LI1>& lhs,
                    const Quantity<L2, M2, T2, EC2, TT2, AS2, LI2>& rhs ) {
        static_assert( L1 == L2 && M1 == M2 && T1 == T2 && EC1 == EC2 && TT1 == TT2 && AS1 == AS2 && LI1 == LI2, 
                       "Type of values being compared must be same.");
        return (lhs.getValue() < rhs.getValue());
    }
    template<int L1, int M1, int T1, int EC1, int TT1, int AS1, int LI1, 
             int L2, int M2, int T2, int EC2, int TT2, int AS2, int LI2>
    bool operator>( const Quantity<L1, M1, T1, EC1, TT1, AS1, LI1>& lhs,
                    const Quantity<L2, M2, T2, EC2, TT2, AS2, LI2>& rhs ) {
        static_assert( L1 == L2 && M1 == M2 && T1 == T2 && EC1 == EC2 && TT1 == TT2 && AS1 == AS2 && LI1 == LI2, 
                       "Type of values being compared must be same.");
        return (lhs.getValue() > rhs.getValue());
    }

    // Global operator overloading with typename Type
    template<typename Type, int L, int M, int T, int EC, int TT, int AS, int LI>
    Quantity<L, M, T, EC, TT, AS, LI> 
    operator*( const Quantity<L, M, T, EC, TT, AS, LI>& lhs,
               const Type rhs ) {
        return Quantity<L, M, T, EC, TT, AS, LI>( lhs.getValue() * rhs );
    }
    template<typename Type, int L, int M, int T, int EC, int TT, int AS, int LI>
    Quantity<L, M, T, EC, TT, AS, LI> 
    operator*( const Type lhs,
               const Quantity<L, M, T, EC, TT, AS, LI>& rhs ) {
        return Quantity<L, M, T, EC, TT, AS, LI>( lhs * rhs.getValue() );
    }
    template<typename Type, int L, int M, int T, int EC, int TT, int AS, int LI>
    Quantity<L, M, T, EC, TT, AS, LI> 
    operator/( const Quantity<L, M, T, EC, TT, AS, LI>& lhs,
               const Type rhs ) {
        return Quantity<L, M, T, EC, TT, AS, LI>( lhs.getValue() / rhs );
    }
    template<typename Type, int L, int M, int T, int EC, int TT, int AS, int LI>
    Quantity<-L, -M, -T, -EC, -TT, -AS, -LI> 
    operator/( const Type lhs,
               const Quantity<L, M, T, EC, TT, AS, LI>& rhs ) {
        return Quantity<-L, -M, -T, -EC, -TT, -AS, -LI>( lhs / rhs.getValue() );
    }

    // C++11 Physical quantity classes
    // Base units of the SI system
    using Length            = Quantity<1,0,0,0,0,0,0>;
    using Mass              = Quantity<0,1,0,0,0,0,0>;
    using Time              = Quantity<0,0,1,0,0,0,0>;
    using Current           = Quantity<0,0,0,1,0,0,0>;
    using Temperature       = Quantity<0,0,0,0,1,0,0>;
    using Substance         = Quantity<0,0,0,0,0,1,0>;
    using Luminous          = Quantity<0,0,0,0,0,0,1>;

    // Additional units for our purpose
    using Area              = decltype(Length()*Length()) ;
    using Volume            = decltype(Area()*Length()) ;
    using Speed             = decltype(Length()/Time()) ;
    using Acceleration      = decltype(Speed()/Time()) ;

    // Derived SI units
    // TODO: How can we differentiate between
    //      - Angle vs SolidAngle and
    //      - Luminous vs Luminous Flux and
    //      - Frequency vs Radioactivity??
    using Angle             = Quantity<0,0,0,0,0,0,0>;
    using SolidAngle        = Quantity<0,0,0,0,0,0,0>;
    using Frequency         = decltype(1/Time()) ;
    using Force             = decltype(Mass()*Acceleration()) ;
    using Pressure          = decltype(Force()/Area()) ;
    using Energy            = decltype(Force()*Length()) ;
    using Power             = decltype(Energy()/Time()) ;
    using Charge            = decltype(Current()*Time()) ;
    using Voltage           = decltype(Power()/Current()) ;
    using Capacitance       = decltype(Charge()/Voltage()) ;
    using Resistance        = decltype(Voltage()/Current()) ;
    using Conductance       = decltype(1/Resistance()) ;
    using MagneticFlux      = decltype(Voltage()*Time()) ;
    using MagneticField     = decltype(MagneticFlux()/Area()) ;
    using Inductance        = decltype(MagneticFlux()/Current()) ;
    using LuminousFlux      = decltype(Luminous()*SolidAngle()) ;
    using Illuminance       = decltype(LuminousFlux()/Area()) ;
    using Radioactivity     = decltype(1/Time()) ;
    using AbsorbedDose      = decltype(Energy()/Mass()) ;
    using EquivalentDose    = decltype(Energy()/Mass()) ;
    using CatalyticActivity = decltype(Substance()/Time()) ;

    // 
    // Derived quantities. These depend on the above operators and hence 
    // have to be defined after the operators.
    //
    // See http://physics.nist.gov/cuu/Units/units.html
    //
    using DynamicViscosity       = decltype(Pressure()*Time()) ;
    using MomentOfForce          = decltype(Force()*Length()) ;
    using SurfaceTension         = decltype(Force()/Length()) ;
    using AngularVelocity        = decltype(Angle()/Time()) ;
    using AngularAcceleration    = decltype(AngularVelocity()/Time()) ;
    using Irradiance             = decltype(Power()/Area()) ;
    using HeatFluxDensity        = decltype(Irradiance()) ; 
    using Entropy                = decltype(Energy()/Temperature()) ;
    using HeatCapacity           = decltype(Entropy()) ;
    using SpecificEntropy        = decltype(Entropy()/Mass()) ;
    using SpecificHeatCapacity   = decltype(SpecificEntropy()) ;
    using SpecificEnergy         = decltype(Energy()/Mass()) ;
    using ThermalConductivity    = decltype(Power()/(Length()*Temperature())) ;
    using EnergyDensity          = decltype(Energy()/Volume()) ;
    using ElectricFieldStrength  = decltype(Voltage()/Length()) ;
    using ElectricChargeDensity  = decltype(Charge()/Volume()) ;
    using ElectricFluxDensity    = decltype(Charge()/Area()) ;
    using Permittivity           = decltype(Capacitance()/Length()) ;
    using Permeability           = decltype(Inductance()/Length()) ;
    using MolarEnergy            = decltype(Energy()/Substance()) ;
    using MolarEntropy           = decltype(MolarEnergy()/Temperature()) ;
    using MolarHeatCapacity      = decltype(MolarEnergy()/Temperature()) ;
    using Exposure               = decltype(Charge()/Mass()) ;
    using AbsorbedDoseRate       = decltype(AbsorbedDose()/Time()) ;
    using RadiantIntensity       = decltype(Power()/SolidAngle()) ;
    using Radiance               = decltype(RadiantIntensity()/Area()) ;
    using CatalyticConcentration = decltype(CatalyticActivity()/Volume()) ;

    // These are handy for the Convert functions to convert between units
    constexpr Length kilometer( 1e3 ) ;
    constexpr Length kilometre( 1e3 );
    constexpr Length meter( 1.0 ) ;
    constexpr Length metre( 1.0 );
    constexpr Length centimeter( 1e-2 ) ;
    constexpr Length centimetre( 1e-2 );
    constexpr Length millimeter( 1e-3 ) ;
    constexpr Length milimetre( 1e-3 );

    constexpr Mass kilogram( 1.0 );
    constexpr Mass gram( 1e-3 );
    constexpr Mass tonne( 1e3 );

    constexpr Area meter2( 1.0 ) ;
    constexpr Area metre2( 1.0 );
    constexpr Area kilometer2( 1.0e6 );
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
    //              may be defined by the system in the future and ours will be ignored then!
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

    template<typename T>
    struct HasFundamentalUnit
    {
        using FunitType = typename T::FundamentalUnitType ;

        template<typename U>
        static char check(typename U::NameType*) ;

        template<typename U>
        static long check(U*) ;

        static const bool value = sizeof(check<FunitType>(0)) == sizeof(char) ;
    } ;

    template<int L, int M, int T, int EC, int TT, int AS, int LI, 
    typename std::enable_if<HasFundamentalUnit<Quantity<L, M, T, EC, TT, AS, LI>>::value>::type* = nullptr>
    std::ostream& operator<<( std::ostream& os, const Quantity<L, M, T, EC, TT, AS, LI>& q ) 
    {
        using FunitType = typename Quantity<L, M, T, EC, TT, AS, LI>::FundamentalUnitType ;
        os << q.getValue() << " " << FunitType::Name ; 
        return os ;
    }

    //
    // Fundamental units of various Quantities. 
    //
    template<>
    struct FundamentalUnit<Length>
    {
        using NameType = const char* ;
        static constexpr NameType Name = "m" ;
    } ;

    template<>
    struct FundamentalUnit<Mass>
    {
        using NameType = const char* ;
        static constexpr NameType Name = "kg" ;
    } ;

    template<>
    struct FundamentalUnit<Time>
    {
        using NameType = const char* ;
        static constexpr NameType Name = "s" ;
    } ;

    template<>
    struct FundamentalUnit<Current>
    {
        using NameType = const char* ;
        static constexpr NameType Name = "A" ;
    } ;

    template<>
    struct FundamentalUnit<Temperature>
    {
        using NameType = const char* ;
        static constexpr NameType Name = "K" ;
    } ;

    template<>
    struct FundamentalUnit<Substance>
    {
        using NameType = const char* ;
        static constexpr NameType Name = "mol" ;
    } ;

    template<>
    struct FundamentalUnit<Luminous>
    {
        using NameType = const char* ;
        static constexpr NameType Name = "cd" ;
    } ;

    template<>
    struct FundamentalUnit<Angle>
    {
        using NameType = const char* ;
        static constexpr NameType Name = "rad" ;
    } ;

    template<>
    struct FundamentalUnit<Frequency>
    {
        using NameType = const char* ;
        static constexpr NameType Name = "Hz" ;
    } ;

    template<>
    struct FundamentalUnit<Force>
    {
        using NameType = const char* ;
        static constexpr NameType Name = "N" ;
    } ;

    template<>
    struct FundamentalUnit<Pressure>
    {
        using NameType = const char* ;
        static constexpr NameType Name = "Pa" ;
    } ;

    template<>
    struct FundamentalUnit<Energy>
    {
        using NameType = const char* ;
        static constexpr NameType Name = "J" ;
    } ;

    template<>
    struct FundamentalUnit<Power>
    {
        using NameType = const char* ;
        static constexpr NameType Name = "W" ;
    } ;

    template<>
    struct FundamentalUnit<Charge>
    {
        using NameType = const char* ;
        static constexpr NameType Name = "C" ;
    } ;

    template<>
    struct FundamentalUnit<Voltage>
    {
        using NameType = const char* ;
        static constexpr NameType Name = "V" ;
    } ;

    template<>
    struct FundamentalUnit<Capacitance>
    {
        using NameType = const char* ;
        static constexpr NameType Name = "F" ;
    } ;

    template<>
    struct FundamentalUnit<Resistance>
    {
        using NameType = const char* ;
        static constexpr NameType Name = "Ohm" ;
    } ;

    template<>
    struct FundamentalUnit<Conductance>
    {
        using NameType = const char* ;
        static constexpr NameType Name = "S" ;
    } ;

    template<>
    struct FundamentalUnit<MagneticFlux>
    {
        using NameType = const char* ;
        static constexpr NameType Name = "Wb" ;
    } ;

    template<>
    struct FundamentalUnit<MagneticField>
    {
        using NameType = const char* ;
        static constexpr NameType Name = "T" ;
    } ;

    template<>
    struct FundamentalUnit<Inductance>
    {
        using NameType = const char* ;
        static constexpr NameType Name = "H" ;
    } ;

    template<>
    struct FundamentalUnit<Illuminance>
    {
        using NameType = const char* ;
        static constexpr NameType Name = "lx" ;
    } ;

    template<>
    struct FundamentalUnit<AbsorbedDose>
    {
        using NameType = const char* ;
        static constexpr NameType Name = "Gy" ;
    } ;

    template<>
    struct FundamentalUnit<CatalyticActivity>
    {
        using NameType = const char* ;
        static constexpr NameType Name = "kat" ;
    } ;

    template<>
    struct FundamentalUnit<DynamicViscosity>
    {
        using NameType = const char* ;
        static constexpr NameType Name = "Pa s" ;
    } ;

    template<>
    struct FundamentalUnit<AngularAcceleration>
    {
        using NameType = const char* ;
        static constexpr NameType Name = "rad/s^2" ;
    } ;

    template<>
    struct FundamentalUnit<Irradiance>
    {
        using NameType = const char* ;
        static constexpr NameType Name = "W/m^2" ;
    } ;

    template<>
    struct FundamentalUnit<Entropy>
    {
        using NameType = const char* ;
        static constexpr NameType Name = "J/K" ;
    } ;

    template<>
    struct FundamentalUnit<SpecificEntropy>
    {
        using NameType = const char* ;
        static constexpr NameType Name = "J/(kg K)" ;
    } ;

    template<>
    struct FundamentalUnit<ThermalConductivity>
    {
        using NameType = const char* ;
        static constexpr NameType Name = "W/(m K)" ;
    } ;

    template<>
    struct FundamentalUnit<ElectricFieldStrength>
    {
        using NameType = const char* ;
        static constexpr NameType Name = "V/m" ;
    } ;

    template<>
    struct FundamentalUnit<ElectricChargeDensity>
    {
        using NameType = const char* ;
        static constexpr NameType Name = "C/m^3" ;
    } ;

    template<>
    struct FundamentalUnit<ElectricFluxDensity>
    {
        using NameType = const char* ;
        static constexpr NameType Name = "C/m^2" ;
    } ;

    template<>
    struct FundamentalUnit<Permittivity>
    {
        using NameType = const char* ;
        static constexpr NameType Name = "F/m" ;
    } ;

    template<>
    struct FundamentalUnit<Permeability>
    {
        using NameType = const char* ;
        static constexpr NameType Name = "H/m" ;
    } ;

    template<>
    struct FundamentalUnit<MolarEnergy>
    {
        using NameType = const char* ;
        static constexpr NameType Name = "J/mol" ;
    } ;

    template<>
    struct FundamentalUnit<MolarEntropy>
    {
        using NameType = const char* ;
        static constexpr NameType Name = "J/(mol K)" ;
    } ;

    template<>
    struct FundamentalUnit<Exposure>
    {
        using NameType = const char* ;
        static constexpr NameType Name = "C/kg" ;
    } ;

    template<>
    struct FundamentalUnit<AbsorbedDoseRate>
    {
        using NameType = const char* ;
        static constexpr NameType Name = "Gy/s" ;
    } ;

    template<>
    struct FundamentalUnit<CatalyticConcentration>
    {
        using NameType = const char* ;
        static constexpr NameType Name = "kat/m^3" ;
    } ;

    template<>
    struct FundamentalUnit<Speed>
    {
        using NameType = const char* ;
        static constexpr NameType Name = "m/s" ;
    } ;

    template<>
    struct FundamentalUnit<Acceleration>
    {
        using NameType = const char* ;
        static constexpr NameType Name = "m/s^2" ;
    } ;

    template<int L, int M, int T, int EC, int TT, int AS, int LI, 
    typename std::enable_if<not HasFundamentalUnit<Quantity<L, M, T, EC, TT, AS, LI>>::value>::type* = nullptr>
    std::ostream& operator<<( std::ostream& os, const Quantity<L, M, T, EC, TT, AS, LI>& q ) 
    {
        static const std::array<std::string, NUM_BASE_UNITS> base_units {
            FundamentalUnit<Length>::Name,  
            FundamentalUnit<Mass>::Name,  
            FundamentalUnit<Time>::Name,  
            FundamentalUnit<Current>::Name,  
            FundamentalUnit<Temperature>::Name,  
            FundamentalUnit<Substance>::Name,  
            FundamentalUnit<Luminous>::Name  
        } ;
        static const std::array<int, NUM_BASE_UNITS> exponents { 
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

}
// namespace SciQ;

// conversion macro
#define ConvertTo(_x, _y) (_x).Convert(1.0_##_y)

#endif /* SCIENTIFICQUANTITIES_HPP_ */
