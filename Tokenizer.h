//
// Created by halek on 8/2/16.
//

#ifndef SHELL_TOKENIZER_H
#define SHELL_TOKENIZER_H

#include <string>
#include <iostream>

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
