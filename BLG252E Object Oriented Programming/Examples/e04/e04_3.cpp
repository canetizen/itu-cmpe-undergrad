// e04_3.cpp
//	Destructors 

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
	String(const char*);   // Constructor
	void print();           // A member function
	~String();              // Destructor
private:
	 size_t m_size;		    // length of a string
	 char *m_contents;
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
	 strcpy_s(m_contents, m_size+1, inData);		// input_data is copied to the contents
	 print();
 }

void String::print()
{
	 cout<< m_contents << " " << m_size << endl;
}

// Destructor
// Memory pointed to by the pointer contents is given back to the heap
String::~String()
{
	 cout << "Destructor has been invoked" << endl;
	 print();
	 delete[] m_contents;
}

//------- Main Function -------
int main()
{
	cout << "--------- Start of Blok 1 ------" << endl;
	String string1{"string 1"};
	String string2{"another string"};
	 {
		 cout << "--------- Start of Blok 2 ------" << endl;
		 String string3{"The inner string"};
		 cout << "--------- End of Blok 2 ------" << endl;
	 }
	 //string3.print();   ERROR! string3 is out of the scope
	 cout << "--------- End of Blok 1 ------" << endl;
	 return 0;
 }