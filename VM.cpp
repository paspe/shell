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
    if(this->cmd.compare("cd") == 0){
        chdir(this->getArgs()[0].c_str());
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
    int fh;
    int fds[2];
    fds[0] = dup(0);
    fds[1] = dup(1);
    fds[2] = dup(2);

    //Check for redirection of stdout

    if(newPid < 0){
        cout << "Error spawning process." << endl;
        return -1;
    }

    // Child Process
    if (newPid == 0){

        // Do we have stdout redirection?
        if(this->getOut().compare("screen") != 0){

            // Open file to redirect to
            fh = open(&this->getOut()[0], O_RDWR | O_CREAT, 0777);

            if(fh < 0){
                cout << "Error opening file..." << endl;
                return -1;
            }

            // Redirect stdout
            dup2(fh, 1);
        }


        if(this->getCmd().compare("ls") == 0){

            DIR *dpdf;
            struct dirent *epdf;
            dpdf = opendir("./");
            if (dpdf != NULL){
                while (epdf = readdir(dpdf)){
                    if(epdf->d_name == ".\0" or epdf->d_name == "..") continue;
                    cout << epdf->d_name << endl;
                }
            }
            execlp("echo", "echo", NULL);

        }

        else{
            args = vtos(this->args);
            execlp("gnome-terminal", "gnome-terminal", "-x", "sh", "-c", &this->cmd[0], args, NULL);
        }
    }
        // Main process
    else{
        // Wait for child to end
        waitpid(newPid, NULL, 0);

        // If we had redirection restore it
        if(this->getOut().compare("screen") != 0) {
            dup2(1, fh);
            close(fh);
        }
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