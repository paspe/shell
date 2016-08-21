//
// Created by halek on 8/20/16.
//

#include "encEdit.h"

encEdit::encEdit(string f, string p){
    password = p;
    file = f;
    tmpfile = "~" + f;
}


bool encEdit::checkFileExists(string s) {
    if (FILE *file = fopen(s.c_str(), "r")) {
        fclose(file);
        return true;
    } else {
        return false;
    }
}

int encEdit::open() {
    string cmd;

    if(this->checkFileExists(this->file)){
        cmd = "openssl enc -aes-256-ofb -d -in " + this->file;
        cmd = cmd + " -out " + this->tmpfile + " -K " + this->password + " -iv ff";
        system(&cmd[0]);
        cmd = "gedit " + this->tmpfile;
        system(&cmd[0]);
    }
    else{
        cmd = "gedit " + this->tmpfile;
        system(&cmd[0]);
    }
    return 0;
}


int encEdit::close() {
    string cmd;

    if(this->checkFileExists(this->tmpfile)) {
        cmd = "openssl enc -aes-256-ofb -e -in " + this->tmpfile;
        cmd = cmd + " -out " + this->file + " -K " + this->password + " -iv ff";
        system(&cmd[0]);
    }
    if(this->checkFileExists(this->tmpfile)) {
        remove(&this->tmpfile[0]);
    }
    return 0;
}