/* BLG 102E Midterm 2 Question 2 Template
Do not change the function name.
Do not change the order of the function calls in main.
*/
#include <stdio.h>

double alternating_function(/*define the function parameters*/)
{
    //implement the function
}


int main()
{
    //Define variables here.
	
    printf("Enter up to 10 non-negative integers (-1 to terminate):");
    //Complete the code
	
	
	//Do not change the code below or add new lines below this comment. Fill the function parameters only. 
	int choice;
    printf("\nEnter your choice (1 for alternating sum or 2 for alternating division):");
    scanf("%d", &choice);
    double result = alternating_function(/*fill the parameters*/);
    printf("The result is %.2f\n", result);
    return 0;
}
