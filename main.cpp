#include <iostream>
#include <sstream>      // std::stringstream
#include <string.h>
#include <stdlib.h>
#include <vector>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include "Base.h"
#include "Semi.h"
#include "Command.h"
#include "And.h"
#include "Or.h"


using namespace std;
                                                                        // it converts a string into an array of char*
char * Convert(string line){
    char *array =  (char*)malloc( line.size() );                          // allocates memory 
    strcpy( array, line.c_str() );                                        // converts string into char*
    return array;                                                       // return char*

} 


void execute(vector<Base*> B){
    for(unsigned i = 0; i < B.size(); i++){
        pid_t pid = fork();
                                                //child running 
        if (pid == 0){
                ( B.at(i) )->execute();         // execute the base
        } /// parent running
        else if (pid > 0){     // parent runing youw wait
            wait(NULL);
        }
        else{
            cout << "Fork fails \n";          // fork failed
            exit(-1);
        }
    }
}

Base * BuiltTree(string line){                  // built a tree with the command passed in
    string l = line;                            // copy the string
    char * pointer= Convert(line);              // conver string to char*
    stringstream broken;                        
    broken << l;                                // string into the streamstring 
    string single;                              // where the stream will go to 
    vector<string> v;                           // vector of strings
    bool start =  false;                        // the flag 
    vector<Base*> VB;                           // where the vase will be store

    while(broken >> single){                    // string store into
        if(single == "&&"){
            if(false == start){                 // two commands made here else just one
                Command * c1 = new Command(v);  // make a command 
                pointer = strtok(pointer,"&|"); // finding the next command
                pointer = strtok(NULL, "&|");   // gets second command
                string loc(pointer);            // second command into string
                stringstream nextCom(loc);      // convert into words
                string x;                       // store word here
                vector<string> nol;             // string
                while(nextCom >> x){            
                    nol.push_back(x);           // store the command and flags in the vector string
                }
                Command * c2 = new Command(nol);    //mak a new command
                And * n = new And(c1, c2);          // make and And 
                VB.push_back(n);                    // push into the VB
                start = true;                   /// turn flag off
            }
            else{
                pointer = strtok(NULL, "|&");       // get the next command
                string p(pointer);
                stringstream f(p);              // convert into stream and then string
                string co;
                vector<string> w;
                while(f >> co ){                // store command and flags in vector
                    w.push_back(co);
                }       
                Command* c = new Command(w);        // make new command
                Base* temp = new And(VB.at(0), c);  // passed in the previousone and the command
                VB.at(0) = temp;                    // point VB into the top of the tree
            }
            
        }
        else if( single == "||" ){                    // if or 
            if( false == start ){                     // first should make two commands
                Command * c1 = new Command( v );      // make a command
                pointer = strtok(pointer,"&|");     // look for th enext command
                pointer = strtok(NULL, "&|");
                string loc(pointer);                // transfer the next string to char using strtoke
                stringstream nextCom(loc);          // the tring into individual commands
                string x;                           
                vector<string> nol;
                while(nextCom >> x){
                    nol.push_back(x);               // push into the vector 
                }
                Command * c2 = new Command(nol);    // make a new command 
                Or * n = new Or(c1, c2);            // push both inot the or that was made
                VB.push_back(n);                    // push back into the VB

                start = true;
            }
            else{
                 pointer = strtok(NULL, "|&");  // case two  only one command 
                string p(pointer);              //convert pointer to string
                stringstream f(p);              // stream inot the string 
                string co;                  
                vector<string> w;   
                while(f >> co ){    
                    w.push_back(co);            // put it into the vector 
                }
                Command* c = new Command(w);    // make a new command
                Base* temp = new Or(VB.at(0), c);   // base command
                VB.at(0) = temp;                // repoint the tree     
            }    
        }
        v.push_back(single);
    }
  return VB.at(0); 
}


vector<string> split(char* l){                  // splits the original command by the ;
    vector<string> v;                   
    char *pointer  = strtok(l,";");             // splits at the ;
    string p(pointer);                          // cpmverts it to string and store
    v.push_back(p);                             // push the v back
    pointer  = strtok(NULL,";");                //  continue where you left off 
    while(pointer != 0){                        // do it till the end of the llooop
        string s(pointer);                      // conver string
        s.erase(0,1);                           // erase the string 
        v.push_back(s);                         // push back;
        pointer  = strtok(NULL,";");                    
    }
    return v;
} 
 bool checkQuit(string line){
    string w = line;
    char *point = Convert(w);
    point = strtok(point, " ");
    // string temp(point);
    // stringstream word;                           stream word 
    // word.str("");                                clearingthe stream of word
    // word.clear();                                more clearing
    // word << line;                               dumps the content of line into word.
    
    while (point != NULL){                          // line is a sentence so when it word does this to a string it only outputs word by word.
        // // cout << w << endl;
        string temp(point);
        if(temp == "exit"){                        // checks for quit 
            return true;
        }
        if(temp == "Exit"){
            return true;
        }
        
        point = strtok(NULL, " ");
    }
    return false;
 }
 
