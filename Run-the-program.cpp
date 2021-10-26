#include "utilities.cpp"
#include "fileSystemSim.cpp"

#include <dirent.h>
#include <stdio.h>
#include <iostream>
#include <direct.h>
#include <vector>
#include <string.h>
#include <windows.h>
#include <sys/types.h>
#include <sys/stat.h>

using namespace std;



// THE SKELETON BELOW HAS BEEN PROVIDED TO GIVE YOU IDEAS
// YOU CAN ADD ANY OTHER COMPONENT YOU WISH TO ADD


string theDirectory = replaceSlash(getCurrentDirectoryOnWindows()) + "\\\\root";
char * rootDirectoryMain = const_cast<char*>(theDirectory.c_str());

int main(){
    printWelcomeDisplay();

    // Create the root.
    //Directory * pwd = new Directory(); // pwd stands for present working directory
    // At the beginning the pwd is the root. It is the only directory created, so far.
    Directory * pwd = new Directory();
    // Initialize some variables
    string input;
    vector<string> args;

    char * PATH = rootDirectoryMain;

    deleteDirs(PATH);

    if(pwd->deleteMakeRoot() == -1){
        cout << "PLEASE DELETE THE FOLDER NAMED ''ROOT'' FOLDER THEN RESTART THE PROGRAM !!" <<endl;
    }else{
        // A loop that will run until 'exit' is typed
        while(true){
            // Get a command from the user
            cout << "Mitch:" << pwd->getPath() << " $ "; // this mimics the Linux (ubuntu) command prompt
            getline(cin, input); // put the entire line onto input
            if(input == "exit") break;

            // Tokenize the input
            args = splitString(input);

            // Run the command
            pwd = runCommand(pwd, args);

        }
    }



    return 0;
}


