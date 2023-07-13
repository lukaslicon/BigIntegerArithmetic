/*********************************************************************************
* Lukas Licon, llicon
* 2023 Winter CSE101 PA#6
* List.cpp
* 03/3/2023
* Implementation file for List ADT
*********************************************************************************/

#include <iostream>
#include <iomanip>
#include "List.h"

//  -------------------------------------------------------- Private Constructor --------------------------------------------------------
//Node Constructor
List::Node::Node(ListElement x){
    data = x;
    next = nullptr;
    prev = nullptr;
}

//  -------------------------------------------------------- Class Constructors & Destructors -------------------------------------------
//NewList() basically in an empty state
List::List(){
    frontDummy = new Node(0);
    backDummy = new Node(1);
    frontDummy->next = backDummy;
    backDummy->prev = frontDummy;
    beforeCursor = frontDummy;
    afterCursor = backDummy;
    pos_cursor = 0;
    num_elements = 0;
}
//Copy Constructor
List::List(const List& L){
    frontDummy = new Node(0);
    backDummy = new Node(1);
    frontDummy->next = backDummy;
    backDummy->prev = frontDummy;
    beforeCursor = frontDummy;
    afterCursor = backDummy;
    pos_cursor = 0;
    num_elements = 0;
    Node* temp = L.frontDummy->next;
    while (temp != L.backDummy) {
        this->insertBefore(temp->data);
        temp = temp->next;
    }
    this->moveFront();
}
//Destructor
List::~List(){
    clear();
    delete(frontDummy);
    delete(backDummy);
}

// -------------------------------------------------------- Access functions --------------------------------------------------------

int List::length() const{
  return num_elements;
}

// front()
// Returns the front element in this List.
// pre: length()>0
ListElement List::front() const{
    return frontDummy->data;
}

// back()
// Returns the back element in this List.
// pre: length()>0
ListElement List::back() const{
    return backDummy->data;
}


// position()
// Returns the position of the cursor in this List. The value returned
// will be in the range 0 to size().

int List::position() const{
    return pos_cursor;
}

// peekNext()
// Returns the element after the cursor.
// pre: position()<size()
ListElement List::peekNext() const{
    if (position() >= num_elements){
        std::cerr << "Error: cannot call peekNext(), no next element" << std::endl;
        exit(EXIT_FAILURE);
    }
    else
        return afterCursor->data;
}
// peekPrev()
// Returns the element before the cursor.
// pre: position()>0

ListElement List::peekPrev() const{
    if (position() <= 0){
        std::cerr << "Error: cannot call peekPrev(), no prev element" << std::endl;
        exit(EXIT_FAILURE);
    }
    else
        return beforeCursor->data;
}
// ----------------------------------------------------- Manipulation procedures -------------------------------------------------

// clear()
// Deletes all elements in this List, setting it to the empty state.
void List::clear(){
    this->moveFront();
    while (num_elements != 0) {
        this->eraseAfter();
    }
}

// moveFront()
// Moves cursor to position 0 in this List.
// clear()
// Deletes all elements in this List, setting it to the empty state.
void List::moveFront(){
    pos_cursor = 0;
    afterCursor = frontDummy->next;
    beforeCursor = frontDummy;
}

// moveBack()
// Moves cursor to position size() in this List.
void List::moveBack(){
    pos_cursor = num_elements; //moves cursor to last position
    afterCursor = backDummy;
    beforeCursor = backDummy->prev;
}

// moveNext()
// Advances cursor to next higher position. Returns the List element that
// was passed over. 
// pre: position()<size() 
ListElement List::moveNext(){
    if (position() >= num_elements) {
        std::cerr << "Error: cannot call moveNext() on no next element" << std::endl;
        exit(EXIT_FAILURE);
    }
    beforeCursor = afterCursor;
    afterCursor = beforeCursor->next;
    pos_cursor++;
    return beforeCursor->data;
}

