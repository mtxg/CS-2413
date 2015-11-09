//
//  Vector.h
//  Project-3
//
//  Created by Max Guerrero on 4/28/15.
//  Copyright (c) 2015 Data Structures. All rights reserved.
//

#ifndef Project_3_Vector_h
#define Project_3_Vector_h

#include <iostream>

using namespace std;

template <typename T>
class Vector
{
private:
    
    // Constants
    
    // The default size for the default constructor
    static const int defaultSize = 20;
    
    // Fields
    
    // Pointer to first element in array for this vector
    T* vectorArray;
    
    // Current size (size of vector array) of the array for this vector
    unsigned int vectorSize;
    
    // Current number of elements stored in vector
    unsigned int vectorElementCount;
    
public:
    // Constructors/Deconstructor
    
    // Default (empty) constructor
    Vector(void);
    
    // Constructor with predetermined size
    Vector(int size);
    
    // Copy constructor
    Vector(const Vector<T>& old);
    
    // Deconstructor
    ~Vector();
    
    // Private Helper Methods
    
    // Doubles the amount of storage in the vector
    void expand();
    
    // Shifts data from a certain index to the right a set number of shifts
    void shiftUp(int unsigned index, int unsigned shifts);
    
    // Shifts data from a certain index to the left a set number of shifts
    void shiftDown(int unsigned index, int unsigned shifts);
    
    // Public Methods
    
    // Returns the current size (size of vector array) of the vector
    unsigned int getVectorSize();
    
    // Returns the number of elements in the vector
    unsigned int getVectorElementCount();
    
    // Returns element at specified index
    T getAtIndex(unsigned int index);
    
    // Returns a reference to the element at the specified index
    T& getRefAtIndex(unsigned int index);
    
    // Sequentually prints all the elements stored in the vector
    void printVector();
    
    // Vector Manipulation Methods
    
    // Adds a new value to the end of the vector
    void add(const T newVal);
    
    // Ammends the value at the specified index with the value
    void replace(int index, T newVal);
    
    // Inserts the new value at the specified index and shifts the target element and all elements after it 1 shift to the right
    void insert(int index, T newVal);
    
    // Shifts all elements beyond one to the left, deleting the element at the index
    void deleteItem(int index);
    
    // Vector helper methods
    
    // Checks if the index exists within the vector
    bool isInBounds(unsigned int index);
    
    // Operator Overloaders
    
    // Overloads the [] operator
    T operator[](int index);
};
// Constructors/Deconstructor

// Default (empty) constructor
template <typename T>
Vector<T>::Vector(void)
{
    //cout << "constructing vector" << endl;
    vectorElementCount = 0;
    vectorSize = defaultSize;
    
    vectorArray = new T[defaultSize];
}

// Constructor (non empty)
template <typename T>
Vector<T>::Vector(int size)
{
    vectorElementCount = 0;
    vectorSize = size;
    
    vectorArray = new T[size];
}

// Copy constructor
template <typename T>
Vector<T>::Vector(const Vector<T>& old)
{
    this->vectorSize = old.vectorSize;
    this->vectorElementCount = old.vectorElementCount;
    
    this->vectorArray = new T[vectorSize];
    
    // Copies data from old to new
    for(unsigned int i=0; i < vectorElementCount; i++)
    {
        this->vectorArray[i] = old.vectorArray[i];
    }
}

// Deconstructor
template <typename T>
Vector<T>::~Vector()
{
    //cout << "deleting vector" << endl;
    delete[] vectorArray;
}

// Private Helper Methods

// Doubles the amount of storage in the vector
template <typename T>
void Vector<T>::expand()
{
    int newSize = vectorSize*2;
    
    // Create new array with 2x the size
    T* newVectorArray = new T[newSize];
    
    // Copy the data over to the new array
    for(unsigned int i=0; i<vectorElementCount; i++)
    {
        newVectorArray[i] = vectorArray[i];
    }
    
    vectorSize = newSize;
    
    delete vectorArray;
    
    vectorArray = newVectorArray;
}

// Shifts data from a certain index to the right a set number of shifts
template <typename T>
void Vector<T>::shiftUp(int unsigned index, int unsigned shifts)
{
    // Expand the vector if there isn't enough room
    while(vectorSize < vectorElementCount + shifts)
    {
        expand();
    }
    
    // Shifts and prepares for new data to occupy the spots
    for(int i = vectorElementCount - 1; i >= index; i--)
    {
        vectorArray[i + shifts] = vectorArray[i];
    }
}

// Shifts data from a certain index to the left a set number of shifts
template <typename T>
void Vector<T>::shiftDown(unsigned int index, unsigned int shifts)
{
    // There cannot be more shifts than there are elements
    if(vectorElementCount < shifts)
        throw 0; // TODO THROW EXCEPTION
    
    // Remove the element
    vectorArray[index] = NULL;
    
    // Shift the elements down
    for(unsigned int i=index; i < (vectorElementCount - shifts); i++)
    {
        vectorArray[i] = vectorArray[i + shifts];
    }
}

// Public Methods

// Returns the current size (size of vector array) of the vector
template <typename T>
unsigned int Vector<T>::getVectorSize()
{
    return vectorSize;
}

// Returns the number of elements in the vector
template <typename T>
unsigned int Vector<T>::getVectorElementCount()
{
    return vectorElementCount;
}

// Returns element at specified index
template <typename T>
T Vector<T>::getAtIndex(unsigned int index)
{
    if(index > vectorElementCount)
        throw 0; // TODO THROW EXCEPTION
    
    return vectorArray[index];
}

// Returns a reference to the element at the specified index
template <typename T>
T& Vector<T>::getRefAtIndex(unsigned int index)
{
    if(index > vectorElementCount)
        throw 0; // TODO THROW EXCEPTION
    
    return vectorArray[index];
}

// Sequentually prints all the elements stored in the vector
template <typename T>
void Vector<T>::printVector()
{
    for(unsigned int i=0; i<vectorElementCount; i++)
        cout << i << ". " << vectorArray[i] << endl;
}


// Vector Manipulation Methods

// Adds a new value to the end of the vector
template <typename T>
void Vector<T>::add(const T newVal)
{
    // Expand if the size of the vector is exceeded
    if(vectorElementCount >= vectorSize)
        expand();
    
    vectorArray[vectorElementCount] = newVal;
    
    ++vectorElementCount;
}

// Ammends the value at the specified index with the value
template <typename T>
void Vector<T>::replace(int index, T newVal)
{
    if(!isInBounds(index))
        throw 0; // TODO THROW EXCEPTION
    
    vectorArray[index] = newVal;
}

// Inserts the new value at the specified index and shifts the target element and all elements after it 1 shift to the right
template <typename T>
void Vector<T>::insert(int index, T newVal)
{
    if(!isInBounds(index))
        throw 0; // TODO THROW EXCEPTION
    
    // Make room for the new value
    shiftUp(index, 1);
    
    // An element was added
    ++vectorElementCount;
    
    replace(index, newVal);
}

// Shifts all elements beyond one to the left, deleting the element at the index
template <typename T>
void Vector<T>::deleteItem(int index)
{
    // Shift over the element at the index once
    shiftDown(index, 1);
    
    // The element was removed
    --vectorElementCount;
}

// Vector helper methods

// Checks if the index exists within the vector
template <typename T>
bool Vector<T>::isInBounds(unsigned int index)
{
    return (index >= 0 && index <= (vectorElementCount - 1));
}

// Operator Overloaders

// Overloads the [] operator
template <typename T>
T Vector<T>::operator[](int index)
{
    return this->getAtIndex(index);
}


#endif
