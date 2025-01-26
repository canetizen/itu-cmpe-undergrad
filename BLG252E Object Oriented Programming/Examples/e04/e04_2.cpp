// e04_2.cpp
// Constructor with parameters

#include <iostream>
#include <cmath>
using std::cout;
using std::endl;

class Point {				// Declaration of the Point Class with low-limits
public:
	Point(int, int);				// Constructor with two parameters to initialize x and y coordinates
	double distanceFromZero();		// Calculates and returns the distance of a point from (0,0)
	// Getters:
	int getX() { return m_x; }         // Accessor for x coordinate
	int getY() { return m_y; }         // Accessor for y coordinate
	int getMIN_x() { return MIN_x; }   // Accessor for the limit of the x coordinate
	int getMIN_y() { return MIN_y; }   // Accessor for the limit of the y coordinate
	// Setters:
	void setX(int);
	void setY(int);
private:
	// Lower Limits of x and y
	//Constants are usually defined as static members! (See static members)
	const int MIN_x{};            // Zero initialization
	const int MIN_y{};
	int m_x{ MIN_x }, m_y{ MIN_y };	  // x and y coordinates are intialized 
	
};

// ***** Bodies of Member Functions *****

// Constructor with two parameters to initialize x and y coordinates
Point::Point(int firstX, int firstY)
{
	cout << "Constructor is called..." << endl;
	// It can call its methods
	setX(firstX); // Accepts only valid values 
	setY(firstY); // Accepts only valid values 
}

 // Calculates and returns the distance of a point from (0,0)
double Point::distanceFromZero() {
	return sqrt(m_x * m_x + m_y * m_y);   // distance from (0,0)
}

// Setters
void Point::setX(int new_x) {
	if (new_x >= MIN_x) m_x = new_x;  // Accepts only valid values 
}
void Point::setY(int new_y) {
	if (new_y >= MIN_y) m_y = new_y;  // Accepts only valid values 
}

// -------- Main Program -------------
int main()
{
	Point point1 {10, 20};			// Curly brace notation
	Point point2 (30, 40);			// Function call notation 
	Point point3 {-50, 60};		// First parameter will not be accepted
	// Point point4;				// ERROR! No default constructor 
	cout << "x = " << point1.getX() << " y= " << point1.getY() << endl;
	cout << "Distance from Zero = " << point1.distanceFromZero() << endl;
	cout << "x = " << point2.getX() << " y= " << point2.getY() << endl;
	cout << "Distance from Zero = " << point2.distanceFromZero() << endl;
	cout << "x = " << point3.getX() << " y= " << point3.getY() << endl;
	cout << "Distance from Zero = " << point3.distanceFromZero() << endl;

	Point *pointPtr;				    // ptr in not an object, construct is NOT called 
	pointPtr = new Point{70, -80};		// Second parameter will not be accepted
	cout << "x = " << pointPtr->getX() << " y= " << pointPtr->getY() << endl;
	cout << "Distance from Zero = " << pointPtr->distanceFromZero() << endl;
	
	delete pointPtr;
	return 0;
}