// e05_4.cpp
// Overloading the + operator for ComplexNumber objects

#include <iostream>
#include <cmath>
using std::cout;
using std::endl;

class ComplexNumber {								// Declaration/definition of the ComplexNumber Class 
public:
	ComplexNumber() = default;						// Default constructor (empty body)
	ComplexNumber(double, double);					// Constructor with two parameters to initialize real and imaginary parts
	ComplexNumber operator+(const ComplexNumber&) const; // Signature of the method for operator + 
	void print() const;								// print real and imaginary parts
private:
	double m_re{}, m_im{1};							// real and imaginary parts are initialized 
};

// ***** Bodies of Member Functions *****

// Constructor with two parameters to initialize real and imaginary parts
ComplexNumber::ComplexNumber(double in_re, double in_im): m_re{in_re}, m_im{in_im}
{
	cout << "Constructor with to paramters is called" << endl;
}

// The Body of the function for operator + 
ComplexNumber ComplexNumber::operator+(const ComplexNumber& in_number) const
{
	cout << "Operator + is called" << endl;
	double result_re, result_im; // Local variables to store the results
	result_re = m_re + in_number.m_re;
	result_im = m_im + in_number.m_im;
	return ComplexNumber(result_re, result_im);  // constructor ComplexT(double,double) is called
}

// A const method to print the complex number on the screen
void ComplexNumber::print() const {
	cout << "Real = " << m_re;
	cout << " Imaginary = " << m_im << endl;
}

// -------- Main Program -------------
int main()
{
	ComplexNumber complex0;
	ComplexNumber complex1{ 1.1, 1.2 };			
	ComplexNumber complex2{ 2.1, 2.2 };
	cout << "Before the addition complex0: ";
	complex0.print();
	complex0 = complex1 + complex2;
	cout << "After the addition complex0: ";
	complex0.print();
	return 0;
}