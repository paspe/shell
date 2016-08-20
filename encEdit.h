//
// Created by halek on 8/20/16.
//

#ifndef SHELL_ENCEDIT_H
#define SHELL_ENCEDIT_H

#include <string>
#include <iostream>

using namespace std;

class encEdit {
private:
    string password;
    string file;
    string tmpfile;

    char* text;
//    void encrypt();
//    void decrypt();
    bool checkFileExists(string);

public:
    encEdit(string, string);
    int open();
    int close();
};


#endif //SHELL_ENCEDIT_H
