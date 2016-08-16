//
// Created by Dillon
//

#include <cstring>
#include "VM.h"

using namespace std;


void VM::setCmd( string command )
{
    cmd = command;
    return;

}

void VM::setArgs ( string arguments )
{
    args->push_back(arguments);
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

vector<string>* VM::getArgs(void)
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
    return fork_proc();
//    if(this->cmd.compare("cd") == 0){
//
//    }
//    else if(this->cmd.compare("ls") == 0){
//
//    }
//    else{
//        return fork_proc();
//    }
    return NO_ERROR;
}


int VM::fork_proc(){
    pid_t newPid;
    char **args;
    newPid = fork();

    if(newPid < 0){
        cout << "Error spawning process." << endl;
        return -1;
    }

    this->args->push_back(NULL);

    execvp(&this->cmd[0], args);

    return 0;
}
