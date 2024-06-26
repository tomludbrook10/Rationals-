/* 
Integer.cpp 
Author Thomas Ludbrook
Implements the Integer Class in the Integer.h file. 
*/

#include <string>
#include <sstream>
#include <vector> 
#include <regex> 
#include "Integer.h"

#define DEFAULT_STRING "0"; 

namespace cosc326 {

	/* Default Constructor */
	Integer::Integer()
	{
		main = DEFAULT_STRING; 
		isPostive = true;
	}

	/* Copy constructor */ 
	Integer::Integer(const Integer& i) : main(i.main), isPostive(i.isPostive) {}


	/* Constructor for string input. 
	* Handles the checking for invalid inputs
	* If the input is invalid, main will init to 0. 
	*/
	Integer::Integer(const std::string& s)
	{
		
		bool check = true; 
		size_t i = 0; 
		std::string str = s; 
		
		if(str.empty()) {
			new (this) Integer(); 
		}
		// Negitive check
		if(str[0] == '-') {
			isPostive = false; 
			str.erase(0,1);
		} else 
			isPostive = true;

		while(check && !(i == str.size())) {
			if(!isdigit(str[i])) {
				check = false; 
			} 
			i++; 
		}

		// Default init. 
		if(!check) {
			std::cout << "Tried to convert an non number to an Integer\n";
			std::cout << "Integer will be initalized to 0\n";
			main = "0";
		} else {
			main = str; 
		}
	}

	// Destructor (Don't need to delete anything)
	Integer::~Integer() {}

	// preserves the number and the sign
	Integer& Integer::operator=(const Integer& i)
	{
		main = i.main; 
		isPostive = i.isPostive; 
		return *this;
	}

	/* unary operator.
	* Constructors a new Integer and changes the sign. 
	*/
	Integer Integer::operator-() const 
	{
		Integer res = Integer(*this); 
		res.isPostive = !res.isPostive; 
		return res;
	}

	/* unary operator.
	* Constructors a new Integer and ensures the sign is postive. 
	*/

	Integer Integer::operator+() const 
	{
		Integer res = Integer(*this); 

		if(!res.isPostive) 
			res = -res;
		return res; 
	}

	/* Addition
	* Can be equivalently defined as subtraction depeding on the size of two integers and/or their signs. 
	*/ 
	Integer& Integer::operator+=(const Integer& i) 
	{
		// -10 + 20 or 20 + - 10. Same as 20 - 10. 
		if((*this > i) && (!isPostive && i.isPostive) || (isPostive && !i.isPostive)) 
			main = findDiff(main,i.main);

		// -10 + 20 or 10 + -20. Same as 20 - 10. 
		else if ((*this < i) && (!isPostive && i.isPostive) || (isPostive && !i.isPostive) ) {
			main = findDiff(i.main,main);
			isPostive = !isPostive; 
		} else 
			main = findSum(main, i.main);

		main = removeLeadingZeros(main); 
		return *this;
	}

	/* Subtraction
	* Can be equivalently defined as addition depeding on the size of two Integers and/or their signs. 
	*/ 
	Integer& Integer::operator-=(const Integer& i) 
	{

		/* -10 - 20 or 10 - -20. Same as 10 + 20. 
		* Note that we don't have to change the sign as in the first case *this is already negitive so 
		* adding the two number we get 30 but the sign is still the same so we have -30. 
		*/
		if((!isPostive && i.isPostive) || (isPostive && !i.isPostive) ) 
			main = findSum(main,i.main); 

		// 20 - 10. 
		else if(*this > i)
			main = findDiff(main, i.main);
		
		// 10 - 20. Same as 20 - 10 and flipping the sign. 
		else if (*this < i) {
			main = findDiff(i.main, main); 
			isPostive = !isPostive; 
		// 10 - 10 = 0. More efficant than calling any functions.
		} else {
			main = "0"; 
			isPostive = true;
		}

		main = removeLeadingZeros(main); 
		return *this;
	}

	/* 
	* Multiplcation
	*/
	Integer& Integer::operator*=(const Integer& i) 
	{

		if((isPostive && !i.isPostive) || (!isPostive && !i.isPostive))
			isPostive = !isPostive; 
	
		main = multiply(main,i.main);
		main = removeLeadingZeros(main); 
		return *this;
	}

