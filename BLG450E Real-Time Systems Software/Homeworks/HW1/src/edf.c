// Author: Mustafa Can Caliskan, 150200097

#include <stdio.h>
#include "edf.h"
#include "utils.h"

void edf(Task tasks[], int task_count, int simulation_time) {
    printf("\nEDF is starting...\n");

    // Initialize task instances
    TaskInstance task_instances[task_count];
    for (int i = 0; i < task_count; i++) {
        task_instances[i].task = &tasks[i];
        task_instances[i].remaining_time = 0;
        task_instances[i].absolute_deadline = tasks[i].release_time + tasks[i].deadline;
        task_instances[i].next_release_time = tasks[i].release_time;
        task_instances[i].completed = 0; // Flag to track whether the task has completed execution
    }

    for (int current_time = 0; current_time < simulation_time; current_time++) {
        // Release tasks at the appropriate time
        for (int i = 0; i < task_count; i++) {
            if (current_time == task_instances[i].next_release_time && task_instances[i].completed == 0) {
                if (task_instances[i].remaining_time == 0) {
                    task_instances[i].remaining_time = tasks[i].execution_time; // Reset execution time
                    task_instances[i].absolute_deadline = current_time + tasks[i].deadline; // Set new deadline
                    task_instances[i].next_release_time += tasks[i].period; // Update the next release time
                }
            }
        }

        // Check for deadline miss for all incomplete tasks
        for (int i = 0; i < task_count; i++) {
            if (task_instances[i].remaining_time > 0 && (current_time + 1) > task_instances[i].absolute_deadline) {
                deadline_missed(*task_instances[i].task, current_time + 1);
                return; // Stop the EDF algorithm if any incomplete task misses its deadline
            }
        }

        // Select the highest priority task (earliest deadline) that hasn't finished
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
