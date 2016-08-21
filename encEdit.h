// Created by Glasser Dillon, Mauldin Andrew, Peppas Alexis
// for CS3070 course project

#ifndef SHELL_ENCEDIT_H
#define SHELL_ENCEDIT_H

#include "main.h"

using namespace std;

class encEdit {
private:
    string password;
    string file;
    string tmpfile;

    char* text;
    bool checkFileExists(string);

public:
    encEdit(string, string);
    int open();
    int close();
};


#endif //SHELL_ENCEDIT_H
