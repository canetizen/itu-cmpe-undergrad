// e03_3.cpp
// Private methods
// Point class with lower limits

#include <iostream>
using std::cout;
using std::endl;

class Point{					// Declaration of the Point Class with limits
public:
	bool move(int, int);		// A function to move points
	void print();				// to print cordinates on the screen
private:
	void reset();				// private method
	// Lower Limits of x and y
	//Constants are usually defined as static members! (See static members)
	const int MIN_x{ 0 };
	const int MIN_y{ 0 };
	// x and y coordinates are initialized to their minimum values
	int m_x{ MIN_x }, m_y{ MIN_y };
};					

// ***** Bodies of Member Functions *****

// A function to move the points 
// It checks the input values.
// If the values fall within the limits they are accepted, the point moves, and the function returns true.
// If the values are smaller than the lower limits, it calls the reset method, and the function returns false.
bool Point::move(int new_x, int new_y)
{
	if (new_x >= MIN_x && new_y >= MIN_y)					// if new_x and new_y are within the limits					
	{
		m_x = new_x;						// assigns new value to x coordinate
		m_y = new_y;						// assigns new value to y coordinate 
		return true;	                    // new values are accepted
	}
	reset();								// calls reset
	return false;							// new values are not accepted
}

// To print the coordinates on the screen 
void Point::print()
{
	cout << "X= " << m_x << ", Y= " << m_y << endl;
}

// To reset coordinates to zero
void Point::reset()
{
	m_x = MIN_x;
	m_y = MIN_y;
}
	
// Main function to test the Point class
int main()
{
  Point point1;									// point1 object is defined
  if (point1.move(10, 20))    		// try to move to 10,20 
	   cout << "Input values are accepted" << endl;
  else cout << "Input values are NOT accepted" << endl;
	   point1.print();								// Print coordinates on the screen
  if (point1.move(-10, 20))    		// try move to -10,20 
	   cout << "Input values are accepted" << endl;
  else cout << "Input values are NOT accepted" << endl;
	   point1.print();								// Print coordinates on the screen
  return 0;
}
