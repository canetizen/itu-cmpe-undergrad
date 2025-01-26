// e03_4.cpp
// Accessors (Getters) and Mutators (Setters)

#include <iostream>
#include <cmath>     // To use the std::sqrt() function

using std::cout;
using std::endl;

// Point class with lower limits
class Point{							// Declaration of the Point Class with low-limits
public:
	double distanceFromZero();			// Calculates and returns the distance of a point from (0,0)
	// Getters:
	int getX() { return m_x; }         // Accessor for x coordinate
	int getY() { return m_y; }         // Accessor for y coordinate
	// Setters:
	void setX(int);
	void setY(int);
private:
	// Lower Limits of x and y. They are constants equal to zero 
	//Constants are usually defined as static members! (See static members)
	const int MIN_x { };				// Minimum value for x is zero
	const int MIN_y { };				// Minimum value for y is zero
	// x and y coordinates are initialized to their minimum values
	int m_x{ MIN_x }, m_y{ MIN_y };
};

// ***** Bodies of Member Functions *****

 // Calculates and returns the distance of a point from (0,0)
double Point::distanceFromZero() {
	return std::sqrt(m_x * m_x + m_y * m_y);   // distance from (0,0)
	// The sqrt() function returns the square root of a number. This function is defined in the cmath header file.
}

// Setters
// They checks the input values.
// The values are accepted only if they fall within the limits.
void Point::setX(int new_x){
    if (new_x >= MIN_x) m_x = new_x;	// Accepts only valid values 
  }
 void Point::setY(int new_y){
    if (new_y >= MIN_y) m_y = new_y;	// Accepts only valid values 
  }


 // Main function to test the Point class
int main()
{
  Point point1;							// point1 object is defined
  cout << "x = " << point1.getX() << " y= " << point1.getY() << endl;
  cout << "Distance from Zero = " << point1.distanceFromZero() << endl;

  point1.setX(10);    // Accepted
  point1.setY(-10);	// Not accepted
  cout << "x = " << point1.getX() << " y= " << point1.getY() << endl;
  cout << "Distance from Zero = " << point1.distanceFromZero() << endl;
  return 0;
}