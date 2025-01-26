// e02_5.cpp
//Return by constant reference

#include <iostream>

// max  function returns a constant refference to the largest element of an array
// max function cannot be used on the left side of an assignment statement
const int&  max(const int a[], unsigned int length)			
{
	unsigned int i{};    							// i is indices of the largest element
   for (unsigned int j=0 ; j<length ; j++)	
	   if (a[j] > a[i])  i = j;
   return a[i];										// returns refference to a[i]
}

int main()
{
   int array[] = {12, -54 , 1 , 123, 63};							// An aray with 5 elements
   int largest;
   largest=max(array,5);										// Get the largest element
   //max(array, 5)=0;										        // Compiler error!
   for(unsigned int i=0; i<5; i++) std::cout << array[i] << " ";    // Print the array on the screen
   std::cout << "\nLargest = "<< largest;							// Print the largest element
   return 0;
}

