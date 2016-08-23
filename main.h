// Created by Glasser Dillon, Mauldin Andrew, Peppas Alexis
// for CS3070 course project

#ifndef SHELL_MAIN_H
#define SHELL_MAIN_H

#include <iostream>
#include <string>
#include <vector>
#include <unistd.h>
#include <fstream>
#include <fcntl.h>
#include <dirent.h>
#include <cstdlib>
#include <sys/stat.h>
#include <cerrno>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <csignal>

#include "parser.h"

#define STDIN 0
#define STDOUT 1
#define NO_ERROR 0
#define ERROR -1
#define PIPE_FILE "/tmp/pipefile.txt"

using namespace std;

string getDir();

#endif //SHELL_MAIN_H
