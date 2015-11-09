//
//  main.cpp
//  Project-3
//
//  Created by Max Guerrero on 4/28/15.
//  Copyright (c) 2015 Data Structures. All rights reserved.
//

#include "Vector.h"
#include "ArrayClass.h"
#include <iostream>
#include <string>
using namespace std;

int main()
{
    // changed size() method to getSize()
    
    Vector<int> ai;
    
    int i;
    int intData[100];
    
    for( i=0; i< 100; i++)
        intData[i] = i;
    
    // string data
    string zero("zero");
    string one("One");
    string two = "Two";
    string three = "Three";
    string four = "Four";
    string five = "Five";
    string six = "Six";
    string seven = "Seven";
    string eight = "Eight";
    string nine = "Night";
    string ten = "Ten";
    
    // ========================================================
    
    
    ArrayLinkedList<int> myIntList;
    ArrayLinkedList<string>* pMyStringList;
    
    
    cout << endl << "== Basic Operations ============================================================" << endl << endl;
    
    
    cout << "The size of myIntList is: " << myIntList.getSize() << endl;
    
    
    
    if( myIntList.isEmpty())
        cout << "The list is empty." << endl;
    else
        cout << "The list is not empty." << endl;
    
    // test add method
    
    cout << endl << "================================================================================" << endl << endl;
    
    cout << "Adding objects to the list:";
    for( i=10; i> 0; i--)
    {
        myIntList.add( intData[i+10]);
        cout << " " << intData[i+10];
    }
    cout << endl;
    
    // test size method
    cout << "The size of myIntList is: " << myIntList.getSize() << endl;
    
    
    if( myIntList.isEmpty())
        cout << "The list is empty." << endl;
    else
        cout << "The list is not empty." << endl;
    
    // test ostream<<
    cout << "myIntList:" << endl;
    cout << myIntList << endl;
    
    cout << endl << "================================================================================" << endl << endl;
    
    
    // test insertAt;
    // head
    cout << "Insert " << intData[0] << " to position " << 0 << endl;
    myIntList.insertAt( intData[0], 0);
    
    // tail
    int tail = myIntList.getSize();
    cout << "Insert " << intData[1] << " to position " << tail << endl;
    myIntList.insertAt( intData[1], tail);
    
    // somewhere in the middle
    cout << "Insert " << intData[50] << " to position " << tail/2 << endl;
    myIntList.insertAt( intData[50], tail/2);
    cout << myIntList << endl;
    
    
    
    // test copy constructor
    
    cout << endl << "================================================================================" << endl << endl;
    
    ArrayLinkedList<int> * pMyNewIntList;
    
    
    pMyNewIntList = new ArrayLinkedList<int>(myIntList);
    
    cout << "*pMyNewIntList (copied from muIntList)" << endl;
    cout << *pMyNewIntList << endl;
    
    cout << "myIntList:" << endl;
    cout << myIntList << endl;
    
    
    
    // test assignment operator
    
    cout << endl << "================================================================================" << endl << endl;
    
    
    pMyNewIntList->add( intData[51]); // add 51 to myIntList
    
    cout << "*pMyNewIntList" << endl;
    cout << *pMyNewIntList << endl;
    
    
    cout << "myIntList = *pMyNewIntList" << endl;
    
    myIntList = *pMyNewIntList;
    
    cout << "*pMyNewIntList" << endl;
    cout << *pMyNewIntList << endl;
    
    cout << "myIntList:" << endl;
    cout << myIntList << endl;
    
    
    cout << endl << "================================================================================" << endl << endl;
    
    
    
    // test remove
    
    cout << "Removing data from myIntList:";
    while( !myIntList.isEmpty())
        cout << " " << myIntList.remove();
    cout << endl;
    cout << "myIntList: (empty now)" << endl;
    cout << myIntList << endl;
    
    
    
    cout << "Copy from *pMyNewIntList" << endl;
    myIntList = *pMyNewIntList;
    
    cout << "myIntList:" << endl;
    cout << myIntList << endl;
    
    cout << endl << "================================================================================" << endl << endl;
    
    // test the destructor
    delete pMyNewIntList;
    pMyNewIntList = NULL;
    
    cout << "Removing the object at position 0, value: " <<  myIntList.removeAt(0) << endl; // head
    cout << "Removing the object at position 4, value: " <<  myIntList.removeAt(4) << endl; // 5th object
    
    cout << "myIntList:" << endl;
    cout << myIntList << endl;
    
    cout << "Adding an object with value 50 to the list, it will be at the position of last object removed in the array." << endl;
    myIntList.add( intData[50]);
    
    cout << "myIntList:" << endl;
    cout << myIntList << endl;
    
    cout << "Adding objects with value 51 and 23 to the list." << endl;
    myIntList.add( intData[51]);
    myIntList.add( intData[23]);
    
    cout << "myIntList:" << endl;
    cout << myIntList << endl;
    
    cout << endl << "================================================================================" << endl << endl;
    
    // test find
    cout << "Testing find() ..." << endl;
    cout << "The first object with value 51 is store at position " << myIntList.find(51) << " of the array." << endl;
    
    cout << "The first object with value 23 is store at position " << myIntList.find(23) << " of the array." << endl << endl;
    
    
    cout << "Testing operator[]..." << endl;
    for (i=0; i< myIntList.getSize(); i++) {
        cout << myIntList[i] << " ";
    }
    cout << endl << endl;
    
    cout << "Replace the head with " << intData[80] << endl;
    
    myIntList[0] = intData[80];
    
    cout << "New list:" << endl;
    
    for (i=0; i< myIntList.getSize(); i++) {
        cout << myIntList[i] << " ";
    }
    cout << endl << endl;
    
    // call displayRaw()
    myIntList.displayRaw();
    
    
    // test exception handling
    
    cout << endl <<"== Exception Handling ==========================================================" << endl << endl;
    
    
    try{
        myIntList.removeAt(101);
    }
    catch (LinkedListBounds e)
    {
        cout << "Out of bounds." << endl;
    }
    
    try{
        myIntList.insertAt(intData[72], 50);
    }
    catch (LinkedListBounds e)
    {
        cout << "Out of bounds." << endl;
    }
    
    int size = myIntList.getSize();
    
    try{
        
        for( i=0; i< 101 - size; i++)
        {
            myIntList.add(intData[i]);
        }
    }
    catch (LinkedListMemory e)
    {
        cout << "List full ( i = " << i << ")." << endl;
    }
    
    
    try{
        myIntList.insertAt(intData[20], 30);
    }
    catch (LinkedListMemory e)
    {
        cout << "List full." << endl;
    }
    
    
    try{
        cout << myIntList[200] << endl;
    }
    catch (LinkedListBounds e)
    {
        cout << "Out of bounds." << endl;
    }
    
    cout << myIntList << endl;
    
    try{
        myIntList.find(500);
    }
    catch (LinkedListNotFound e)
    {
        cout << "500: Not found." << endl;
    }
    
    cout << endl << "== String ======================================================================" << endl << endl;
    
    // test the class on the string
    
    // test non default constructor
    pMyStringList = new ArrayLinkedList<string>(zero);
    
    cout << *pMyStringList << endl;
    
    // add
    pMyStringList->add(one);
    pMyStringList->add(three);
    pMyStringList->add(five);
    pMyStringList->add(six);
    pMyStringList->add(seven);
    pMyStringList->add(eight);
    pMyStringList->add(nine);
    pMyStringList->add(ten);
    
    cout << *pMyStringList << endl;
    
    // insertAt
    
    pMyStringList->insertAt( four, 3);    
    pMyStringList->insertAt( two, 2);
    
    cout << *pMyStringList << endl;
    
    // remove
    pMyStringList->remove();
    cout << *pMyStringList << endl;
    
    // removeAt
    pMyStringList->removeAt(5);
    cout << *pMyStringList << endl;
    
    cout << seven << " is found at position " << pMyStringList->find(seven) <<endl;
    
    // =operator
    ArrayLinkedList<string> MyNewStringList;
    
    MyNewStringList = *pMyStringList;
    
    delete pMyStringList;
    
    pMyStringList = NULL;
    
    cout << MyNewStringList << endl;
    
    for (i=0; i< MyNewStringList.getSize(); i++) {
        cout << MyNewStringList[i] << " ";
    }
    cout << endl;
    
    cout << MyNewStringList << endl;
    
    
    MyNewStringList.displayRaw();
    
    cin.get();
    
    return 0;
}
