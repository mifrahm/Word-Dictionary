#include<iostream>
#include<stdlib.h>
#include<iomanip>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <queue>
#include <vector>


using namespace std;

#include "DATA.h"
#include "AvlChild.h"


//Global function for traversing an AVL tree
void print(DATA ss) {
    cout << "Word: " << ss.key << " |";
    cout << " Frequency: " << ss.frequency << endl;
    cout << endl;
}


//trim words
string trimWord(string input){
    stringstream ss;
    for (int x=0; x< (int) input.size(); x++){
        if(isalpha(input[x])){
            ss << input[x];

        }
    }


    if(ss.str().length()> 0) {
        string data = ss.str();
        std::transform(data.begin(), data.end(), data.begin(), ::tolower);
        return data;
    } else {
        return "";
    }

}

//add words
void readWords(string textfile, AvlChild& tree){
    ifstream fin;
    string word;
    DATA newItem;

    do {
        fin.open(textfile);
        if (fin.fail()) {
            cout << "Input file opening failed.\n";
        }

    } while (fin.fail());


    // read from file
    int i = 0;

    DATA data;

    while (!fin.eof()) {

        fin >> word;

        word = trimWord(word);


        if (word != "") {
            if (!tree.AVL_Retrieve(word, data)) { //if node does not exist
                newItem.key = word;
                newItem.frequency = 1;
                tree.AVL_Insert(newItem);
            } else {
                tree.AVL_Update(data);
            }
        }


        i++;
    }

    cout << "This document contains: " << data.count << " words " << endl;
}


//add phrases
void readPhrases(string textfile, AvlChild& tree){
    ifstream fin;
    DATA newItem;

    do {
        fin.open(textfile);
        if (fin.fail()) {
            cout << "Input file opening failed.\n";
        }

    } while (fin.fail());


    string word, nextWord;

    vector<string> phrase(3);

    do {
        fin >> nextWord;
        phrase[0] = trimWord(nextWord);
        word = phrase[0];
    } while (phrase[0] == "");


    for (int i = 1; i < 3; i++) {
        do {
            fin >> nextWord;
            phrase[i] = trimWord(nextWord);
        } while (phrase[i] == "");
        word = word + " " + phrase[i];
    }

    while (!fin.eof()) {


        // read from file
        int z = 0;


        DATA data;


        if (!tree.AVL_Retrieve(word, data)) { //if node does not exist
            newItem.key = word;
            newItem.frequency = 1;
            tree.AVL_Insert(newItem);
        } else {
            tree.AVL_Update(data);
        }

        phrase.erase(phrase.begin());
        word = phrase[0] + " " + phrase[1];

        do {
            fin >> nextWord;
            nextWord = trimWord(nextWord);
        } while (nextWord == "");
        phrase.push_back(nextWord);
        word = word + " " + phrase[2];

        z++;
    }
}


