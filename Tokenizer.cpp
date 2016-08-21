// Created by Glasser Dillon, Mauldin Andrew, Peppas Alexis
// for CS3070 course project

#include "Tokenizer.h"

Tokenizer::Tokenizer() {
    line = "";
    pos = 0;
}


Tokenizer::~Tokenizer() {}


bool Tokenizer::hasMoreTokens(){
    return pos < line.size();
}

void Tokenizer::setLine(string s){
    line = s;
    pos = 0;
    // cout << "Token " << s << endl;
    return;
}

void Tokenizer::consumeNextToken(){
    string token = "";
    int len = line.size();
    if(pos >= len){
        current_token = "EOF";
        return;
    }

    while(line[pos] != ' ' && pos < len){
        token += line[pos++];
    }
    pos++;
    current_token = token;
    // cout << "Consume Token" << current_token << endl;
    return;
}


string Tokenizer::currentToken() {
	// cout << "Current Token" << current_token << endl;
    return current_token;
}
