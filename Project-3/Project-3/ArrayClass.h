//
//  ArrayClass.h
//  Project-3
//
//  Created by Max Guerrero on 4/28/15.
//  Copyright (c) 2015 Data Structures. All rights reserved.
//

#ifndef Project_3_ArrayClass_h
#define Project_3_ArrayClass_h
#include <iostream>

using namespace std;

template<typename T>
class ArrayLinkedListRow
{
    
private:
    
    T* info; // store data
    int next; // next node
    int nextEmpty; // next empty slot
    
public:
    
    // Constructor
    ArrayLinkedListRow();
    
    // Constructor (empty row)
    ArrayLinkedListRow(int nextEmpty);
    
    // Constructor
    ArrayLinkedListRow(T info, int next, int nextEmpty);
    
    // Copy Constructor
    ArrayLinkedListRow(const ArrayLinkedListRow& oldRow);
    
    // Destructor
    ~ArrayLinkedListRow();
    
    // Getters
    
    T* getInfo();
    
    int getNext();
    
    int getNextEmpty();
    
    // Setters
    
    void setInfo(T* info);
    
    void setNext(int next);
    
    void setNextEmpty(int nextEmpty);
    
    // Operator Overloading
    
    // Overloaded assignment operator
    void operator =(const ArrayLinkedListRow<T>& r);
    
    // Overloaded ostream operator

    friend ostream& operator <<(ostream& out, ArrayLinkedListRow<T>& row);
};

// Constructor
template <typename T>
ArrayLinkedListRow<T>::ArrayLinkedListRow()
{
    info = NULL; // nothing to point to
    
    next = -2;
    nextEmpty = -1;
}

// Constructor (empty row)
template <typename T>
ArrayLinkedListRow<T>::ArrayLinkedListRow(int nextEmpty)
{
    info = NULL; // nothing to point to
    
    next = -2;
    this->nextEmpty = nextEmpty;
}

// Constructor
template <typename T>
ArrayLinkedListRow<T>::ArrayLinkedListRow(T info, int next, int nextEmpty)
{
    this->info = new T;
    *(this->info) = info;
    
    this->next = next;
    this->nextEmpty = nextEmpty;
}

// Copy Constructor
template <typename T>
ArrayLinkedListRow<T>::ArrayLinkedListRow(const ArrayLinkedListRow& oldRow)
{
    this->info = new T; // allocate new memory
    
    if(oldRow.info == NULL)
    {
        this->info = NULL; // the old pointer is null
    }
    else
    {
        this->info = new T; // allocate new memory
        *(this->info) = *(oldRow.info); // deep copy from the old pointer
    }
    
    this->next = oldRow.next;
    this->nextEmpty = oldRow.nextEmpty;
}


// Destructor
template <typename T>
ArrayLinkedListRow<T>::~ArrayLinkedListRow()
{
    //cout << "deleting" << endl;
    
    if(info != NULL)
    {
        delete info;
        info = NULL;
    }
}

// Getters

template <typename T>
T* ArrayLinkedListRow<T>::getInfo()
{
    return this->info;
}

template <typename T>
int ArrayLinkedListRow<T>::getNext()
{
    return this->next;
}

template <typename T>
int ArrayLinkedListRow<T>::getNextEmpty()
{
    return this->nextEmpty;
}

// Setters

template <typename T>
void ArrayLinkedListRow<T>::setInfo(T* info)
{
    this->info = info;
}

template <typename T>
void ArrayLinkedListRow<T>::setNext(int next)
{
    this->next = next;
}

template <typename T>
void ArrayLinkedListRow<T>::setNextEmpty(int nextEmpty)
{
    this->nextEmpty = nextEmpty;
}

// Operator Overloading

// Overloaded assignment operator
template <typename T>
void ArrayLinkedListRow<T>::operator =(const ArrayLinkedListRow<T>& oldRow)
{
    if(this->info != NULL)
        delete this->info; // delete the old information if it exists
    
    if(oldRow.info == NULL)
    {
        this->info = NULL; // the old pointer is null
    }
    else
    {
        this->info = new T; // allocate new memory
        *(this->info) = *(oldRow.info); // deep copy from the old pointer
    }
    
    this->next = oldRow.next;
    this->nextEmpty = oldRow.nextEmpty;
}

