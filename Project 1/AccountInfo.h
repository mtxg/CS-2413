//
//  AccountInfo.h
//  Project 1
//
//  Created by Max Guerrero on 2/4/15.
//  Copyright (c) 2015 Max Guerrero. All rights reserved.
//


//Defining default values for data fields
const char* DEFAULT_HOME ="/home/";
const char* DEFAULT_SHELL = "/bin/bash";
const char END_CHAR = '\0';

const unsigned int DEFAULT_HOME_LENGTH =6 ;
const unsigned int DEFAULT_SHELL_LENGTH = 9;
const unsigned int DEFAULT_GROUP_ID  = 1001;
const unsigned int FIRST_USER_ID = 1001;
const unsigned int MAX_ACCOUNT_INFO = 200;



//Defining the class AccountInfo
class AccountInfo
{
    //private Data fileds
private:
    char* _userLoginName; //field store user login name
    char* _password;//filed to store password
    unsigned int _uid;//field to store user id
    unsigned int _gid;//field to store group id
    char* _gecos;//field to store user general information
    char* _home;//field to store home directory information
    char* _shell;//field to store shell of the user
    
    //Public method declarations
public:
    AccountInfo();//defualt constructor
    ~AccountInfo();//Default destructor
    unsigned int getUserId();//Metod declaration to get the user id
    void setUserId(unsigned int);//Method declaration set the user id
    //Mutators/settors
    void setUserLoginName(char*);
    char* getUserLoginName();
    void setPassword(char *);
    char* getPassword();
    void setGecos(char *);
    char* getGecos();
    void setHome(char *);
    char* getHome();
    void setShell(char* );
    char* getShell();
    unsigned int getGroupId();//Metod declaration to get the user id
    void setGroupId(unsigned int);//Method declaration set the user id
    void copyString (const char* from,char* to, int size);
    
    //friend function to oveload << operator
    friend ostream& operator<<(ostream&,const AccountInfo&);
};

//Implenting method in AccountInfo class

//Implementing AccountInfo default constructor
AccountInfo :: AccountInfo()
{
    _password = END_CHAR;
    _gecos = END_CHAR;
    _gid = DEFAULT_GROUP_ID;
    
    //Initializing default  value for shell
    _shell = new char[DEFAULT_SHELL_LENGTH+1];
    copyString (DEFAULT_SHELL,_shell, DEFAULT_SHELL_LENGTH+1);
    
    
}

//implemetation for deafault destructor
AccountInfo :: ~AccountInfo()
{
    
}

// method to set user id
void AccountInfo ::setUserId(unsigned int userId)
{
    _uid = userId;
}

//Method  get the user id
unsigned int AccountInfo:: getUserId()
{
    return _uid;
}

// method to set group id
void AccountInfo ::setGroupId(unsigned int groupId)
{
    _gid = groupId;
}

//Method  get the user id
unsigned int AccountInfo:: getGroupId()
{
    return _gid;
}

//Method to copy string
void AccountInfo :: copyString (const char* from,char* to, int size) {
    //to = new char[size+1];
    for (int i=0; i < size; i++) to[i] = from[i];
    to[size] = '\0';
}

//This method set user login name
void  AccountInfo :: setUserLoginName(char* userLoginName)
{
    //setting user login name
    int length=0;
    while(userLoginName[length]!= END_CHAR)
    {
        length++;
    }
    //Initilizing variable _userLoginName
    _userLoginName = new char[length+1];
    copyString(userLoginName,_userLoginName,length);
    
    
    //set up the default home
    _home = new char[length+DEFAULT_HOME_LENGTH+1];
    copyString(DEFAULT_HOME,_home,DEFAULT_HOME_LENGTH+1);
    
    for(int i=0;i <length+1 ;i++)
    {
        _home[DEFAULT_HOME_LENGTH+i] = _userLoginName[i];
    }
}

//This Method return user login name
char* AccountInfo :: getUserLoginName()
{
    return _userLoginName;
}

//Method to set user password
void AccountInfo :: setPassword(char *password)
{
    //setting user password
    int length = 0;
    
    //reading the length of the passowrd
    while(password[length]!= END_CHAR)
    {
        length++;
    }
    
    //initilazing variable _password
    _password = new char[length+1];
    copyString(password,_password,length+1);
    
}

//This Method return user passowrd
char* AccountInfo ::getPassword()
{
    return _password;
}

void AccountInfo :: setGecos(char *gecos)
{
    
    int length = 0;
    
    //reading the length of the passowrd
    while(gecos[length]!= END_CHAR)
    {
        length++;
    }
    
    //initilazing variable _gecos
    _gecos = new char[length+1];
    
    //set value to _gecos
    copyString(gecos,_gecos,length+1);
    
}

//Method to get the gecos
char* AccountInfo ::getGecos()
{
    return _gecos;
}

//Method to set user account home
void AccountInfo :: setHome(char *home)
{
    
    int length = 0;
    //reading the length of the passowrd
    while(home[length]!= END_CHAR)
    {
        length++;
    }
    
    //initilazing variable _home
    _home = new char[length+1];
    copyString(home,_home,length+1);
    
    
    
}

//Method to get user home

