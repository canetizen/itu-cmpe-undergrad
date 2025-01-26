#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct student
{
    int id;
    char name[50];
    double gpa;
};

void search(char *file_name, int id)
{
	struct student std;
	FILE *fp;

	if(!(fp = fopen(file_name, "rb"))) {
		printf("Could not open file!\n");
		exit(1);
	}
	
	int i = 1;
	while(1) {
		fread(&std, sizeof(struct student), 1, fp);
		if (feof(fp)) {
			break;
		}
		if(id == std.id) {
			printf("   %d. Name: %s, GPA: %.2lf\n", i, std.name, std.gpa);
			i++;
		}
	}
	printf("Found %d occurrences!\n", i - 1);
}

void insert(char *file_name, struct student std)
{
    FILE *fp;
	if (!(fp = fopen(file_name, "rb"))) {
		fclose(fp);
		fp = fopen(file_name, "wb");
	}
	else {
		fclose(fp);
		fp = fopen(file_name, "ab");
	}
	fwrite(&std, sizeof(struct student), 1, fp);
	fclose(fp);
}

int main()
{
    struct student std;
    int choice, id;
    char file_name[100];

    printf("Enter data file name: ");
    scanf("%s", file_name);

    while(true)
    {
        printf("Enter 1 to search for data, 2 to insert student record (0 to exit): ");

        scanf("%d", &choice);

        if(choice == 1)
        {
            printf("   Enter student id to search: ");
            scanf("%d", &id);
            search(file_name, id);
        }
        else if(choice == 2)
        {
            printf("   Student id: ");
            scanf("%d", &(std.id));
            
            printf("   Student name: ");
            scanf("%s", std.name    );

            printf("   Student gpa: ");
            scanf("%lf", &(std.gpa));

            insert(file_name, std);   
        }
        else if(choice == 0)
        {
            break;
        }
        else
        {
            printf("Invalid choice!\n");
        }
    }

    return 0;
}