#ifndef RATIONAL_H_INCLUDED
#define RATIONAL_H_INCLUDED

#include <iostream>
#include <string>
#include "Integer.h"

namespace cosc326 {

	class Rational {
    
	public:

		Rational();
        Rational(const std::string& str);
        Rational(const Rational& r);
        Rational(const Integer& a); // a
        Rational(const Integer& a, const Integer& b); // a/b
        Rational(const Integer& a, const Integer& b, const Integer& c); // a + b/c
        
		~Rational();

		bool getSign() const; // + or - ?

        Rational& operator=( const Rational& r); // q = r;
        
		// Unary operators
		Rational operator-() const; // -r;
		Rational operator+() const; // +r;
	   
        // Arithmetic assignment operators
		Rational& operator+=(const Rational& r); // q += r;
		Rational& operator-=(const Rational& r); // q -= r;
		Rational& operator*=(const Rational& r); // q *= r;
		Rational& operator/=(const Rational& r); // q /= r;
												 
		friend bool operator<(const Rational& lhs, const Rational& rhs); // lsh < rhs
		friend bool operator> (const Rational& lhs, const Rational& rhs); // lhs > rhs
		friend std::ostream& operator<<(std::ostream& os, const Rational& i); // std::cout << i << std::endl;
		friend bool operator==(const Rational& lhs, const Rational& rhs); // lhs == rhs
		

	private:
		// Can add internal storage or methods here
		void simpilfy(); // 8/10 -> 4/5
		Integer m;
		Integer n; 
	};

	// Binary operators
	Rational operator+(const Rational& lhs, const Rational& rhs); // lhs + rhs;
	Rational operator-(const Rational& lhs, const Rational& rhs); // lhs - rhs;
	Rational operator*(const Rational& lhs, const Rational& rhs); // lhs * rhs;
	Rational operator/(const Rational& lhs, const Rational& rhs); // lhs / rhs;
	
	
	std::istream& operator>>(std::istream& is, Rational& i);        // std::cin >> i;

	
	bool operator<=(const Rational& lhs, const Rational& rhs); // lhs <= rhs
	bool operator>=(const Rational& lhs, const Rational& rhs); // lhs >= rhs
	bool operator!=(const Rational& lhs, const Rational& rhs); // lhs != rhs

}

#endif
