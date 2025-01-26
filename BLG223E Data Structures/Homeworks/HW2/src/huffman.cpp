//--- 2022-2023 Fall Semester Data Structure Assignment 2 ---//
//--------------------------//
//---Name & Surname: Mustafa Can Çalışkan
//---Student Number: 150200097
//--------------------------//

//-------------Do Not Add New Libraries-------------//
//-------------All Libraries Needed Were Given-------------//
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string.h>
#include <bits/stdc++.h>

#include "huffman.h"
#include "structs.h"

using namespace std;

//-------------Complete The Functions Below-------------//

bool find (string s, char x) {  //own function to search string for a spesific character.
    for (char i: s) {
        if (i == x)
            return true;
    }
    return false;
}


//-----------------------------------------------------//
//-----------Reads the key from text file--------------//
//------------DO NOT CHANGE THIS FUNCTION--------------//
//-----------------------------------------------------//
void Huffman::readKey(const char* argv){
    ifstream readKeyFile;
    readKeyFile.open(argv);

    if(readKeyFile.is_open()){
        while(!readKeyFile.eof()){
            readKeyFile >> key;
        }
    }
    readKeyFile.close();
}
//-----------------------------------------------------//


//-----------------------------------------------------//
//---------Sorts the key in an alpabetic order---------//
//------------DO NOT CHANGE THIS FUNCTION--------------//
//-----------------------------------------------------//
void Huffman::sortKey(){
    sortedKey = key;
    sort(sortedKey.begin(), sortedKey.end());
}
//-----------------------------------------------------//


//-----------------------------------------------------//
//-------Finds the frequency of the characters---------//
//-----------------------------------------------------//
void Huffman::findFrequency(){
    //DO NOT CHANGE THIS
    sortKey();

    int counter = 1;
    for (unsigned int i = 1; i < sortedKey.size(); i++){
        if (sortedKey[i] == sortedKey[i - 1]) {
            counter++;
        }
        else {
            Node* new_node = new Node();
            new_node->token.val = counter;
            new_node->token.symbol = sortedKey[i - 1];
            this->queue.enque(new_node);
            counter = 1;
        }
    }

    Node* new_node2 = new Node();
    new_node2->token.val = counter;
    new_node2->token.symbol = sortedKey[sortedKey.size() - 1];
    this->queue.enque(new_node2);
}
//-----------------------------------------------------//


//-----------------------------------------------------//
//----------------Creates Huffman Tree-----------------//
//-----------------------------------------------------//
void Huffman::createHuffmanTree(){
    this->findFrequency();
    while (this->queue.head->next != NULL) {
        Node* temp1 = this->queue.dequeue();
        Node* temp2 = this->queue.dequeue();
        this->queue.enque(this->huffmanTree.mergeNodes(temp1, temp2));
    }
    this->huffmanTree.root = this->queue.dequeue();
}
//-----------------------------------------------------//


//-----------------------------------------------------//
//---------------Prints the Huffman Tree---------------//
//------------DO NOT CHANGE THIS FUNCTION--------------//
//-----------------------------------------------------//
void Huffman::printHuffmanTree(){
    huffmanTree.printTree(huffmanTree.root, 0);
}
//-----------------------------------------------------//

//-----------------------------------------------------//
//-------------Finds and returns the binary------------//
//----------------value to given character-------------//
//-----------------------------------------------------//
string Huffman::getTokenBinary(char tokenChar, Node* traverse, string tokenBinary){
    if (traverse != NULL) {
        if (traverse->token.symbol[0] == tokenChar && traverse->token.symbol.size() == 1)
            return tokenBinary;
        
        else if (find(traverse->left->token.symbol, tokenChar)) {
            tokenBinary += '0';
            tokenBinary = getTokenBinary(tokenChar, traverse->left, tokenBinary);
        }

        else if (find(traverse->right->token.symbol, tokenChar)) {
            tokenBinary += '1';
            tokenBinary = getTokenBinary(tokenChar, traverse->right, tokenBinary);
        }
    }

    return tokenBinary;
}

//-----------------------------------------------------//

//-----------------------------------------------------//
//--------------Encodes the given password-------------//
//-----------------------------------------------------//
void Huffman::encodePassword(string password){
    for (char i: password) {
        encodedValPassword += to_string(getTokenBinary(i, this->huffmanTree.root, "\0").size());
        encodedBinaryPassword += getTokenBinary(i, this->huffmanTree.root, "\0");
    }
}
//-----------------------------------------------------//

//-----------------------------------------------------//
//-------------Prints the encoded password-------------//
//------------DO NOT CHANGE THIS FUNCTION--------------//
//-----------------------------------------------------//
void Huffman::printEncodedPassword(){
    cout << "Encoded Password Binary: " << encodedBinaryPassword << endl;
    cout << "Encoded Password Value: " << encodedValPassword << endl;
}

//-----------------------------------------------------//
//--------------Decodes the given password-------------//
//-----------------------------------------------------//
void Huffman::decodePassword(string encodedValPassword, string encodedBinaryPassword){
    unsigned int i = 0;
    int j = 0;
    while (i < encodedBinaryPassword.size()) {
        stringstream strm;
        strm << encodedValPassword[j];
        int number = std::stoi(strm.str());
        decodeToken(encodedBinaryPassword.substr(i, number));
        j++;
        i += number;
    }
}

//-----------------------------------------------------//

//-----------------------------------------------------//
//---------------Decodes the given binary--------------//
//-----------------------------------------------------//
void Huffman::decodeToken(string encodedToken){
    Node* temp = this->huffmanTree.root;
    int i = 0;
    while (temp->right != NULL || temp->left != NULL) {
        if (encodedToken[i] == '1') {
            temp = temp->right;
        }
        else {
            temp = temp->left;
        }
        i++;
    }
    decodedPassword += temp->token.symbol;
}
//-----------------------------------------------------//

//-----------------------------------------------------//
//-------------Prints the decoded password-------------//
//------------DO NOT CHANGE THIS FUNCTION--------------//
//-----------------------------------------------------//
void Huffman::printDecodedPassword(){
    cout << "Decoded Password: " << decodedPassword << endl;
}