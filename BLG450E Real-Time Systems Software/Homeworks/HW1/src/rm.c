// Author: Mustafa Can Caliskan, 150200097

#include <stdio.h>
#include "rm.h"
#include "utils.h"

void rm(Task tasks[], int task_count, int simulation_time) {
    printf("\nRM is starting...\n");

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

        // Check for deadline misses for tasks that are not completed
        for (int i = 0; i < task_count; i++) {
            if (task_instances[i].remaining_time > 0 && task_instances[i].absolute_deadline <= current_time) {
                deadline_missed(*task_instances[i].task, current_time);
                task_instances[i].remaining_time = 0; // Prevent task from being executed again
                return;
            }
        }

        // Select the highest priority task (shortest period)
        TaskInstance *current_task = NULL;
        int highest_priority = INT_MAX;
        for (int i = 0; i < task_count; i++) {
            // Only consider tasks that have remaining time to execute and have not completed
            if (task_instances[i].remaining_time > 0 && task_instances[i].completed == 0 && tasks[i].period < highest_priority) {
                highest_priority = tasks[i].period;
                current_task = &task_instances[i];
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

            // Check for deadline miss
            if ((current_time + 1) > current_task->absolute_deadline && current_task->remaining_time > 0) {
                deadline_missed(*current_task->task, current_time + 1);
                return;
            }
        } else {
            printf("Time %d: CPU is idle.\n", current_time);
        }
    }
}