// Overloaded ostream operator
template <typename T>
ostream& operator <<(ostream& out, ArrayLinkedListRow<T>& row)
{
    T infoToDisplay = *(row.info);
    
    out << "Info: " << infoToDisplay << ", Next: " << row.next << ", Next Empty: " << row.nextEmpty;
    
    return out;
}

class LinkedListException :public exception
{
public:
    LinkedListException();
    ~LinkedListException();
    virtual const void exception() = 0;
};
LinkedListException::LinkedListException()
{
    
}

LinkedListException::~LinkedListException()
{
    
}

class LinkedListMemory :public LinkedListException
{
public:
    LinkedListMemory();
    ~LinkedListMemory();
    const void exception();
};

LinkedListMemory::LinkedListMemory()
{
    
}

LinkedListMemory::~LinkedListMemory()
{
    
}

const void LinkedListMemory::exception()
{
    cout << "The linked list is out of memory." << endl;
}

class LinkedListBounds :public LinkedListException
{
public:
    LinkedListBounds();
    ~LinkedListBounds();
    const void exception();
};

LinkedListBounds::LinkedListBounds()
{
    
}

LinkedListBounds::~LinkedListBounds()
{
    
}

const void LinkedListBounds::exception()
{
    cout << "The input is out of bounds." << endl;
}




class LinkedListNotFound :public LinkedListException
{
public:
    LinkedListNotFound();
    ~LinkedListNotFound();
    const void exception();
};

LinkedListNotFound::LinkedListNotFound()
{
    
}

LinkedListNotFound::~LinkedListNotFound()
{
    
}

const void LinkedListNotFound::exception()
{
    cout << "The key was not found in the list." << endl;
}


template <typename T>
class ArrayLinkedList
{
private:
    
    //    T* _info[MAX_SIZE];  // store data
    //    int _next[MAX_SIZE];   // next node
    //    int _nextEmpty[MAX_SIZE];  // next empty slot
    
    LinkedListMemory llm;
    LinkedListBounds llb;
    LinkedListNotFound llnf;
    
    static const int defaultListSize = 100;
    
    Vector<ArrayLinkedListRow<T>>* rows;
    
    int head; // head of the list, -1 if empty
    int firstEmpty; // first empty slot, -1 if none
    int size; // nodes in the list
    
    // Private Methods
    
    // Copy from another List
    void copy(const ArrayLinkedList<T>& oldList);
    
    // add a new node with next as it's next node and returns the index of new node
    int newNode(T& newObject, int next);
    
    // Gets the index in the Vector of a row at a certain position in the list
    int getIndexOfRowAtPosition(int position);
    
public:
    
    // Constructor
    ArrayLinkedList();
    
    // Constructor (float is used to remove constructor ambiguity)
    ArrayLinkedList(float floatCapacity);
    
    // Constructor
    ArrayLinkedList(T& newObject);
    
    // Constructor
    ArrayLinkedList(T& newObject , int capacity);
    
    // Copy Constructor
    ArrayLinkedList(const ArrayLinkedList<T>& oldList);
    
    // Destructor
    ~ArrayLinkedList();
    
    // Public Methods
    
    // Checks to see if the list is empty
    bool isEmpty();
    
    // Checks to see if the list is full
    bool isFull();
    
    // Adds An object to the tail
    void add(T& newObject);
    
    // Inserts a new row right after the specified position in the list
    void insertAt(T& newObject, int position);
    
    // Removes the head
    T remove();
    
    // Removes the node at the position in the list
    T removeAt(int position);
    
    // Finds the object that matches the key, returns the index of that object or throws a LinkedListNotFound exception
    int find(T key);
    
    // Display raw data of the members
    void displayRaw();
    
    // Display data in Vector row form
    void displayRowForm();
    
    // Getters
    
    // Returns the Vector containing the LinkedListRows
    Vector<ArrayLinkedListRow<T>> getRows();
    
    // Returns the index in the Vector of the head
    int getHead();
    
    // Gets the index in the Vector of the First Empty Node
    int getFirstEmpty();
    
    // Returns the number of nodes in the list
    int getSize();
    
    // Operator Overloading
    
    // overloaded assignment operator
    void operator =(const ArrayLinkedList<T>& oldList);
    
