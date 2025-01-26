//--- 2022-2023 Fall Semester Data Structure Assignment 2 ---//
//--------------------------//
//---Name & Surname: Mustafa Can Çalışkan
//---Student Number: 150200097
//--------------------------//

//-------------Do Not Add New Libraries-------------//
//-------------All Libraries Needed Were Given-------------//
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <fstream>

#include "structs.h"

using namespace std;

//-------------Complete The Functions Below-------------//

//-------------Initialize Priority Queue-------------//
PriorityQueue::PriorityQueue(){
    this->head = NULL;
}

//-------------Insert New Node To Priority Queue-------------//
void PriorityQueue::enque(Node* newnode){
    if (newnode == NULL)
        return;

    if (this->head == NULL) {
        this->head = newnode;
        return;
    }

    Node* temp = this->head;

    if (this->head != NULL) {
        if (this->head->token.val > newnode->token.val) {
            this->head = newnode;
            this->head->next = temp;
            return;
        }
    }

    while (temp->next != NULL) {
        if (newnode->token.val < temp->next->token.val) {
            newnode->next = temp->next;
            temp->next = newnode;
            return;
        }
        temp = temp->next;
    }

    temp->next = newnode;
}

//-------------Remove Node From Priority Queue-------------//
Node* PriorityQueue::dequeue(){
    if (this->head == NULL)
        return NULL;

    Node* temp = this->head;
    this->head = this->head->next;
    temp->next = NULL;
    return temp;   
}

//-------------Initialize Tree-------------//
Tree::Tree(){
    this->root = NULL;
}

//-------------Delete Tree Nodes From Memory-------------//
Tree::~Tree(){
    if (this->root != NULL)
        this->deleteTree(this->root);
    this->root = NULL;
}

//-------------Delete Tree From Memory-------------//
void Tree::deleteTree(Node* node){
    if (node != NULL) {
        this->deleteTree(node->left);
        this->deleteTree(node->right);
        delete node;
    }
}

//-------------Merges Two Node Into One-------------//
Node* Tree::mergeNodes(Node* temp1, Node* temp2){
    if (temp1 == NULL || temp2 == NULL)
        return NULL;
    Node* new_node = new Node();
    new_node->token.symbol += temp1->token.symbol;
    new_node->token.symbol += temp2->token.symbol;
    new_node->token.val = temp1->token.val + temp2->token.val;    new_node->left = temp1;
    new_node->right = temp2;
    return new_node;
}

void Tree::printTree(Node* traverse, int level){
    cout << level << "\t";
    for (int i = 0; i < level; i++)
        cout << "\t"; 

    cout << traverse->token.symbol << "(" << traverse->token.val << ")" << endl;

    if(traverse->left)
        printTree(traverse->left, level + 1);  
    if(traverse->right)
        printTree(traverse->right, level + 1);
}