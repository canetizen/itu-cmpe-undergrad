// e04_10.cpp
// Case 1: Passing objects by value (inefficient!!)
// Gets the argument by value
// Returns result by value

#include <iostream>
#include <cmath>
using std::cout;
using std::endl;

class Point {							// Declaration of the Point Class with low-limits
public:
	Point();							// Default Constructor
	Point(int, int);					// Constructor to initialize x and y cooridinates
	Point(const Point&);				// Copy Constructor
	void operator=(const Point&);		// Assignment operatior (we will cover it in  the next examples)
	double distanceFromZero() const;	// const method calculates and returns the distance of a point from (0,0)
	void print() const;					// const method prints coordinates on the screen
	// Getters are const:
	int getX() const { return m_x; }    // Accessor for x coordinate
	int getY() const { return m_y; }    // Accessor for y coordinate
	int getMIN_x() const { return MIN_x; }   // Accessor for the limit of the x coordinate
	int getMIN_y() const { return MIN_y; }   // Accessor for the limit of the y coordinate
	unsigned int getPrintCount() const { return m_printCount; }
	// Setters are NOT const:
	void setX(int);
	void setY(int);
	bool move(int, int);					// A non-constant method to move points
	~Point();								// Destructor

private:
	// Lower Limits of x and y coordinates
	const int MIN_x{};            // Zero initialization
	const int MIN_y{};
	int m_x{ MIN_x }, m_y{ MIN_y };	  // x ve y coordinates are initialized 
	mutable unsigned int m_printCount{};  // A mutable variable to count how many times a point object is printed
};

// ***** Bodies of Member Functions *****

// The default Constructor
// We write the default constructor only to monitor how many objects are created
Point::Point() {
	cout << "Default Constructor is called..." << endl;
}

// Constructor to initialize x and y coordinates
Point::Point(int in_x, int in_y) : m_printCount{}
{
	cout << "Constructor is called..." << endl;
	// It can call its methods
	setX(in_x); // Accepts only valid values 
	setY(in_y); // Accepts only valid values 
}

// Copy Constructor
Point::Point(const Point& in_point)
{
	cout << "The Copy constructor is called..." << endl;
	setX(in_point.m_x); // Accepts only valid values 
	setY(in_point.m_y); // Accepts only valid values 
}
// We could delegate this operation to the constructor.
// To monitor how many times constructors run, we do not call the constructor again here.

// Assignment operator (we will cover it later)
void Point::operator=(const Point& in_point)
{
	setX(in_point.m_x); // Accepts only valid values 
	setY(in_point.m_y); // Accepts only valid values 
}

// We could delegate this operation to the constructor.
// To monitor how many times constructors run, we do not call the constructor again here.
// A const method calculates and returns the distance of a point from (0,0)
double Point::distanceFromZero() const {
	return sqrt(m_x * m_x + m_y * m_y);   // distance from (0,0)
}

// A const method to print the coordinates on the screen
// It also increments and prints the mutable printCount
void Point::print() const
{
	std::cout << "X= " << m_x << ", Y= " << m_y << std::endl;
	std::cout << "Print count= " << ++m_printCount << std::endl;  // increment and print the mutable printCount
}

// Setters
void Point::setX(int new_x) {
	if (new_x >= MIN_x) m_x = new_x;  // Accepts only valid values 
}
void Point::setY(int new_y) {
	if (new_y >= MIN_y) m_y = new_y;  // Accepts only valid values 
}

// A function to move the points 
// It checks the input values.
// If the values fall within the limits they are accepted, the point moves, and the function returns true.
// If the values are not within the limits, the point does not move, and the function returns false.
bool Point::move(int new_x, int new_y)
{
	if (new_x >= MIN_x &&  // if new_x is within the limits
		new_y >= MIN_y)    // if new_x is within the limits
	{
		m_x = new_x;						// assigns new value to x coordinate
		m_y = new_y;						// assigns new value to y coordinate 
		return true;
	}
	return false;						// new values are not accepted
}

// Destructor
// A user-defined destructor is NOT necessary for the Point class
// We write it only to monitor how many objects are created and destructed
Point::~Point() {
	cout << "Destructor is called..." << endl;
}


// A class that contains Point-related graphic tools 
class GraphicTools {
public:
	Point maxDistanceFromZero(Point, Point); // Not appropriate! Call by value, return by value
};

// Returns the point object that has the larger distance from zero
// Call by value, return by value. Inefficient, not appropriate!
Point GraphicTools::maxDistanceFromZero(Point in_point1, Point in_point2) {
	cout << "Max Distance Function is called..." << endl;
	if (in_point1.distanceFromZero() > in_point2.distanceFromZero())
		return in_point1;
	else
		return in_point2;
}
// -------- Main Program -------------
int main()
{
	Point point1{0, 20};       // 1. point object
	Point point2{10,20};	   // 2. point object
		
	GraphicTools tool;

	// 3. point3 object
	Point point3;
	point3 = tool.maxDistanceFromZero(point1, point2);
	cout << "Distance from Zero = " << point3.distanceFromZero() << endl;
	point3.print();
	return 0;
}