int main() {
    AvlChild tree;
    int option;



    cout << "Please select from the following options: " << endl;
    cout << "1. Learn dictionary from a file (without phrases)." << endl;
    cout << "2. Learn dictionary from a file (with words and phrases)." << endl;
    cout << "3. Load dictionary from a file." << endl;
    cout << "4. Output dictionary to a file." << endl;
    cout << "5. Print the whole dictionary with the information of each word and its frequency." << endl;
    cout << "6. Print the AVL tree with the information of the total number of words" << endl;
    cout << "7. Print the words in order of frequency" << endl;
    cout << "8. Find similar words according to your input" << endl;
    cout << "9. Delete words/phrases with lower frequency" << endl;
    cout << "10. Inverted index: Display the list of names of all the files that contain the word." << endl;
    cout << "0. Quit" << endl;


    do {

        cout << "\n Main Menu: Enter your input. Write 99 to exit " << endl;
        cin >> option;

        if (option == 1) {
            //Learn dictionary from a file (without phrases).

            string textfile;

            cout << "Enter in file name, e.g. article1.txt" << endl;
            cin >> textfile;
            readWords(textfile, tree);

            cout << "Dictionary now has " << tree.AVL_Count() << " words." << endl;
        } else if (option == 2) {
            // Learn dictionary from a file (with phrases).

            string textfile;
            cout << "Enter in file name, e.g. article1.txt" << endl;
            cin >> textfile;

            readWords(textfile, tree);
            readPhrases(textfile, tree);

            cout << "Words successfully added! Dictionary now has " << tree.AVL_Count() << " words." << endl;

        }
        else if (option == 3)
        {
            //Load dictionary from a file.

            ifstream fin;
            string word;
            DATA newItem;
            char deliminator;
            char space;
            int freq;
            int total;


            string textfile;

            do {
                cout << "Enter in file name to load dictionary, e.g. dictionary.txt" << endl;
                cin >> textfile;
                fin.open(textfile);
                if (fin.fail()) {
                    cout << "Input file opening failed.\n";
                }

            } while(fin.fail());

            // read from file
            int i = 0;

            while(!fin.eof()){

                fin >> word;
                fin.get(space);
                fin.get(deliminator);
                fin.get(space);
                fin >> freq;
                fin.get(deliminator);
                fin >> total;

                DATA data;

                if (!tree.AVL_Retrieve(word, data)){ //if node does not exist
                    newItem.key = word;
                    newItem.frequency = freq;
                    tree.AVL_Insert(newItem);
                } else {
                    tree.AVL_Update(data);
                }

                i++;
            }
            cout << "I'm done!" << endl;

        }
        else if (option == 4)
        {

            tree.OutputDictionary();

            cout << tree.AVL_Count() << " words successfully added" << endl;

        }

        else if (option == 5)
        {
            // Print the whole dictionary with the information of each word and its frequency.
            if(tree.AVL_Empty())
                cout << "Empty tree."<< endl;
            else
                tree.PrintDictionary();
        }

        else if (option == 6) {

            //Print the AVL tree with the information of the total number of words

            cout << "AVL Tree" << endl;
            tree.AVL_Print();

            cout << "\nTotal words in dictionary: " << tree.AVL_Count() << endl << endl;

        }

        else if (option == 7) {
            // Generate a priority queue for each input of characters in the order of frequency from your frequency dictionary

            cout<<"Words by Frequency:" << endl;
            tree.printWordsByFreq();
            cout<<endl;
        }
        else if (option == 8) {
            // Display a list of words from the priority queue according to your input.
            cout << "Similar Word Search:" << endl;
            tree.printSimilarWords();
            cout << endl;
        }
        else if (option == 9)
        {
            // Extend your frequency dictionary so that it can delete words/phrases with lower frequency

            tree.LowFrequency();


        }
        else if (option == 10) {
            // Extend your frequency dictionary to contain an inverted index so that whenever a word is input,
            // your program will display the list of names of all the files that contain the word.

            int files;
            string textfile;

            cout << "How many files would you like to add?" << endl;
            cin >> files;
            for (int k = 0; k < files; k++) {

                ifstream fin;
                string word;
                DATA newItem;

                do {
                    cout << "Enter in file name, e.g. article1.txt" << endl;
                    cin >> textfile;
                    fin.open(textfile);
                    if (fin.fail()) {
                        cout << "Input file opening failed.\n";
                    }

                } while(fin.fail());


                // read from file
                int i = 0;

                while(!fin.eof()){

                    fin >> word;

                    word = trimWord(word);

                    DATA data;


                    if (word != ""){
                        if (!tree.AVL_Retrieve(word, data)){ //if node does not exist
                            newItem.key = word;
                            newItem.frequency = 1;
                            newItem.fileName.insert(textfile);
                            tree.AVL_Insert(newItem);
                        } else {
                            newItem.fileName.insert(textfile);
                            // FEEDBACK : There is
                            // data.newFile = textfile;
                            tree.AVL_Update(data);

                        }
                    }


                    i++;
                }

                cout << "Learning from file: Textfile/" + textfile << endl;
                cout << "Words successfully added! Dictionary now has " << tree.AVL_Count() << " words." << endl << endl;
            }

            tree.AVL_searchInvertedIndex();


        }

        else if (option == 11){

            //testing purposes


        }

        else if (option == 99) {
        }
        else {
            cout << "Invalid option, please try again" << endl;
        }

    } while (option != 99 || !(option<=10));

    return 0;
}

