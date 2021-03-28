/*
* Lane Albrecht, ltalbrec
* 2021 Winter CSE 101 pa4
* Shuffle.cpp
* 
*/

#include"List.h"
#include<iostream>
#include<fstream>
#include<string>
#include<iomanip>

using namespace std;

void shuffle(List& D);

int main(int argc, char* argv[]){
    ofstream out;
    string line = "-";
    List deck = List();
    List comp;
    int count = 1;
    int width = 16;
    int size;

    // check command line inputs
    if (argc != 2){
        cerr << "Usage: " << argv[0] << "Positive Integer" << endl;
        return(EXIT_FAILURE);
    }
    // open file for writing
    //out.open(argv[2]);
    //if (!out.is_open()){
    //    cerr << "Unable to open file" << argv[2] << " for writing" << endl;
    //    return(EXIT_FAILURE);
    //}

    // get desired deck size
    size = atoi(argv[1]);
    if (size < 0) {
        cerr << "Usage: " << argv[0] << "Positive Integer <output file>" << endl;
        return(EXIT_FAILURE);
    }

    // setup output file header
    cout << setw(width);
    cout << left << "deck size";
    cout << right << "shuffle count" << endl;
    for(int i = 1; i <= 30; i++) 
        cout << line;
    cout << endl;
    //out << setw(width+1);
    // fill the deck
    for(int i = 0; i < size; i++) {
        deck.insertBefore(i);
        comp = deck;
        shuffle(deck);
        // check how many shuffles are needed then setup output
        while(!comp.equals(deck)){
            shuffle(deck);
            count++;
        }
        //out << setw(width+1);
        cout << " " << i+1 << setw(width) << count << endl;
        //out << count << endl;
        count = 1; //reset shuffle count
    }

    //close files
    //out.close();
    return(EXIT_SUCCESS);
}

void shuffle(List& D){
    List L = List();
    int half = D.size() / 2;
    bool odd = ((D.size() % 2) > 0);
    D.moveFront();

    for(int i = 0; i < half; i++) {
        L.insertBefore(D.moveNext());
        D.eraseBefore();
    }
    // create shuffled deck D
    L.moveFront();
    for(D.moveFront(); D.position() < D.size(); D.moveNext()) {
        if( (D.position() % 2) != 0)
            D.insertAfter(L.moveNext());
    }
    if(!odd)
        D.insertAfter(L.moveNext());
}