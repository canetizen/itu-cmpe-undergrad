// e04_7.cpp
// Compiler-generated copy constructor for the user-defined String class
// Caution: There is a run-time memory problem in this program!

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
class String {
public:
	String(const char*);			// Constructor
	void print() const;				// A member function to print the string
	void setContents(const char*);  // Setter
	~String();						// Destructor
private:
	size_t m_size;					// length of a string
	char* m_contents;				// pointer to the character array
};


// Constructor
// Allocates memory 
// copies the input character array that terminates with null character
// to the contents of the string
String::String(const char *inData)
{
	 cout<< "Constructor has been invoked" << endl;
	 m_size = strlen(inData);
	 m_contents = new char[m_size +1];   // +1 for null character
	 strcpy_s(m_contents,  m_size+1, inData);		// input_data is copied to the contents
 }

void String::print() const
{
	 cout<< m_contents << " " << m_size << endl;
}

// Setter
void String::setContents(const char* inContents) {
	//  Copies only size bytes from inContents to contents
	// This method is not appropriate. Check the example e04_8.cpp for a better version
	strcpy_s(m_contents, m_size, inContents);		// input_data is copied to the contents
}

// Destructor
// Memory pointed to by the pointer contents is released
String::~String()
{
	 cout << "Destructor has been invoked" << endl;
	 delete[] m_contents;
}

//------- Main Function -------
int main()
{
  String originalString{"string 1"};
  String copyString{originalString};				// Compiler-generated copy constructor runs
  originalString.print();
  copyString.print();
  
  originalString.setContents("Another");  // We change the contents of the original string
  originalString.print();   
  copyString.print();                              // The copy also changes
  return 0;											// Memory fault! Destructor tries to release the same variable twice.
 }