	/* Division. 
	* We asign a new Integer here rather than a string. 
	* As we our division algorithm is defined in terms of our other Integer functions. 
	*/ 
	Integer& Integer::operator/=(const Integer& i) 
	{

		bool temp = true; 
		if((!isPostive && i.isPostive) || (isPostive && !i.isPostive))
			temp = false; 
		
		*this = division(+*this, +i); 
		isPostive = temp; 

		return *this;
	}

	/* Modulus
	* Use an indentical function to division, other than we output the remainder.
	*/
	Integer& Integer::operator%=(const Integer& i) 
	{
		isPostive = true;
		*this = remainder(+*this, +i);
		return *this;
	}

	bool Integer::getSign() const 
	{
		return isPostive; 
	}

	/*
	* Defining our basic operation with our class methods.
	*/
	Integer operator+(const Integer& lhs, const Integer& rhs) 
	{
		Integer res = Integer(lhs);
		return res+=rhs; 
	}
	// ^^
	Integer operator-(const Integer& lhs, const Integer& rhs) 
	{
		Integer res = Integer(lhs);
		return res-=rhs; 
	}
	// ^^
	Integer operator*(const Integer& lhs, const Integer& rhs) 
	{
		Integer res = Integer(lhs); 
		return res*=rhs; 
	}
	// ^^
	Integer operator/(const Integer& lhs, const Integer& rhs) 
	{
		Integer res = Integer(lhs);
		return res/= rhs; 
	}
	// ^^
	Integer operator%(const Integer& lhs, const Integer& rhs) 
	{
		Integer res = Integer(lhs);
		return res%= rhs; 
	}

	// basic oupstream. 
	std::ostream& operator<<(std::ostream& os, const Integer& i) 
	{
		if(!i.isPostive)
			os << "-"; 
		os << i.main; 
		return os; 
	}
	
	/* 
	* Basic input stream.
	*/
	std::istream& operator>>(std::istream& is, Integer& i) 
	{

		using namespace std; 
    	string in; 
		cin >> in; 
		Integer j = Integer(in); 
		i = j;
		return is; 
	}
	
	/*
	* This function is plagiarised from stack overflow (Can't find the link),
	* Basic < operator but for to numbers repersented by strings.
	*/
	bool operator<(const Integer& lhs, const Integer& rhs) 
	{

		int n1 = lhs.main.size(), n2 = rhs.main.size();
		
		/*
		* Modified, adding this if else statement to check the easy cases to speed things up.
		*/
		if(!lhs.isPostive && !rhs.isPostive) 
			return +lhs > +rhs;
		else if (!lhs.isPostive && rhs.isPostive) 
			return true; 
		else if (lhs.isPostive && !rhs.isPostive)
			return false;

		// From stack overflow onwards.
    	if (n1 < n2)
        	return true;
    	if (n2 < n1)
        	return false;
 
    	for (int i = 0; i < n1; i++)
        	if (lhs.main[i] < rhs.main[i])
            	return true;
        	else if (lhs.main[i] > rhs.main[i])
            	return false;
 
    	return false;
	}

	//  Basically the same as above.
	bool operator> (const Integer& lhs, const Integer& rhs) {
		 
		int n1 = lhs.main.size(), n2 = rhs.main.size();
		
	
		if(!lhs.isPostive && !rhs.isPostive)
			return +lhs < +rhs; 
		else if (!lhs.isPostive && rhs.isPostive)
			return false; 
		else if (lhs.isPostive && !rhs.isPostive)
			return true;
	
    	if (n1 > n2)
        	return true;
    	if (n2 > n1)
        	return false;
 
    	for (int i = 0; i < n1; i++)
        	if (lhs.main[i] > rhs.main[i])
            	return true;
        	else if (lhs.main[i] < rhs.main[i])
            	return false;
 
    	return false;
	}

	bool operator<=(const Integer& lhs, const Integer& rhs)
	{
		return !(lhs > rhs); 
	}

	bool operator>=(const Integer& lhs, const Integer& rhs)
	{
		return !(lhs < rhs);
	}

