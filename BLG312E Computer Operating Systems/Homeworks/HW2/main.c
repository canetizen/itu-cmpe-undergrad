/**
 * Mustafa Can Caliskan
 * 150200097
 * COS Project 2
*/

#include "allocator.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

#define NUMBER_OF_PROCESSES 4

typedef struct {
    int name;
    size_t size;
    int strategy;
    pid_t pid;
    void* allocatedMemoryStartingAddress;
} Process;

int main(int argc, char** argv) {

    // Initialize MyMalloc
    if (InitMyMalloc(atoi(argv[1])) != 0) {
        fprintf(stderr, "Initialization failed");
        return EXIT_FAILURE;
    }
    Process processes[NUMBER_OF_PROCESSES] = {{0, 0, 0, 0, NULL}};
    int pipefd[NUMBER_OF_PROCESSES][2]; // 2D array to store pipe file descriptors

    // Create pipes
    for (int i = 0; i < NUMBER_OF_PROCESSES; i++) {
        if (pipe(pipefd[i]) == -1) {
            fprintf(stderr, "Pipe creation failed.\n");
            return EXIT_FAILURE;
        }
    }

    printf("\nDumping Free List before allocations:\n");
    DumpFreeList();

    printf("\n");

    for (int i = 0; i < NUMBER_OF_PROCESSES; ++i) {
        processes[i].name = i + 1;
        printf("Please enter the strategy type (%d for BF, %d for WF, %d for FF, or %d for NF) for P%d: ", BF, WF, FF, NF, processes[i].name);
        scanf("%d", &processes[i].strategy);
        processes[i].size = 512 + i * 256;
    }

    printf("\nAllocating of each process is started...\n\n");

    // Create child processes
    for (int i = 0; i < NUMBER_OF_PROCESSES; i++) {
        processes[i].pid = fork();
        if (processes[i].pid < 0) {
            fprintf(stderr, "Fork failed.\n");
            return EXIT_FAILURE;
        } else if (processes[i].pid == 0) {
            // Child process
            close(pipefd[i][0]); // Close unused read end of pipe
            processes[i].allocatedMemoryStartingAddress = MyMalloc(processes[i].size, processes[i].strategy);
            if (processes[i].allocatedMemoryStartingAddress != NULL) {
                // Write allocated memory address to the pipe
                if (write(pipefd[i][1], &processes[i].allocatedMemoryStartingAddress, sizeof(void*)) == -1) {
                    fprintf(stderr, "Write to pipe failed.\n");
                    return EXIT_FAILURE;
                }
                printf("Memory allocation for P%d (PID: %d) succeeded at address using strategy %d: %p\n", processes[i].name, getpid(), processes[i].strategy, processes[i].allocatedMemoryStartingAddress);
            } else {
                printf("Memory allocation for P%d (PID: %d) failed using strategy %d.\n", processes[i].name, getpid(), processes[i].strategy);
            }
            close(pipefd[i][1]); // Close write end of pipe
            exit(EXIT_SUCCESS);
        }
    }

    // Wait for all child processes to finish
    for (int i = 0; i < NUMBER_OF_PROCESSES; i++) {
        waitpid(processes[i].pid, NULL, 0);
    }

    // Print the status of free memory blocks after allocations
    printf("\nAllocation for each process is completed. Dumping Free List after allocations:\n");
    DumpFreeList();

    for (int i = 0; i < NUMBER_OF_PROCESSES; i++) {
        close(pipefd[i][1]); // Close write end of pipe
        void* memPtr;
        if (read(pipefd[i][0], &memPtr, sizeof(void*)) > 0) {
            processes[i].allocatedMemoryStartingAddress = memPtr;
        }
        close(pipefd[i][0]); // Close read end of pipe
    }

    printf("\nDeallocating of each process is started...\n\n");

    // Deallocate memory for all processes
    for (int i = 0; i < NUMBER_OF_PROCESSES; i++) {
        if (!MyFree(processes[i].allocatedMemoryStartingAddress)) {
            printf("Memory for P%d (PID: %d) deallocated.\n", processes[i].name, processes[i].pid);
        } else {
            fprintf(stderr, "NULL pointer deallocation for PID: %d.\n", processes[i].pid);
        }
    }
    printf("\nAll Deallocations are completed. Dumping Free List after deallocations:\n");
    DumpFreeList();

    return EXIT_SUCCESS;
}
