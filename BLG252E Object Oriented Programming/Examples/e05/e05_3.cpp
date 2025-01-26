// e05_3.cpp
// Defaulting the equality operator ==

#include <iostream>
#include <cmath>
using std::cout;
using std::endl;

class ComplexNumber {								// Declaration/definition of the ComplexNumber Class 
public:
	ComplexNumber() = default;						// Default constructor (empty body)
	ComplexNumber(double, double);					// Constructor with two parameters to initialize real and imaginary parts
	double getSize() const;							// calculates and returns the size
	bool operator==(const ComplexNumber&) const =default;	// Default equality operator, member-wise comparison
	void print() const;								// print real and imaginary parts
private:
	double m_re{}, m_im{1};							// real and imaginary parts are initialized 
};

// ***** Bodies of Member Functions *****

// Constructor with two parameters to initialize real and imaginary parts
ComplexNumber::ComplexNumber(double in_re, double in_im): m_re{in_re}, m_im{in_im}
{}

// calculates and returns the size
double ComplexNumber::getSize() const
{
	return sqrt(m_re * m_re + m_im * m_im);
}

// A const method to print the complex number on the screen
void ComplexNumber::print() const {
	cout << "Real = " << m_re << endl;
	cout << "Imaginary = " << m_im << endl;
}

// -------- Main Program -------------
int main()
{
	ComplexNumber complex0;
	ComplexNumber complex1{ 1.1, 2.3 };			
	ComplexNumber complex2{ 0, 1.0 };
	
	if (complex1 == complex2) cout << "complex1 is equal to complex2" << endl;
	else cout << "complex1 is equal to complex2" << endl;
	if (complex0 == complex2) cout << "Equal" << endl;
	else cout << "Not equal" << endl;
	
	/*
	/*
	// -----
	ComplexNumber *ptrComplex;		// Pointer to complex numbers
	if (complex0 > complex1) ptrComplex = &complex0;			// pointer points to complex1
	else ptrComplex = &complex1;								// pointer points to complex2
	ptrComplex->print();

	ComplexNumber complex3{ 4, 5 };
	if (complex3 > *ptrComplex) ptrComplex = &complex3;
	ptrComplex->print();
	*/
	return 0;
}