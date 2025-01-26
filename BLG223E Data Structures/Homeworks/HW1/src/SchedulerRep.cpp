/* @Author
Student Name: Mustafa Can Caliskan
Student ID : 150200097
Date: 20-10-2022
*/
#include <iostream> 
#include <stdio.h>
#include <string.h>
#include "SchedulerRep.h"

using namespace std;

SchedulerRep::SchedulerRep() //constructor
{
    for (int i = 0; i < 3; i++)
        this->mpProcessFIFO[i] = new FIFORep();
        
    this->mpRunningProcess = NULL;
    this->pCpuObj = new CPURep();
    this->timeSliceCount = 0;
    this->totalTime = 0;
}
SchedulerRep::~SchedulerRep() // deconstructor
{
    for (int i = 0; i < 3; i++)
        delete this->mpProcessFIFO[i];
    delete this->pCpuObj;
    if (this->mpRunningProcess != NULL)
        delete this->mpRunningProcess;
}

FIFORep* SchedulerRep::getProcessFIFO(int index) //geting scheduler list by index number
{
    return this->mpProcessFIFO[index];
}

void SchedulerRep::setProcessFIFO(FIFORep* fifo, int index) //setting scheduler list by index number
{
    this->mpProcessFIFO[index] = fifo;
}

void SchedulerRep::setRunningProcess(ProcessRep* p) //to setting running process and assigning start time of running process, it is also changing the quantum time
{
    if (p != NULL)
        if (p->startTime == -1)
            p->startTime = this->totalTime;

    this->timeSliceCount = 0;
    this->mpRunningProcess = p;
}

ProcessRep* SchedulerRep::getRunningProcess() //to getting running process
{
    return this->mpRunningProcess;
}

void SchedulerRep::pushProcess(ProcessRep* p) //to pushing process to scheduler lists by checking types of processes
{   
    if (p == NULL)
        return;

    if (p->getProcessType() == "A")
        this->mpProcessFIFO[0]->queue(p);

    else if (p->getProcessType() == "B")
        this->mpProcessFIFO[1]->queue(p);

    else if (p->getProcessType() == "C")
        this->mpProcessFIFO[2]->queue(p);
}

ProcessRep* SchedulerRep::popProcess() //to pushing process to CPU by checking priority of lists 
{
    if (this->mpProcessFIFO[0]->getHead() != NULL)
        return this->mpProcessFIFO[0]->dequeue();

    else if (this->mpProcessFIFO[1]->getHead() != NULL)
        return this->mpProcessFIFO[1]->dequeue();

    else if (this->mpProcessFIFO[2]->getHead() != NULL)
        return this->mpProcessFIFO[2]->dequeue();

    return NULL;
}

bool SchedulerRep::checkTimeSlice() //checking quantum time by type
{ 
    if (getRunningProcess() == NULL)
        return false;

    if (this->getRunningProcess()->getProcessType() == "A") {
        if (this->timeSliceCount == 2)
            return true;
    }

    else if (this->getRunningProcess()->getProcessType() == "B"){
        if (this->timeSliceCount == 4)
            return true;
    }

    else if (this->getRunningProcess()->getProcessType() == "C") {
        if (this->timeSliceCount == 8)
            return true;
    }

    return false;
}

ProcessRep* SchedulerRep::sendProcessToCPU(ProcessRep* p){ //to running process by calling runCPU
    return this->pCpuObj->runCPU(p, this->totalTime);
}

void SchedulerRep::schedule(string type, int id, int arrivalTime, int processTime) //to directing main schedule function
{   
    ProcessRep* new_process = new ProcessRep(type, id, arrivalTime, processTime);
    schedule(new_process); 
}

void SchedulerRep::schedule(ProcessRep* p)
{
    if (p != NULL)
        this->pushProcess(p);

    if (getRunningProcess() == NULL)
        this->setRunningProcess(popProcess());

    if (this->checkTimeSlice()) {
        this->pushProcess(getRunningProcess());
        this->setRunningProcess(popProcess());
    }

    if(this->getRunningProcess() != NULL && p != NULL)
        if (getRunningProcess()->getProcessType() > p->getProcessType()) {
            this->pushProcess(getRunningProcess());
            this->setRunningProcess(popProcess());
        }

    this->totalTime++;
    this->timeSliceCount++;

    if (sendProcessToCPU(getRunningProcess()) != NULL) //in order to checking completeness of the running process
        this->setRunningProcess(popProcess());
}
