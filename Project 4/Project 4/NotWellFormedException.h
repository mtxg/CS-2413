//
//  NotWellFormedException.h
//  Project 4
//
//  Created by Max Guerrero on 4/14/15.
//  Copyright (c) 2015 Data Structures. All rights reserved.
//

#ifndef Project_4_NotWellFormedException_h
#define Project_4_NotWellFormedException_h



#include <iostream>
using namespace std;

// The NotWellFormedException class is an exception that is thrown when an XML file is verified to be not well formed
class NotWellFormedException: public exception
{
public:
    
    NotWellFormedException();
    
    const virtual void what(); // call to std exception
    
    virtual ~NotWellFormedException();
};



// Public Methods

NotWellFormedException::NotWellFormedException()
{

};

const void NotWellFormedException::what()
{
    cout << "The xml file is not well formed." << endl;
}

NotWellFormedException::~NotWellFormedException()
{

};

#endif
