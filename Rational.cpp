/* 
Rationals.cpp 
Author Thomas Ludbrook. 
Implements the Rational Class in the Rational.h file. 
*/

#include <iostream>
#include <sstream>
#include <regex>
#include <boost/algorithm/string.hpp>
#include "Rational.h"
#include "Integer.h"

namespace cosc326 {
	
	/*  Default constructor 
	* To 0/1. 
	*/ 
	Rational::Rational() 
	{
		(Rational(Integer())); 
	}

	/* Constructor String Input. 
	* Inputs with mix, improper and proper fractors. 
	*/ 
	Rational::Rational(const std::string& str) 
	{
		using namespace std; 

		Integer w, m1, n1; 
		Integer t = Integer("1"); 
		vector<string> parts;
		string s = str; 

		if(s.empty()){
			new (this) Rational(); 
		}else{
			if(s[0] == '+') {
				s.erase(0,1); 
			}
			if(str[0] == '-') {
				t = Integer("-1");
				s.erase(0,1); 
			}

			string delimiters("./");
			boost::algorithm::split(parts, s, boost::is_any_of(delimiters)); 
		}

		// if mixed fraction
		if(parts.size() == 3) {
			w = Integer(parts.at(0))*t;
			m1 = Integer(parts.at(1))*t;
			n1 = Integer(parts.at(2)); 
			new (this) Rational(w,m1,n1); 
		// if improper or proper fraction
		}else if (parts.size() == 2) {
			m1 = Integer(parts.at(0))*t;
			n1 = Integer(parts.at(1));
			new (this) Rational(m1,n1); 
		}else if (parts.size() == 1) {
		//if its a whole number.
			new (this) Rational(Integer(parts.at(0))*t); 
		} else {
			std::cerr <<  "Something went wrong, Try w.n/d" << "\n"; 
		}
	}

	/* Copy constructor */ 
	Rational::Rational(const Rational& r) : m(Integer(r.m)), n(Integer(r.n)) {}

	/* Constructor to a whole number. */
	Rational::Rational(const Integer& a) : m(Integer(a)) , n(Integer("1")) {}
	
	/* Constructor for two Integers 
	* Ensures we never init a Rational Object with b as the denominator. 
	*/ 
	Rational::Rational(const Integer& a, const Integer& b)
	{
		// if b == 0. 
		if(b == Integer()) {
			std::cerr << "Not a valid rational with denominator = 0 \n"; 
			std::cerr << "Denominator will be initalized to 1" << std::endl;
			new (this) Rational(a); 
		}else { 
			m = a; 
			n = b; 
			
		}
	}
	
	/* Constructor for inputs as a mix number */
	Rational::Rational(const Integer& a, const Integer& b, const Integer& c) 
	{
		Rational r = Rational(a); 
		Rational s = Rational(b,c); 
		*this = r+s; 
	}
	
	/* Nothing to delete. */ 
	Rational::~Rational() {}

	/* Most the functionality is handled by the underlying Integer = operator implmentation */ 
	Rational& Rational::operator=(const Rational& r)
	{
		n = r.n; 
		m = r.m; 
		return *this;
	}

	/* Unary Operator. 
	* Flips the sign of the numerator.
	*/
	Rational Rational::operator-() const 
	{
		Rational res = Rational(*this); 
		res.m = -res.m; 
		return res; 
	}

	/* Unary Operator. 
	* Ensures the sign of the Rational is postive. 
	*/
	Rational Rational::operator+() const 
	{
		Rational res = Rational(*this);
		
		// check if rational is negitive. 
		if(!getSign()) { 
			res.m = -res.m; 
		}
		return res;
	}

	/* Addition
	* Using most of the functionality of the Addition in the Integer class 
	* But Adjusting for a Rational number.
	*/ 
	Rational& Rational::operator+=(const Rational& r) 
	{

		if(n == r.n) m+=r.m; 
		else {

			m = m*r.n + r.m*n; 
			n *=r.n; 
		}	
		// Keeps the number in the most simpily form. 
		simpilfy(); 
		return *this;
	}

	/* Subtraction. 
	* Same as above but for substraction
	*/ 
	Rational& Rational::operator-=(const Rational& r) 
	{
		
		if(n == r.n) m-=r.m; 
		else {

			m = m*r.n - r.m*n; 
			n *=r.n; 
		}	
		// ^^ same as above 
		simpilfy(); 

		return *this;
	}

	/* Multiplication
	* Trivally Implemented
	*/ 
	Rational& Rational::operator*=(const Rational& r) 
	{
		m*=r.m;
		n*=r.n; 
		simpilfy(); 
		return *this;
	}

