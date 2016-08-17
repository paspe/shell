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

    }
    else if(this->cmd.compare("ls") == 0){

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
        cout << newPid << " " << this->getCmd() << " " << args << endl;
        execlp("gnome-terminal", "gnome-terminal", "-x", "sh", "-c",  &this->cmd[0], args, "--noconsole", NULL);

    }
    return 0;
}


string VM::vtos(vector<string> s){
    string args;



    return args;
}