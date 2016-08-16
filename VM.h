//
// Created by Dillon
//

#ifndef VM_H_VM_H
#define VM_H_VM_H
#include <iostream>
#include <string>
#include <vector>

using namespace std;


class VM {

    private:
        string cmd;
        // FIX?
        vector<string> *args;
        string in;
        string out;
    public:
        //setters
        void setCmd(string);
        void setArgs(string);
        void setIn(string);
        void setOut(string);

        //getters
        string getCmd();
        vector<string>* getArgs();
        string getIn();
        string getOut();

        void execute();

};


#endif //VM_H_VM_H
