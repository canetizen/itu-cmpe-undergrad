#include <stdio.h>
#include <stdlib.h>

typedef struct {
	char name[7];
	char id[4];
	int exam[3];
	int homework[3];
	char grade;
} Student;

int read_from_source(Student* temp_student_ptr, FILE *fp) {
	int value = fscanf(fp, "%s %s %d %d %d %d %d %d %c", temp_student_ptr->name, temp_student_ptr->id,
											 &temp_student_ptr->exam[0], &temp_student_ptr->exam[1], &temp_student_ptr->exam[2],
											 &temp_student_ptr->homework[0], &temp_student_ptr->homework[1], &temp_student_ptr->homework[2],
											 &temp_student_ptr->grade);
	if (value != 9) {
		return 0;
	}
	return 1;
}

void write_into_binary(Student* temp_student_ptr, FILE *fp) {
	fwrite(temp_student_ptr, sizeof(Student), 1, fp);
}

int read_from_binary(Student* temp_student_ptr, FILE *fp) {
	int value = fread(temp_student_ptr, sizeof(Student), 1, fp);
	
	if (value != 1) {
		return 0;
	}
	return 1;
}

void write_into_text(Student* temp_student_ptr, FILE *fp) {
	fprintf(fp, "%-6s %4s %2d %2d %2d %3d %3d %3d %c\n", temp_student_ptr->name, temp_student_ptr->id,
											 temp_student_ptr->exam[0], temp_student_ptr->exam[1], temp_student_ptr->exam[2],
											 temp_student_ptr->homework[0], temp_student_ptr->homework[1], temp_student_ptr->homework[2],
											 temp_student_ptr->grade);
}

int main(int argc, char** argv) {
	if (argc != 4){
        printf("Enter:\n");
        printf("%s ", argv[0]);
        printf("\"Source Text File Name\" ");
        printf("\"Destination Text File Name\" ");
        printf("\"Destination Binary File Name\" ");
        return 1;
    }
    
	Student temp_student;
	FILE *fp_text;
	FILE *fp_binary;
	if(!(fp_text = fopen(argv[1], "r"))) {
		printf("\nCannot open %s\n", argv[1]);
        return 1;
	}
	if(!(fp_binary = fopen (argv[2], "wb"))) {
		printf("\nCannot open %s\n", argv[2]);
        return 1;	
	}
	
// TASK 1
    printf("\nReading from text file and writing into binary file started...");
	
	while (read_from_source(&temp_student, fp_text)) {
		write_into_binary(&temp_student, fp_binary);
	}
	
	fclose(fp_text);
	fclose(fp_binary);
	
    printf("\nRead from text file and written into binary file successfully!\n");

// TASK 2
    printf("\nReading from binary file and writing into text file started...");
	
	if(!(fp_binary = fopen(argv[2], "rb"))) {
		printf("\nCannot open %s\n", argv[2]);
		return 1;
	}
	
	if(!(fp_text = fopen (argv[3], "w"))) {
		printf("\nCannot open %s\n", argv[3]);
		return 1;
	}
	
	while (read_from_binary(&temp_student, fp_binary)) {
		write_into_text(&temp_student, fp_text);
	}
	
	fclose(fp_text);
	fclose(fp_binary);
	
    printf("\nRead from binary and written into text file successfully!\n");
	
	return EXIT_SUCCESS;
}
