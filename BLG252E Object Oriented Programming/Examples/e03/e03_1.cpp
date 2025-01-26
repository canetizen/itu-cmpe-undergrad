// e03_1.cpp
// Declaring and defining classes
// Point class
// As we have not yet covered all the subjects, this program has some shortcomings.
// We will improve it later

#include <iostream>
using std::cout;
using std::endl;

class Point{					// Delaration Point Class
public:
	void move(int, int);		// A function to move points
	void print();				// to print cordinates on the screen
	bool isOnZero();		   // is point on the zero point(0,0)?
private:
	int m_x{}, m_y{};		   // Properties: x and y coordinates. Initial values: 0,0
};

// ***** Bodies of Member Functions *****

// A function to move the points 
void Point::move(int new_x, int new_y)
{
	m_x = new_x;				// assigns new value to x coordinat
	m_y = new_y;				// assigns new value to y coordinat 
}

// To print the coordinates on the screen 
void Point::print()
{
	cout << "X= " << m_x << ", Y= " << m_y << endl;
}
				
// is the point on the zero point(0,0)
bool Point::isOnZero()
{
	return (m_x == 0) && (m_y == 0);	  
}

// Main function to test the Point class
int main()
{
	Point point1, point2;					// 2 object are defined: point1 and point2
	cout << "Cooridnates of the point1: ";
	point1.print();							// point1's coordinates to the screen
	point1.move(500,50);			// point1 moves to (100,50)
	cout << "Cooridnates of the point1: ";
	point1.print();							// point1's coordinates to the screen
	cout << "Cooridnates of the point2: ";
	point2.print();							// point2's coordinates to the screen
	if(point1.isOnZero())					// is point1 on (0,0)?
		cout << "point1 is on zero point(0,0)" << endl;
	else
		cout << "point1 is NOT on zero point(0,0)" << endl;
	if(point2.isOnZero())					// is point2 on (0,0)?
		cout << "point2 is on zero point(0,0)" << endl;
	else
		cout << "point2 is NOT on zero point(0,0)" << endl;
	return 0;
}
