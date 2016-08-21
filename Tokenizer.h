// Created by Glasser Dillon, Mauldin Andrew, Peppas Alexis
// for CS3070 course project

#ifndef SHELL_TOKENIZER_H
#define SHELL_TOKENIZER_H

#include "main.h"

using namespace std;

class Tokenizer {
private:
    string line;
    string current_token;
    int pos;


public:
    Tokenizer();
    virtual ~Tokenizer();
    bool hasMoreTokens();
    void consumeNextToken();
    void setLine(string);
    string currentToken();



};


#endif //SHELL_TOKENIZER_H
