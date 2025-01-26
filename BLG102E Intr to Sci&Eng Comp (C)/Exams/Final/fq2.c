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
    // Provide your implementation here


}

void insert(char *file_name, struct student std)
{
    // Provide your implementation here

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