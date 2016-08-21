// Created by Glasser Dillon, Mauldin Andrew, Peppas Alexis
// for CS3070 course project

#ifndef SHELL_PARSER_H
#define SHELL_PARSER_H

#include "main.h"
#include "Tokenizer.h"
#include "VM.h"

using namespace std;

int parseLine(string);

string current();

void consume();
/*
int parser(string);
void split_on_space(const string&, char,vector<string>&);
int runProgram(string);
*/
#endif //SHELL_PARSER_H