// movePrev()
// Advances cursor to next lower position. Returns the List element that
// was passed over. 
// pre: position()>0
ListElement List::movePrev(){
    if (pos_cursor <= 0){
        std::cerr << "Error: cannot call movePrev() on no prev element" << std::endl;
        exit(EXIT_FAILURE);
    }
    afterCursor = beforeCursor;
    beforeCursor = afterCursor->prev;
    pos_cursor--;
    return afterCursor->data;
}

// insertAfter()
// Inserts x after cursor.
void List::insertAfter(ListElement x){
    Node* nodeTemp = new Node(x);
    nodeTemp->prev = beforeCursor;
    nodeTemp->next = afterCursor;
    beforeCursor->next = nodeTemp;
    afterCursor->prev = nodeTemp;
    afterCursor = nodeTemp;
    num_elements++;
}

// insertBefore()
// Inserts x before cursor.
void List::insertBefore(ListElement x){
     Node* nodeTemp = new Node(x);
     nodeTemp->prev = beforeCursor;
     nodeTemp->next = afterCursor;
     beforeCursor->next = nodeTemp;
     afterCursor->prev = nodeTemp;
     beforeCursor = nodeTemp;
     num_elements++;
     pos_cursor++;
}

//setAfter()
//Overwrites the list element after the cursor with x
//pre: position < length
void List::setAfter(ListElement x) {
    if (position() > length()) {
        throw std::length_error("List(): setAfter(): Position() > Length()");
    }
    if (afterCursor == backDummy) {
        throw std::range_error("List(): setAfter(): Error, trying to set element of a non-existing node");
    }
    afterCursor->data = x;
}

 //setBefore()
 //Overwrites the list element before the cursor with x
 //pre: position > 0
void List::setBefore(ListElement x) {
    if (position() < 0) {
        throw std::length_error("List(): setBefore(): Position() < 0");
    }
    if (beforeCursor == frontDummy) {
        throw std::range_error("List(): setBefore(): Error, trying to set element of a non-existing node");
    }
    beforeCursor->data = x;
}


// eraseAfter()
// Deletes element afterCursor.
// pre: position()<size()
void List::eraseAfter(){
    if (position() >= num_elements) {
        std::cerr << "Error: cannot call eraseAfter(),no element after last." << std::endl;
        exit(EXIT_FAILURE);
    }
    Node* nodeTemp;
    nodeTemp = afterCursor;
    afterCursor = afterCursor->next;
    beforeCursor->next = afterCursor;
    afterCursor->prev = beforeCursor;
    delete nodeTemp;
    num_elements--;
}

// eraseBefore()
// Deletes element beforeCursor.
// pre: position()>0
void List::eraseBefore(){
    if (pos_cursor <= 0){
        std::cerr << "Error: cannot call eraseBefore(), no element before." << std::endl;
        exit(EXIT_FAILURE);
    }
    Node* nodeTemp;
    nodeTemp = beforeCursor;
    beforeCursor = beforeCursor->prev;
    beforeCursor->next = afterCursor;
    afterCursor->prev = beforeCursor;
    delete nodeTemp;
    pos_cursor--;
    num_elements--;
}

// ----------------------------------------------------- Other Functions ---------------------------------------------------------
// findNext()
// Starting from the current cursor position, performs a linear search (in 
// the direction front-to-back) for the first occurrence of the element x.
// If x is found, places the cursor immediately after the found element (so 
// eraseBefore() would remove the found element), and returns the final 
// cursor position. If x is not found, places the cursor at position size(),
// and returns -1. 
int List::findNext(ListElement x){
    while (afterCursor != backDummy) {
        if (afterCursor->data == x) {
            this->moveNext();
            return position();
        }
        this->moveNext();
    }
    return -1;
}

// findPrev()
// Starting from the current cursor position, performs a linear search (in 
// the direction back-to-front) for the first occurrence of the element x.
// If x is found, places the cursor immediately before the found element (so 
// eraseAfter() would remove the found element), and returns the final 
// cursor position. If x is not found, places the cursor at position 0, and 
// returns -1. 
int List::findPrev(ListElement x){
    while (beforeCursor != frontDummy) {
        if (beforeCursor->data == x) {
            this->movePrev();
            return position();
        }
        this->movePrev();
    }
    return -1;
}

