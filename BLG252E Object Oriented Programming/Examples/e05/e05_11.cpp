// e05_11.cpp
// Overloading of unary pre-increment and post-increment operator ++ 
// These operators increment the real part of a complex number by 0.1

#include <iostream>
#include <cmath>
using std::cout;
using std::endl;

class ComplexNumber {									// Declaration/definition of the ComplexNumber Class 
public:
	ComplexNumber() = default;							// Default constructor (empty body)
	ComplexNumber(double, double);						// Constructor with two parameters to initialize real and imaginary parts
	void operator=(const ComplexNumber&);				// Assignment operator 
	const ComplexNumber& operator++();					// pre-increment ++ operator 
	ComplexNumber operator++(int);						// pos-tincrement ++ operator
	void print() const;									 // print real and imaginary parts
private:
	double m_re{}, m_im{ 1 };							// real and imaginary parts are initialized 
};

// Constructor with two parameters to initialize real and imaginary parts
ComplexNumber::ComplexNumber(double in_re, double in_im) : m_re{ in_re }, m_im{ in_im }
{
	cout << "Constructor with to paramters is called" << endl;
}

// Function for operator =
// Compiler provides the same function
// The main program rus correctly even if this function is deleted
void ComplexNumber::operator=(const ComplexNumber& in_number)
{
	m_re = in_number.m_re;
	m_im = in_number.m_im;
	cout << "Assignment operator has been invoked" << endl;
}
// Pre-incerement ++ operator
// increments the real part of a complex number by 0.1
const ComplexNumber& ComplexNumber::operator++()
{
	m_re = m_re + 0.1;
	return *this;
}

// post-increment ++ operator
// increments the real part of a complex number by 0.1
ComplexNumber  ComplexNumber::operator++(int)
{
	ComplexNumber temp{ *this };	// creates a copy of the original object
	m_re = m_re + 0.1;
	return temp;				    // returns the copy of the original object
}

// A const method to print the complex number on the screen
void ComplexNumber::print() const {
	cout << "Real = " << m_re;
	cout << " Imaginary = " << m_im << endl;
}


int main()
{
	ComplexNumber complex0;
	ComplexNumber complex1{ 1.1, 2.3 };
	
	complex0 = ++complex1;								// pre-increment operator++() is called

	cout << "After the operation" << endl;
	cout << "complex0 = ";
	complex0.print();
	cout << "complex1 = ";
	complex1.print();

	complex0 = complex1++;								// post-increment operator++(int) is called

	cout << "After the operation" << endl;
	cout << "complex0 = ";
	complex0.print();
	cout << "complex1 = ";
	complex1.print();
	return 0;
}