	bool operator==(const Integer& lhs, const Integer& rhs) 
	{
		return (lhs.main == rhs.main) && (lhs.isPostive == rhs.isPostive);
	}

	bool operator!=(const Integer& lhs, const Integer& rhs) {
		return !(lhs == rhs);
	}

	// basic gcd algorithm, needed for many of the methods.
	Integer gcd(const Integer& a, const Integer& b) 
	{
		

		if(a == b)
			return a;
		// Note, line below is (b == 0). 
		if(b == Integer())
			return a; 

		if(a == b)
			return a; 

		if(a > b)
			return gcd(a-b, b);
		return gcd(a, b-a); 
	}

	/*
	* Function for taking two strings and adding the together. https://www.geeksforgeeks.org/sum-two-large-numbers/
	*/ 
	std::string findSum(std::string str1, std::string str2)
	{
		using namespace std; 

    	// Before proceeding further, make sure length
    	// of str2 is larger.

    	if (str1.length() > str2.length())
        	swap(str1, str2);
 
    	// Take an empty string for storing result
    	string str = "";
 
    	// Calculate length of both string
    	int n1 = str1.length(), n2 = str2.length();
 
    	// Reverse both of strings
    	reverse(str1.begin(), str1.end());
    	reverse(str2.begin(), str2.end());
 
    	int carry = 0;
    	for (int i=0; i<n1; i++)
    	{
        	// Do school mathematics, compute sum of
        	// current digits and carry
        	int sum = ((str1[i]-'0')+(str2[i]-'0')+carry);
        	str.push_back(sum%10 + '0');
 
        	// Calculate carry for next step
        	carry = sum/10;
    	}
 
    	// Add remaining digits of larger number
    	for (int i=n1; i<n2; i++)
    	{
        	int sum = ((str2[i]-'0')+carry);
        	str.push_back(sum%10 + '0');
        	carry = sum/10;
    	}
 
    	// Add remaining carry
    	if (carry)
        	str.push_back(carry+'0');
 
    	// reverse resultant string
    	reverse(str.begin(), str.end());
 
    	return str;
	}

	/*
	* Function for taking two strings and substracting then. https://www.geeksforgeeks.org/difference-of-two-large-numbers/
	*/ 
	std::string findDiff(std::string str1, std::string str2)
	{ 

		using namespace std;

		string minus = ""; 

    	if (Integer(str1) < Integer(str2)) {
        	swap(str1, str2);
			minus = "-";
		}
    	// Take an empty string for storing result
    	string str = "";
 
    	// Calculate length of both string
    	int n1 = str1.length(), n2 = str2.length();
 
    	// Reverse both of strings
    	reverse(str1.begin(), str1.end());
    	reverse(str2.begin(), str2.end());
 
    	int carry = 0;

		// Run loop till small string length
    	// and subtract digit of str1 to str2
    	for (int i = 0; i < n2; i++) {
        	// Do school mathematics, compute difference of
        	// current digits
 
        	int sub = ((str1[i] - '0') - (str2[i] - '0') - carry);
 
        	// If subtraction is less then zero
        	// we add then we add 10 into sub and
        	// take carry as 1 for calculating next step
        	if (sub < 0) {
            	sub = sub + 10;
            	carry = 1;
       	 	}
        	else
            	carry = 0;
 
        	str.push_back(sub + '0');
    	}

		// subtract remaining digits of larger number
    	for (int i = n2; i < n1; i++) {
        	int sub = ((str1[i] - '0') - carry);
 
        	// if the sub value is -ve, then make it positive
        	if (sub < 0) {
            	sub = sub + 10;
            	carry = 1;
        	}
        	else
            	carry = 0;
 
        	str.push_back(sub + '0');
    	}
 
    	// reverse resultant string
    	reverse(str.begin(), str.end());
 
    	return minus + str;
	}

