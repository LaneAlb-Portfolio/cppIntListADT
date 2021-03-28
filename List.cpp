/*
* Lane Albrecht, ltalbrec
* 2021 Winter CSE 101 pa4
* List.cpp
* Implementation file for List ADT
*/

#include"List.h"
#include<iostream>
#include<string>

using namespace std;

// Private Constructor  ----------------------------------------------------

// Node Constructor
List::Node::Node(int x){
    data = x;
    next = nullptr;
    prev = nullptr;
};

// Class Constructors & Destructors ----------------------------------------

// Creates new List in the empty state.
List::List(){
    frontDummy = new Node(SENTINEL_VAL);
    backDummy = new Node(SENTINEL_VAL);
    frontDummy->next = backDummy;
    backDummy->prev = frontDummy;
    beforeCursor = afterCursor = frontDummy;
    pos_cursor = 0;
    num_elements = 0;
};

// Copy constructor.
List::List(const List& L){
    frontDummy = new Node(SENTINEL_VAL);
    backDummy = new Node(SENTINEL_VAL);
    frontDummy->next = backDummy;
    backDummy->prev = frontDummy;
    beforeCursor = afterCursor = frontDummy;
    pos_cursor = 0;
    num_elements = 0;

    // copy from L
    Node* T = L.frontDummy->next;
    while(T != L.backDummy){
        insertAfter(T->data);
        moveNext();
        T = T->next;
    }
    //reset cursor pos
    moveFront();
};

// Destructor
List::~List(){
    if(num_elements > 0){
        clear();
    }
    //delete dummy nodes
    delete(frontDummy);
    delete(backDummy);
};

// Access functions --------------------------------------------------------

// isEmpty()
// Returns true if this List is empty, false otherwise.
bool List::isEmpty(){
    return(this->num_elements == 0);
};

// size()
// Returns the size of this List.
int List::size(){
    return(this->num_elements);
};

// position()
// Returns the position of the cursor in this List. The value returned
// will be in the range 0 to size().
int List::position(){
    return(this->pos_cursor);
};

// Manipulation procedures -------------------------------------------------

// moveFront()
// Moves cursor to position 0 in this List.
void List::moveFront(){
    pos_cursor = 0;
    beforeCursor = frontDummy;
    afterCursor = frontDummy->next;
};

// moveBack()
// Moves cursor to position size() in this List.
void List::moveBack(){
    pos_cursor = num_elements;
    beforeCursor = backDummy->prev;
    afterCursor = backDummy;
};

// peekNext()
// Returns the element after the cursor.
// pre: position()<size()
int List::peekNext(){
    if(this->pos_cursor == this->num_elements){
        cerr << "List Error: calling peekNext() with cursor position == size()" << endl;
        exit(EXIT_FAILURE);
    }
    return(this->afterCursor->data);
};

// peekPrev()
// Returns the element before the cursor.
// pre: position()>0
int List::peekPrev(){
    if(this->pos_cursor == 0){
        cerr << "List Error: calling peekPrev() with cursor position at 0" << endl;
        exit(EXIT_FAILURE);
    }
    return(this->beforeCursor->data);
};  

// moveNext()
// Advances cursor to next higher position. Returns the List element that
// was passed over. 
// pre: position() < size() 
int List::moveNext(){
    if(this->pos_cursor == this->num_elements){
        cerr << "List Error: calling moveNext() with cursor position == size()" << endl;
        exit(EXIT_FAILURE);
    }
    pos_cursor++;
    afterCursor = afterCursor->next;
    beforeCursor = beforeCursor->next;
    return beforeCursor->data;
};

// movePrev()
// Advances cursor to next lower position. Returns the List element that
// was passed over. 
// pre: position()>0
int List::movePrev(){
    if(this->pos_cursor == 0){
        cerr << "List Error: calling movePrev() with cursor position at 0" << endl;
        exit(EXIT_FAILURE);
    }
    pos_cursor--;
    afterCursor = afterCursor->prev;
    beforeCursor = beforeCursor->prev;
    return afterCursor->data;
};