	/* Division
	* Multiply by the reciprocal. 
	*/ 
	Rational& Rational::operator/=(const Rational& r) 
	{
		Rational res = Rational(r.n, r.m);
		*this*=res; 
		simpilfy(); 
		return *this;
	}

	/* Simpilfy. 
	* Method Simpilfies the rational. 
	*/ 
	void Rational::simpilfy() 
	{
		Integer res = Integer(); 
		if(m == Integer()) {
			n = Integer("1");
		}else {
			res = gcd(+m,+n); 
			m /= res;
			n /= res; 
		}
	}

	/* Return the sign of the ratinoal number.*/ 
	bool Rational::getSign() const 
	{
		Integer res = m * n; 
		return res.getSign(); 
	}

	/* Defined with class methods */ 
	Rational operator+(const Rational& lhs, const Rational& rhs) 
	{
		Rational res = Rational(lhs); 
		return res+=rhs; 
	}

	/* Defined with class methods */ 
	Rational operator-(const Rational& lhs, const Rational& rhs) 
	{
		Rational res = Rational(lhs); 
		return res-=rhs; 
	}

	/* Defined with class methods */ 
	Rational operator*(const Rational& lhs, const Rational& rhs) 
	{
		Rational res = Rational(lhs); 
		return res*=rhs; 
	}

	/* Defined with class methods */ 
	Rational operator/(const Rational& lhs, const Rational& rhs) 
	{
		Rational res = Rational(lhs); 
		return res/=rhs; 
	}

	/* Output Stream
	* Uses the output stream from the Integer class and outputs in mix fraction form. 
	*/ 
	std::ostream& operator<<(std::ostream& os, const Rational& i) 
	{
		using namespace std; 
		Rational res = i;
		res.simpilfy(); 
		Integer m = res.m; 
		Integer n = res.n;
		string out  = "";

		if(m == Integer()){
			os << "0"; 
			return os; 
		}

		if(!i.getSign()) {
			out.append("-"); 
		}

		if(n == Integer("1"))
			os << +m; 
		else if (+m < +n)
			os << +m << "/" << +n; 
		else {
			Integer w = Integer(m % n);
			w = (+m - +w)/+n; 
			Integer t = Integer(+m-((+w*+n)));

			if(t == Integer("0"))
				os << w; 
			else
				os << +w << "." << +t << "/" << +n; 
		}
		return os; 
	}

	/* Input Stream
	* Inputs a string then the constructors handle all of the error and input checking. 
	*/ 
	std::istream& operator>>(std::istream& is, Rational& i) 
	{
		using namespace std;
		string s; 
		is >> s; 
		i = Rational(s); 
		return is; 
	}

	/* < operator. 
	* First we check the trival cases i.e if rhs positve and lhs negitive then clearly true. 
	* If none of the trivally cases are true we check which of the product of terms is larger. 
	*/  
	bool operator<(const Rational& lhs, const Rational& rhs) {

		if(!lhs.getSign() && rhs.getSign())
			return true; 
		if(lhs.getSign() && !rhs.getSign())
			return false; 
		if(!lhs.getSign() && !rhs.getSign())
			return +lhs.m*+rhs.n > +lhs.n*+rhs.m; 

		return lhs.m*rhs.n > lhs.n*rhs.m;
	}

	/* Similiar as above. 
	*
	*/ 
	bool operator> (const Rational& lhs, const Rational& rhs) {

		if(!lhs.getSign()&& rhs.getSign())
			return false; 
		if(lhs.getSign()&& !rhs.getSign())
			return true; 
		if(!lhs.getSign()&& !rhs.getSign())
			return +lhs.m*+rhs.n < +lhs.n*+rhs.m; 

		return lhs.m*rhs.n > lhs.n*rhs.m;
	}

	/* defined from above */ 
	bool operator<=(const Rational& lhs, const Rational& rhs) {
		return !(lhs > rhs); 
	}

	/* defined from above */ 
	bool operator>=(const Rational& lhs, const Rational& rhs) {
		return !(lhs < rhs); 
	}

	/* Normalising via the products and checking the signs are the same. */ 
	bool operator==(const Rational& lhs, const Rational& rhs) {
		return (lhs.m*rhs.n == lhs.n*rhs.m) && (lhs.getSign() == rhs.getSign()); 
	}

	/* defined from above */ 
	bool operator!=(const Rational& lhs, const Rational& rhs) {
		return !(lhs == rhs); 
	}
}
