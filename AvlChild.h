//
////// Created by Mifrah Mahroof on 23/5/19.
//

#ifndef DSAASSIGNMENT2_AVL_ADTCHILD_H
#define DSAASSIGNMENT2_AVL_ADTCHILD_H

#include "AVL_ADT.h"
#include<iostream>
#include<map>

class AvlChild: public AvlTree<DATA,string> {

private:
    priority_queue<DATA> pq;
    map<int, DATA> invertedIndex;
    ofstream fout;

public:
    AvlChild(){

    }
    ~AvlChild(){

    }
    void AVL_Update (DATA&  newNode);
    void AVL_traversalChildPQ (NODE<DATA> *root);
    void AVL_traversalChildDictionary (NODE<DATA> *root);
    void AVL_printRange (NODE<DATA> *root, string a, string b);
    void printWordsByFreq();
    void printSimilarWords();
    void OutputDictionary();
    void PrintDictionary();
    void LowFrequency();
    void AVL_UpdateScore(DATA& newNode);
    void AVL_DeleteChild (string dltKey);
    void AVL_searchInvertedIndex();
    void AVL_printInvertedRange(NODE<DATA> *root, string a, string b);


};


void AvlChild :: AVL_Update(DATA& newNode) {

    NODE<DATA> *oldNode;
    oldNode = _retrieve(newNode.key, tree);
    if (oldNode) {
        oldNode->data.frequency++;
    }

    newNode.frequency = oldNode->data.frequency;

    if(newNode.newFile.size() > 0){ //this is used if there are multiple files being added
        oldNode->data.fileName.insert(newNode.newFile);
    }

};


/* ============ AVL_traversalChildPQ ==============
 This function traverse tree using inorder traversal.
 Each node is processed by being added to the priority queue: PQ.

    Pre: Tree has been created (may be null)
    Post: All nodes processed.

*/

void AvlChild ::  AVL_traversalChildPQ (NODE<DATA> *root)
{
    if (root)
    {
        AVL_traversalChildPQ  (root->left);
        pq.push(root->data);
        AVL_traversalChildPQ  (root->right);
    } //  if
    return;
}



/* ============ printWordsbyFreq ==============
 * Print dictionary words by order of frequency. Operator < overloaded to sort data by frequency.

 * Pre: Tree has been created and contains words.
 * Post: Priority queue is empty.

*/

void AvlChild :: printWordsByFreq(){

    AVL_traversalChildPQ (tree); //call function, pass paramater as the root (pointer)
    // after this function runs, the priority queue PQ is filled with data objects.

    while(!pq.empty()) { //process each data object
        cout << pq.top().key << " | Freq: " << pq.top().frequency << endl; // print out word and frequency
        pq.pop(); // remove printed object from queue
    }

}


void AvlChild ::printSimilarWords(){

    string userInput, userWord, temp;
    DATA found;
    cout << "Please enter in a search, press # to return to main menu" << endl;

    do {

        cin >> userInput;
        userWord.append(userInput);

        string lower;

        if (userWord.length()==0){
            cout << "No input found" << endl;
        } else if (userWord.length()>0) {
            lower = userWord;
            temp = userWord;
            char userInputNext = ++temp.front();
            string upper(1, userInputNext);
            AVL_printRange(tree, lower, upper);
        }



        cout << "Search Results: " << endl;


        if (AVL_Retrieve(userWord, found)){
            cout << found.key << " has been found " <<  endl;
            break;
        } else {
            if (pq.empty()) {
                cout << "No matching words found." << endl;
            } else {
                cout << "An exact match not found, do you mean the following? " << endl;
                while (!pq.empty()) {
                    cout << pq.top().key << " | Freq: " << pq.top().frequency << endl;
                    pq.pop();
                }
            }
        }

        cout << userWord;

    } while (userInput != "#");

}



void AvlChild ::AVL_printRange(NODE<DATA> *root, string a, string b){

    if (root == NULL) return;


    if (a < root->data.key)
        AVL_printRange(root->left, a, b);

    if (a <= root->data.key && b > root->data.key )
        pq.push(root->data);

    if (b > root->data.key)
        AVL_printRange(root->right, a, b);

}