// insertAfter()
// Inserts x after cursor.
void List::insertAfter(int x){
    Node* T = new Node(x);
    // check if first insert
    if (frontDummy->next == backDummy) {
        afterCursor = T;
        frontDummy->next = T;
        T->prev = frontDummy;
        T->next = backDummy;
        backDummy->prev = T;
        num_elements++;
        return;
    }
    //setup node links
    T->prev = beforeCursor;
    T->next = afterCursor;
    beforeCursor->next = T;
    afterCursor->prev = T;
    //keep afterCursor after the cursor position
    afterCursor = T;
    num_elements++;
};

// insertBefore()
// Inserts x before cursor.
void List::insertBefore(int x){
    Node* T = new Node(x);
    // check if first insert
    if (frontDummy->next == backDummy) {
        beforeCursor = T;
        afterCursor = backDummy;
        frontDummy->next = T;
        T->prev = frontDummy;
        T->next = backDummy;
        backDummy->prev = T;
        num_elements++;
        pos_cursor++;
        return;
    }
    //setup node links
    T->prev = beforeCursor;
    T->next = afterCursor;
    beforeCursor->next = T;
    afterCursor->prev = T;
    //keep afterCursor after the cursor position
    beforeCursor = T;
    num_elements++;
    pos_cursor++;
};

// eraseAfter()
// Deletes element after cursor.
// pre: position() < size()
void List::eraseAfter(){
    if(this->pos_cursor == this->num_elements){
        cerr << "List Error: calling eraseAfter() with cursor position == size()" << endl;
        exit(EXIT_FAILURE);
    }
    Node* T = afterCursor;
    afterCursor = afterCursor->next;
    afterCursor->prev = beforeCursor;
    beforeCursor->next = afterCursor;
    num_elements--;
    delete(T);
};

// eraseBefore()
// Deletes element before cursor.
// pre: position()>0
void List::eraseBefore(){
    if(this->pos_cursor == 0){
        cerr << "List Error: calling eraseBefore() with cursor position at 0" << endl;
        exit(EXIT_FAILURE);
    }
    Node* T = beforeCursor;
    beforeCursor = beforeCursor->prev;
    afterCursor->prev = beforeCursor;
    beforeCursor->next = afterCursor;
    num_elements--;
    pos_cursor--;
    delete(T);
};

// findNext()
// Starting from the current cursor position, performs a linear search (in 
// the direction front-to-back) for the first occurrence of the element x.
// If x is found, places the cursor immediately after the found element (so 
// eraseBefore() would remove the found element), and returns the final 
// cursor position. If x is not found, places the cursor at position size(),
// and returns -1. 
int List::findNext(int x){
    int found = -1;
    int curse = (pos_cursor == 0) ? size() : pos_cursor-1; //variable for checking search completed

    while(pos_cursor != curse && x != found)
    {
        if(pos_cursor == size()) //&& pos_cursor != curse) // dont loop back to the front if we need to stop
            break;
            //moveFront();
        else
            found = moveNext();
    }
    // if cursor has looped back to curse, x wasn't found
    if(pos_cursor == size()){
        moveBack();
        return -1;
    } else {
        return pos_cursor;
    }
};

// findPrev()
// Starting from the current cursor position, performs a linear search (in 
// the direction back-to-front) for the first occurrence of the element x.
// If x is found, places the cursor immediately before the found element (so 
// eraseAfter() would remove the found element), and returns the final 
// cursor position. If x is not found, places the cursor at position 0, and 
// returns -1. 
int List::findPrev(int x){
    int found = -1;
    int curse = (pos_cursor == size()) ? 0 : pos_cursor+1; //variable for checking search completed

    while(pos_cursor != curse && x != found)
    {
        if(pos_cursor == 0) //&&pos_cursor != curse) // dont loop to the back if we need to stop
            break;
            //moveBack();
        else
            found = movePrev();
    }
    // if Temp has looped back to its original position, x wasn't found
    if(pos_cursor == 0){
        moveFront();
        return -1;
    } else {
        return pos_cursor;
    }
};

