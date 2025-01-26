/**
 * Mustafa Can Caliskan
 * 150200097
 * COS Project 2
*/

#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#include <stdlib.h>
#include <stdio.h>

#define BF 0
#define WF 1
#define FF 2
#define NF 3

typedef struct ListNode {
    size_t size;
    struct ListNode* next;
    unsigned int isFree; // free: 1, allocated: 0
} ListNode;

extern ListNode* listHead;
extern ListNode* lastSplit; // For the next fit strategy.

extern int InitMyMalloc(int);
extern void* MyMalloc(int, int);
extern int MyFree(void*);
extern void DumpFreeList();

#endif