/* BLG 102E Midterm 2 Question 1 Template
Do not change the function names.
Do not change the order of the function calls in main.
*/

#include <stdio.h>

void get_characters(char array[])
{
    for (int i = 0; i < 20; i++) {
		scanf("%c", &array[i]);
	}
}

void reverse_characters(char array[], char array2[])
{	
    for (int i = 0; i < 20; i++) {
		array2[i] = array[19-i];
	}
}

void print_characters(char array[])
{
    for (int i = 0; i < 20; i++) {
		printf("%c", array[i]);
	}
	printf("\n");
}


int main()
{
char arr[20], arr2[20];
	
	//Do not change the code below or add new lines below this comment. Fill the function parameters only. 
	printf("Insert 20 consecutive characters:");
	get_characters(arr);
	printf("\nThe user entered the following characters:");
	print_characters(arr);
    reverse_characters(arr, arr2);
	printf("The characters in reverse order are: ");
    print_characters(arr2);
	
    return 0;
}
