/*
* Lane Albrecht, ltalbrec
* 2021 Winter CSE 101 pa4
* ListTest.cpp
* X test client for List ADT
*/

#include<iostream>
#include<string>
#include"List.h"

using namespace std;

int main(){
    //ENTER PERSONAL TESTING
    List L = List();
    cout << "Created" << endl;
    // isEmpty()
    if (L.isEmpty()) {cout << "Empty" << endl;}
    // Size()
    cout << "Size == " << L.size() << endl;
    // Position()
    cout << "Cursor Pos == " << L.position() << endl;
    // insert and move cursor
    cout << "Insert 1" << endl;
    L.insertAfter(1);
    cout << "Moving Cursor behind 1" << endl;
    L.moveNext();
    cout << "Cursor at : " << L.position() << endl;
    // insert multiple after
    for(int i = 2; i < 10; i++){
        L.insertAfter(i);
    }
    cout << "Populated List : ";
    cout << L.to_string() << endl;
    // delete 9 - 3
    cout << "Delete all above 2" << endl;
    for(int i = 1; i < 8; i++){
        L.eraseAfter();
    }
    cout << "List is now: ";
    cout << L.to_string() << endl;
    //Copy and then insert before to get ordered version of list 1.0
    List Z = List(L);
    cout << "List Z is now: ";
    cout << Z.to_string() << endl;
    // isEmpty()
    if (Z.isEmpty()) {cout << "Empty" << endl;}
    // Size()
    cout << "Size == " << Z.size() << endl;
    // Position()
    cout << "Cursor Pos == " << Z.position() << endl;
    cout << "Z will now Grow..." << endl;
    Z.moveBack();
    for(int i = 3; i < 11; i++){
        Z.insertBefore(i);
    }
    cout << "List Z is now: ";
    cout << Z.to_string() << endl;
    // peek and cursor test
    cout << "Time to peek at Z a bunch" << endl;
    Z.moveFront();
    Z.moveNext();
    cout << "Cursor at 1 == "<< Z.position() << endl << endl;
    cout << "Cursor Peek Chart" << endl << "Y: Z | X "<< endl;
    for(int i = 0; i < Z.size()-1;i++){
        cout << (i+1) << ": " << Z.peekPrev() << " " << Z.peekNext() << endl;
        Z.moveNext();
    }

    // concat and compare list test
    cout << "List Y & W created from Empty List and Z & Z from Empty" << endl;
    List X = List();
    List Y = Z.concat(X);
    List W = X.concat(Z);
    cout << "Y and W should be the same" << endl << endl;
    cout << "List Y is: " << Y.to_string() << endl;
    cout << "List W is: " << W.to_string() << endl;
    cout << "Therefore ";
    if (Y == W)
        cout << "They are the same" << endl;
    else
        cout << "NOT the same"<< endl;

    cout << "However I just created List V differnt from V and W by deleting '2'" << endl;
    List V = W;
    V.moveFront();
    V.moveNext();
    V.eraseAfter();
    cout << "List V is: " << V.to_string() << endl;
    cout << "Therefore ";
    if ((V == W))
        cout << "They are the same" << endl;
    else
        cout << "NOT the same"<< endl;
    // finding tests
    //Z.moveFront();
    int ff = 2;
    cout << endl << "Time to Find stuff in V and Z" << endl;
    cout << "List Z is: " << Z.to_string() << endl;
    cout << "List V is: " << V.to_string() << endl;
    cout << "FindNext 2 in Z: " << Z.findNext(ff) << endl;
    Z.eraseBefore();
    cout << "FindPrev the just deleted 2 in Z: " << Z.findPrev(ff) << endl;
    //Z.eraseAfter();
    cout << "V does not have 2 so -1 should exist" << endl;
    cout << "FindNext 2 in V: " << V.findNext(ff) << endl;
    cout << "FindPrev 2 in V: " << V.findPrev(ff) << endl;
    cout << "Now Z and V should be the same.. 1 iff True: " << (Z == V) << endl;
    cout << "List Z is: " << Z.to_string() << endl;
    cout << "List V is: " << V.to_string() << endl;
    //insert repeated values and cleanup
    for(int i = 0; i < 3; i++){
        Z.insertAfter(ff);
        Z.insertBefore(ff);
        V.insertAfter(ff);
    }
    cout << "List Z is: " << Z.to_string() << endl;
    cout << "List V is: " << V.to_string() << endl;
    cout << "Deleting the Repeated Elements" << endl;
    Z.cleanup();
    cout << "List Z is: " << Z.to_string() << "Which is NOT the same as List V: " << (Z == V) << endl;
    V.cleanup();
    cout << endl << "Z and V have no repeating elements now and are the same!" << endl;
    cout << "List Z is: " << Z.to_string() << endl;
    cout << "List V is: " << V.to_string() << endl;
    cout << "TRUE is 1 == " << (Z == V) << endl;
    //PERSONAL TESTING END
    // ENTERING PROVIDED LIST CLIENT TESTS
    cout << endl << "ENTERING LISTCLIENT OUTPUT" << endl << endl;
    int i;
    List A, B, C, D, E;

    for(i=1; i<=10; i++){
       A.insertAfter(i);
       B.insertAfter(11-i);
       C.insertBefore(i);
       D.insertBefore(11-i);
    }

    cout << endl;
    cout << "A = " << A << endl;
    cout << "A.position() = " << A.position() << endl;
    cout << "B = " << B << endl;
    cout << "B.position() = " << B.position() << endl;
    cout << "C = " << C << endl;
    cout << "C.position() = " << C.position() << endl;
    cout << "D = " << D << endl;
    cout << "D.position() = " << D.position() << endl;
    cout << endl;

    A.moveBack();
    B.moveBack();
    C.moveFront();
    D.moveFront();
 
    cout << "A = " << A << endl;
    cout << "A.position() = " << A.position() << endl;
    cout << "B = " << B << endl;
    cout << "B.position() = " << B.position() << endl;
    cout << "C = " << C << endl;
    cout << "C.position() = " << C.position() << endl;
    cout << "D = " << D << endl;
    cout << "D.position() = " << D.position() << endl;

    cout << endl << "B: ";
    for(i=1; i<=7; i++){
       cout << B.movePrev() << " ";
    }
    cout << endl << "B.position() = " << B.position() << endl;
   
    cout << endl << "C: ";
    for(i=1; i<=7; i++){
       cout << C.moveNext() << " ";
    }
    cout << endl << "C.position() = " << C.position() << endl;

    cout << endl;
    cout << "A==B is " << (A==B?"true":"false") << endl;
    cout << "B==C is " << (B==C?"true":"false") << endl;
    cout << "C==D is " << (C==D?"true":"false") << endl;
    cout << "D==A is " << (D==A?"true":"false") << endl;
    cout << endl;

    cout << B.findNext(5) << endl;
    cout << B << endl;
    B.eraseBefore();
    B.eraseAfter();
    cout << B << endl;
    cout << B.position() << endl;
    cout << B.findPrev(2) << endl;
    B.eraseBefore();
    B.eraseAfter();
    cout << B << endl;
    cout << B.position() << endl;
    cout << B.findNext(20) << endl; 
    cout << B.position() << endl;
    cout << B.findPrev(20) << endl;
    cout << B.position() << endl;
    cout << endl;

    for( i=10; i>=1; i--){
       A.insertAfter(i);
       A.movePrev();
    }
    cout << "A = " << A << endl;
    for( i=1; i<=15; i++){
       A.moveNext();
    }
    cout << A.position() << endl;
    A.cleanup();
    cout << "A = " << A << endl;
    cout << A.position() << endl;
    cout << endl;

    E = A;
    cout << "E==A is " << (E==A?"true":"false") << endl;
    List F;
    F = A.concat(B);
    A = A;
    cout << endl;

    cout << "A = " << A << endl;
    cout << "B = " << B << endl;
    cout << "C = " << C << endl;
    cout << "D = " << D << endl;
    cout << "E = " << E << endl;
    cout << "F = " << F << endl;
    //cleanup position test
    B.clear();
    B.insertBefore(1);
    B.insertBefore(2);
    B.insertBefore(2);
    B.insertBefore(1);
    B.insertBefore(2);
    B.insertBefore(3);
    B.insertBefore(1);
    B.findPrev(3);
    B.movePrev();
    B.cleanup();
    cout << B << " Looking for 2: " << B.position() <<endl;
    A.clear();
    A.insertBefore(1);
    A.insertBefore(2);
    A.insertBefore(2);
    A.insertBefore(1);
    A.insertBefore(2);
    A.insertBefore(3);
    A.insertBefore(1);
    A.findPrev(3);
    A.cleanup();
    cout << A << " Looking for 2: " << A.position() <<endl;
    // cleanup equals
    A.clear();
    B.clear();
    A.insertBefore(3);
    A.insertBefore(3);
    A.insertBefore(1);
    A.insertBefore(3);
    A.insertBefore(2);
    A.insertBefore(2);
    A.insertBefore(1);
    A.insertBefore(4);
    B.insertBefore(3);
    B.insertBefore(1);
    B.insertBefore(2);
    cout << "A: " << A << endl << "B: " << B << endl;
    if (A.equals(B)) cout << 1;

    A.cleanup();
    cout << "A: " << A << endl;
    if (A.equals(B)) cout << 2;

    A.moveBack();
    A.eraseBefore();
    cout << "A: " << A << endl;
    if (!A.equals(B)) cout << 3;

    cout << endl << "Auto Destroy" << endl;
    return 0;
}