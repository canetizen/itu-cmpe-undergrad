#include <stdio.h>

double alternating_function(int arr[], int choice, int size) {
	double total;
	if (choice == 1) {
        total = 0;
		for (int i = 0; i < size; i += 2) {
			total += arr[i];
		}
		for (int i = 1; i < size; i += 2) {
			total += -1 * arr[i];
		}
	}
	else if (choice == 2) {
		total = 1;
		for (int i = 0; i < size; i += 2) {
			total *= arr[i];
		}
		for (int i = 1; i < size; i += 2) {
			total /= arr[i];
		}
	}
	return total;
}

int main() {
    int arr[10], size = 10;
    printf("Enter up to 10 non-negative integers (-1 to terminate):");
    for (int i = 0; i < size; i++) {
		scanf("%d", &arr[i]);
		if (arr[i] == -1) {
			size = i;
		}
		else {
			size = 10;
		}
	}
	int choice;
    printf("\nEnter your choice (1 for alternating sum or 2 for alternating division):");
    scanf("%d", &choice);
    double result = alternating_function(arr, choice, size);
    printf("The result is %.2f\n", result);
    return 0;
}
