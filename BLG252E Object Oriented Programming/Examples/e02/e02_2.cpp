// e02_2.cpp
// Global and local variables
// Scope resolution operator ::

#include<iostream>

double value1{ 3.14 }; // Global

int main() {
	int value1{ 10 };		// Outer local value1 hides global value1
	int value2{ 20 };		// Outer local value2
	std::cout << "Value of global value1 = " << ::value1 << std::endl;
	std::cout << "Value of outer local value1 = " << value1 << std::endl;
	std::cout << "Value of local value2 = " << value2 << std::endl;
	::value1 = ::value1 + value1;	// Add global value1 and local value1
	std::cout << "Value of modified global value1 = " << ::value1 << std::endl;
	std::cout << "Value of outer local value1 = " << value1 << std::endl;
	{ /* New (inner) block scope starts here... */
		int value1{ 15 };			// This is a new variable that hides the outer value1
		int value3{ 30 };			// Local inner value3
		::value1 = ::value1 + 0.1;  // Modify the global value1
		std::cout << "\nValue of inner local value1 = " << value1 << std::endl;
		std::cout << "Value of global value1 = " << ::value1 << std::endl;
		std::cout << "Value of local value2 = " << value2 << std::endl;
	} /* ...and ends here. */
	value2++;  // We can access outer local value2
	std::cout << "Value of local value2 = " << value2 << std::endl;	
	//value3++;  You cannot access a inner local variable anymore.
	return 0;
}