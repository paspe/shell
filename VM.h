// Created by Glasser Dillon, Mauldin Andrew, Peppas Alexis
// for CS3070 course project

#ifndef VM_H_VM_H
#define VM_H_VM_H

#include "encEdit.h"
#include "main.h"

using namespace std;

class VM {

    private:
        string cmd;
        vector<string> args;
        string in;
        string out;
        int val;
        int fork_proc(int);
        void show_help();
        void enceditHelp();
    public:
        VM();
        ~VM(){};

        //setters
        void setCmd(string);
        void setArgs(string);
        void setIn(string);
        void setOut(string);
        void setVal(int);

        //getters
        string getCmd();
        vector<string> getArgs();
        string getIn();
        string getOut();

        int execute(int);

};


#endif //VM_H_VM_H
