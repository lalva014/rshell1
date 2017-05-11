#include "Command.h"
#include <unistd.h> //library for Fork, execvp, watpid
#include <stdio.h>  //for perror
#include <stdlib.h> // for malloc
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <iostream>
#include <sys/types.h> 

using namespace std;




//use fork
bool Command::execute(){
    int status;
    char **argc =  ( char**)malloc( sizeof( char** )*( c.size()+ 1 ) );   // allocates memory for char**
    vector<char*> v;                                            // vector use to in the transfer of files 
    for( unsigned int i = 0; i < c.size(); i++ ){                 // converts all the strings of the vector into the char*
        string commandss = c.at( i );                                 // copy of the string
        char*array = ( char* )malloc( c.at( i ).size() );                 // allocate memory for the v.
        strcpy( array, commandss.c_str() );                           // copy string into char*
        array = strtok( array,"&|" );                                 // break it down into word by word in char*
        v.push_back( array );                                         // push word char* in the vector 
        
    }
    for( unsigned int i= 0; i < v.size();i++ ){                   // copys the vector conten into the argc
        argc[i] = v.at(i);                          
    }        
    argc[c.size()] = NULL;                                      // buts a null at the end
    pid_t pid = fork();                                          // initiate fork 
  
    if (pid == 0){                                              // child running 
        if( execvp(argc[0], argc)  == -1){                      // probably needs to be <0;  
            perror(argc[0]);
            exit(2);
        }
                
                
              
    }                                                       /// parent running
    else if (pid > 0){
        wait(&status);
        wait(0);
        if(WIFEXITED(status)){
            if(WEXITSTATUS(status)){                        // outputs true or false dending on what happens in the child terminate with exit(2);
                return false;
            }
            return true;
        }
            
        if(WIFEXITED(status)){
            return false;
        }
        else {
            return true;
        }
    }
    else{
        // fork failed
        cout << "Fork fails \n";                        // outputs if fork fails
        exit(-1);
    }

       
        return true;
}