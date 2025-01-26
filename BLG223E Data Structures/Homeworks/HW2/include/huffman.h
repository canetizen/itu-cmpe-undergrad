//--- 2022-2023 Fall Semester Data Structure Assignment 2 ---//
//--------------------------//
//---Name & Surname: Mustafa Can Çalışkan
//---Student Number: 150200097
//--------------------------//

#ifndef _huffman
#define _huffman

//-------------Do Not Add New Libraries-------------//
//-------------All Libraries Needed Were Given-------------//
#include <iostream>
#include <stdio.h>
#include <string.h>

#include "structs.h"

using namespace std;

//--------------Do Not Change The Class--------------//
//--------------Do Not Add A New Class---------------//
//--------------You Can Add New Functions------------//

//-------------Huffman Class-------------//
class Huffman{
    private:
        string key;
        string sortedKey;

        PriorityQueue queue;

        Tree huffmanTree;

        string encodedBinaryPassword;
        string encodedValPassword;

        string decodedPassword;
        
    public:
        void readKey(const char*);
        void sortKey();

        void findFrequency();
        void createHuffmanTree();

        void printHuffmanTree();

        string getTokenBinary(char, Node*, string);
        void encodePassword(string);
        void printEncodedPassword();

        void decodePassword(string, string);
        void decodeToken(string);
        void printDecodedPassword();
};

#endif