    // Overloaded [] operator. Returns a reference to the object at the specified position
    T& operator [](const int position);
    
    // Ostream Operator. Outputs in format: info(indexInVector) --> ...
   
    friend ostream& operator <<(ostream& out, ArrayLinkedList<T>& list);
};
// Private Methods

// Copy from Another List
template <typename T>
void ArrayLinkedList<T>::copy(const ArrayLinkedList<T>& oldList)
{
    for(unsigned int i=0; i<oldList.rows->getVectorElementCount(); i++) // copies the data over from the old list
    {
        this->rows->add(oldList.rows->getAtIndex(i));
    }
}


// add a new node with next as it's next node and returns the index of new node
template <typename T>
int ArrayLinkedList<T>::newNode(T& newObject, int next)
{
    ArrayLinkedListRow<T> newRow = ArrayLinkedListRow<T>(newObject, next, -2);
    
    rows->replace(firstEmpty, newRow); // insert the new element at the tail
    
    return firstEmpty;
}

// Gets the index in the Vector of a row at a certain position in the list
template <typename T>
int ArrayLinkedList<T>::getIndexOfRowAtPosition(int position)
{
    // The first position in the linked list is position 0.
    // The last position in the linked list is position (size - 1)
    
    int indexOfRowAtPosition = head;
    
    int nextValueAtPosition = rows->getAtIndex(head).getNext();
    
    for(int i=0; i<position; i++) // starts at the head of the list and works through it to find the insertion
    {
        indexOfRowAtPosition = nextValueAtPosition;
        
        nextValueAtPosition = rows->getAtIndex(nextValueAtPosition).getNext();
    }
    
    return indexOfRowAtPosition;
}

// Public Methods

// Constructor
template <typename T>
ArrayLinkedList<T>::ArrayLinkedList()
{
    rows = new Vector<ArrayLinkedListRow<T>>(ArrayLinkedList<T>::defaultListSize); // creates a Vector of default size 100
    
    head = -1; // no head
    firstEmpty = 0; // first spot is empty
    size = 0; // currently an empty list
    
    for(int i=0; i<ArrayLinkedList<T>::defaultListSize; i++)
    {
        if(i < ArrayLinkedList<T>::defaultListSize - 1)
            rows->add(ArrayLinkedListRow<T>(i+1)); // all but tail
        else
            rows->add(ArrayLinkedListRow<T>(-1));
    }
}

// Constructor (float is used to remove constructor ambiguity)
template <typename T>
ArrayLinkedList<T>::ArrayLinkedList(float floatCapacity)
{
    int capacity = (int)floatCapacity;
    
    if(capacity < 1) // illegal capacity
        throw llb;
    
    rows = new Vector<ArrayLinkedListRow<T>>(capacity); // creates a Vector of default size 100
    
    head = -1; // no head
    firstEmpty = 0; // first spot is empty
    size = 0; // currently an empty list
    
    for(int i=0; i<capacity; i++)
    {
        ArrayLinkedListRow<T> row;
        
        if(i < capacity - 1)
            row = ArrayLinkedListRow<T>(i+1); // all but tail
        else
            row = ArrayLinkedListRow<T>(-1); // tail
        
        rows->add(row);
    }
}

// Constructor
template <typename T>
ArrayLinkedList<T>::ArrayLinkedList(T& newObject)
{
    rows = new Vector<ArrayLinkedListRow<T>>(ArrayLinkedList<T>::defaultListSize); // creates a Vector of default size 100
    
    head = -1; // no head
    firstEmpty = 0; // first spot is empty
    size = 0; // currently an empty list
    
    for(int i=0; i<ArrayLinkedList<T>::defaultListSize; i++)
    {
        if(i < ArrayLinkedList<T>::defaultListSize - 1)
            rows->add(ArrayLinkedListRow<T>(i+1)); // all but tail
        else
            rows->add(ArrayLinkedListRow<T>(-1));
    }
    
    add(newObject);
}

