#include "Integer.h"
#include "Rational.h"
#include "Rational.cpp"
#include "Integer.cpp"


using namespace cosc326; 

int main(){


    Integer m = Integer("2342342927342374923749237492347293471237401824124701410824"); 
    Integer n = Integer("2123124123"); 
    std::cout << m / n << "\n";


    Integer i = Integer("42342"); 
    Integer j = Integer("2223234");  

    Rational r = Rational(i,j);
    Rational f = r * r; 
    std::cout << f << "\n"; 

    return 0; 
}