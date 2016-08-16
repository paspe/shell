#ifndef SHELL_PARSER_H
#define SHELL_PARSER_H

#include <string>
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <cerrno>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <cstdlib>
#include <vector>

#include "Tokenizer.h"

using namespace std;

void parseLine(string);

string current();

void consume();
/*
int parser(string);
void split_on_space(const string&, char,vector<string>&);
int runProgram(string);
*/
#endif //SHELL_PARSER_H
