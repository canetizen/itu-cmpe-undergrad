/* @Author
Student Name: Mustafa Can Caliskan
Student ID : 150200097
Date: 20-10-2022
*/
#include <iostream> 
#include <stdio.h>
#include <string.h>

#include "ProcessRep.h"
#include "FIFORep.h"

using namespace std;

FIFORep::FIFORep() //constructor to assigning tail and node to their starting values
{
    this->mpHead = NULL; 
    this->mpTail = NULL;
}

FIFORep::FIFORep(ProcessRep* head)
{
    this->mpHead = head;
    this->mpTail = this->mpHead;
}

FIFORep::~FIFORep() //deconstructor
{
    delete this->mpHead;
}

void FIFORep::setHead(ProcessRep* head) //to assigning head
{
    this->mpHead = head;
}

ProcessRep* FIFORep::getHead() //to reaching head
{
    return this->mpHead;
}

void FIFORep::setTail(ProcessRep* tail) // to setting tail of the list
{
    this->mpTail = tail;
}

ProcessRep* FIFORep::getTail() // to assigning tail to the list
{
    return this->mpTail;
}

void FIFORep::queue(ProcessRep* p) // queue function to implementing FIFO approach
{
    if (this->getHead() == NULL){ 
        this->setHead(p);
        this->setTail(p);
    }
    else {
        this->mpTail->setNext(p);
        this->setTail(p);
        this->getTail()->setNext(NULL);
    }
}

ProcessRep* FIFORep::dequeue() //dequeue function that separates from list
{   
    ProcessRep* temp = NULL;
    if (this->getHead() == this->getTail()) { 
        temp = this->getHead();
        this->setHead(NULL);
        this->setTail(NULL);
    }

    else {
        temp = this->getHead();
        this->setHead(this->mpHead->getNext());
    }
    return temp;
}

ProcessRep* FIFORep::searchID(int id) //to finding node by id
{   
    ProcessRep* temp = this->getHead();
    while (temp != NULL && temp->getProcessID() != id)
        temp = temp->getNext();
    return temp;
}

void FIFORep::printFIFO() //to printing the list
{
    ProcessRep* temp = this->getHead();

    if (temp == NULL)
        return;
    
    while (temp != this->getTail()){
        cout << temp->getProcessType() << temp->getProcessID() << " " << temp->startTime << " " << temp->endTime << " ";
        temp = temp->getNext();
    }
    cout << temp->getProcessType() << temp->getProcessID() << " " << temp->startTime << " " << temp->endTime << " ";
}