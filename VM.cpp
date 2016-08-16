//
// Created by Dillon
//

#include "VM.h"
#include <iostream>
#include <string>
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
    if(this->cmd.compare("exit")){
        return EXIT;
    }
    else if(this->cmd.compare("cd")){

    }
    else if(this->cmd.compare("ls")){

    }
    else{
        return ERROR;
    }
    return NO_ERROR;
}



