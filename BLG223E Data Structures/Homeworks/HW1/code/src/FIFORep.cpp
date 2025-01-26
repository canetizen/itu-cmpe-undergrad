/* @Author
Student Name: 
Student ID : 
Date: 
*/
#include <iostream> 
#include <stdio.h>
#include <string.h>

#include "ProcessRep.h"
#include "FIFORep.h"

using namespace std;

FIFORep::FIFORep()
{
    
    /*
        YOUR CODE HEAR
    */
}

FIFORep::FIFORep(ProcessRep* head)
{
    /*
        YOUR CODE HEAR
    */
}


FIFORep::~FIFORep()
{
}

void FIFORep::setHead(ProcessRep* head)
{
    /*
        YOUR CODE HEAR
    */
}

ProcessRep* FIFORep::getHead()
{
    /*
        YOUR CODE HEAR
    */
}

void FIFORep::setTail(ProcessRep* tail)
{
    /*
        YOUR CODE HEAR
    */
}

ProcessRep* FIFORep::getTail()
{
    /*
        YOUR CODE HEAR
    */
}

void FIFORep::queue(ProcessRep* p)
{
    /*
        The function add a process to the tail of the queue.
    */
    /*
        YOUR CODE HEAR
    */
}

ProcessRep* FIFORep::dequeue()
{   
    /*
        The function remove a process from the tail of the queue and returns it.
    */   
    /*
        YOUR CODE HEAR
    */
}

ProcessRep* FIFORep::searchID(int id)
{   
    /*
        The function search a process by id and returns it if it exist otherwise returns NULL.
    */ 
    /*
        YOUR CODE HEAR
    */
}

void FIFORep::printFIFO()
{
    /*
        The function prints the proceses in the queue starting from Head to tail.
    */
    /*
        YOUR CODE HEAR
    */
}