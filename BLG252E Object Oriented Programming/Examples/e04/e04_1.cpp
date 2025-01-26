// e04_1.cpp
// Default Constructor

#include <iostream>
#include <cmath>
using std::cout;
using std::endl;

class Point {						// Declaration/definition of the Point Class with low-limits
public:
	Point();						// Default Constructor
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
	const int MIN_x{ };         // Zero initialization 
	const int MIN_y{ };         // Zero initialization
	int m_x, m_y;				// x and y coordinates, initialization is not necessary

};

// ***** Bodies of Member Functions *****

// Default Constructor
Point::Point()
{
	cout << "Default Constructor is called..." << endl;
	m_x = MIN_x;					// Assigns minimum values to coordinates
	m_y = MIN_y;
}

 // Calculates and returns the distance of a point from (0,0)
double Point::distanceFromZero() {
	return std::sqrt(m_x * m_x + m_y * m_y);   // distance from (0,0)
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
	Point point1, point2;				// Default construct is called 2 times
	cout << "x = " << point1.getX() << " y= " << point1.getY() << endl;
	cout << "Distance from Zero = " << point1.distanceFromZero() << endl;
	cout << "x = " << point2.getX() << " y= " << point2.getY() << endl;
	cout << "Distance from Zero = " << point2.distanceFromZero() << endl;

	Point *pointPtr;						// ptr in not an object, construct is NOT called 
	pointPtr = new Point;					// Default construct is called once 
	cout << "x = " << pointPtr->getX() << " y= " << pointPtr->getY() << endl;
	cout << "Distance from Zero = " << pointPtr->distanceFromZero() << endl;
	
	delete pointPtr;
	return 0;
}
