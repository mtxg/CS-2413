#ifndef ELEMENT_H
#define ELEMENT_H

//#include "stdafx.h"
#include "ItemNotFoundException.h"
#include <iostream>
#include <list>

using namespace std;
// The Element class is used to create the recursive generalized tree structure
class Element
{
private:
    
    list<Element*> children;
    char* tag;
    int value;
    
    ItemNotFoundException infe;
    
    // Uses recursion to create deep copies of a node's children for the assignment op and the copy constructor
    // Deletes any children that exist in the node before the copy
    void copyChildren(const Element& oldElement);
    
    // Find the first element such that tag == key. Returns “this” pointer of this element
    Element* findTagHelper(char* key);
    
    // Recursively prints out all the children of the selected node
    void printChildrenHelper(int tabs);
    
    // Recursively prints out all the children of the selected node in XML format
    void displayXMLHelper(int tabs);
    
public:
    
    // Constructor
    Element();
    
    // Constructor
    Element(char* name);
    
    // Constructor
    Element(char* name, int value);
    
    // Constructor
    Element(char* name, char* value);
    
    // Copy constructor
    Element(const Element& oldElement);
    
    // destructor must recursively destruct its children
    // and release the memory allocated for tag
    ~Element();
    
    // Adds a child to the node
    void addChild(Element* child);
    
    // Wrapper for the "printChildrenHelper" method
    // Also prints out the node that calls the method
    void printChildren();
    
    // Wrapper for the "displayXMLHelper" method
    // Also prints out the informtion of the node that calls the method
    void displayXML();
    
    // Wrapper for the "findTagHelper" method
    Element* findTag(char* key);
    
    // Recursively gets the height of the tree (the height of the tree-node that called the method and its children)
    int getHeight();
    
    // Recursively gets the size of the tree (the size of the tree-node that called the method and its children)
    int getSize();
    
    // Getters
    
    // Returns the tag
    char* getTag();
    
    // Returns the value
    int getValue();
    
    // Setters
    
    // Deletes the old tag and dynamically allocates the new tag
    void setTag(char* tag);
    
    void setValue(int value);
    
    // Overloaded Operators
    
    // Overloaded assignment operator
    Element& operator =(const Element& oldElement);
    
    // Overloaded ostream operator
    friend ostream& operator <<(ostream& out, Element& element);
};

// Private Methods

// Uses recursion to create deep copies of a node's children for the assignment op and the copy constructor
// Deletes any children that exist in the node before the copy


void Element::copyChildren(const Element& oldElement)
{
    list<Element*> tempChildren = oldElement.children;
    
    while(!this->children.empty()) // recursively delete all of the children so that the new children can be copied
    {
        Element* childToDelete = this->children.front();
        delete childToDelete; // calls the destructor, which recursively deletes all of the child's children, as well
        this->children.pop_front();
    }
    
    while(!tempChildren.empty()) // copy over the new children and their children
    {
        Element* currentChild = tempChildren.front(); // selects the child to be copied
        Element* newChild = new Element(currentChild->tag, currentChild->value); // allocates new memory for the child to be copied
        this->addChild(newChild); // add the child to the node
        newChild->copyChildren(*currentChild); // if the child has children, add their children too
        tempChildren.pop_front();
    }
}

// Recursively find the first element such that tag == key. Returns “this” pointer of this element
Element* Element::findTagHelper(char* key)
{
    list<Element*> tempChildren = this->children;
    char* cstringToCompare = this->tag;
    Element* nodeToReturn = NULL;
    
    if(strcmp(cstringToCompare, key) == 0)
        nodeToReturn = this;
    else
    {
        while(!tempChildren.empty() && nodeToReturn == NULL)
        {
            Element* currentChild = tempChildren.front();
            
            nodeToReturn = currentChild->findTagHelper(key);
            
            tempChildren.pop_front();
        }
    }
    
    if(nodeToReturn == NULL)
        return NULL;
    else
        return nodeToReturn;
}

// Recursively prints out all the children of the selected node.
void Element::printChildrenHelper(int tabs)
{
    list<Element*> tempChildren = this->children;
    
    while(!tempChildren.empty())
    {
        for(int i=0; i<tabs; i++) // print out the spaces
        {
            cout << "   ";
        }
        
        Element* currentChild = tempChildren.front(); // get the next child
        
        cout << currentChild->tag; // print out the tag name of the node
        
        if(currentChild->value != -999) // print out the value, if it is set
            cout << " : " << currentChild->value; // print the value
        
        cout << endl;
        
        if(!currentChild->children.empty())
        {
            int tempTabs = tabs;
            currentChild->printChildrenHelper(tabs + 1); // print out the nodes children if they exist
            tabs = tempTabs;
        }
        
        tempChildren.pop_front(); // remove the child that was printed from the temp list
    }
}

// Recursively prints out all the children of the selected node in XML format
void Element::displayXMLHelper(int tabs)
{
    list<Element*> tempChildren = this->children;
    
    while(!tempChildren.empty())
    {
        for(int i=0; i<tabs; i++) // print out the tabs
        {
            cout << "\t";
        }
        
        Element* currentChild = tempChildren.front(); // get the next child
        
        cout << "<" << currentChild->tag << ">" << endl; // print out start tag
        
        if(currentChild->value != -999) // if there is a value
        {
            for(int i=0; i<tabs; i++) // print out the tabs
            {
                cout << "\t";
            }
            
            cout << currentChild->value << endl; // print the value
        }
        
        
        if(!currentChild->children.empty())
        {
            int tempTabs = tabs;
            currentChild->displayXMLHelper(tabs + 1); // print out the child's children in XML format, if they exist
            tabs = tempTabs;
        }
        
        for(int i=0; i<tabs; i++) // print out the tabs
        {
            cout << "\t";
        }
        
        cout << "</" << currentChild->tag << ">" << endl; //print out the end tag
        
        tempChildren.pop_front(); // remove the child that was printed from the temp list
    }
}

