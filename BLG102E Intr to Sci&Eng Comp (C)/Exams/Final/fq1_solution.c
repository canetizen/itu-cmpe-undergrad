#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char **argv) {
	int n_female = 0, n_male = 0, len_male = 0, len_female = 0;
	if (argc < 2 || argc > 6) {
		printf("Enter 1 to 5 arguments!\n");
		return 1;
	}
	
	for (int i = 1; i < argc; i++) {
		if (strncmp(argv[i], "M_", 2) != 0 && strncmp(argv[i], "F_", 2) != 0) {
			printf("Names should start with either M_ or F_!");
			return 1;
		}
	}	

	for (int i = 1; i < argc; i++) {
		if (strlen(argv[i]) == 2) {
			printf("Names should contain at least 1 character after gender prefix!");
			return 1;
		}			
	}
	
	for (int i = 1; i < argc; i++) {
		if (argv[i][0] == 'M') {
			len_male += strlen(argv[i]) - 2;
			n_male++;
		}
		
		else if (argv[i][0] == 'F') {
			len_female += strlen(argv[i]) - 2;
			n_female++;
		}
	}
	
	double f_avg = (double) len_female / n_female;
	double m_avg = (double) len_male / n_male;
	
	if (len_female == 0) {
		f_avg = 0;
	}
	
	if (len_male == 0) {
		m_avg = 0;
	}


	printf("Female count: %d, avg. female name length: %2.1f\n", n_female, f_avg);
	printf("Male count: %d, avg. male name length: %2.1f\n", n_male, m_avg);

	return 0;
}