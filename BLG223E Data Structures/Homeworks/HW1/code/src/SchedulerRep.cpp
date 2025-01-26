/* @Author
Student Name: 
Student ID : 
Date: 
*/
#include <iostream> 
#include <stdio.h>
#include <string.h>
#include "SchedulerRep.h"

using namespace std;

SchedulerRep::SchedulerRep()
{
/*
    YOUR CODE HEAR
*/
}
SchedulerRep::~SchedulerRep()
{
}

FIFORep* SchedulerRep::getProcessFIFO(int index)
{
/*
    YOUR CODE HEAR
*/
}

void SchedulerRep::setProcessFIFO(FIFORep* fifo, int index)
{
/*
    YOUR CODE HEAR
*/
}

void SchedulerRep::setRunningProcess(ProcessRep* p)
{
/*
    YOUR CODE HEAR
*/
}

ProcessRep* SchedulerRep::getRunningProcess()
{
/*
    YOUR CODE HEAR
*/
}

void SchedulerRep::pushProcess(ProcessRep* p)
{
/*
    YOUR CODE HEAR
*/
}

ProcessRep* SchedulerRep::popProcess()
{
/*
    YOUR CODE HEAR
*/
}

bool SchedulerRep::checkTimeSlice()
{   
/*
    YOUR CODE HEAR
*/
}
ProcessRep* SchedulerRep::sendProcessToCPU(ProcessRep* p){
/*
    YOUR CODE HEAR
*/
}
void SchedulerRep::schedule(string type, int id, int arrivalTime, int processTime)
{   
    /*  
        The function is used to schedule the processes. If a process is reached the function it will be scheduled by the function
        according to the rules which is defined below.

            1) All process types have their own time slice (quantum). When running a process, If the scheduler reachs the time slice 
                (quantum) of the running process, the process will be preempted and put back to the queue.
            2) if a process that has higher priority comes, the running process will be preempted and put back to the queue.
            3) if a process that has less or same priority with running process comes, the running process will continue to run. 
                The new process will be put back to the queue.
            4) If running process and new process have same priority and they are put back to the queue, the new process will 
                be put back to the queue first.


    */
    /*
        YOUR CODE HEAR
    */
}
void SchedulerRep::schedule(ProcessRep* p)
{   
    /*  
        The function is used to schedule the processes. If a process is reached the function it will be scheduled by the function
        according to the rules which is defined below.

            1) All process types have their own time slice (quantum). When running a process, If the scheduler reachs the time slice 
                (quantum) of the running process, the process will be preempted and put back to the queue.
            2) if a process that has higher priority comes, the running process will be preempted and put back to the queue.
            3) if a process that has less or same priority with running process comes, the running process will continue to run. 
                The new process will be put back to the queue.
            4) If running process and new process have same priority and they are put back to the queue, the new process will 
                be put back to the queue first.


    */
/*
    YOUR CODE HEAR
*/
}
