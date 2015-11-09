//
//  main.cpp
//  Project 4
//
//  Created by Max Guerrero on 04/02/15.
//  Copyright (c) 2015 Data Structures. All rights reserved.
//



#include <fstream>
#include <stack>
#include <list>
#include <iostream>
#include "Element.h"
#include "ItemNotFoundException.h"
#include "NotWellFormedException.h"

using namespace std;

// Verifies XML input file and creates
// a generalized tree structure from
// the XML file.

const static bool debug = false;

// Checks if a character is a digit
bool IsDigit(char c)
{
    return ( '0' <= c && c <= '9' );
}

// Used to print the tokens if an error in the XML file is detected
void displayTokens(Element* root)
{
    cout << "Tokens in the tree so far: " << endl;
    cout << *root << endl;
}

// Verifies that a file follows XML format and creates a generalized tree from the XML tags
Element* constructTreeFromXML(char* filename)
{
    NotWellFormedException exception; // exception to be thrown if the XML file is not well formed

    Element* root = NULL; // the root Element
    
    stack<Element*> elements; // a stack of Element pointers
    
    ifstream file;
    
    char buffer[256];
    
    file.open (filename);
    
    if(file.is_open())
    {
        while(!file.eof())
        {
            file.getline(buffer, 256); // load the line from the XML file into the buffer
            
            if(debug)
                cout << buffer << endl;
            
            for(unsigned int i=0; i<strlen(buffer); i++) // iterates over all the characters in the buffer
            {
                if(buffer[i] == '<') // check if the tag is well formed and add it to the stack
                {
                    int indexOfFirstBracket = i; // saves the index of '<'
                    
                    while(buffer[i] != '>') // sets i equal to the position in the buffer of the next '>'
                    {
                        if(i >= 255) // last index must be the '\0'
                        {
                            displayTokens(root);
                            throw exception; // a bracket was not closed - not well formed
                        }
                        
                        ++i;
                    }
                    
                    int indexOfSecondBracket = i; // calculates the index in the buffer of the second bracket
                    
                    int indexOfFirstTagCharacter = indexOfFirstBracket + 1; // the index of the first char in the tag name
                    
                    int indexOfLastTagCharacter = indexOfSecondBracket - 1; // the index of the last char in the tag name
                    
                    int lengthOfTag = (indexOfLastTagCharacter - indexOfFirstTagCharacter) + 1; // calculates the number of characters in the tag
                    
                    char* newTag = new char[lengthOfTag + 1]; // must be dynamically allocated because only dynamically allocated tags can have variables in the size declaration
                    
                    strncpy(newTag, buffer + indexOfFirstTagCharacter, lengthOfTag); // copy the tag characters
                    
                    newTag[lengthOfTag] = '\0'; // terminate the new tag
                    
                    if(newTag[0] != '/') // if it is not an end tag
                    {
                        // create element
                        if(elements.empty())
                        {
                            if(root != NULL)
                            {
                                displayTokens(root);
                                throw exception; // 2 roots implies there is an error - not well formed
                            }
                            
                            root = new Element(newTag); // create the root
                            
                            elements.push(root); // push onto the stack
                        }
                        else // add a child
                        {
                            Element* child = new Element(newTag); // create the child
                            
                            elements.top()->addChild(child); // add the child
                            
                            elements.push(child); // pushes the child onto the stack
                        }
                    }
                    else // it is an end tag
                    {
                        char* previousTagOnStack = elements.top()->getTag(); // gets the tag of the last element on the stack (it must be the one being closed)
                        
                        char* endTagToCompare = new char[lengthOfTag]; // allocates memory for the end tag without the '/'
                        
                        strncpy(endTagToCompare, newTag + 1, lengthOfTag - 1); // copies the end tag without the first '/'
                        
                        endTagToCompare[lengthOfTag - 1] = '\0'; // terminate the end tag
                        
                        delete[] newTag; // delete the tag because it is an end tag
                        
                        if(strcmp(previousTagOnStack, endTagToCompare) == 0) // tags match
                        {
                            delete[] endTagToCompare;
                            
                            elements.pop(); // pop the Element that was closed from the stack
                        }
                        else // not valid - tags do not match
                        {
                            delete[] previousTagOnStack;
                            delete[] endTagToCompare;
                            
                            displayTokens(root);
                            throw exception; // the tag names do not match - not well formed
                        }
                    }
                    
                    i = indexOfSecondBracket; // set i to the last bracket
                }
                else if(IsDigit(buffer[i])) // the current character is a digit
                {
                    int indexOfFirstDigitInBuffer = i; // the index of the first digit in the value
                    
                    while(IsDigit(buffer[i]))
                    {
                        if(i >= 255) // last index must be the '\0'
                        {
                            displayTokens(root);
                            throw exception; // the number is too large - not well formed
                        }
                        
                        ++i;
                    }
                    
                    --i; // reset i to the last digit in buffer
                    
                    int indexOfLastDigitInBuffer = i; // the index of the last digit in the value
                    
                    int lengthOfValue = indexOfLastDigitInBuffer - indexOfFirstDigitInBuffer + 1; // get the length of the value string
                    
                    char* newValue = new char[lengthOfValue + 1]; // dynamically allocate the memory for the vlue strng
                    
                    strncpy(newValue, buffer + indexOfFirstDigitInBuffer, lengthOfValue); // copy the value string from buffer to the new value string
                    
                    newValue[lengthOfValue] = '\0'; // terminate the value string
                    
                    if(elements.top()->getValue() == -999) // checks if the value of the element on the top of the stack has been set
                        elements.top()->setValue(atoi(newValue)); // sets the value
                    else // it has been set -> throw an error
                    {
                        displayTokens(root);
                        throw exception; // the value for the element has already been set - not well formed
                    }
                    
                    delete[] newValue; // no longer needed
                }
                else if(buffer[i] != ' ' && buffer[i] != '\t' && buffer[i] != '\n' && buffer[i] != '\v' && buffer[i] != '\r') // only white spaces and tabs are allowed
                {
                    displayTokens(root);
                    throw exception; // the character is not allowed - not well formed
                }
            }
        }
        
        // if all the tags aren't closed OR the file was empty (no tags -> no root), the file was not well formed
        if(!elements.empty() || root == NULL)
        {
            displayTokens(root);
            throw exception; // not all of the tags have been closed or no root has been created - not well formed
        }
    }
    file.close();
    return root;
}

