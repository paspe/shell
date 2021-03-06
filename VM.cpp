// Created by Glasser Dillon, Mauldin Andrew, Peppas Alexis
// for CS3070 course project

#include <cstring>
#include <wait.h>
#include "VM.h"

using namespace std;


VM::VM(){
    this->in = "keyboard";
    this->out = "screen";
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


void VM::setVal(int v){
    val = v;
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


int VM::execute(int val)
{
    if(this->cmd.compare("cd") == 0){
        chdir(this->getArgs()[0].c_str());
    }
    else if(this->cmd.compare("?") == 0){
        show_help();
    }
    else if(this->getCmd().compare("pid") == 0){
        cout << "Current process ID: " << getpid() << endl;
    }
    else{
        return fork_proc(val);
    }
    return NO_ERROR;
}


int VM::fork_proc(int val){
    pid_t newPid;
    int fh, fh1, dummy;
    char** args;
    args = new char*[this->getArgs().size()+2];

    // Create the two possible pipefiles
    string pipefile = "/tmp/pipefile";
    pipefile.push_back((char)val);
    string prev_pipefile = "/tmp/pipefile";
    prev_pipefile.push_back((char)(val-1));

    // Check for special command. We keep this function in the parent process and not spawn another
    // to avoid IPC information leak

    if(this->getCmd().compare("encedit") == 0){

        // If arguments are not exactly 2 return error
        if(this->getArgs().size() != 2){
            enceditHelp();
            return ERROR;
        }

        // Open file
        encEdit* e = new encEdit(this->getArgs()[0].c_str(), this->getArgs()[1].c_str());
        dummy = e->open();
        if(dummy == 0){
            // Wait till the file closes
            dummy = e->close();
            if(dummy != 0)
                return ERROR;
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

            // Do we have pipe?
            if(this->getOut().compare("out_pipe") == 0){
                this->setOut(pipefile);
            }

            // Open file to redirect to
            fh = open(&this->getOut()[0], O_RDWR | O_CREAT, 0777);

            if(fh < 0){
                cout << "Error opening file..." << endl;
                return ERROR;
            }
            ftruncate(fh, 0);
            // Redirect stdout
            dup2(fh, STDOUT);
            close(fh);
        }

        // Do we have stdin redirection?
        if(this->getIn().compare("keyboard") != 0){

            // Do we have pipe?
            if(this->getIn().compare("in_pipe") == 0){
                this->setIn(prev_pipefile);
            }

            // Check file exists
            if (FILE *file = fopen(this->getIn().c_str(), "r")) {
                fclose(file);
            } else {
                cout << "File does not exist..." << endl;
                kill(getpid(), SIGKILL);
            }

            // Open file to redirect from
            fh1 = open(&this->getIn()[0], O_RDONLY, 0777);

            if(fh1 < 0){
                cout << "Error opening file..." << endl;
                return ERROR;
            }

            // Redirect stdin
            dup2(fh1, STDIN);
            close(fh1);
        }


        // Convert Command and Arguments to char** to pass to execvp
        args[0] = (char*)this->getCmd().c_str();

        for(int q = 0;q < this->getArgs().size();q++){
            args[q+1] = (char*)this->getArgs()[q].c_str();
        }
        args[this->getArgs().size() + 1] = NULL;    // Add NULL pointer at the end of the args array

        // Change executable code of the child process
        execvp(args[0], args);

        // If we reached here, there was an error so return error number
        if(this->getOut().compare("screen") != 0){
            dup2(STDOUT, fh);
        }
        cout << "There was an error launching the program. Error: " << errno << endl;
        kill(getpid(), SIGKILL);

    }
        // Main process
    else{
        // Wait for child to end
        //TODO: option to wait or not
        waitpid(newPid, NULL, 0);

    }

    return NO_ERROR;
}


void VM::show_help(){
    cout << "cd\t\tChange Directory." << endl;
    cout << "ls\t\tList contents of current Directory." << endl;
    cout << "pid\t\tPrint the current process ID." << endl;
    cout << "encedit\t\tOpen/create encrypted text file." << endl;
    cout << "any\t\tWill try to find an executable with that name and run it in a new window." << endl << endl;
}


void VM::enceditHelp() {
    cout << "Usage:\tencedit FILE_NAME PASSWORD" << endl;
    cout << "\tFILE_NAME\tthe file to open. If it does not exist it creates it." << endl;
    cout << "\tPASSWORD\tthe password used to encrypt/decrypt the file" << endl << endl;
}
