// Author: Mustafa Can Caliskan, 150200097

#ifndef UTILS_H
#define UTILS_H

#include "task.h"

#define MAX_TASKS 100

int read_csv(const char *filename, Task tasks[]);
void show_tasks(Task tasks[], int task_count);
void print_task_execution(Task task, int current_time, int execution_time);

void deadline_missed(Task task, int current_time);
int is_task_released(Task *task, int current_time);
int calculate_laxity(TaskInstance *instance, int current_time);

#endif
