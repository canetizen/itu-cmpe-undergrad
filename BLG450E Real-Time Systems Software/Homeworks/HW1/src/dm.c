// Author: Mustafa Can Caliskan, 150200097

#include <stdio.h>
#include "dm.h"
#include "utils.h"

void dm(Task tasks[], int task_count, int simulation_time) {
    printf("\nDM is starting...\n");

    // Initialize task instances
    TaskInstance task_instances[task_count];
    for (int i = 0; i < task_count; i++) {
        task_instances[i].task = &tasks[i];
        task_instances[i].remaining_time = 0;
        task_instances[i].absolute_deadline = tasks[i].release_time + tasks[i].deadline;
        task_instances[i].next_release_time = tasks[i].release_time;
        task_instances[i].completed = 0; // Flag to track task completion
    }

    for (int current_time = 0; current_time < simulation_time; current_time++) {
        // Release tasks at the appropriate time
        for (int i = 0; i < task_count; i++) {
            if (current_time == task_instances[i].next_release_time && task_instances[i].completed == 0) {
                if (task_instances[i].remaining_time > 0) {
                    // Previous instance missed its deadline
                    deadline_missed(*task_instances[i].task, current_time);
                    return;
                }
                task_instances[i].remaining_time = tasks[i].execution_time; // Reset execution time
                task_instances[i].absolute_deadline = current_time + tasks[i].deadline; // Set new deadline
                task_instances[i].next_release_time += tasks[i].period; // Update the next release time
            }
        }

        // Select the highest priority task (earliest deadline)
        TaskInstance *current_task = NULL;
        int earliest_deadline = INT_MAX;
        for (int i = 0; i < task_count; i++) {
            // Only consider tasks that have remaining time to execute and have not completed
            if (task_instances[i].remaining_time > 0 && task_instances[i].completed == 0) {
                if (task_instances[i].absolute_deadline < earliest_deadline) {
                    earliest_deadline = task_instances[i].absolute_deadline;
                    current_task = &task_instances[i];
                }
            }
        }

        // Check for deadline miss BEFORE execution (if the task is already late)
        if (current_task != NULL && (current_time + 1) > current_task->absolute_deadline && current_task->remaining_time > 0) {
            deadline_missed(*current_task->task, current_time + 1);
            return;
        }

        // Execute the selected task if there is one
        if (current_task != NULL) {
            print_task_execution(*current_task->task, current_time, 1);
            current_task->remaining_time -= 1;

            // If task execution is complete, mark it as completed
            if (current_task->remaining_time == 0) {
                current_task->completed = 1;
                printf("Task %s completed at time %d.\n", current_task->task->name, current_time + 1);
            }
        } else {
            printf("Time %d: CPU is idle.\n", current_time);
        }
    }
}
