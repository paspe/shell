// Created by Glasser Dillon, Mauldin Andrew, Peppas Alexis
// for CS3070 course project

#include "parser.h"

using namespace std;

/*
string Test[] = {"ls", "-arg", "<", "foo_file", "|", "cd", "|", "fail", "EOF"};
string ct;
unsigned int cti = 0;

// function for just testing until Tokenizer is complete
string current(){
	if (cti < 0){
		return NULL;
	}
	return Test[cti];
}

// function for testing until Tokenizer is complete
void consume(){
	if (cti < sizeof(Test)/sizeof(*Test)){
		cti++;
	}
	return;
}
*/

// Takes a string and parses the line into its components - cmd, args, pipes, redirections
// The function loops through parsing the line into is commands to generate VMs. The VMs are
// executed after a complete VM is created.  After the VM has completed execution, it then
// parses the rest of the commands.
int parseLine(string line){

	Tokenizer* token = new Tokenizer();
	token->setLine(line);

	bool pipe = false;
	int numArgs = 0;
	string cmd;
	string* args = NULL;
	string input;
	string output;

	VM* vm = new VM();

	while (token->hasMoreTokens()) {

		// Case that the previous command was pipe
		if (pipe){
			input = "in_pipe";
		}
		else{
			input = "keyboard";
		}
		token->consumeNextToken();
		// cout << "In the parser" << endl;
		// Command
		cmd = token->currentToken();
		token->consumeNextToken();

		// Arguments
		while (token->currentToken().compare("<") != 0 && token->currentToken().compare(">") != 0 && token->currentToken().compare("|") != 0 && token->currentToken().compare("EOF") != 0){//token->hasMoreTokens()){
			string tempArgs[numArgs+1];
			copy(args, args+numArgs, tempArgs);
			numArgs++;
			args = new string[numArgs];
			copy(tempArgs, tempArgs+numArgs, args);
			args[numArgs-1] = token->currentToken();
			token->consumeNextToken();
		}

		// Input Redirection
		if (token->currentToken().compare("<") == 0 && !pipe){
			token->consumeNextToken();
			input = token->currentToken();
			token->consumeNextToken();
		}

		// Pipe or Output Redirection.
		// Pipe here
		if (token->currentToken().compare("|") == 0){
			//token->consumeNextToken();
			output = "out_pipe";
			pipe = true;
		}
		// Output Redirection
		else if (token->currentToken().compare(">") == 0){
			token->consumeNextToken();
			output = token->currentToken();
			token->consumeNextToken();
		}
		else{
			output = "screen";
		}

        if(cmd.compare("exit") ==0){
            return -1;
        }
		// Execute VM here


		vm->setCmd(cmd);
		vm->setIn(input);
		vm->setOut(output);
//		cout << cmd << "\t ";
//		for(int i = 0; i < numArgs; i++){
//			cout << args[i] << ' ';
//			vm->setArgs(args[i]);
//		}
//		cout << "\t " << input << "\t " << output << "\n";
		vm->execute();

		numArgs = 0;

	}
	delete vm;
	delete token;
	return 0;
}


/*
int parser(string userInput){
    string command;
    vector<string> tokens;
    char delim = char(32);

    split_on_space(userInput, delim, tokens);
    command = tokens[0];

    if(command.compare("gt") == 0){
        chdir(tokens[1].c_str());
    }

    else if(command.compare("exit") == 0){
        return -1;
    }

    else if(command.compare("list") == 0){
        system("ls -la");
    }

    else if(command.compare("run") == 0){

        if(tokens[1].size() == 0){
            cout << "Nothing to run." << endl;
        }
        if(runProgram(tokens[1]) == -1){
            cout << "Error running program." << endl;
        }
        else{
            cout << "Running " << tokens[1] << endl;
        }
    }

    else if(command.compare("?") == 0){
        cout << "Available command:" << endl;
        cout << "\tlist\t\tView the current directory contents" << endl;
        cout << "\tgt\t\t\tGoTo directory specified" << endl;
        cout << "\trun\t\t\tRun the program specified" << endl;
        cout << "\texit\t\tExit the current shell" << endl << endl;
    }

    else{
        cout << "Unknown command." << endl;
    }

    return 0;
}


void split_on_space(const string& s, char delim, vector<string>& v) {
    size_t i = 0;
    size_t pos = s.find(delim);

    while (pos != string::npos) {
        v.push_back(s.substr(i, pos-i));
        i = ++pos;
        pos = s.find(delim, pos);

        if (pos == string::npos)
            v.push_back(s.substr(i, s.length()));
    }
    if(v.size() == 0){
        v.push_back(s);
    }
}


int runProgram(string arg){



    return 0;
}
*/
