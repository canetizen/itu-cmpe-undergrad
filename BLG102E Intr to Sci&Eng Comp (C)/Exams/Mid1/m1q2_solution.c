#include <stdio.h>
#include <stdbool.h>

void reverse(int num1, int num2, int num3) {
	printf("%d %d %d\n", num3, num2, num1);
}

void max(int num1, int num2, int num3) {
	int max_value;
	
	if (num1 >= num2 && num1 >= num3) {
		max_value = num1;
	}
	
	else if (num2 >= num1 && num2 >= num3) {
		max_value = num2;
	}
	
	else if (num3 >= num1 && num3 >= num2) {
		max_value = num3;
	}
	printf("the maximum number is %d\n", max_value);
}

void inc_dec_check(int num1, int num2, int num3) {
    if ((num1 >= num2 && num2 > num3) || (num1 > num2 && num2 >= num3)) {
        printf("strictly decreasing\n");
    }
    
    else if ((num1 <= num2 && num2 < num3) || (num1 < num2 && num2 <= num3)) {
        printf("strictly increasing\n");
    }
    
    else {
        printf("none of the two\n");
    }

}

void strictly_inc_dec_check(int num1, int num2, int num3) {
    if (num1 > num2 && num2 > num3) {
        printf("strictly decreasing\n");
    }
    
    else if (num1 < num2 && num2 < num3) {
        printf("strictly increasing\n");
    }
    
    else {
        printf("none of the two\n");
    }
}

int main() {
	int number1, number2, number3, choice;
	bool continue_check = true;
	
	printf("Give three integers separated with space:");
	scanf("%d %d %d", &number1, &number2, &number3);
	
	while(continue_check) {
		printf("Which task would you like to perform?\n");
		printf("1 to check if the list is strictly increasing or decreasing\n");
		printf("2 to check if the list is increasing or decreasing\n");
		printf("3 to compute the maximum number in the list\n");
		printf("4 to reverse the list\n");
		printf("5 to enter a new list of integers\n");
		printf("-1 to terminate the program\n");
	
		scanf("%d", &choice);
	
		switch(choice) {
			case 1:
				strictly_inc_dec_check(number1, number2, number3);
				break;
			case 2:
				inc_dec_check(number1, number2, number3);
				break;
			case 3:
				max(number1, number2, number3);
				break;
			case 4:
				reverse(number1, number2, number3);
				break;
			case 5:
				printf("Give three integers separated with space:");
				scanf("%d %d %d", &number1, &number2, &number3);
				break;
			case -1:
				continue_check = false;
				break;
			default:
				printf("not a defined option, try again\n");
				break;
		}
	}
	return 0;	
} 
