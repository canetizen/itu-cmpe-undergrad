// Author: Mustafa Can Caliskan, 150200097

#include "rm.h"
#include "dm.h"
#include "llf.h"
#include "edf.h"
#include "utils.h"

typedef void (*SchedulingAlgorithm)(Task *tasks, int task_count, int simulation_time);

int main() {
    Task tasks[MAX_TASKS];
    int task_count;

    task_count = read_csv("tasks.csv", tasks);
    if (task_count == -1) {
        return 1;
    }

    show_tasks(tasks, task_count);

    int simulation_time = 100;

    SchedulingAlgorithm algorithms[] = {rm, dm, edf, llf};
    int num_algorithms = sizeof(algorithms) / sizeof(algorithms[0]);

    for(int i = 0; i < num_algorithms; i++) {
        algorithms[i](tasks, task_count, simulation_time);
    }

    return 0;
}
