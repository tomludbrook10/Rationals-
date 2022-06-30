#ifndef INTEGER_H_INCLUDED
#define INTEGER_H_INCLUDED

#include <iostream>
#include <string>

namespace cosc326 {

	class Integer {

	public:

		Integer();                             // Integer i;
		Integer(const Integer& i);             // Integer j(i);
		Integer(const std::string& s);        // Integer k("123");

		~Integer();

		Integer& operator=(const Integer& i);  // j = i;

		// Unary operators
		Integer operator-() const;                   // -j;
		Integer operator+() const;                   // +j;

		// Arithmetic assignment operators
		Integer& operator+=(const Integer& i); // j += i;
		Integer& operator-=(const Integer& i); // j -= i;
		Integer& operator*=(const Integer& i); // j *= i;
		Integer& operator/=(const Integer& i); // j /= i;
		Integer& operator%=(const Integer& i); // j %= i;

		
		friend bool operator<(const Integer& lhs, const Integer& rhs);
		friend bool operator>(const Integer& lhs, const Integer& rhs); // lhs > rhs
		friend bool operator==(const Integer& lhs, const Integer& rhs); // lhs == rhs
		friend Integer division(Integer, Integer);
		friend Integer remainder(Integer, Integer); 
		friend std::ostream& operator<<(std::ostream& os, const Integer& i);  // std::cout << i << std::endl;

		bool getSign() const; 

	private:
		
		// storage of the class. 
		std::string main; 
		bool isPostive;

	};

	// Binary operators
	Integer operator+(const Integer& lhs, const Integer& rhs); // lhs + rhs;
	Integer operator-(const Integer& lhs, const Integer& rhs); // lhs - rhs;
	Integer operator*(const Integer& lhs, const Integer& rhs); // lhs * rhs;
	Integer operator/(const Integer& lhs, const Integer& rhs); // lhs / rhs;
	Integer operator%(const Integer& lhs, const Integer& rhs); // lhs % rhs;

	std::istream& operator>>(std::istream& is, Integer& i);        // std::cin >> i;

	bool operator<=(const Integer& lhs, const Integer& rhs); // lhs <= rhs
	bool operator>=(const Integer& lhs, const Integer& rhs); // lhs >= rhs
	bool operator==(const Integer& lhs, const Integer& rhs); // lhs == rhs
	bool operator!=(const Integer& lhs, const Integer& rhs); // lhs != rhs

	Integer gcd(const Integer& a, const Integer& b);  // i = gcd(a, b);

	std::string findSum(std::string, std::string);
	std::string findDiff(std::string, std::string); 
	std::string multiply(std::string, std::string); 
	std::string removeLeadingZeros(std::string);
}

#endif
