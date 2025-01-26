//--- 2022-2023 Fall Semester Data Structure Assignment 2 ---//
//--------------------------//
//---Name & Surname: Mustafa Can Çalışkan
//---Student Number: 150200097
//--------------------------//

//-------------Do Not Add New Libraries-------------//
//-------------All Libraries Needed Were Given-------------//
#include <iostream> 
#include <stdio.h>

#include "huffman.h"


using namespace std;

//-------------Do Not Change This Function Definitions-------------//
void mainMenu();
//------------------------------------------------------------------//


//-------------Do Not Change or Add Anything in Main-------------//
int main(int argc, char* argv[]){
	system("clear");

    int mainMenuChoice;
    string password;
    string encodedBinaryPassword;
    string encodedValPassword;
 

    Huffman newHuffman;

    while(true){
        mainMenu();
        cin>>mainMenuChoice;

        switch (mainMenuChoice)
        {
        case 1:
            newHuffman.readKey(argv[1]);
            break;

        case 2:
            newHuffman.createHuffmanTree();
            break;

        case 3:
            newHuffman.printHuffmanTree();
            break;

        case 4:
            cout << "Enter the password: ";
            cin >> password;
            newHuffman.encodePassword(password);
            break;

        case 5:
            newHuffman.printEncodedPassword();
            break;

        case 6:
            cout << "Enter the binary password : ";
            cin >> encodedBinaryPassword;
            cout << "Enter the encoded password value: ";
            cin >> encodedValPassword;
            newHuffman.decodePassword(encodedValPassword,encodedBinaryPassword);
            newHuffman.printDecodedPassword();
            
            break;
        case 7:
            return EXIT_SUCCESS;

        default:
            cout << "Please enter a valid choice!!!" << endl;
            break;
        }
    }
    return EXIT_FAILURE;
};

//-------------Do Not Change This Function-------------//
void mainMenu(){
    cout << endl;
    cout << "-------- Menu --------" << endl;
    cout << "1. Read Key File" << endl;
    cout << "2. Create Token" << endl;
    cout << "3. Print Huffman Tree" << endl;
    cout << "4. Encode Password" << endl;
    cout << "5. Print Encoded Password" << endl;
    cout << "6. Decode Password" << endl;
    cout << "7. Exit" << endl;
    cout << endl;
    cout << "Choice: ";
};
//-----------------------------------------------------//