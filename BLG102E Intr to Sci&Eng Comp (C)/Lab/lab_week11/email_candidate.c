#include <stdio.h>
#include <stdlib.h>
#include <time.h>
// Do not use <string.h> for exercise.
#define MAXLEN 50

int strlength(char *arr) {
	int i = 0, counter = 0;
	while (*(arr + i) != '\0') {
		counter++;
		i++;
	}
	return counter;
}

void suggestion_one(char* arr, char* name,  char* surname, char* birth, char* itu, int lengthitu) {
	*arr = *name;
	int lengthsurname = strlength(surname);
	int i, j, k;
	
	for (i = 0; i < lengthsurname; i++) {
		*(arr + i + 1) = *(surname + i);
	}
	
	for (k = 0; k < 2; k++) {
		*(arr + i + k + 1) = *(birth + k + 2);
	}
	
	for (j = 0; j < lengthitu; j++) {
		*(arr + i + k + j + 1) = *(itu + j);
	}

	*(arr + i + k + j + 1) = '\0';
}

void suggestion_two(char* arr, char* name, char* surname, char* random_string, char* itu, int lengthitu) {
	int i , j, k, l;
	
	for (i = 0; i < 2; i++) {
		*(arr + i) = *(name + i);
	}
	
	for (j = 0; j < 2; j++) {
		*(arr + i + j) = *(surname + j);
	}
	
	for (k = 0; k < 4; k++) {
		*(arr + i + j + k) = *(random_string + k);
	}
	
	for (l = 0; l < lengthitu; l++) {
		*(arr + i + j + k + l) = *(itu + l);
	}
	
	*(arr + i + k + j + l) = '\0';
}

void suggestion_three(char* arr, char* name, char* surname, char* birth, char* itu, int lengthitu) {
	int i, j, k, l;
	int lengthname = strlength(name);
	int lengthsurname = strlength(surname);
	for (i = 0; i < lengthsurname; i++) {
		*(arr + i) = *(surname + i);
	}
	
	for (j = 0; j < lengthname; j++) {
		*(arr + i + j) = *(name + j);
	}
	
	for (k = 0; k < 4; k++) {
		*(arr + i + j + k) = *(birth + k);
	}
	
	for (l = 0; l < lengthitu; l++) {
		*(arr + i + j + k + l) = *(itu + l);
	}
	*(arr + i + k + j + l) = '\0';
}

int main() {
	char name[MAXLEN], surname[MAXLEN], birth[5];
	char itu[] = "@itu.edu.tr";
	char sug1[MAXLEN], sug2[MAXLEN], sug3[MAXLEN];
	int lengthitu = strlength(itu);
	
	srand(time(NULL));
	int random = rand() % 10000;
	char random_string[5];
	sprintf(random_string, "%d", random); // integer to string
	
	printf("Enter Your Name:");
	scanf("%s", name);
	
	printf("Enter Your Surname:");
	scanf("%s", surname);
	
	printf("Enter Your Birthyear:");
	scanf("%s", birth);
	
	suggestion_one(sug1, name, surname, birth, itu, lengthitu);
	suggestion_two(sug2, name, surname, random_string, itu, lengthitu);
	suggestion_three(sug3, name, surname, birth, itu, lengthitu);
	printf("Email Candidate 1: %s\n", sug1);
	printf("Email Candidate 2: %s\n", sug2);
	printf("Email Candidate 3: %s\n", sug3);
	
	return 0;
}