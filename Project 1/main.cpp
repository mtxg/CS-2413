//
//  main.cpp
//  Project 1
//
//  Created by Max Guerrero on 1/19/15.
//  Copyright (c) 2015 Max Guerrero. All rights reserved.
//

#include <iostream>
#include <stdlib.h>
using namespace std;

#include "AccountInfo.h"

void emptyString(char* token, int size) {
    for (int i=0; i < size; i++) token[i] = '\0';
}

int getNextToken(char* buffer, char* token, int startPos, int bufSize, int tokenSize, char delimeter)
{
    int i, j;
    
    emptyString (token, tokenSize);
    
    i = startPos;
    j = 0;
    
    while ((buffer[i] == ' ') && (i < bufSize)) i++; //skipblanks
    if (i < 256) {
        while ((buffer[i] != delimeter) && (i < 256) && (j < tokenSize))
            token[j++] = buffer[i++];
    }
    return i;
}//read user input by token

int main() {
    char buffer[256];
    char uloginName[9];
    char homeDirectory[33];
    int userID;
    int groupID;
    char password[17];
    char shell[17];
    char gecos[65];
    int k;
    char flag[3];
    char IDString[6];
    char command[11];
    char blank = ' ';
    
    bool isDefaultUserId = false;
    
    
    AccountInfo *tempAccount;
    UserDB *userDB;
    userDB = new UserDB();
    
    while (!cin.eof()) {
        cin.getline(buffer,256);
        cout<<endl <<endl<< buffer << endl;
        k = getNextToken(buffer,command,0,256,10,blank);
        switch(command[0]) {
            case 'a': {//begin of "adduser"
                tempAccount = new AccountInfo();
                cout << "Add User" << endl;
                k = getNextToken(buffer, uloginName,k,256,9, blank);
                cout << "****** " << uloginName << endl;
                
                (*tempAccount).setUserLoginName(uloginName);
                isDefaultUserId = false;
                
                while (k < 256) {
                    k = getNextToken(buffer,flag,k,256,3, blank);
                    if (k < 256) {
                        switch (flag[1]) {
                            case 'd': k = getNextToken(buffer,homeDirectory,k,256,32, blank);
                                cout << "****** " << flag << endl;
                                cout << "****** " << homeDirectory << endl;
                                (*tempAccount).setHome(homeDirectory);
                                break;
                                //end of setting home directory
                            case 's': k = getNextToken(buffer,shell,k,256,17, blank);
                                cout << "****** " << flag << endl;
                                cout << "****** " << shell << endl;
                                (*tempAccount).setShell(shell);
                                break;
                                //end of setting shell of the user
                            case 'p': k = getNextToken(buffer,password,k,256,17, blank);
                                cout << "****** " << flag << endl;
                                cout << "****** " << password << endl;
                                (*tempAccount).setPassword(password);
                                break;
                                //end of collecting password
                            case 'c': k = getNextToken(buffer,gecos,k,256,65, '-');
                                cout << "****** " << flag << endl;
                                cout << "****** " << gecos << endl;
                                (*tempAccount).setGecos(gecos);
                                break;
                                //end of setting user general information
                            case 'g': k = getNextToken(buffer,IDString,k,256,6, blank);
                                groupID = atoi(IDString);
                                cout << "****** " << flag << endl;
                                cout << "****** " << IDString << "=" << groupID << endl;
                                (*tempAccount).setGroupId(groupID);
                                break;
                                //end of setting user group information
                            case 'u': k = getNextToken(buffer,IDString,k,256,6, blank);
                                userID = atoi(IDString);
                                cout << "****** " << flag << endl;
                                cout << "****** " << IDString << "= " << userID << endl;
                                (*tempAccount).setUserId(userID);
                                isDefaultUserId = true;
                                break;
                                //end of setting user group information
                            default: k = 256; break;
                        } //end Switch(flag[1])
                    } // end while (k < 256)
                }
                if(!isDefaultUserId)
                {
                    (*tempAccount).setUserId((*userDB).getNextUId());
                    (*userDB).setNextUId();
                }
                (*userDB).addUser(tempAccount);
                cout<<"["<<(*tempAccount).getUserLoginName()<<"] with "<<(*tempAccount).getUserId()<< " added."<<endl;
                
                break;				
            } //end of adduser
            case '#': {cout<< endl << "Comment" << endl; break;}
            case 's': {//begin of "showuser" or "showpassword" 
                if (command[4] == 'u') {					
                    (*userDB).showUsers();
                }//end of showuser
                else if (command[4] == 'p') {					
                    (*userDB).showPassword();
                }//end of showpassword
                break;
            }
            case 'f': {				
                k = getNextToken(buffer, uloginName,k,256,9, blank);
                (*userDB).finger(uloginName);
                break;
            }//end of "finger" a user.
            default: cout << "Command not found!!" << endl;
        } 
    }
    delete userDB;
    
}
