// e05_6.cpp
// COPY CONSTRUCTOR AND ASSIGNMENT OPERATOR
// Assignment operator in this example can be chained as a=b=c

#include <iostream>         // for IO operations 
#include <cstring>			// for old string functions inherited from C
// The new header for strings is <string>
using std::cout;
using std::endl;

/*
The standard library of C++ contains a std::string class.
Programmers do not need to write their own String classes.
We write this class using old string functions inherited from C, only to show some concepts.
*/

// A class to define strings
// contents of strings terminate with a null character '\0'
class String {
public:
	String(const char*);        // Constructor
	String(const String&);     // Copy Constructor
	const String& operator=(const String&);  // assignment operator
	void print() const;        // A member function to print the string
	void setContents(const char*);  // Setter
	~String();                 // Destructor
private:
	size_t size;		    // length of a string
	char* contents;        // pointer to the character array
};

// Constructor
// Allocates memory 
// copies the input character array that terminates with null character
// to the contents of the string
String::String(const char* inData)
{
	cout << "Constructor has been invoked" << endl;
	size = strlen(inData);
	contents = new char[size + 1];   // +1 for null character
	strcpy_s(contents, size + 1, inData);		// input_data is copied to the contents
}

// Copy Constructor
// Allocates memory 
// copies the contents of the existing object to the newly constructed object
String::String(const String& originalString)
{
	cout << "Copy Constructor has been invoked" << endl;
	size = originalString.size;
	contents = new char[size + 1];   // Memory allocation. +1 for null character
	strcpy_s(contents, size + 1, originalString.contents);	 // copy between two contents
}

// Assignment operator
const String& String::operator=(const String& in_object)
{
	cout << "Assignment operator has been invoked" << endl;
	if (this != &in_object) {					// checking for self-assignment
		if (size != in_object.size) {			// if the sizes of the source and destination are different
			size = in_object.size;				
			delete[] contents;					// The old contents is deleted
			contents = new char[size + 1];		// Memory allocation for the new contents
		}
		// Copy the contents of the sourse to the destination
		strcpy_s(contents, size+1,in_object.contents);
	}
	return *this;  								// returns a reference to the object
}

void String::print() const
{
	cout << contents << " " << size << endl;
}

// Setter
void String::setContents(const char* inContents) {
	delete[] contents;    // Delete previous contents
	size = strlen(inContents);
	contents = new char[size + 1];   // +1 for null character
	strcpy_s(contents, size + 1, inContents);		// inputContents is copied to the contents
}

// Destructor
// Memory pointed to by the pointer contents is given back to the heap
String::~String()
{
	cout << "Destructor has been invoked" << endl;
	delete[] contents;
}


int main()
{
	String firstString{ "First String" };				// Constructor is called
	String secondString{ firstString };				   // Copy constructor is invoked
	String thirdString = secondString;				   // Copy constructor is invoked. This is NOT an assignemnt!
	firstString.print();								// All of them have the same text in different memory locations
	secondString.print();
	thirdString.print();
	
	// Assignements
	String fourthString{ "fourth String" };				// A new String object
	secondString = firstString = fourthString;			// Assignment
	
	cout << "The firts String: ";
	firstString.print();
	cout << "The second String: ";
	secondString.print();
	cout << "The third String: ";
	thirdString.print();
	cout << "The fourth String: ";
	fourthString.print();

	firstString = firstString;						// Self assignment does not cause a problem

	return 0;
}