/* ============ printWordsbyFreq ==============
 * Output dictionary words onto a new file.
 *
 * Pre: Tree has been created and contains words.
 * Post: Priority queue is empty, file is created.

*/


void AvlChild :: OutputDictionary(){

    fout.open("dictionary.txt");

    AVL_traversalChildDictionary (tree);

    cout << "Words have been added to dictionary" << endl;

    fout.close();
}


void AvlChild ::  AVL_traversalChildDictionary (NODE<DATA> *root)
{

    if (root)
    {
        fout << root->data.key << " | " << root->data.frequency << "," << root->data.count << endl;
        AVL_traversalChildDictionary  (root->left);
        AVL_traversalChildDictionary  (root->right);
    } //  if
    return;
}

void AvlChild :: PrintDictionary(){

    //Output dictionary to a file.

    AVL_traversalChildPQ (tree);

    double frequency;

    while(!pq.empty()) {

        frequency = (1000.00/pq.top().count) * pq.top().frequency;
        cout << pq.top().key << " (" << frequency << " per thousand words)" << endl;

        pq.pop();
    }

    cout << endl << "Total Words in Dictionary: " << count << endl;
}


void AvlChild :: LowFrequency(){


    AVL_traversalChildPQ (tree);
    double threshold;

    cout << "Supply low frequency threshold" << endl;
    cin >> threshold;

    DATA data;
    while(!pq.empty()) {

        data = pq.top();
        AVL_UpdateScore(data);

        if (data.score < threshold){
            AVL_DeleteChild (data.key);
            cout << "This word has successfully been deleted: " << data.key << endl;
        }

        pq.pop();
    }

}



void AvlChild :: AVL_UpdateScore(DATA& newNode) {

    NODE<DATA> *oldNode;
    oldNode = _retrieve(newNode.key, tree);
    if (oldNode) {
        oldNode->data.score = 1000.00/count*oldNode->data.frequency;
    }

    newNode.score = oldNode->data.score;

};


void  AvlChild:: AVL_DeleteChild (string dltKey) {
//	Local Definitions
    bool shorter;
    bool success;

    NODE<DATA> *newRoot;

//	Statements
    newRoot = _delete(tree, dltKey, shorter, success);
    if (success) {
        tree = newRoot;
        count--;
    } // if

}


void AvlChild ::AVL_searchInvertedIndex(){

    string userInput, userWord, temp;
    int choice;
    DATA found;

    cout << "Please enter in a search, press # to return to main menu" << endl;

    do {

        cin >> userInput;
        userWord.append(userInput);

        string lower;

        if (userWord.length()==0){
            cout << "No input found" << endl;
        } else if (userWord.length()>0) {
            lower = userWord;
            temp = userWord;
            char userInputNext = ++temp.front();
            string upper(1, userInputNext);
            AVL_printInvertedRange(tree, lower, upper);
        }



        cout << "Search Results: " << endl;


        if (invertedIndex.empty()) {
            cout << "No matching words found." << endl;
        } else {
            cout << "Select from the following: " << endl;

            for(auto it = invertedIndex.cbegin(); it != invertedIndex.cend(); ++it)
            {
                std::cout << it->first << ": " << it->second.key << "\n";
            }

            cout << "Insert number to select word " << endl;
            cin >> choice;
            userWord = invertedIndex.find(choice)->second.key;

            if (AVL_Retrieve(userWord, found)){
                cout << "Word <" << found.key << ">" << " appears in the following files: " <<  endl;
                for (const std::string& x: found.fileName) std::cout << x << endl;
                break;
            }
        }


        cout << userWord;

    } while (userInput != "#");

}

void AvlChild ::AVL_printInvertedRange(NODE<DATA> *root, string a, string b){

    if (root == NULL) return;

    if (a < root->data.key)
        AVL_printInvertedRange(root->left, a, b);

    if (a <= root->data.key && b > root->data.key){
        mapIndex++;
        invertedIndex.insert(pair<int,DATA>(mapIndex, root->data));
    }

    if (b > root->data.key)
        AVL_printInvertedRange(root->right, a, b);

}

#endif //DSAASSIGNMENT2_AVL_ADTCHILD_H
