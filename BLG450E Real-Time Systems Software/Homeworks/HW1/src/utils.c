// Author: Mustafa Can Caliskan, 150200097

#include <stdio.h>
#include "utils.h"

int read_csv(const char *filename, Task tasks[]) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Read error!\n");
        return -1;
    }

    char line[256];
    int task_count = 0;

    if (fgets(line, sizeof(line), file) == NULL) {
        fclose(file);
        return -1;
    }

    while (fgets(line, sizeof(line), file) && task_count < MAX_TASKS) {
        Task t;
        sscanf(line, "%[^,],%d,%d,%d,%d", t.name, &t.release_time, &t.period, &t.execution_time, &t.deadline);
        tasks[task_count++] = t;
    }

    fclose(file);
    return task_count;
}

void show_tasks(Task tasks[], int task_count) {
    printf("\n%d tasks loaded:\n", task_count);
    for (int i = 0; i < task_count; i++) {
        printf("Task: %s, Release Time: %d, Period: %d, Execution Time: %d, Deadline: %d\n",
               tasks[i].name, tasks[i].release_time, tasks[i].period, tasks[i].execution_time, tasks[i].deadline);
    }
    printf("\n--------\n");
}

void print_task_execution(Task task, int current_time, int execution_time) {
    printf("Time %d: %s is executing for %d unit(s).\n", current_time, task.name, execution_time);
}

// Helper function to notify deadline miss and exit
void deadline_missed(Task task, int current_time) {
    printf("Time %d: Deadline missed for task %s.\n", current_time, task.name);
}

// Function to check if a task is released at the current time
int is_task_released(Task *task, int current_time) {
    return (current_time >= task->release_time) && 
           ((current_time - task->release_time) % task->period == 0);
}

// Function to calculate laxity for LLF
int calculate_laxity(TaskInstance *instance, int current_time) {
    return (instance->absolute_deadline - current_time) - instance->remaining_time;
}