// Public Methods

// Constructor
Element::Element()
{
    tag = NULL; // no tag specified
    
    value = -999; // value is set to -999 since it is not given
}

// Constructor
Element::Element(char* name)
{
    size_t len = strlen(name);
    tag = new char[len + 1];
    strcpy(tag, name); // copies the two strings (does not copy the terminating char)
    tag[len] = '\0';
    
    value = -999; // value is set to -999 since it is not given
}

// Constructor
Element::Element(char* name, int value)
{
    size_t len = strlen(name);
    tag = new char[len + 1];
    strcpy(tag, name); // copies the two strings (does not copy the terminating char)
    tag[len] = '\0';
    
    this->value = value;
}

// Constructor
Element::Element(char* name, char* value)
{
    size_t len = strlen(name);
    tag = new char[len + 1];
    strcpy(tag, name); // copies the two strings (does not copy the terminating char)
    tag[len] = '\0';
    
    this->value = atoi(value);
}

// Copy constructor
Element::Element(Element const& oldElement)
{
    this->setTag(oldElement.tag);
    
    this->setValue(oldElement.value);
    
    this->copyChildren(oldElement); // recursively copies the children over
    
}

// destructor must recursively destruct its children
// and release the memory allocated for tag
Element::~Element()
{
    char* currentTag = this->tag;
    
//    if(currentTag == NULL)
//        cout << "Deleting a tag with name: " << endl;
//    else
//        cout << "Deleting a tag with name: " << currentTag << endl;
//    
    if(currentTag != NULL) // delete the dynamically allocated tag, if it is set
    {
        delete[] currentTag;
        
        currentTag = NULL;
    }
    
    while(!this->children.empty()) // recursively delete the children, as long as they exist
    {
        Element* currentChild = this->children.front();
        
        if(currentChild != NULL)
        {
            delete currentChild;
            
            currentChild = NULL;
        }
        
        this->children.pop_front();
    }
}

// Adds a child to the node
void Element::addChild(Element* child)
{
    this->children.push_back(child);
}

// Wrapper for the "printChildrenHelper" method
// Also prints out the information of the node that calls the method
void Element::printChildren()
{
    int tabs = 0;
    
    cout << this->tag;
    
    if(this->value != -999) // print out the value if it exists
        cout << " : " << this->value; // print out the value
    
    cout << endl;
    
    this->printChildrenHelper(tabs + 1);
}

// Wrapper for the "displayXMLHelper" method
// Also prints out the informaton of the node that calls the method
void Element::displayXML()
{
    int tabs = 0;
    
    cout << "<" << this->tag << ">" << endl;
    
    if(this->value != -999) // print out the value if it exists
        cout << this->value << endl;
    
    this->displayXMLHelper(tabs + 1);
    
    cout << "</" << this->tag << ">" << endl;
}

// Wrapper for the "findTagHelper" method
Element* Element::findTag(char* key)
{
    Element* elementToReturn = findTagHelper(key);
    
    if(elementToReturn == NULL)
        throw infe;
    
    return elementToReturn;
}

// Recursively gets the height of the tree (the height of the tree-node that called the method and its children)
int Element::getHeight()
{
    list<Element*> tempChildren = this->children; // get the children
    
    int size = 0;
    
    while(!tempChildren.empty())
    {
        Element* currentChild = tempChildren.front();
        
        size = std::max(size, currentChild->getHeight() + 1);
        
        tempChildren.pop_front();
    }
    
    return size;
}

// Recursively gets the size of the tree (the size of the tree-node that called the method and its children)
int Element::getSize()
{
    list<Element*> tempChildren = this->children; // get the children
    
    int size = 1; // 1 for the node that is currently accessing the method
    
    while(!tempChildren.empty())
    {
        Element* currentChild = tempChildren.front();
        
        size += currentChild->getSize(); // add 1 for all the children of the children... etc
        
        tempChildren.pop_front();
    }
    
    return size;
}

// Getters

// Returns the tag
char* Element::getTag()
{
    return tag;
}

// Returns the value
int Element::getValue()
{
    return value;
}

// Setters

// Deletes the old tag and dynamically allocates the new tag
void Element::setTag(char* tag)
{
    if(this->tag != NULL)
    {
        delete[] this->tag;
        this->tag = NULL;
    }
    
    if(tag != NULL)
    {
        int len = strlen(tag);
        this->tag = new char[len + 1];
        strcpy(this->tag, tag); // copies the two strings (does not copy the terminating char)
        tag[len] = '\0';
    }
    else
        this->tag = NULL;
}

// Sets the value
void Element::setValue(int value)
{
    this->value = value;
}

// Overloaded Operators

// Overloaded assignment operator
Element& Element::operator =(const Element& oldElement)
{
    this->setTag(oldElement.tag);
    
    this->setValue(oldElement.value);
    
    this->copyChildren(oldElement); // recursively copies the children over
    
    return *this;
}

// Overloaded ostream operator
ostream& operator <<(ostream& out, Element& element)
{
    element.printChildren();
    
    return out;
}

#endif