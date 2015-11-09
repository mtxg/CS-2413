//
//  ItemNotFoundException.h
//  Project 4
//
//  Created by Max Guerrero on 4/14/15.
//  Copyright (c) 2015 Data Structures. All rights reserved.
//

#ifndef __Project_4__ItemNotFoundException__
#define __Project_4__ItemNotFoundException__


#include <exception>
#include <iostream>

using namespace std;

// The ItemNotFoundException class is an exception that is thrown when a tag can not be found during a generalized tree search
class ItemNotFoundException: public exception
{
public:
    
    ItemNotFoundException();
    
    const virtual void exception(); // call to std exception
    
    ~ItemNotFoundException();
};

ItemNotFoundException::ItemNotFoundException()
{

}

const void ItemNotFoundException::exception()
{
    cout << "The item could not be found in the binary tree." << endl;
}

ItemNotFoundException::~ItemNotFoundException()
{
    
}


#endif /* defined(__Project_4__ItemNotFoundException__) */
