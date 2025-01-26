// e04_8.cpp
// Programmer-defined copy constructor for the user-defined String class

#include <iostream>
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
class String{
public:
	String(const char*);        // Constructor
	String(const String&);     // Copy Constructor
	void print() const;        // A member function to print the string
	void setContents(const char*);  // Setter
	~String();                 // Destructor
private:
	 size_t size;		    // length of a string
	 char *contents;        // pointer to the character array
};

// Constructor
// Allocates memory 
// copies the input character array that terminates with null character
// to the contents of the string
String::String(const char *inData)
{
	 cout<< "Constructor has been invoked" << endl;
	 size = strlen(inData);
	 contents = new char[size +1];   // +1 for null character
	 strcpy_s(contents,size+1, inData);		// input_data is copied to the contents
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
void String::print() const
{
	 cout<< contents << " " << size << endl;
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

//------- Main Function -------
int main()
{
  String originalString{"string 1"};
  String copyString{originalString};     // Programmer-definedd copy constructor runs
  originalString.print();
  copyString.print();

  originalString.setContents("Another Text");
  originalString.print();
  copyString.print();
  return 0;
 }