// cleanup()
// Removes any repeated elements in this List, leaving only unique data
// values. The order of the remaining elements is obtained by retaining
// the frontmost occurrance of each element, and removing all other 
// occurances. The cursor is not moved with respect to the retained 
// elements, i.e. it lies between the same two retained elements that it 
// did before cleanup() was called.
void List::cleanup(){
    Node* searcher = nullptr;
    int x = -1;
    int count = 1;
    int origin = (position() == 0) ? 0 : position();
    int delBefore = 0; //count of how many elements are deleted before original cursor position
    for(searcher = frontDummy->next; searcher != backDummy; searcher = searcher->next){
        x = searcher->data;
        for(moveFront(); position() < count; moveNext()){} // move cursor until after our unique set of elements
        
        while(position() < size())
        {  // iterate across rest of list to search and destroy
            if(moveNext() == x){
                eraseBefore();
                if(position() <= origin)
                    delBefore++;
            }
        }
        count++;
    }
    if(origin != 0){
        for(moveFront(); ( position() < (origin-delBefore)+1 ) && ( position() < size() ); moveNext()); //move cursor back to proper position / END of list
    } else
        moveFront();
};

// clear()
// Deletes all elements in this List, setting it to the empty state.
void List::clear(){
    //if (isEmpty()){
    //    cerr << "List Error: calling clear() on an empty List" << endl;
    //    exit(EXIT_FAILURE);
    //}
    moveFront();
    while (!isEmpty()){
        eraseAfter();
    }
    // now empty list besides sentinels
};

// concat()
// Returns a new List consisting of the elements of this List, followed
// the elements of L. The returned List's cursor will be at its front
// (position 0).
List List::concat(const List& L){
    List C;
    Node* T = frontDummy->next;
    Node* N = L.frontDummy->next;
    while(T != backDummy){
        C.insertBefore(T->data);
        T = T->next;
    }
    while(N != L.backDummy){
        C.insertBefore(N->data);
        N = N->next;
    }
    C.moveFront();
    return C;
};


// Other Functions ---------------------------------------------------------

// to_string()
// Returns a string representation of this List consisting of a comma 
// separated sequence of elements, surrounded by parentheses.
std::string List::to_string(){
    Node* T = nullptr;
    string s = "";

    for(T = frontDummy->next; T != backDummy; T = T->next){
        s+= std::to_string(T->data)+" ";
    }
    return s;
};

// equals()
// Returns true if and only if this List is the same integer sequence as R.
// The cursors in this List and in R are unchanged.
bool List::equals(const List& R){
    bool e = false;
    Node* T = nullptr;
    Node* N = nullptr;

    e = (this->num_elements == R.num_elements) ? true : false;
    T = this->frontDummy;
    N = R.frontDummy;

    while (e && T!= nullptr){
        e = (T->data == N->data) ? true : false;
        T = T->next;
        N = N->next;
    }
    return e;
};


// Overriden Operators -----------------------------------------------------
   
// operator<<()
// Inserts string representation of L into stream.
std::ostream& operator<<( std::ostream& stream, List& L ){
    return stream << L.List::to_string();
};

// operator==()
// Returns true if and only if A is the same integer sequence as B. The 
// cursors in both Lists are unchanged are unchanged.
bool operator==( List& A, const List& B ){
    return A.List::equals(B);
};

// operator=()
// Overwrites the state of this List with state of L.
List& List::operator=( const List& L ){
    if(this != &L) {
        List temp = L;

        std::swap(frontDummy, temp.frontDummy);
        std::swap(backDummy, temp.backDummy);
        std::swap(num_elements, temp.num_elements);
        std::swap(pos_cursor, temp.pos_cursor);
        std::swap(beforeCursor, temp.beforeCursor);
        std::swap(afterCursor, temp.afterCursor);
    }
    return *this;
};
