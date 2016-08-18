#include <iostream>
#include "parser.h"
#include "VM.h"

#define GetCurrentDir getcwd
#define MAXBUFFER 256

using namespace std;

//int main() {
////	parseLine("ls -a < file | stuff | more stuff > out");
//    VM* tmp = new VM;
//    tmp->setCmd("top");// "/home/halek/ClionProjects/shell/a.out");
////    tmp->setArgs("-l");
//    tmp->execute();
//
//	return 0;
//}


string getDir();

int main() {
    string userInput;

    cout << "Entering the GMP Shell..." << endl;
    cout << "Enter '?' for help" << endl << endl;

    while(1) {

        cout << getDir() << " :: ";
        getline(cin, userInput);
        if(parseLine(userInput) == -1){
            break;
        }
    }
    cout << "Goodbye..." << endl;
    return 0;
}



string getDir(){
    char cCurrentPath[FILENAME_MAX];

    if (!GetCurrentDir(cCurrentPath, sizeof(cCurrentPath)))
    {
        return "Error getting working directory...";
    }

    cCurrentPath[sizeof(cCurrentPath) - 1] = '\0';

    return cCurrentPath;
}