	/*
	* Function for taking two strings and multiplying then. https://www.geeksforgeeks.org/multiply-large-numbers-represented-as-strings/
	*/  
	std::string multiply(std::string num1, std::string num2)
	{
		using namespace std;

		int len1 = num1.size();
    	int len2 = num2.size();
    	if (len1 == 0 || len2 == 0)
    		return "0";
 
    	// will keep the result number in vector
    	// in reverse order
    	vector<int> result(len1 + len2, 0);
 
    	// Below two indexes are used to find positions
    	// in result.
    	int i_n1 = 0;
    	int i_n2 = 0;

		// Go from right to left in num1
    	for (int i=len1-1; i>=0; i--)
    	{
        	int carry = 0;
        	int n1 = num1[i] - '0';

        	i_n2 = 0;
         
        	for (int j=len2-1; j>=0; j--)
        	{
            
            	int n2 = num2[j] - '0';
            	int sum = n1*n2 + result[i_n1 + i_n2] + carry;
 
            	
            	carry = sum/10;
 
            
            	result[i_n1 + i_n2] = sum % 10;
 
            	i_n2++;
        	}
		
        if (carry > 0)
            result[i_n1 + i_n2] += carry;
 
        i_n1++;
   		}	
 
    	// ignore '0's from the right
    	int i = result.size() - 1;
    	while (i>=0 && result[i] == 0)
    	i--;
 
    	// If all were '0's - means either both or
    	// one of num1 or num2 were '0'
    	if (i == -1)
    		return "0";
 
    	// generate the result string
    	string s = "";
     
    	while (i >= 0)
        s += std::to_string(result[i--]);
 
    	return s;
	}

	/* Division
	* Less naive version of counting how many times, one can minus divisor off of the dividend. 
	* Instead, we can increase the divisor by a order of mangitude for each iteration until the current divident is larger than the divisor, at which point we can now substract it.
	* Then we can multiple the Quotient for each iteration. For example 4400 / 4 = 1100. Thus the naive approach has 1100 operations. 
	* Compared: 4400 / 4000 = 1, R = 400. 400 / 400 = 1 R = 0. Then (1*1000) + (1*100)  = 1100. Here, we have a total of 7 operations.
	*/
	Integer division(Integer divided, Integer divisor) 
	{

		if(divided == divisor)
			return Integer("1");

		if(divisor > divided)
			return divided; 

		Integer one = Integer("1"); 
		Integer result = Integer(); 

		size_t lengthT = (divided.main.size() - divisor.main.size() + 1);
		Integer currDivisor; 

		for (size_t i = 0; i < lengthT; i++) { 
			
			currDivisor = divisor; 
			size_t countT = 0; 
			
			// algorithm for making dividend larger
			do {
				currDivisor.main += "0"; 
				countT++; 
			}while(divided > currDivisor); 

			currDivisor.main = currDivisor.main.substr(0,currDivisor.main.size()-1); 
			countT--; 

			// init to 0. 
			Integer count = Integer(); 

			while(divided >= currDivisor) {
				count+=one; 
				divided-=currDivisor; 
			}
			
			// Taking into account how much larger we made the dividend. 
			for(int j = 0; j < countT; j++)
				count.main += "0"; 

			result+=count; 
		}
		return result; 
	}

	 
	/* Remainder 
	* Same as the divison algorithm but we return the divided at the end.
	*/
	Integer remainder(Integer divided, Integer divisor) 
	{

		if(divided == divisor)
			return Integer("1");

		if(divisor > divided)
			return divided; 

		Integer one = Integer("1"); 
		Integer result = Integer(); 

		size_t lengthT = (divided.main.size() - divisor.main.size() + 1);
		Integer currDivisor; 

		for (size_t i = 0; i < lengthT; i++) { 
			
			currDivisor = divisor; 
			size_t countT = 0; 
			
			do {
				currDivisor.main += "0"; 
				countT++; 
			}while(divided > currDivisor); 

			currDivisor.main = currDivisor.main.substr(0,currDivisor.main.size()-1); 
			countT--; 

			Integer count = Integer(); 

			while(divided >= currDivisor) {
				count+=one; 
				divided-=currDivisor; 
			}
			
			for(int j = 0; j < countT; j++)
				count.main += "0"; 
			result+=count; 
		}
		return divided; 
	}

	std::string removeLeadingZeros(std::string s) 
	{
		const std::regex pattern("^0+(?!$)");
		s = regex_replace(s, pattern, "");
		return s;
	}
}