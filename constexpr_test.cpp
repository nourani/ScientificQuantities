/**
 * \file Make sure that all methods and independent operators that are 
 * declared \c constexpr can be used as constant expressions. 
 *
 * If any constexpr method or operator is not working correctly then this 
 * file will fail to compile. There is not need to run the executable 
 * generated from this file as the mere fact that it compiles is an 
 * indication of a successful test.
 */
#include "ScientificQuantities.hpp"

using namespace SciQ ;

int main(int argc, char *argv[])
{
    //
    // Constructors
    //
    {
        constexpr auto foo = Length(1.0) ;
        constexpr auto bar = foo ;
    }
    // 
    // Quantity::in()
    //
    {
        constexpr auto foo = Length(1.0) ; 
        constexpr auto bar = foo.in(kilometer) ;
    }
    //
    // Quantity::compType()
    //
    {
        constexpr auto foo = Length(1.0) ; 
        constexpr auto bar = kilometer ; 
        constexpr auto zoo = foo.compType(bar) ;
    }

    return 0;
}