char* AccountInfo::getHome()
{
    return _home;
}


//set user shell
void AccountInfo :: setShell(char* shell)
{
    int length = 0;
    //reading the length of the passowrd
    while(shell[length]!= END_CHAR)
    {
        length++;
    }
    //initilazing variable _shell
    _shell = new char[length+1];
    copyString(shell,_shell,length+1);
    
}

//get user shell
char* AccountInfo :: getShell()
{
    return _shell;
}

//ostream operator for AccountInfo class
ostream& operator<<(ostream& s,const AccountInfo& accountInfo)
{
    s<<endl<<endl<<"Login: ["<<accountInfo._userLoginName<<"]"<<endl<<"Directory: ["<<accountInfo._home<<"]"<<endl<<"Shell: ["<<accountInfo._shell<<"]"<<endl<<"Gecos: [";
    if(accountInfo._gecos!=NULL)
    {
        s<<accountInfo._gecos<<"]";
    }
    else
    {
        s<<"]";
    }
    return s;
}


//Defining the class UserDB
class UserDB
{
    //Declaring private data fields
    AccountInfo* _accounts[MAX_ACCOUNT_INFO];
    unsigned int _size;
    unsigned int _nextUid;
    unsigned int _defaultGid;
    //Declaring public methods
public:
    UserDB();// Empty constructor
    ~UserDB();//Default destructor
    void addUser(AccountInfo* newUser);//Add a new user to the DB
    void showUsers();//Method declaration to print all users
    void showPassword();//Method to print user info in paswad format
    void finger(char *userLoginName);//Method to finger account info
    int size();//Return number of account returned
    void setNextUId();
    unsigned int getNextUId();
    //friend function to oveload << operator
    friend ostream& operator<<(ostream&,const UserDB&);
    
    
};

//Implementation for deafualt constructor
UserDB :: UserDB()
{
    //setting default values
    _size = 0;
    _nextUid = FIRST_USER_ID;
    _defaultGid = DEFAULT_GROUP_ID;
    
    
}

//Implentation for defualt destructor
UserDB :: ~UserDB()
{
    for(int i = 0; i < size();i++)
    {
        if(_accounts[i] !=NULL)
        {
            delete _accounts[i];
        }
    }
}

//Method to set next user id
void UserDB ::setNextUId()
{
    _nextUid = _nextUid+1;
}

//Method to get next user id
unsigned int UserDB ::getNextUId()
{
    return _nextUid;
}

//Method to add account info
void UserDB :: addUser(AccountInfo* newUser)
{
    _accounts[_size] = newUser;
    _size++;
}

//Method to  all users
void UserDB:: showUsers()
{
    //Calling  the print
    cout<<endl;
    cout<<endl;
    cout<<"List of users:"<<endl;
    if(_size > 0)
    {
        for(unsigned int i = 0 ; i < _size;i++)
        {
            int length = 0;
            cout<<(*_accounts[i]).getUserLoginName()<<endl;
            
        }
    }
    if(_size == 0)
    {
        cout<<"There's no users found  in the system";
    }
    else if(_size == 1)
    {
        cout<<"1 user found in the system";
    }
    else
    {
        cout<<_size<<" users found in the system";
    }
}

//dispaly user information in password format
void UserDB::showPassword()
{
    cout<<*this;
}

//This method print user information which matches the given user login name
void UserDB::finger(char *userLoginName)
{
    bool isFound = false;
    char *tempUser;
    //check weather the user account info availble
    unsigned int count = 0;
    int wordCount;
    int mismatchCount;
    if(_size >0)
    {
        while(!isFound && count < _size)
        {
            tempUser = (*_accounts[count]).getUserLoginName();
            wordCount =0;
            mismatchCount = 0;
            while(userLoginName[wordCount]!= END_CHAR)
            {
                //Check Weather all characters are matching with the given user name
                if(userLoginName[wordCount] != tempUser[wordCount])
                {
                    mismatchCount++;
                }
                wordCount++;
                
            }
            if(mismatchCount == 0)
            {
                isFound = true;
                //Call AccountInfo Ostream operator
                cout<<*_accounts[count];
            }
            count++;
            
        }
    }
}

//Return the number of users in the User DB
int UserDB::size()
{
    return _size;
}

//ostream operator for UserDB class
ostream& operator<<(ostream& s,const UserDB& userDB)
{
    if(userDB._size > 0)
    {
        s<<endl;
        for(unsigned int i =0;i < userDB._size ; i++)
        {
            s<<endl;
            s<<userDB._accounts[i]->getUserLoginName();			
            if(userDB._accounts[i]->getPassword()!= END_CHAR)
            {
                s<<":"<<userDB._accounts[i]->getPassword();
            }
            else
            {
                s<<":x";
            }
            s<<":"<<userDB._accounts[i]->getUserId()<<":"<<userDB._accounts[i]->getGroupId();			
            if(userDB._accounts[i]->getGecos() != END_CHAR)
            {
                s<<":"<<userDB._accounts[i]->getGecos();
            }
            else
            {
                s<<":";
            }
            s<<":"<<userDB._accounts[i]->getHome()<<":"<<userDB._accounts[i]->getShell();
        }
    }
    return s;
}