// cleanup()
// Removes any repeated elements in this List, leaving only unique data
// values. The order of the remaining elements is obtained by retaining
// the frontmost occurrance of each element, and removing all other 
// occurances. The cursor is not moved with respect to the retained 
// elements, i.e. it lies between the same two retained elements that it 
// did before cleanup() was called.
void List::cleanup(){
    Node* tempBef = beforeCursor;
    Node* tempAft = afterCursor;
    int* arrayTemp = new int[num_elements];
    int cursor = pos_cursor;
    int index = 0;
    int tempD; //needed
    bool check = false;
    for (int i = 0; i < num_elements; i++)
        arrayTemp[i] = 0;
    moveFront();
    while (pos_cursor != length()) {
        check = false;
        tempD = afterCursor->data;
        for (int i = 0; i < index; i++) {
            if (afterCursor->data == arrayTemp[i]) {
                if (pos_cursor < cursor) {
                    cursor--;
                }
                if (afterCursor == tempBef) {
                    tempBef = tempBef->prev;
                }
                else if (afterCursor == tempAft) {
                    tempAft = tempAft->next;
                }
                check = true;
                break;
            }   
        }
        if (check == true)
            eraseAfter();
        else
            moveNext();

        arrayTemp[index] = tempD;
        index++;
    }
    pos_cursor = cursor;
    beforeCursor = tempBef;
    afterCursor = tempAft;
    delete[] arrayTemp;
}


// concat()
// Returns a new List consisting of the elements of this List, followed
// the elements of L. The returned List's cursor will be at its front
// (position 0).
List List::concat(const List& L) const{
    List conC;
    Node* nodeTemp1 = this->frontDummy->next;
    Node* nodeTemp2 = L.frontDummy->next;
    while (nodeTemp1 != this->backDummy) {
        conC.insertBefore(nodeTemp1->data);
        nodeTemp1 = nodeTemp1->next;
    }
    while (nodeTemp2 != L.backDummy) {
        conC.insertBefore(nodeTemp2->data);
        nodeTemp2 = nodeTemp2->next;
    }
    conC.moveFront();
    return conC;
}


// to_string()
// Returns a string representation of this List consisting of a comma 
// separated sequence of elements, surrounded by parentheses.
std::string List::to_string() const{
    Node* nodeTemp = nullptr;
    std::string tempString = "(";

    for (nodeTemp = frontDummy->next; nodeTemp != backDummy->prev; nodeTemp = nodeTemp->next) {
        tempString += std::to_string(nodeTemp->data) + ", ";
    }
    tempString += std::to_string(nodeTemp->data);
    tempString += ")";
    return tempString;
}


// equals()
// Returns true if and only if this List is the same integer sequence as R.
// The cursors in this List and in R are unchanged.
bool List::equals(const List& R) const{
    bool eQ = false;
    Node* eq1 = nullptr;
    Node* eq2 = nullptr;
    eQ = (this->num_elements == R.num_elements);
    eq1 = this->frontDummy->next;
    eq2 = R.frontDummy->next;
    while (eQ && eq1 != this->backDummy) {
        eQ = (eq1->data == eq2->data);
        eq1 = eq1->next;
        eq2 = eq2->next;
    }
    return eQ;
}
//  ----------------------------------------------------- Overriden Operators -----------------------------------------------------


// operator=()
// Overwrites the state of this List with state of L.
List& List::operator=(const List& L){
    if (this != &L) {
        List temp = L;
        std::swap(this->frontDummy, temp.frontDummy);
        std::swap(this->backDummy, temp.backDummy);
        std::swap(num_elements, temp.num_elements);
    }
    return *this;
}

// operator<<()
// Inserts string representation of L into stream.
std::ostream& operator<<(std::ostream& stream, List& L){
    return stream << L.List::to_string();
}

// operator==()
// Returns true if and only if A is the same integer sequence as B. The 
// cursors in both Lists are unchanged are unchanged.
bool operator==(const List& A, const List& B){
    return A.List::equals(B);
}