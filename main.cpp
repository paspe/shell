#include <iostream>
#include "parser.h"

#define GetCurrentDir getcwd
#define MAXBUFFER 256

using namespace std;

//int main() {
//	parseLine("ls -a < file | stuff | more stuff > out");
//	return 0;
//}


string getDir();

int main() {
    string userInput;

    cout << "Entering the GMP Shell..." << endl << endl;

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