// Constructor
template <typename T>
ArrayLinkedList<T>::ArrayLinkedList(T& newObject, int capacity)
{
    if(capacity < 1) // illegal capacity
        throw llb;
    
    rows = new Vector<ArrayLinkedListRow<T>>(capacity); // creates a Vector of default size 100
    
    head = -1; // no head
    firstEmpty = 0; // first spot is empty
    size = 0; // currently an empty list
    
    for(int i=0; i<capacity; i++)
    {
        ArrayLinkedListRow<T> row;
        
        if(i < capacity - 1)
            row = ArrayLinkedListRow<T>(i+1); // all but tail
        else
            row = ArrayLinkedListRow<T>(-1); // tail
        
        rows->add(row);
    }
    
    add(newObject);
}

// Copy Constructor
template <typename T>
ArrayLinkedList<T>::ArrayLinkedList(const ArrayLinkedList<T>& oldList)
{
    this->rows = new Vector<ArrayLinkedListRow<T>>(oldList.rows->getVectorElementCount()); // creates new memory space
    
    copy(oldList); // copies information over
    
    this->head = oldList.head;
    this->firstEmpty = oldList.firstEmpty;
    this->size = oldList.size;
}

// Destructor
template <typename T>
ArrayLinkedList<T>::~ArrayLinkedList()
{
    // cout << "deleting ArrayLinkedList" << endl;
    delete rows;
}

// Public Methods

// Checks to see if the list is empty
template <typename T>
bool ArrayLinkedList<T>::isEmpty()
{
    if(size == 0)
        return true;
    else
        return false;
}

// Checks to see if the list is full
template <typename T>
bool ArrayLinkedList<T>::isFull()
{
    if(firstEmpty == -1)
        return true;
    else
        return false;
}

// Adds an object to the tail (firstEmpty)
template <typename T>
void ArrayLinkedList<T>::add(T& newObject)
{
    insertAt(newObject, size);
}

// Inserts a new row right after the node in the specified position in the list
template <typename T>
void ArrayLinkedList<T>::insertAt(T& newObject, int position)
{
    if(isFull()) // there are no more empty spots
        throw llm;
    else if(position < 0 || position > size) // must be in the range of the available positions
        throw llb;
    
    // Positon = 0 is insert at head
    // Position = size is insert at tail
    // Else, insert it somewhere in the middle
    
    int nextFirstEmpty = rows->getAtIndex(firstEmpty).getNextEmpty(); // sets the index of the new first empty to the next empty slot
    
    if(position == 0) // insert at head
    {
        newNode(newObject, head); // adds a new node that points to the old head
        
        head = firstEmpty; // new node is the new head
    }
    else if(position == size) // insert at tail
    {
        int tail = getIndexOfRowAtPosition(size - 1); // finds the index of the current tail
        
        rows->getRefAtIndex(tail).setNext(firstEmpty); // changes the previous tail to point at the new tail
        
        newNode(newObject, -1); // adds a new node at firstEmpty location
    }
    else // somewhere in the middle
    {
        int indexOfRowAtPosition = getIndexOfRowAtPosition(position - 1); // insert to the right of this position
        
        int nextIndexAtPosition = rows->getAtIndex(indexOfRowAtPosition).getNext(); // stores the next index for a given position
        
        rows->getRefAtIndex(indexOfRowAtPosition).setNext(firstEmpty); // changes the node at the position to point to the new node
        
        newNode(newObject, nextIndexAtPosition); // inserts a new node that points to the next node in the list
    }
    
    firstEmpty = nextFirstEmpty; // assigns to the new empty slot
    
    ++size; // a node was added
}

// Removes the head and returns the value at that row
template <typename T>
T ArrayLinkedList<T>::remove()
{
    return removeAt(0);
}

