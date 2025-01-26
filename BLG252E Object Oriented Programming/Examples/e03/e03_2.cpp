// e03_2.cpp
// Access control
// Point class with limits

#include <iostream>

class Point{					// Declaration of the Point Class with limits
public:
	bool move(int, int);		// A function to move points
	void print();				// to print coordinates on the screen
private:
	// Limits of x and y
	//Constants are usually defined as static members! (See static members)
	const int MIN_x{ 0 };
	const int MAX_x{ 500 };
	const int MIN_y{ 0 };
	const int MAX_y{ 300 };
	// x and y coordinates are initlalized to their minimum values
	int m_x{MIN_x}, m_y{MIN_y};
};

// ***** Bodies of Member Functions *****

// A function to move the points 
// It checks the input values.
// If the values fall within the limits they are accepted, the point moves, and the function returns true.
// If the values are not within the limits, the point does not move, and the function returns false.
bool Point::move(int new_x, int new_y)
{
	if (new_x >= MIN_x && new_x <= MAX_x &&		// if new_x is within the limits
		new_y >= MIN_y && new_y <= MAX_y)		// if new_x is within the limits
	{
		m_x = new_x;							// assigns new value to x coordinate
		m_y = new_y;							// assigns new value to y coordinate 
		return true;
	}
	return false;								// new values are not accepted
}

// To print the coordinates on the screen 
void Point::print()
{
	std::cout << "X= " << m_x << ", Y= " << m_y << std::endl;
}
		
// Main function to test the Point class
int main()
{

	Point point1;							// point1 object is defined
	int x, y;								// Two variables to read some values from the keyboard
	std::cout << " Give x and y coordinates ";
		std::cin >> x >> y;       	        // Read two values from the keyboard
	if (point1.move(x, y))    	// send move message and check the result
		std::cout << "Input values are accepted" << std::endl;
	else
		std::cout << "Input values are NOT accepted" << std::endl;
	point1.print();							// Print coordinates on the screen
	return 0;
}
