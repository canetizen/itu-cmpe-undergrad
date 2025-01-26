// Author: Mustafa Can Caliskan, 150200097

#ifndef TASK_H
#define TASK_H

#include <limits.h>

typedef struct {
    char name[20];
    int release_time;
    int period;
    int execution_time;
    int deadline;
} Task;

typedef struct {
    Task *task;
    int remaining_time;
    int absolute_deadline;
    int next_release_time;
    int completed;
} TaskInstance;

#endif