// Removes the node at the position in the list
template <typename T>
T ArrayLinkedList<T>::removeAt(int position)
{
    if(isEmpty()) // if there are no nodes to remove
        throw llm;
    else if(position < 0 || position > size - 1) // must be in the range of the available positions
        throw llb;
    
    // Positon = 0 is remove the head
    // Position = (size - 1) is remove the tail
    // Else, remove a node in the middle
    
    T objectToReturn;
    
    if(position == 0) // remove the head
    {
        int indexOfRowAfterHead = rows->getAtIndex(head).getNext(); // stores the index of the next value for the head to be deleted
        
        objectToReturn = *(rows->getAtIndex(head).getInfo()); // stores the value to return
        
        delete rows->getRefAtIndex(head).getInfo(); // clears up the dynamically allocated info at the head to be deleted
        
        rows->getRefAtIndex(head).setInfo(NULL);
        
        rows->replace(head, ArrayLinkedListRow<T>(firstEmpty)); // replaces head with empty row that points to the previous first empty row
        
        firstEmpty = head; // the new first empty row is the previous head
        
        head = indexOfRowAfterHead; // the new head is assigned
    }
    else if(position == size - 1) // remove the tail
    {
        int tail = getIndexOfRowAtPosition(size - 1); // gets the index of the tail to be deleted
        
        int indexOfRowBeforeTail = getIndexOfRowAtPosition(size - 2); // gets the index of the row before the tail
        
        objectToReturn = *(rows->getAtIndex(tail).getInfo()); // stores the value to return
        
        rows->getRefAtIndex(indexOfRowBeforeTail).setNext(-1); // sets the next of the row before the tail to null
        
        delete rows->getRefAtIndex(tail).getInfo(); // clears up the dynamically allocated info at the head to be deleted
        
        rows->getRefAtIndex(tail).setInfo(NULL);
        
        rows->replace(tail, ArrayLinkedListRow<T>(firstEmpty)); // replaces tail with empty row that points to the previous first empty row
        
        firstEmpty = tail; // the new first empty row is the previous head
    }
    else // remove a node in the middle
    {
        int indexOfRowBeforeRowToBeDeleted = getIndexOfRowAtPosition(position - 1); // gets the index of the node before the node to be deleted
        int indexOfRowToBeDeleted = getIndexOfRowAtPosition(position); // gets the index of the node to be deleted
        int indexOfRowAfterRowToBeDeleted = getIndexOfRowAtPosition(position + 1); // gets the index of the node after the node to be deleted
        
        objectToReturn = *(rows->getAtIndex(indexOfRowToBeDeleted).getInfo()); // stores the value to return
        
        rows->getRefAtIndex(indexOfRowBeforeRowToBeDeleted).setNext(indexOfRowAfterRowToBeDeleted); // sets the node before the node to be deleted to point to the node after the node to be deleted
        
        delete rows->getRefAtIndex(indexOfRowToBeDeleted).getInfo(); // clears up the dynamically allocated info at the head to be deleted
        
        rows->getRefAtIndex(indexOfRowToBeDeleted).setInfo(NULL);
        
        rows->replace(indexOfRowToBeDeleted, ArrayLinkedListRow<T>(firstEmpty)); // replaces node to be deleted with empty row that points to the previous first empty row
        
        firstEmpty = indexOfRowToBeDeleted; // the new first empty row is the node that was deleted
    }
    
    --size; // a node was removed
    
    return objectToReturn;
}

// Finds the object that matches the key, returns the index of that object or throws a LinkedListNotFound exception
template <typename T>
int ArrayLinkedList<T>::find(T key)
{
    int indexOfRowAtPosition = head;
    
    int nextValueAtPosition = rows->getAtIndex(head).getNext();
    
    for(int i=0; i<size; i++) // starts at the head of the list and works through it to finds the match
    {
        T currentObjectToCompare = *(rows->getAtIndex(indexOfRowAtPosition).getInfo());
        
        if(key == currentObjectToCompare) // checks to see if the values are equal
            return indexOfRowAtPosition;
        
        if(i < size - 1)
        {
            indexOfRowAtPosition = nextValueAtPosition;
            nextValueAtPosition = rows->getAtIndex(nextValueAtPosition).getNext(); // there is nothing beyond
        }
    }
    throw llnf;
}

