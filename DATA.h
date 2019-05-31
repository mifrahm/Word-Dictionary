//
// Created by Mifrah Mahroof on 21/5/19.
//

#include <unordered_set>

#ifndef DSAASSIGNMENT2_DATA_H
#define DSAASSIGNMENT2_DATA_H


struct DATA
{
    static int count;
    string key;
    int frequency;
    double score;
    string newFile;
    unordered_set<string> fileName;

    DATA(){
        count++;
    }
};

int DATA::count = 0;


#endif //DSAASSIGNMENT2_DATA_H
