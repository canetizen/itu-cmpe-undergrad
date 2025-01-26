// e05_7.cpp
// Overloading the Subscript operator [] for the String class 

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
	char& operator[](int);    // subscript operator
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

// Subscript operator
// The operator will be used to access the ith character of the string. 
// If index is less the zero then the first character and 
// if index is greater than the size of the string the last character will be accessed.
char & String::operator[](int index)  
{
   if(index < 0)
      return contents[0];					// return first character
	if(index >= size)
		return contents[size-1];				// return last character
	return contents[index];						// return i th character
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


// ----- Main function -----
int main()
{
	 String string1("String");
	 string1.print();
	 string1[1] = 'p';							// modifies an element of the contents
	 string1.print();
	 cout << " 5 th character of the string is: " << string1[5] << endl;  // prints an element of the contents
	 cout << "If index is negative it returns contents[0]:  " << string1[-8] << endl;
	 return 0;
}