int main()
{
    Element* tree = NULL;
    
    try
    {
        tree = constructTreeFromXML("p4input.txt");
    }
    catch(NotWellFormedException nwfe)
    {
        cout << "The inputted XML file was not well formed. Closing..." << endl;
        cin.get();
        
        return 0;
    }
    
    // TEST THE COPY CONSTRUCTOR
    Element* copyConsuctorTest = new Element(*tree);
    
    cout << "Copy constructor test: " << endl << endl << *copyConsuctorTest << endl;
    
    // TEST THE ASSIGNMENT OPERATOR
    Element* assignmentOperatorTest = new Element("test");
    *assignmentOperatorTest = *copyConsuctorTest;
    
    cout << "Assignmenet operator test: " << endl << *assignmentOperatorTest << endl;
    
    // TEST THE TREE
    
    cout << "The generalized tree: " << endl << endl;
    
    cout << *tree << endl;
    
    cout << "The tree size: " << tree->getSize() << endl;
    
    cout << "The tree height: " << tree->getHeight() << endl;
    
    char buffer[256];
    
    while(true)
    {
        cout << "Enter a tag to search for or QUIT to quit: ";
        
        cin.getline(buffer, 255);
        
        if(strlen(buffer) == 4 && strcmp("QUIT", buffer) == 0)
            break;
        
        try
        {
            cout << endl;
            cout << *(tree->findTag(buffer)) << endl;
        }
        catch(ItemNotFoundException infe)
        {
            cout << "The tag " << buffer << " could not be found in the tree" << endl;
        }
    }
    
    delete tree;
    delete copyConsuctorTest;
    delete assignmentOperatorTest;
    
    return 0;
}


