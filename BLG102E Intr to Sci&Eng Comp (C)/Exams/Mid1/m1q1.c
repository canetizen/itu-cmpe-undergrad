//m1q1 spring 2021-22

#include <stdio.h>

int main()
{
	int num1, num2, num3;
	printf("Give three integers separated with space:");
	scanf("%d %d %d %d", &num1, num2, &num3);
	
	if (num1 > num2)
	{
		if (num2 > num3)
		{
			printf("strictly increasing\n");
		}
	}
	else if (num1 < num2)
	{
		if (num2 < num3)
		{
			printf("strictly decreasing\n");
		}
	}
	else
	{
		printf("none of the two\n");
	}
	
} 