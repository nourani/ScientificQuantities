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
    // Quantity::getValue()
    //
    {
        constexpr auto foo = Length(1.0) ;
        constexpr auto foo_value = foo.getValue() ;
    }
    // 
    // Quantity:: operator double() 
    //
    {
        constexpr auto foo = Length(1.0) ;
        constexpr double foo_value = foo ;
    }
    // 
    // operator*(Quantity<>& Quantity<>&)
    //
    {
        constexpr auto foo = Length(1.0) ; 
        constexpr auto bar = Length(2.0) ;
        constexpr auto product = foo * bar ;
    }
    // 
    // operator/(Quantity<>& Quantity<>&)
    //
    {
        constexpr auto foo = Length(1.0) ; 
        constexpr auto bar = Length(2.0) ;
        constexpr auto ratio = foo / bar ;
    }
    // 
    // operator==(Quantity<>& Quantity<>&)
    //
    {
        constexpr auto foo = Length(1.0) ;
        constexpr auto bar = Length(2.0) ; 
        constexpr auto is_equal = (foo == bar) ;
    }
    // 
    // operator!=(Quantity<>& Quantity<>&)
    //
    {
        constexpr auto foo = Length(1.0) ;
        constexpr auto bar = Length(2.0) ; 
        constexpr auto is_not_equal = (foo != bar) ;
    }
    // 
    // operator<=(Quantity<>& Quantity<>&)
    //
    {
        constexpr auto foo = Length(1.0) ;
        constexpr auto bar = Length(2.0) ; 
        constexpr auto is_less_or_equal = (foo <= bar) ;
    }
    // 
    // operator>=(Quantity<>& Quantity<>&)
    //
    {
        constexpr auto foo = Length(1.0) ;
        constexpr auto bar = Length(2.0) ; 
        constexpr auto is_more_or_equal = (foo >= bar) ;
    }
    // 
    // operator<(Quantity<>& Quantity<>&)
    //
    {
        constexpr auto foo = Length(1.0) ;
        constexpr auto bar = Length(2.0) ; 
        constexpr auto is_less = (foo < bar) ;
    }
    // 
    // operator>(Quantity<>& Quantity<>&)
    //
    {
        constexpr auto foo = Length(1.0) ;
        constexpr auto bar = Length(2.0) ; 
        constexpr auto is_greater = (foo > bar) ;
    }
    //
    // operator*(Quantity<>&, T)
    //
    {
        constexpr auto foo = Length(1.0) ; 
        constexpr double bar = 5.0 ; 
        constexpr auto product = foo * bar ; 
    }
    //
    // operator*(T, Quantity<>&)
    //
    {
        constexpr auto foo = Length(1.0) ; 
        constexpr double bar = 5.0 ; 
        constexpr auto product = bar * foo ; 
    }
    //
    // operator/(Quantity<>&, T)
    //
    {
        constexpr auto foo = Length(1.0) ; 
        constexpr double bar = 5.0 ; 
        constexpr auto ratio = foo / bar ; 
    }
    //
    // operator/(T, Quantity<>&)
    //
    {
        constexpr auto foo = Length(1.0) ; 
        constexpr double bar = 5.0 ; 
        constexpr auto ratio = bar / foo ; 
    }
    return 0 ;
}