void semi(vector<string>& commands, vector<Base*> &b){

    vector<int> num; 
    if(commands.size() == 1){                               // if there is just one command check if its a semi
            char * pointer = Convert(commands.at(0));
            pointer = strtok(pointer, "&|");                // check for |&
            string check(pointer);                          // convert to string
            if(check == commands.at(0)){                    // if not  &| then make a semi
                if(check !=  "" ){                          // if not empty string make semi
                    vector<string>v;                    
                    stringstream p(commands.at(0));         // convert the string to stream
                    string single;                          // make a string
                    while(p >> single){
                        v.push_back(single);                // push back the v
                    }   
                    Base * s = new Semi(v);                 // make a new semi
                    b.at(0) = s;
                    commands.at(0) = "";
                    num.push_back(0);
                }
            }
    }
    else{
        char * f = Convert(commands.at(0));  // convert the command to a char
        f = strtok(f, "|&");
        string test(f);                                 // char to string
        if(test == commands.at(0)){                     // check if the command is the same then there is a semi
            // if(test != ""){                             // chek for empty string
                vector<string>v;
                stringstream p(commands.at(0));         // convert string to teh stream
                string single;                          // single line 
                while(p >> single){                     // while loop keeps converting apushing to tit 
                    v.push_back(single);                // put word into the vector
                }
                Base * sv = new Semi(v);                // make a semi
                b.at(0)= sv;                            // sv the vector
                commands.at(0) = "";                    // commands ""
            // }
        }
        unsigned i = 1;
        char * w = Convert(commands.at(i));
        char * point = strtok(w, "|&");
        while(point != NULL){                           // checks for multiple ; in the command
            string t(point);                            // converts the char* to string
            if(t == commands.at(i) ){                   // chck if its the same then make command
                           // check that its not empty
                    vector<string>v;
                    stringstream w(commands.at(i));
                    string single;
                    while(w >> single){
                        v.push_back(single);            // converts into the v which we passed into the new semi
                    }
                    Base * s = new Semi(v);             /// new semi made
                    b.at(i)= s;
                    commands.at(i) = "";                // so that they output in the same order
                              
                
                }
                if(commands.size() == i + 1){           // check to break the loop
                    break;
                }
                i++;
                w = Convert(commands.at(i));            // moves into the next command to check for semi
                point = strtok(w, "|&");

            
            }

        
    }
    

    

    
 }
vector<Base*> Tree( vector <Base*>& b,vector<string> v ){          // builts the tree
    vector<string> s;                                           
    Base* pointer;
    for(unsigned i = 0;  i < v.size(); i++ ){               // forloop that checks to built commands
        if(v.at(i) != ""){                                  // if empty dont built tree they are semi
            pointer = BuiltTree( v.at(i) );               // we call that function
            b.at(i) =pointer;                               // point it to the root
        }
    }
    return b;                                               // return the vector of bases
}   
 string checkComment(string line){          /// checks for comments
    char * pointer = Convert( line );                   // converts to char*
    pointer = strtok( pointer, "#" );               // loops for #
    string newLine( pointer );                      // converts to string and return 
    
    return newLine;
    
 }
 
vector<string> checkAO( vector<string>  s ){            // checks for the signle & or | case of vector 
    bool t = false;    // flag
    for(unsigned int i = 0; i < s.size(); i++){         // checks if there is any & or |
        char* pointer = Convert( s.at(i) );        
        pointer = strtok( pointer, " " );               // firts space or word
        while(pointer != NULL){                         // while not null loop
            string temp(pointer);                       // convert to string and check for single | or &
            if( temp == "&" || temp == "|" ){
                t = true;                                   // if true set flag true so that it doesnt do anything
            }
            pointer = strtok( NULL, " " );              /// move to next 
        }

    }
    if( t == true ){                                    // if flag true delete the vector
         s.erase(s.begin(), s.end());
                    return s;
    }
    return s;
    
}
 
// where we run the loop
void command(){
    vector<string> v;
    vector <Base*> b;
    vector <string> cn;
    while(true){
        cout << "$ ";
        string line;
        getline(cin,line);                          // gets the commands 
        line = checkComment(line);                  // ignores everything after the #
        if( checkQuit(line) ) break;                /// checks if the word Quit is in them. if so exits the shell
        char *l = Convert(line);                    // converts the string line to a char* 
        v = split(l);                               // it return a vector of char* each of them is a command follow by its paramaters;

        b.resize(v.size());                         // the number of base in the vector.
        semi(v,b);                                  // returns all of the commands are executed right away in a vector of bases; cn is commandss

        b = Tree(b,v);
        v.erase(v.begin(), v.end());
        execute(b);

        
    }       
    
}

int main(){
    command();
// 
    return 0;
}