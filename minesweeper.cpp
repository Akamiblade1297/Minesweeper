#include "config.h"
#include <iostream>
#include <cstring>
#include <cstdlib>

#define HERE "--here"

int main ( int argc, char* argv[] ) {
    if ( argc == 1 )  {
        std::string term = TERM;
        std::string path = argv[0];
        std::string args = HERE;
        std::string cmd = term + " " + path + " " + args + " &";
        std::cout << cmd << std::endl;
        if ( system(cmd.data()) != 0 ) {
            std::cerr << "ERROR: Couldn't fork a process" << std::endl;
            exit(1);
        }
    } else if ( ! strcmp(argv[1], HERE) ) {
        std::cout << "Starting proccess here.." << std::endl;
    } else {
        std::cerr << "ERROR: Invalid argmunet" << std::endl;
        exit(1);
    }
    std::cout << "Launched game successfully!" << std::endl;
}