// Display raw data of the members
template <typename T>
void ArrayLinkedList<T>::displayRaw()
{
    cout << "Head Index: " << head << endl; // display head
    cout << "First Empty: " << firstEmpty << endl; // dispay first empty
    cout << "Size: " << size << endl; // display size
    
    cout << "Info: ";
    for(unsigned int i=0; i<rows->getVectorElementCount(); i++)
    {
        if(rows->getAtIndex(i).getInfo() == NULL) // empty row have a next value of -2
            cout << "x"; // display the NULL value (as per project description)
        else
            cout << *(rows->getAtIndex(i).getInfo()); // display the info values
        
        if(i < rows->getVectorElementCount() - 1) // no extra space needed at the end
            cout << " ";
        else
            cout << endl; // end line
    }
    
    cout << "Next: ";
    for(unsigned int i=0; i<rows->getVectorElementCount(); i++)
    {
        cout << rows->getAtIndex(i).getNext(); // display the next values
        
        if(i < rows->getVectorElementCount() - 1) // no extra space needed at the end
            cout << " ";
        else
            cout << endl; // end line
    }
    
    cout << "Next Empty: ";
    for(unsigned int i=0; i<rows->getVectorElementCount(); i++)
    {
        cout << rows->getAtIndex(i).getNextEmpty(); // display the next values
        
        if(i < rows->getVectorElementCount() - 1) // no extra space needed at the end
            cout << " ";
        else
            cout << endl; // end line
    }
}

// Display data in Vector row form
template <typename T>
void ArrayLinkedList<T>::displayRowForm()
{
    cout << "Head: " << head << ", First_Empty: " << firstEmpty << ", Size: " << size << endl;
    
    for(unsigned int i=0; i < rows->getVectorElementCount(); i++)
    {
        if(rows->getAtIndex(i).getInfo() == NULL)
            cout << "Row: " << i << ". Info: " << "NULL" << ", Next: " <<  rows->getAtIndex(i).getNext() << ", Next_Empty: " <<  rows->getAtIndex(i).getNextEmpty() << endl;
        else
            cout << "Row: " << i << ". Info: " << *(rows->getAtIndex(i).getInfo()) << ", Next: " <<  rows->getAtIndex(i).getNext() << ", Next_Empty: " <<  rows->getAtIndex(i).getNextEmpty() << endl;
    }
}

// Getters

// Returns the Vector containing the LinkedListRows
template <typename T>
Vector<ArrayLinkedListRow<T>> ArrayLinkedList<T>::getRows()
{
    return *rows;
}


// Returns the index in the Vector of the head
template <typename T>
int ArrayLinkedList<T>::getHead()
{
    return head;
}

// Gets the index in the Vector of the First Empty Node
template <typename T>
int ArrayLinkedList<T>::getFirstEmpty()
{
    return firstEmpty;
}

// Returns the number of nodes in the list
template <typename T>
int ArrayLinkedList<T>::getSize()
{
    return size;
}

// Operator Overloading

// Overloaded assignment operator
template <typename T>
void ArrayLinkedList<T>::operator =(const ArrayLinkedList<T>& oldList)
{
    this->rows = new Vector<ArrayLinkedListRow<T>>(oldList.rows->getVectorElementCount()); // creates new memory space
    
    copy(oldList); // copies information over
    
    this->head = oldList.head;
    this->firstEmpty = oldList.firstEmpty;
    this->size = oldList.size;
}

// Overloaded [] operator. Returns a reference to the object at the specified position
template <typename T>
T& ArrayLinkedList<T>::operator [](const int position)
{
    if(isEmpty() || position < 0 || position > size - 1) // must be in the range of the available positions (0...size-1)
        throw llb;
    
    int indexOfRowAtPosition = getIndexOfRowAtPosition(position);
    
    return *(rows->getRefAtIndex(indexOfRowAtPosition).getInfo());
}

// Ostream Operator. Outputs in format: info(indexInVector) --> ...
template <typename T>
ostream& operator <<(ostream& out, ArrayLinkedList<T>& list)
{
    if(list.isEmpty()) // there are no nodes in the list
    {
        out << "The linked list is empty";
        return out;
    }
    
    int indexOfRowAtPosition = list.head;
    
    int nextValueAtPosition = list.rows->getAtIndex(list.head).getNext();
    
    for(int i=0; i<list.size; i++) // starts at the head of the list and works through it to finds the match
    {
        T currentInfoToDisplay = *(list.rows->getAtIndex(indexOfRowAtPosition).getInfo());
        
        out << currentInfoToDisplay << "(" << indexOfRowAtPosition << ")"; 
        
        if(i < list.size - 1)
        {
            out << " --> ";
            
            indexOfRowAtPosition = nextValueAtPosition;
            nextValueAtPosition = list.rows->getAtIndex(nextValueAtPosition).getNext(); // there is nothing beyond -1
        }
    }
    
    return out;
}




#endif
