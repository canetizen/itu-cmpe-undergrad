/* @Author
Student Name: Mustafa Can Caliskan
Student ID : 150200097
Date: 20-10-2022
*/
#include <iostream>
#include <stdio.h>
#include <string.h>
// #include "node.h"
#include "ProcessRep.h"
#include "FIFORep.h"
#include "CPURep.h"

using namespace std;

CPURep::CPURep() //constructor
{
    this->mFinishedProcess = new FIFORep();
}

CPURep::~CPURep() //deconstructor
{
    delete this->mFinishedProcess;
}

ProcessRep* CPURep::runCPU(ProcessRep* p, int time) //to running CPU by decreasing remaining time and sending to finished process list
{   
    if (p != NULL) {
        p->remainingTime--;
        if (p->remainingTime == 0){
            p->endTime = time;
            this->getFinishedProcess()->queue(p);
            return p;
        }
        return NULL;
    }
    else
        return NULL;
}

FIFORep* CPURep::getFinishedProcess() //getting finished process list
{
    return this->mFinishedProcess;
}

void CPURep::setFinishedProcess(FIFORep* finishedProcess) //setting finished process list
{
    this->mFinishedProcess = finishedProcess;
}