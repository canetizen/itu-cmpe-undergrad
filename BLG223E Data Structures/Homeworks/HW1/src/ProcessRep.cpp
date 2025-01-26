/* @Author
Student Name: Mustafa Can Caliskan
Student ID : 150200097
Date: 20-10-2022
*/
#include <iostream> 
#include <stdio.h>
#include <string>
#include "ProcessRep.h"


using namespace std;

ProcessRep::ProcessRep(string processType, int processID, int deliverTime, int processTime) //constructor to assign methods.
{   
    this->mpNext = NULL;
    this->mProcessType = processType;
    this->mProcessID = processID;
    this->mDeliverTime = deliverTime;
    this->mProcessTime = processTime;
    this->startTime = -1;
    this->endTime = -1;
    this->remainingTime = processTime;
}

ProcessRep::~ProcessRep() //deconstructor
{
    if(this->mpNext != NULL)
        delete this->mpNext;
}

ProcessRep* ProcessRep::getNext() // to reaching next of node
{
    return this->mpNext;
}

void ProcessRep::setNext(ProcessRep *next) // to assigning next
{
    this->mpNext = next;
}

string ProcessRep::getProcessType() // to reaching process type of node
{
    return this->mProcessType;
}

void ProcessRep::setProcessType(string processType)// to assigning process type of node
{
    this->mProcessType = processType;
}

int ProcessRep::getDeliverTime() //to reaching deliver time of node
{
    return this->mDeliverTime;
}

void ProcessRep::setDeliverTime(int deliverTime) //to assigning deliver time of node
{
    this->mDeliverTime = deliverTime;
}

int ProcessRep::getProcessID() // to reaching id of node
{
    return this->mProcessID;
}

void ProcessRep::setProcessID(int processID) // to assigning process time
{
    this->mProcessID = processID;
}

int ProcessRep::getProcessTime() // to reaching process time
{
    return this->mProcessTime;
}

void ProcessRep::setProcessTime(int ProcessTime) // to assigning process time of node
{
    this->mProcessTime = ProcessTime;
}