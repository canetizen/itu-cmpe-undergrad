// e05_1.cpp
// Overloading the operator > for compelx numbers

#include <iostream>
using std::cout;
using std::endl;

class ComplexNumber {								// Declaration/definition of the ComplexNumber Class 
public:
	ComplexNumber()=default;						// Default constructor (empty body)
	ComplexNumber(double, double);					// Constructor with two parameters to initialize real and imaginary parts
	bool operator>(const ComplexNumber&) const;		// Method to overload the operator >
	bool is_greater(const ComplexNumber&) const;	// Method to compare complex numbers (same function as the operator > , unnecessary)
	void print() const;								// print real and imaginary parts
private:
	double m_re{}, m_im{1};							// real and imaginary parts are initialized 
};

// ***** Bodies of Member Functions *****

// Constructor with two parameters to initialize real and imaginary parts
ComplexNumber::ComplexNumber(double in_re, double in_im): m_re{in_re}, m_im{in_im}
{}

bool ComplexNumber::operator>(const ComplexNumber& in_number) const   // Method to overload the operator >
{
	cout << "Operator > is called" << endl;
	return (m_re * m_re + m_im * m_im) > (in_number.m_re * in_number.m_re + in_number.m_im * in_number.m_im);     // To compare them sqrt is not necessary
	
	/* This is the longer version
	if ( (m_re * m_re + m_im * m_im) > (in_number.m_re * in_number.m_re + in_number.m_im * in_number.m_im) ) return true;
	else return false;
	*/
}

// Method to compare complex numbers (now unnecessary)
bool ComplexNumber::is_greater(const ComplexNumber& in_number) const   
{
	return (m_re * m_re + m_im * m_im) > (in_number.m_re * in_number.m_re + in_number.m_im * in_number.m_im);     // To compare them sqrt is not necessary

	/* This is the longer version
	if ( (m_re * m_re + m_im * m_im) > (in_number.m_re * in_number.m_re + in_number.m_im * in_number.m_im) ) return true;
	else return false;
	*/
}

// A const method to print the complex number on the screen
void ComplexNumber::print() const {
	cout << "Real = " << m_re << endl;
	cout << "Imaginary = " << m_im << endl;
}



// -------- Main Program -------------
int main()
{
	ComplexNumber complex1{ 1.1, 2.3 };			
	ComplexNumber complex2{ 2.5, 3.7 };
	
	if (complex1 > complex2) cout << "Size of the complex1 is greater than the size of the complex2" << endl;
	else cout << "Size of the complex1 is NOT greater than the size of the complex2" << endl;

	// ----- Using a poiter to complex numbers
	ComplexNumber *ptrComplex;									// Pointer to complex numbers
	if (complex1 > complex2) ptrComplex = &complex1;			// pointer points to complex1
	else ptrComplex = &complex2;								// pointer points to complex2
	ptrComplex->print();

	ComplexNumber complex3{ 4, 5 };
	if (complex3 > *ptrComplex) ptrComplex = &complex3;
	ptrComplex->print();

	// Instad of the operator > we can use the is_greater function. Which one is easier to understand?
	if (complex1.is_greater(complex2)) cout << "Size of the complex1 is greater than the size of the complex2" << endl;
	else cout << "Size of the complex1 is NOT greater than the size of the complex2" << endl;
	return 0;
}