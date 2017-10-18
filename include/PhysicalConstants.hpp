#ifndef PHYSICALCONSTANTS_HPP
#define PHYSICALCONSTANTS_HPP
/**
 * \file
 *
 * This file contains definitions of fundamental physical constants with 
 * units based on ScientificQuantities.hpp. The values of the fundamental 
 * physical constants are obtained from the following NIST site:
 *
 * http://physics.nist.gov/cuu/Constants/
 *
 * Values of the constants without any units are available with the same
 * names but with "Value" suffix. The symbolic names of the constants are 
 * same as those used by NIST.
 */
#include "ScientificQuantities.hpp"

namespace SciQ {

    /*********************************************************************
     *                        Universal Constant                         *
     * (http://physics.nist.gov/cgi-bin/cuu/Category?view=html&Universal.x=95&Universal.y=9) *
     *********************************************************************/

    /**
     * See http://physics.nist.gov/cgi-bin/cuu/Value?z0|search_for=universal_in!
     */
    constexpr double VacuumImpedanceValue = 376.730313461 ; // Ohm
    constexpr Resistance z_0 {VacuumImpedanceValue} ;
    constexpr Resistance VacuumImpedance {VacuumImpedanceValue} ;
    /**
     * See http://physics.nist.gov/cgi-bin/cuu/Value?ep0|search_for=universal_in!
     */
    constexpr double ElectricConstantValue = 8.854187817e-12 ; // F/m
    constexpr Permittivity ep_0 { ElectricConstantValue } ;
    constexpr Permittivity ElectricConstant { ep_0 } ;
    constexpr Permittivity VacuumPermittivity { ep_0 } ;
    
    /**
     * See http://physics.nist.gov/cgi-bin/cuu/Value?mu0#mid
     */
    constexpr double MagneticConstantValue = 12.566370614e-7 ; // H/m
    constexpr Permeability mu_0 { MagneticConstantValue } ;
    constexpr Permeability MagneticConstant { mu_0 } ;
    constexpr Permeability VacuumPermeability { mu_0 } ;

    /*********************************************************************
     *                     Electromagnetic Constants                     *
     * (http://physics.nist.gov/cgi-bin/cuu/Category?view=html&Electromagnetic.x=100&Electromagnetic.y=8)
     *********************************************************************/

    /**
     * See http://physics.nist.gov/cgi-bin/cuu/Value?e|search_for=elecmag_in!
     */
    constexpr double ElementaryChargeValue = 1.602176565e-19 ;  // C
    constexpr Charge q_elem { ElementaryChargeValue } ;
    constexpr Charge ElementaryCharge { q_elem } ;
    constexpr Charge q_elec { -ElementaryChargeValue } ;
    constexpr Charge ElectronCharge { q_elec } ;

    /*********************************************************************
     *                   Atomic and Nuclear Constants                    *
     * (http://physics.nist.gov/cgi-bin/cuu/Category?view=html&Atomic+and+nuclear.x=90&Atomic+and+nuclear.y=14) *
     *********************************************************************/

    /**
     * See http://physics.nist.gov/cgi-bin/cuu/Value?me|search_for=atomnuc!
     */
    constexpr double ElectronMassValue = 9.10938291e-31 ; // kg
    constexpr Mass ElectronMass { ElectronMassValue } ;
    constexpr Mass m_e { ElectronMassValue } ;

    /*********************************************************************
     *                    Physico-Chemical Constants                     *
     * (http://physics.nist.gov/cgi-bin/cuu/Category?view=html&Physico-chemical.x=110&Physico-chemical.y=17) *
     *********************************************************************/

	constexpr Length PlanckLength = 1.61619997e-35_m;
	constexpr Mass PlanckMass = 2.1765113e-8_kg;
	constexpr Time PlanckTime = 5.3910632e-44_s;
	constexpr Charge PlanckCharge = 1.87554595641e-18_C;
	constexpr Temperature PlanckTemperature = 1.41683385e+32_K;
	
	constexpr Speed SpeedOfLight = PlanckLength / PlanckTime;
	constexpr GravitationalConstantUnit GravitationalConstant = PlanckLength*PlanckLength*PlanckLength/PlanckMass/PlanckTime/PlanckTime;
	
	constexpr Mass MassOfEarth = 5.97219e+24_kg;
    /*********************************************************************
     *                          Adopted Values                           *
     * (http://physics.nist.gov/cgi-bin/cuu/Category?view=html&Adopted+values.x=99&Adopted+values.y=10) *
     *********************************************************************/

    /*********************************************************************
     *                           Non-SI units                            *
     * (http://physics.nist.gov/cgi-bin/cuu/Category?view=html&Non-SI+units.x=95&Non-SI+units.y=15) *
     *********************************************************************/


} 
#endif /* end of include guard: PHYSICALCONSTANTS_HPP */
