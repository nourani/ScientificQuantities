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

#include <sstream>
#include <iostream>
#include <cmath>
#include <assert.h>
#include <stdexcept>
#include <array>
#include <ratio>
#include <vector>
#include <memory>
#include <cstring>

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

    class IQuantity {
      // Interface class
    };

    /**
     * Representation of a physical/scientific quantity using a combination of
     * seven base quantities: length (L), mass (M), temperature (T), electric
     * current (EC), thermodynamic temperature (TT), amount of substance (AS),
     * and luminous intensity (LI). See
     * [this](http://physics.nist.gov/cuu/Units/units.html) page for more
     * information. 
     *
     * TODO Can we use a string literal? We can use this to define the unit as
     * well as coping with quantities with similar base units
     * 
     * \see 
     * - [International System of Units: Units and Prefixes](https://en.wikipedia.org/wiki/International_System_of_Units#Units_and_prefixes)
     * - [SI Base Units](http://physics.nist.gov/cuu/Units/units.html)
     * - [Application of C++11 User-Defined Literals to Handling Scientific Quantities, Number Representation and String Manipulation](http://www.codeproject.com/Articles/447922/Application-of-Cplusplus11-User-Defined-Literals-t)
     * - [Fixing it once and for all: Enforcing units of measure in C++11](http://grahampentheny.com/archives/106)
     *
     */
    template<class L, class M, class T, class EC, class TT, class AS, class LI>
    class Quantity : public IQuantity {
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
         * Get the value of the current quantity in its fundamental SI unit.
         */
        constexpr double getValue() {
            return value;
        }
        /**
         * Returns the type of the unit as a string.
         * @return
         */
        constexpr std::string getUnitStr()
        {
            std::ostringstream os;
            os << Quantity<L, M, T, EC, TT, AS, LI>::FundamentalUnitType::Name;
            return os.str();
        }
        /**
         * Compares if the unit matches the string.
         * @param type_given String containing the unit
         * @return True if the string matches the unit
         */
        constexpr bool isSameUnit( const std::string unit_str ) {

          if( getUnitStr().compare(unit_str) == 0) {
            return true;
          }
          return false;
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
        constexpr operator double() {
            return value;
        }
        
        constexpr std::string toString() {
        	char str[128];
        	sprintf( str, "%f: L=%ld/%ld, M=%ld/%ld, T=%ld/%ld, EC=%ld/%ld, TT=%ld/%ld, AS=%ld/%ld, LI=%ld/%ld", 
        		value, L::num, L::den, M::num, M::den, T::num, T::den, EC::num, EC::den, TT::num, TT::den, AS::num, AS::den, LI::num, LI::den );
        	return (std::string)str;
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
    template<class L, class M, class T, class EC, class TT, class AS, class LI>
    Quantity<L, M, T, EC, TT, AS, LI> 
    operator+( const Quantity<L, M, T, EC, TT, AS, LI>& lhs,
               const Quantity<L, M, T, EC, TT, AS, LI>& rhs ) {
        return Quantity<L, M, T, EC, TT, AS, LI>( lhs ) += rhs;
    }

    template<class L, class M, class T, class EC, class TT, class AS, class LI>
    Quantity<L, M, T, EC, TT, AS, LI> 
    operator-( const Quantity<L, M, T, EC, TT, AS, LI>& lhs,
               const Quantity<L, M, T, EC, TT, AS, LI>& rhs ) {
        return Quantity<L, M, T, EC, TT, AS, LI>( lhs ) -= rhs;
    }

    template<class L1, class M1, class T1, class EC1, class TT1, class AS1, class LI1, 
             class L2, class M2, class T2, class EC2, class TT2, class AS2, class LI2>
    constexpr Quantity<std::ratio_add<L1,L2>, std::ratio_add<M1,M2>, std::ratio_add<T1,T2>, std::ratio_add<EC1,EC2>, std::ratio_add<TT1,TT2>, std::ratio_add<AS1,AS2>, std::ratio_add<LI1,LI2>> 
    operator*( const Quantity<L1, M1, T1, EC1, TT1, AS1, LI1>& lhs,
               const Quantity<L2, M2, T2, EC2, TT2, AS2, LI2>& rhs ) {
        using ResultType = Quantity<std::ratio_add<L1,L2>, std::ratio_add<M1,M2>, std::ratio_add<T1,T2>, std::ratio_add<EC1,EC2>, std::ratio_add<TT1,TT2>, std::ratio_add<AS1,AS2>, std::ratio_add<LI1,LI2>> ;
        return ResultType( lhs.getValue() * rhs.getValue() );
    }

    template<class L1, class M1, class T1, class EC1, class TT1, class AS1, class LI1, 
             class L2, class M2, class T2, class EC2, class TT2, class AS2, class LI2>
    constexpr Quantity<std::ratio_subtract<L1,L2>, std::ratio_subtract<M1,M2>, std::ratio_subtract<T1,T2>, std::ratio_subtract<EC1,EC2>, std::ratio_subtract<TT1,TT2>, std::ratio_subtract<AS1,AS2>, std::ratio_subtract<LI1,LI2>>
    operator/( const Quantity<L1, M1, T1, EC1, TT1, AS1, LI1>& lhs,
               const Quantity<L2, M2, T2, EC2, TT2, AS2, LI2>& rhs ) {
        using ResultType = Quantity<std::ratio_subtract<L1,L2>, std::ratio_subtract<M1,M2>, std::ratio_subtract<T1,T2>, std::ratio_subtract<EC1,EC2>, std::ratio_subtract<TT1,TT2>, std::ratio_subtract<AS1,AS2>, std::ratio_subtract<LI1,LI2>> ;
        return ResultType( lhs.getValue() / rhs.getValue() );
    }

    template<class L1, class M1, class T1, class EC1, class TT1, class AS1, class LI1, 
             class L2, class M2, class T2, class EC2, class TT2, class AS2, class LI2>
    constexpr bool 
    operator==( const Quantity<L1, M1, T1, EC1, TT1, AS1, LI1>& lhs,
                     const Quantity<L2, M2, T2, EC2, TT2, AS2, LI2>& rhs ) {
        static_assert( std::ratio_equal<M1,M2>::value && 
        				std::ratio_equal<L1,L2>::value && 
        				std::ratio_equal<T1,T2>::value && 
        				std::ratio_equal<EC1,EC2>::value && 
        				std::ratio_equal<TT1,TT2>::value && 
        				std::ratio_equal<AS1,AS2>::value && 
        				std::ratio_equal<LI1,LI2>::value,
                       "Type of values being compared must be same.");
        return (lhs.getValue() == rhs.getValue());
    }

    template<class L1, class M1, class T1, class EC1, class TT1, class AS1, class LI1, 
             class L2, class M2, class T2, class EC2, class TT2, class AS2, class LI2>
    constexpr bool 
    operator!=( const Quantity<L1, M1, T1, EC1, TT1, AS1, LI1>& lhs,
                const Quantity<L2, M2, T2, EC2, TT2, AS2, LI2>& rhs ) {
        static_assert( std::ratio_equal<M1,M2>::value && 
        				std::ratio_equal<L1,L2>::value && 
        				std::ratio_equal<T1,T2>::value && 
        				std::ratio_equal<EC1,EC2>::value && 
        				std::ratio_equal<TT1,TT2>::value && 
        				std::ratio_equal<AS1,AS2>::value && 
        				std::ratio_equal<LI1,LI2>::value, 
                       "Type of values being compared must be same.");
        return (lhs.getValue() != rhs.getValue());
    }

    template<class L1, class M1, class T1, class EC1, class TT1, class AS1, class LI1, 
             class L2, class M2, class T2, class EC2, class TT2, class AS2, class LI2>
    constexpr bool 
    operator<=( const Quantity<L1, M1, T1, EC1, TT1, AS1, LI1>& lhs,
                const Quantity<L2, M2, T2, EC2, TT2, AS2, LI2>& rhs ) {
        static_assert( std::ratio_equal<M1,M2>::value && 
        				std::ratio_equal<L1,L2>::value && 
        				std::ratio_equal<T1,T2>::value && 
        				std::ratio_equal<EC1,EC2>::value && 
        				std::ratio_equal<TT1,TT2>::value && 
        				std::ratio_equal<AS1,AS2>::value && 
        				std::ratio_equal<LI1,LI2>::value,
                       "Type of values being compared must be same.");
        return (lhs.getValue() <= rhs.getValue());
    }

    template<class L1, class M1, class T1, class EC1, class TT1, class AS1, class LI1, 
             class L2, class M2, class T2, class EC2, class TT2, class AS2, class LI2>
    constexpr bool 
    operator>=( const Quantity<L1, M1, T1, EC1, TT1, AS1, LI1>& lhs,
                const Quantity<L2, M2, T2, EC2, TT2, AS2, LI2>& rhs ) {
        static_assert( std::ratio_equal<M1,M2>::value && 
        				std::ratio_equal<L1,L2>::value && 
        				std::ratio_equal<T1,T2>::value && 
        				std::ratio_equal<EC1,EC2>::value && 
        				std::ratio_equal<TT1,TT2>::value && 
        				std::ratio_equal<AS1,AS2>::value && 
        				std::ratio_equal<LI1,LI2>::value,
                       "Type of values being compared must be same.");
        return (lhs.getValue() >= rhs.getValue());
    }

    template<class L1, class M1, class T1, class EC1, class TT1, class AS1, class LI1, 
             class L2, class M2, class T2, class EC2, class TT2, class AS2, class LI2>
    constexpr bool 
    operator<( const Quantity<L1, M1, T1, EC1, TT1, AS1, LI1>& lhs,
               const Quantity<L2, M2, T2, EC2, TT2, AS2, LI2>& rhs ) {
        static_assert( std::ratio_equal<M1,M2>::value && 
        				std::ratio_equal<L1,L2>::value && 
        				std::ratio_equal<T1,T2>::value && 
        				std::ratio_equal<EC1,EC2>::value && 
        				std::ratio_equal<TT1,TT2>::value && 
        				std::ratio_equal<AS1,AS2>::value && 
        				std::ratio_equal<LI1,LI2>::value,
                       "Type of values being compared must be same.");
        return (lhs.getValue() < rhs.getValue());
    }

    template<class L1, class M1, class T1, class EC1, class TT1, class AS1, class LI1, 
             class L2, class M2, class T2, class EC2, class TT2, class AS2, class LI2>
    constexpr bool 
    operator>( const Quantity<L1, M1, T1, EC1, TT1, AS1, LI1>& lhs,
               const Quantity<L2, M2, T2, EC2, TT2, AS2, LI2>& rhs ) {
        static_assert( std::ratio_equal<M1,M2>::value && 
        				std::ratio_equal<L1,L2>::value && 
        				std::ratio_equal<T1,T2>::value && 
        				std::ratio_equal<EC1,EC2>::value && 
        				std::ratio_equal<TT1,TT2>::value && 
        				std::ratio_equal<AS1,AS2>::value && 
        				std::ratio_equal<LI1,LI2>::value,
                       "Type of values being compared must be same.");
        return (lhs.getValue() > rhs.getValue());
    }

    // Global operator overloading with typename Type
    template<typename Type, class L, class M, class T, class EC, class TT, class AS, class LI>
    constexpr Quantity<L, M, T, EC, TT, AS, LI> 
    operator*( const Quantity<L, M, T, EC, TT, AS, LI>& lhs,
               const Type rhs ) {
        return Quantity<L, M, T, EC, TT, AS, LI>( lhs.getValue() * rhs );
    }

    template<typename Type, class L, class M, class T, class EC, class TT, class AS, class LI>
    constexpr Quantity<L, M, T, EC, TT, AS, LI> 
    operator*( const Type lhs,
               const Quantity<L, M, T, EC, TT, AS, LI>& rhs ) {
        return Quantity<L, M, T, EC, TT, AS, LI>( lhs * rhs.getValue() );
    }

    template<typename Type, class L, class M, class T, class EC, class TT, class AS, class LI>
    constexpr Quantity<L, M, T, EC, TT, AS, LI> 
    operator/( const Quantity<L, M, T, EC, TT, AS, LI>& lhs,
               const Type rhs ) {
        return Quantity<L, M, T, EC, TT, AS, LI>( lhs.getValue() / rhs );
    }

    template<typename Type, class L, class M, class T, class EC, class TT, class AS, class LI>
    constexpr Quantity<std::ratio<-L::num>, std::ratio<-M::num>, std::ratio<-T::num>, std::ratio<-EC::num>, std::ratio<-TT::num>, std::ratio<-AS::num>, std::ratio<-LI::num> > 
    operator/( const Type lhs,
               const Quantity<L, M, T, EC, TT, AS, LI>& rhs ) {
        return Quantity<std::ratio<-L::num>, std::ratio<-M::num>, std::ratio<-T::num>, std::ratio<-EC::num>, std::ratio<-TT::num>, std::ratio<-AS::num>, std::ratio<-LI::num> >( lhs / rhs.getValue() );
    }

	// Mathematical operations
	// sqrt
	typedef std::ratio<2,1> two;
    template<class L, class M, class T, class EC, class TT, class AS, class LI>
    constexpr Quantity< std::ratio_divide<L,std::ratio<2> >, std::ratio_divide<M,std::ratio<2> >, std::ratio_divide<T,std::ratio<2> >, std::ratio_divide<EC,std::ratio<2> >, std::ratio_divide<TT,std::ratio<2> >, std::ratio_divide<AS,std::ratio<2> >, std::ratio_divide<LI,std::ratio<2> > >
    sqrt( const Quantity<L, M, T, EC, TT, AS, LI>& lhs ) {
		
		using ResultType = Quantity< std::ratio_divide<L,std::ratio<2> >, std::ratio_divide<M,std::ratio<2> >, std::ratio_divide<T,std::ratio<2> >, std::ratio_divide<EC,std::ratio<2> >, std::ratio_divide<TT,std::ratio<2> >, std::ratio_divide<AS,std::ratio<2> >, std::ratio_divide<LI,std::ratio<2> > >;

    	return ResultType( std::sqrt(lhs.getValue()) );
    }
    // pow
    // TODO: is there away around than using template based power so we are consistent with the std::pow??
    template<int power, class L, class M, class T, class EC, class TT, class AS, class LI>
    constexpr Quantity< std::ratio_multiply<L,std::ratio<power> >, std::ratio_multiply<M,std::ratio<power> >, std::ratio_multiply<T,std::ratio<power> >, std::ratio_multiply<EC,std::ratio<power> >, std::ratio_multiply<TT,std::ratio<power> >, std::ratio_multiply<AS,std::ratio<power> >, std::ratio_multiply<LI,std::ratio<power> > >
    pow( const Quantity<L, M, T, EC, TT, AS, LI>& lhs ) {
		
		using ResultType = Quantity< std::ratio_multiply<L,std::ratio<power> >, std::ratio_multiply<M,std::ratio<power> >, std::ratio_multiply<T,std::ratio<power> >, std::ratio_multiply<EC,std::ratio<power> >, std::ratio_multiply<TT,std::ratio<power> >, std::ratio_multiply<AS,std::ratio<power> >, std::ratio_multiply<LI,std::ratio<power> > >;

    	return ResultType( std::pow(lhs.getValue(), (double)power) );
    }

    // C++11 Physical quantity classes
    // Base units of the SI system
    using Length            = Quantity<std::ratio<1>,std::ratio<0>,std::ratio<0>,std::ratio<0>,std::ratio<0>,std::ratio<0>,std::ratio<0> >;
    using Mass              = Quantity<std::ratio<0>,std::ratio<1>,std::ratio<0>,std::ratio<0>,std::ratio<0>,std::ratio<0>,std::ratio<0> >;
    using Time              = Quantity<std::ratio<0>,std::ratio<0>,std::ratio<1>,std::ratio<0>,std::ratio<0>,std::ratio<0>,std::ratio<0> >;
    using Current           = Quantity<std::ratio<0>,std::ratio<0>,std::ratio<0>,std::ratio<1>,std::ratio<0>,std::ratio<0>,std::ratio<0> >;
    using Temperature       = Quantity<std::ratio<0>,std::ratio<0>,std::ratio<0>,std::ratio<0>,std::ratio<1>,std::ratio<0>,std::ratio<0> >;
    using Substance         = Quantity<std::ratio<0>,std::ratio<0>,std::ratio<0>,std::ratio<0>,std::ratio<0>,std::ratio<1>,std::ratio<0> >;
    using Luminous          = Quantity<std::ratio<0>,std::ratio<0>,std::ratio<0>,std::ratio<0>,std::ratio<0>,std::ratio<0>,std::ratio<1> >;

    // Additional units for our purpose
    //
    // (see Table 2 at http://physics.nist.gov/cuu/Units/units.html)
    //
    using Area                   = decltype(Length()*Length()) ;
    using Volume                 = decltype(Area()*Length()) ;
    using Speed                  = decltype(Length()/Time()) ;
    using Acceleration           = decltype(Speed()/Time()) ;
    using WaveNumber             = decltype(1.0/Length()) ; 
    using MassDensity            = decltype(Mass()/Volume()) ;
    using SpecificVolume         = decltype(Volume()/Mass()) ; 
    using CurrentDensity         = decltype(Current()/Area()) ; 
    using MagneticFieldStrength  = decltype(Current()/Length()) ; 
    using SubstanceConcentration = decltype(Substance()/Volume()) ;
    using Luminance              = decltype(Luminous()/Area()) ; 
    using MassFraction           = decltype(Mass()/Mass()) ;

    // Derived SI units
    //
    // (see Table 3 at http://physics.nist.gov/cuu/Units/units.html)
    // TODO: How can we differentiate between
    //      - Angle vs SolidAngle and
    //      - Luminous vs Luminous Flux and
    //      - Frequency vs Radioactivity??
    using Angle             = Quantity<std::ratio<0>,std::ratio<0>,std::ratio<0>,std::ratio<0>,std::ratio<0>,std::ratio<0>,std::ratio<0>>;
    using SolidAngle        = Quantity<std::ratio<0>,std::ratio<0>,std::ratio<0>,std::ratio<0>,std::ratio<0>,std::ratio<0>,std::ratio<0>>;
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


	// Other stuff
	using GravitationalConstantUnit = decltype(Volume()/Mass()/Time()/Time());
	
    //
    // Scaling prefixes (http://www.nist.gov/pml/wmd/metric/prefixes.cfm)
    //
    constexpr double yotta = 1.0e24 ;
    constexpr double zetta = 1.0e21 ;
    constexpr double exa = 1.0e18 ;
    constexpr double peta = 1.0e15 ; 
    constexpr double tera = 1.0e12 ; 
    constexpr double giga = 1.0e9 ; 
    constexpr double mega = 1.0e6 ; 
    constexpr double kilo = 1.0e3 ; 
    constexpr double hecto = 1.0e2 ; 
    constexpr double deka = 1.0e1 ; 
    constexpr double deci = 1.0e-1 ; 
    constexpr double centi = 1.0e-2 ; 
    constexpr double milli = 1.0e-3 ;
    constexpr double micro = 1.0e-6 ; 
    constexpr double nano = 1.0e-9 ;
    constexpr double pico = 1.0e-12 ; 
    constexpr double femto = 1.0e-15 ; 
    constexpr double atto = 1.0e-18 ; 
    constexpr double zepto = 1.0e-21 ; 
    constexpr double yocto = 1.0e-24 ; 

    // 
    // Specific units for various quantities. These are handy for the Convert
    // functions to convert between units.
    //
    // See:
    //
    // - http://www.nist.gov/pml/wmd/pubs/upload/AppC-12-hb44-final.pdf
    // - http://physics.nist.gov/cuu/Units/units.html
    // - http://physics.nist.gov/cuu/Units/prefixes.html
    // - http://physics.nist.gov/cuu/Units/outside.html
    // - http://en.wikipedia.org/wiki/Unit_of_length
    //
    // Some of these units have names that are obtained from
    // [BIPM](http://en.wikipedia.org/wiki/International_Bureau_of_Weights_and_Measures).
    // For example, "metre" and "kilometre".
    //
    // -------------------------------------------------------------------------
    // Various standard and common units for length.
    // -------------------------------------------------------------------------
    constexpr Length meter { 1.0 } ; 
    constexpr Length metre { meter } ;
    constexpr Length kilometer { kilo * meter } ;
    constexpr Length kilometre { kilometer } ;
    constexpr Length centimeter { centi * meter } ; 
    constexpr Length centimetre { centimeter } ; 
    constexpr Length millimeter { milli * meter } ; 
    constexpr Length milimetre { millimeter } ; 
    constexpr Length micron { micro * meter } ;
    constexpr Length angstrom { 0.1 * nano * meter } ; 
    constexpr Length inch { 2.54 * centimeter } ; 
    constexpr Length line { inch / 12.0 } ; 
    constexpr Length foot { 12 * inch } ; 
    constexpr Length yard { 3 * foot } ; 
    constexpr Length mile { 5280 * foot } ; 
    constexpr Length league { 3 * mile } ; 
    constexpr Length mil { inch / 1000.0 } ;
    constexpr Length nautical_mile { 1852 * meter } ; 
    constexpr Length fathom { 2 * yard } ; 

    // -------------------------------------------------------------------------
    // Various standard and common units for mass.
    //
    // In addition to the links above, also see:
    //
    // - http://en.wikipedia.org/wiki/Mass#Units_of_mass
    // -------------------------------------------------------------------------
    constexpr Mass kilogram { 1.0 } ; 
    constexpr Mass gram { kilogram / 1000.0 } ; 
    constexpr Mass milligram { milli * gram } ; 
    constexpr Mass tonne { 1.0e3 * kilogram } ; 
    constexpr Mass metric_ton { tonne } ; 
    constexpr Mass slug { 14.593903 * kilogram } ; 
    constexpr Mass pound { 0.45359237 * kilogram } ; 
    constexpr Mass carat { 200 * milligram } ; 
    constexpr Mass grain { 64.79891 * milligram } ; 
    constexpr Mass ounce_avdp { 437.5 * grain } ;
    constexpr Mass ounce { ounce_avdp } ;
    constexpr Mass ounce_troy { 480.0 * grain } ; 
    constexpr Mass gross_ton { 2240 * pound } ; 
    constexpr Mass long_ton { gross_ton } ; 
    constexpr Mass short_ton { 2000 * pound } ; 
    constexpr Mass net_ton { short_ton } ;

    // -------------------------------------------------------------------------
    // Various standard and common units for time.
    //
    // In addition to the links above, also see:
    //
    // - http://en.wikipedia.org/wiki/Unit_of_time
    // -------------------------------------------------------------------------
    constexpr Time second { 1.0 } ; 
    constexpr Time minute { 60.0 * second } ; 
    constexpr Time hour { 60.0 * minute } ; 
    constexpr Time day { 24.0 * hour } ; 
    constexpr Time week { 7.0 * day } ;
    constexpr Time julian_year { 365.25 * day } ; 
    constexpr Time year { julian_year } ; 
    constexpr Time decade { 10.0 * year } ; 
    constexpr Time century { 100.0 * year } ;
    constexpr Time millennium { 1000.0 * year } ; 
    constexpr Time yoctosecond { yocto * second } ; 
    constexpr Time jiffy_phys { 3.0e-24 * second } ; 
    constexpr Time zeptosecond { zepto * second } ; 
    constexpr Time attosecond { atto * second } ; 
    constexpr Time femtosecond { femto * second } ; 
    constexpr Time svedberg { 1.0e-13 * second } ; 
    constexpr Time picosecond { pico * second } ; 
    constexpr Time nanosecond { nano * second } ; 
    constexpr Time shake { 1.0e-8 * second } ; 
    constexpr Time microsecond { micro * second } ; 
    constexpr Time millisecond { milli * second } ; 
    constexpr Time fortnight { 2 * week } ; 
    constexpr Time leap_year { 366 * day } ; 
    constexpr Time jubilee { 50 * year } ; 
    constexpr Time epoch { 10 * mega * year } ; 
    constexpr Time era { 100 * mega * year } ; 
    constexpr Time eon { 500 * mega * year } ; 

    // -------------------------------------------------------------------------
    // Various standard and common units for current.
    // -------------------------------------------------------------------------
    constexpr Current ampere { 1.0 } ; 
    constexpr Current milliamp { milli * ampere } ; 
    constexpr Current microamp { micro * ampere } ; 
    constexpr Current nanoamp  { nano * ampere } ; 
    constexpr Current picoamp  { pico * ampere } ; 

    // -------------------------------------------------------------------------
    // Various standard and common units for temperature.
    // -------------------------------------------------------------------------
    constexpr Temperature celcius( 273.15 );
    constexpr Temperature kelvin( 1.0 );
    constexpr Temperature fahrenheit( (1.0-32)*5/9+273.15 );

    // -------------------------------------------------------------------------
    // Various standard and common units for substance
    // -------------------------------------------------------------------------
    constexpr Substance mole { 1.0 } ;

    //
    // -------------------------------------------------------------------------
    // Various standard and common units for luminous
    // -------------------------------------------------------------------------
    constexpr Luminous candela { 1.0 } ;

    // -------------------------------------------------------------------------
    // Various standard and common units for area.
    //
    // In addition to the links above, also see:
    //
    // - http://en.wikipedia.org/wiki/Area
    // -------------------------------------------------------------------------
    constexpr Area meter2 { meter * meter } ;
    constexpr Area metre2 { meter2 } ; 
    constexpr Area square_meter { meter2 } ;
    constexpr Area kilometer2 { kilometer * kilometer } ; 
    constexpr Area kilometre2 { kilometer2 } ; 
    constexpr Area square_kilometer { kilometer2 } ; 
    constexpr Area yard2 { yard * yard } ;
    constexpr Area square_yard { yard2 } ; 
    constexpr Area mile2 { mile * mile } ; 
    constexpr Area square_mile { mile2 } ; 
    constexpr Area hectare { 10000 * square_meter } ; 
    constexpr Area acre { 4840 * square_yard } ; 
    constexpr Area barn { 1.0e-28 * square_meter } ;

    // -------------------------------------------------------------------------
    // Various standard and common units for angle
    // -------------------------------------------------------------------------
    constexpr Angle radian( 1.0 );
    constexpr Angle degree( M_PI / 180. );
    constexpr Angle gradian( 2 * M_PI / 400. ); // For c.lees!
    constexpr Angle turn( 2 * M_PI );
    constexpr Angle angleminute( M_PI/10800 );
    constexpr Angle anglesecond( M_PI/648000 );

    // -------------------------------------------------------------------------
    // Various standard and common units for volume
    // -------------------------------------------------------------------------
    constexpr Volume meter3 { meter * meter * meter } ; 
    constexpr Volume cubic_meter { meter3 } ;
    constexpr Volume centimeter3 { centimeter * centimeter * centimeter } ; 
    constexpr Volume cubic_centimeter { centimeter3 } ;
    constexpr Volume inch3 { inch * inch * inch } ; 
    constexpr Volume cubic_inch { inch3 } ;
    constexpr Volume litre { 0.001 * cubic_meter } ;
    constexpr Volume millilitre { milli * litre } ; 
    constexpr Volume gallon { 3.785411784 * litre } ;
    constexpr Volume liquid_quart { 0.25 * gallon } ; 
    constexpr Volume liquid_pint { 0.5 * liquid_quart } ;
    constexpr Volume gill { 0.25 * liquid_pint } ; 
    constexpr Volume fluid_ounce { 0.0625 * liquid_pint } ; 
    constexpr Volume fluid_dram { 0.0078125 * liquid_pint } ; 
    constexpr Volume cup { 8 * fluid_ounce } ;
    constexpr Volume tablespoon { 15 * millilitre } ; 
    constexpr Volume teaspoon { 5 * millilitre } ; 
    constexpr Volume minim { 0.0001302083 * liquid_pint } ;
    constexpr Volume bushel { 2150.2 * cubic_inch } ; 
    constexpr Volume peck { 0.25 * bushel } ; 
    constexpr Volume dry_quart { 0.125 * peck } ; 
    constexpr Volume dry_pint { 0.5 * dry_quart } ;
    
    // -------------------------------------------------------------------------
    // Various standard and common units for pressure
    // -------------------------------------------------------------------------
    constexpr Pressure pascal { 1.0 } ; 
    constexpr Pressure bar { 1.0e5 * pascal } ; 
    constexpr Pressure atm { 1.01325e5 * pascal } ; 
    constexpr Pressure torr { 133.3224 * pascal } ; 
    constexpr Pressure psi { 6.8948e3 * pascal } ;

    // -------------------------------------------------------------------------
    // Various standard and common units for energy
    // -------------------------------------------------------------------------
    constexpr Energy joule { 1.0 } ;
    constexpr Energy cal { 4.184 * joule } ;
    constexpr Energy erg { 1.0e-7 * joule } ; 
    constexpr Energy eV  { 1.602176565e-19 * joule } ;
    constexpr Energy keV { kilo * eV } ;
    constexpr Energy MeV { mega * eV } ; 

    // C++11 literals
    // NOTE: it is recommended to create own literals starting with _ as literals without _
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

    template<class L, class M, class T, class EC, class TT, class AS, class LI,
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
#if 1
    template<>
    struct FundamentalUnit<AbsorbedDose>
    {
        using NameType = const char* ;
        static constexpr NameType Name = "Gy" ;
    } ;
#endif
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
        static constexpr NameType Name = "Pa*s" ;
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
        static constexpr NameType Name = "J/(kg*K)" ;
    } ;

    template<>
    struct FundamentalUnit<ThermalConductivity>
    {
        using NameType = const char* ;
        static constexpr NameType Name = "W/(m*K)" ;
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
        static constexpr NameType Name = "J/(mol*K)" ;
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

    static const int NUM_UNITS = 42;

    template<class L, class M, class T, class EC, class TT, class AS, class LI, 
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
        // Since 
        static const std::array<int, NUM_BASE_UNITS*2> exponents { 
            L::num, L::den, M::num, M::den, T::num, T::den, EC::num, EC::den, TT::num, TT::den, AS::num, AS::den, LI::num, LI::den
        } ;
        os << q.getValue() ;
        for(int i=0; i<exponents.size(); i+=2) {
            if (0 == exponents[i]) {
                continue ;
            } 
            if (1 == exponents[i] && 1 == exponents[i+1]) {
                os << " " << base_units[i] ; 
            } else {
                os << " " << base_units[i] << "^" << exponents[i] ;
            }
            if (1 != exponents[i+1]) {
            	os << "/" << exponents[i+1];
            }
        }
        
        
        return os ; 
    }

    /**
     * Given a string with a value and a units create the appropriate Quantity / scale the value and return the value
     * TODO: can't deal with scaling. I.e. cannot parse '1 km' as '1000 m'!
     * @param s String containing the value and unit following the same output as the "<<operator" above
     * @return The value of in SI units
     */

    bool from_string( const std::string input_val_unit, double * value ) {
      // Supported units
      std::vector<std::string> UNITS = {
                  FundamentalUnit<Length>::Name,
                  FundamentalUnit<Mass>::Name,
                  FundamentalUnit<Time>::Name,
                  FundamentalUnit<Current>::Name,
                  FundamentalUnit<Temperature>::Name,
                  FundamentalUnit<Substance>::Name,
                  FundamentalUnit<Luminous>::Name,
                  FundamentalUnit<Angle>::Name,
                  FundamentalUnit<Frequency>::Name,
                  FundamentalUnit<Force>::Name,
                  FundamentalUnit<Pressure>::Name,
                  FundamentalUnit<Energy>::Name,
                  FundamentalUnit<Power>::Name,
                  FundamentalUnit<Charge>::Name,
                  FundamentalUnit<Voltage>::Name,
                  FundamentalUnit<Capacitance>::Name,
                  FundamentalUnit<Resistance>::Name,
                  FundamentalUnit<Conductance>::Name,
                  FundamentalUnit<MagneticFlux>::Name,
                  FundamentalUnit<MagneticField>::Name,
                  FundamentalUnit<Inductance>::Name,
                  FundamentalUnit<Illuminance>::Name,
                  FundamentalUnit<AbsorbedDose>::Name,
                  FundamentalUnit<CatalyticActivity>::Name,
                  FundamentalUnit<DynamicViscosity>::Name,
                  FundamentalUnit<AngularAcceleration>::Name,
                  FundamentalUnit<Irradiance>::Name,
                  FundamentalUnit<Entropy>::Name,
                  FundamentalUnit<SpecificEntropy>::Name,
                  FundamentalUnit<ThermalConductivity>::Name,
                  FundamentalUnit<ElectricFieldStrength>::Name,
                  FundamentalUnit<ElectricChargeDensity>::Name,
                  FundamentalUnit<ElectricFluxDensity>::Name,
                  FundamentalUnit<Permittivity>::Name,
                  FundamentalUnit<Permeability>::Name,
                  FundamentalUnit<MolarEnergy>::Name,
                  FundamentalUnit<MolarEntropy>::Name,
                  FundamentalUnit<Exposure>::Name,
                  FundamentalUnit<AbsorbedDoseRate>::Name,
                  FundamentalUnit<CatalyticConcentration>::Name,
                  FundamentalUnit<Speed>::Name,
                  FundamentalUnit<Acceleration>::Name
              };

        // Split the input string into value and unit
        // NOTE: split is done based on space only!
        std::string unit;
        std::string buf;
        std::stringstream ss(input_val_unit);
        std::vector<std::string> unit_vector; // Create vector to hold our words
        while (ss >> buf) {
            unit_vector.push_back(buf);
        }
        if(unit_vector.size() != 2 ) {
          std::cerr << "Invalid input string \'" << input_val_unit << "\'";
          return false;
        }
        try {
          *value = std::stod(unit_vector[0]);
        }
        catch (const std::invalid_argument& ia) {
            std::cerr << "Invalid argument: " << ia.what() << '\n';
            return false;
        }
        unit = unit_vector[1];


        // Is this a valid unit?
        // TODO: scaling of the value can be done here
        for(auto unit_ : UNITS ) {
            if( unit_.compare(unit) == 0) {
                return true;
            }
        }

        return false;
    }

}
// namespace SciQ;

// conversion macro
#define ConvertTo(_x, _y) (_x).Convert(1.0_##_y)

#endif /* SCIENTIFICQUANTITIES_HPP_ */
