// Created by Glasser Dillon, Mauldin Andrew, Peppas Alexis
// for CS3070 course project

#include <cstring>
#include <wait.h>
#include "VM.h"

using namespace std;


VM::VM(){
    this->in = "keyboard";
    this->out = "screen";
//    this->args.push_back(NULL);
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
    int fh, dummy;
    int fds[2];
    fds[0] = dup(0);
    fds[1] = dup(1);
    fds[2] = dup(2);

    // Check for special command. We keep this function in the parent process and not spawn another
    // to avoid IPC information leak
    if(this->getCmd().compare("encedit") == 0){
        if(this->getArgs().size() < 2){
            enceditHelp();
            return ERROR;
        }

        if(this->getArgs().size() > 2)
            return ERROR;

        encEdit* e = new encEdit(this->getArgs()[0].c_str(), this->getArgs()[1].c_str());
        dummy = e->open();
        if(dummy == 0){
            dummy = e->close();
        }
        return NO_ERROR;
    }

    // Fork new process
    newPid = fork();
    if(newPid < 0){
        cout << "Error spawning process." << endl;
        return ERROR;
    }

    // Child Process
    if (newPid == 0){

        // Do we have stdout redirection?
        if(this->getOut().compare("screen") != 0){

            // Open file to redirect to
            fh = open(&this->getOut()[0], O_RDWR | O_CREAT, 0666);

            if(fh < 0){
                cout << "Error opening file..." << endl;
                return ERROR;
            }

            // Redirect stdout
            dup2(fh, STDOUT);
            close(fh);
        }

        // Do we have stdin redirection?
        if(this->getIn().compare("keyboard") != 0){
            fh = open(&this->getIn()[0], O_RDONLY);

            if(fh < 0){
                cout << "Error opening file..." << endl;
                return ERROR;
            }

            // Redirect stdin
            dup2(fh, STDIN);
            close(fh);
        }

        // Use this if we want to completely change new process code
        // execlp("/usr/bin/xterm", "xterm", "-e", &vtos()[0], NULL);

        // Use this to invoke the shell to execute our command
        if(system(&vtos()[0]) == 0) {
            exit(NO_ERROR);
        }
        else{
            exit(ERROR);
        }
    }
        // Main process
    else{
        // Wait for child to end
        waitpid(newPid, NULL, 0);

        // If we had redirection restore it
        if(this->getOut().compare("screen") != 0) {
            dup2(STDOUT, fh);
        }
        if(this->getIn().compare("keyboard") != 0) {
            dup2(STDIN, fh);
        }
    }

    return NO_ERROR;
}


string VM::vtos(){
    string args = "";

    int i;

    // Add command to list of arguments
    if(this->getArgs().size() == 0){
        this->setArgs(this->getCmd());
    }
    else{
        this->args.insert(this->args.begin(), this->getCmd());
    }

    for(i=0; i<this->getArgs().size();i++){
        args = args + " " + this->getArgs()[i];
    }

    return args;
}


void VM::show_help(){
    cout << "cd\t\tChange Directory." << endl;
    cout << "ls\t\tList contents of current Directory." << endl;
    cout << "encedit\t\tOpen/create encrypted text file." << endl;
    cout << "any\t\tWill try to find an executable with that name and run it in a new window." << endl << endl;
}


void VM::enceditHelp() {
    cout << "Usage:\tencedit FILE_NAME PASSWORD" << endl;
    cout << "\tFILE_NAME\tthe file to open. If it does not exist it creates it." << endl;
    cout << "\tPASSWORD\tthe password used to encrypt/decrypt the file" << endl << endl;
}
