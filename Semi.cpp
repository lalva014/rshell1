#include "Semi.h"
#include <stdio.h>  //for perror and exit
#include <stdlib.h> // for malloc
#include <unistd.h> //library for Fork, execvp, watpid
#include <iostream>
#include <string>
#include <string.h>
#include <sys/wait.h>
using namespace std;



Semi::Semi(vector<string> p)
{
    c = p;
}
Semi::~Semi(){
                
        c.erase( c.begin(),c.end() ); // this should work. the function .end() goes all the way to the last thing in the vector.

    
}

bool Semi::execute(){
    char **argc =  ( char**)malloc(sizeof(char**)*(c.size()+ 1));           // allocates memory for char**
    vector<char*> v;                                                        // vector use to in the transfer of files 
    for(unsigned int i = 0; i < c.size(); i++){                              // converts all the strings of the vector into the char*
    string commandss = c.at(i);                                             // copy of the string
    char*array = (char*)malloc(c.at(i).size());                             // allocate memory for the v.
    strcpy(array, commandss.c_str());                                       // copy string into char*
    array = strtok(array,"&|");                                             // break it down into word by word in char*
    v.push_back(array);                                                     // push word char* in the vector 

    }
    for(unsigned int i= 0; i < v.size();i++){                               // copys the vector conten into the argc
        argc[i] = v.at(i);
    }        
    argc[c.size()] = NULL;                                                  // buts a null at the end
    pid_t pid = fork();                                                      // initiate fork
    if (pid == 0){                                                          // child running 
        
        if( execvp(argc[0], argc)  == -1){ // probably needs to be <0;      // probably needs to be <0;  
        perror("exert");
        return false;
        }
        else{
        //delete[] argv;
        return true;
        }
              
    } /// parent running                                                     /// parent running
    else if (pid > 0){
        wait(0);
        return true;
    }
    else
    {
        // fork failed
        cout << "Fork fails \n";
        exit(-1);
    }
        
    return true;
}