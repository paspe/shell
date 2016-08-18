//
// Created by Dillon
//

#include <cstring>
#include <wait.h>
#include "VM.h"

using namespace std;


VM::VM(){
    this->in = "keyboard";
    this->out = "screen";
//    this->args = "";
}


void VM::setCmd( string command )
{
    cmd = command;
    return;

}


void VM::setArgs ( string arguments )
{
    args.push_back(arguments);
    return;
}


void VM::setIn( string settingIn )
{
    in = settingIn;
    return;

}


void VM::setOut( string settingOut )
{
    out = settingOut;
    return;

}


string VM::getCmd(void)
{
    return cmd;
}


vector<string> VM::getArgs(void)
{
    return args;
}


string VM::getIn(void)
{
    return in;
}


string VM::getOut(void)
{
    return out;
}


int VM::execute(void)
{
//    return fork_proc();
    if(this->cmd.compare("cd") == 0){
        chdir(this->getArgs()[0].c_str());
    }
    else if(this->cmd.compare("ls") == 0){

    }
    else if(this->cmd.compare("?") == 0){
        show_help();
    }
    else{
        return fork_proc();
    }
    return NO_ERROR;
}


int VM::fork_proc(){
    pid_t newPid;
    string args;
    newPid = fork();

    if(newPid < 0){
        cout << "Error spawning process." << endl;
        return -1;
    }

    if (newPid == 0){

        args = vtos(this->args);
        execlp("gnome-terminal", "gnome-terminal", "-x",  &this->cmd[0], args, NULL);
//        execlp(&this->cmd[0],  &this->cmd[0], args, NULL);

    }
    return 0;
}


string VM::vtos(vector<string> s){
    string args = "";

    int i;

    for(i=0; i<s.size();i++){
        args = args + s[i];
    }

    return args;
}


void VM::show_help(){
    cout << "cd\t\tChange Directory." << endl;
    cout << "ls\t\tList contents of current Directory." << endl;
    cout << "any\t\tWill try to find an executable with that name and run it in a new window." << endl << endl;
}