/**
 * Mustafa Can Caliskan
 * 150200097
 * COS Project 2
*/

#include "allocator.h"
#include <unistd.h>
#include <sys/mman.h>

ListNode* listHead = NULL;
ListNode* lastSplit = NULL;

int InitMyMalloc(int HeapSize) {
    if (HeapSize <= 0) {
        fprintf(stderr, "Invalid size for PID: %d.\n", getpid());
        return -1; // Invalid size.
    }

    // The size of the heap is rounded up to the size of the page.
    int systemPageSize = getpagesize();
    if (HeapSize % systemPageSize != 0) {
        unsigned int numberOfPage = (systemPageSize + HeapSize - 1) / systemPageSize;
        HeapSize = numberOfPage * systemPageSize;
    }

    // MAP_SHARED is required for other processes to access it.
    void* heapStart = mmap(NULL, HeapSize, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);

    if (heapStart == MAP_FAILED) {
        fprintf(stderr, "nmap failed for PID: %d.\n", getpid());
        return -1; // mmap failed
    } 

    // Initialize free list
    listHead = (ListNode*) heapStart;
    listHead->size = HeapSize - sizeof(ListNode);
    listHead->isFree = 1;
    listHead->next = NULL;

    return 0; // Success
}

void* MyMalloc(int size, int strategy) {
    if (listHead == NULL) { // No enough space.
        fprintf(stderr, "Not enough space for PID: %d.\n", getpid());
        return NULL;
    }
    ListNode* iterNode = listHead;
    ListNode* chosenNode = NULL;
    
    // The free node is selected according to the chosen strategy.
    if (strategy == BF) {
        while (iterNode != NULL) {
            if (iterNode->isFree) {
                if (iterNode->size >= size) {
                    if (chosenNode == NULL) {
                        chosenNode = iterNode;
                    } else {
                        if (chosenNode->size > iterNode->size) {
                            chosenNode = iterNode;
                        }
                    }
                }
            }
            iterNode = iterNode->next;
        }
    } else if (strategy == WF) {
        while (iterNode != NULL) {
            if (iterNode->isFree) {
                if (iterNode->size >= size) {
                    if (chosenNode == NULL) {
                        chosenNode = iterNode;
                    } else {
                        if (chosenNode->size < iterNode->size) {
                            chosenNode = iterNode;
                        }
                    }
                }
            }
            iterNode = iterNode->next;
        }
    } else if (strategy == FF) {
        while (iterNode != NULL) {
            if (iterNode->isFree) {
                if (iterNode->size >= size) {
                    if (chosenNode == NULL) {
                        chosenNode = iterNode;
                        break;
                    } else {
                        if (chosenNode->size > iterNode->size) {
                            chosenNode = iterNode;
                            break;
                        }
                    }
                }
            }
            iterNode = iterNode->next;
        }

    } else if (strategy == NF) { 
        if (lastSplit != NULL) { // If the last split node is exist.
            if (lastSplit->next != NULL) { // If the last split node is not the last element.
                iterNode = lastSplit->next;
            } 
        }
        while (iterNode != NULL) {
            if (iterNode->isFree) {
                if (iterNode->size >= size) {
                    if (chosenNode == NULL) {
                        chosenNode = iterNode;
                        break;
                    } else {
                        if (chosenNode->size > iterNode->size) {
                            chosenNode = iterNode;
                            break;
                        }
                    }
                }
            }
            iterNode = iterNode->next;
        }
    } else {
        fprintf(stderr, "Invalid strategy for PID: %d.\n", getpid());
        return NULL; // Invalid strategy.
    }

    if (chosenNode == NULL) {
        fprintf(stderr, "Not enough space for PID: %d.\n", getpid());
        return NULL; // Enough space does not found.
    }


    if (chosenNode->size > size + sizeof(ListNode)) { // If there is an increasing surplus of memory, a new free node will be created.
        ListNode* newFreeNode = (void*)((void*)chosenNode + size + sizeof(ListNode));
        newFreeNode->size = chosenNode->size - size - sizeof(ListNode);
        newFreeNode->isFree = 1;
        newFreeNode->next = chosenNode->next;
        chosenNode->size = size;
        chosenNode->next = newFreeNode;
        chosenNode->isFree = 0;
        lastSplit = chosenNode;
    } else if (chosenNode->size == size) {
        chosenNode->isFree = 0;
        lastSplit = chosenNode;
    } else if (chosenNode->size > size && chosenNode->size <= size + sizeof(ListNode)) { // If the selected node's size is larger but insufficient to create a new node, it will prevent fragmentation.
        fprintf(stderr, "Not enough space for PID: %d.\n", getpid());
        return NULL; // Enough space does not found.        
    }
    
    return (void*)(chosenNode + 1);
}

int MyFree(void* ptr) {
    if (ptr == NULL) {
        return -1;
    }

    ListNode* currentNode = (ListNode*) ptr - 1; // Adjust the pointer to point to the metadata of the allocated block.
    currentNode->isFree = 1;

    ListNode *iterNode = listHead;

    while (iterNode != NULL) { // Iterate through the entire list
        while (iterNode->next != NULL && iterNode->isFree && iterNode->next->isFree) { // Coalesce consecutive free blocks
            iterNode->size += sizeof(ListNode) + iterNode->next->size; // Merge sizes
            iterNode->next = iterNode->next->next; // Remove the next node from the list
        }
        iterNode = iterNode->next; // Move to the next node
    }
    return 0;
}

void DumpFreeList() {
    ListNode* currentNode = listHead;
    printf("Addr\tSize\tStatus\n");
    while (currentNode != NULL) {
        printf("%lu\t%lu\t%s\n", (size_t)((void*)currentNode - (void*)listHead), currentNode->size, (currentNode->isFree ? "Empty" : "Full"));
        currentNode = currentNode->next;
    }
}