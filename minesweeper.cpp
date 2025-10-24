#include "defaults.h"
#include "arguments.h"
#include "field.h"
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <stdexcept>
#include <string>

std::string terminal = DTERM;
std::string term_args = DTARGS;
bool here  = DHERE;
size_t width  = DWIDTH;
size_t height = DHIGHT;
size_t bombs  = DBOMBS;

bool term_set, starg_set, here_set, wdth_set, hght_set, bmbs_set = false;

void print_help () {
    std::cout << "usage: minesweeper [options]" << std::endl;
    std::cout << '\t' << HELP  << "\t\t" << SHELP  << "\tshow this page" << std::endl;
    std::cout << '\t' << WIDTH << "\t\t" << SWIDTH << "\tset field width" << std::endl;
    std::cout << '\t' << HIGHT << "\t"   << SHIGHT << "\tset field height" << std::endl;
    std::cout << '\t' << BOMBS << "\t\t" << SBOMBS << "\tset the number of bombs" << std::endl;
    std::cout << '\t' << TERM  << "\t\t" << STERM  << "\tset terminal to spawn in a game(excludes " << HERE << " option)" << std::endl;
    std::cout << '\t' << TARGS << "\t\t" << STARGS << "\tset arguments for terminal (must be with " << TERM << " option)" << std::endl;
    std::cout << '\t' << HERE  << "\t\t" << "\trun game on the current terminal(excludes " << TERM << " option)" << std::endl;
    std::cout << "default: minesweeper " << WIDTH << ' ' << DWIDTH << ' ' << HIGHT << ' ' << DHIGHT << ' ' << BOMBS << ' ' << DBOMBS << ' ';
    if ( DHERE ) std::cout << HERE << std::endl;
    else std::cout << TERM << ' ' << DTERM << ' ' << TARGS << " '" << DTARGS << "'" << std::endl;
    exit(0);
}

ArgumentError parseArgs( int argc, char* argv[], int &i ) {
    for ( i = 1 ; i < argc ; i++ ) {
        if ( !strcmp(argv[i], HELP) || !strcmp(argv[1], SHELP) ) print_help();
        else if ( !strcmp(argv[i], HERE) ) {
            if ( here_set ) return MULTIPLE_ASSIGN;
            else if ( term_set ) return TERM_WITH_HERE;
            here = true;
            here_set = true;
        } else if ( !strcmp(argv[i], TERM) || !strcmp(argv[i], STERM) ) {
            if ( term_set ) return MULTIPLE_ASSIGN;
            else if ( here_set ) return TERM_WITH_HERE;
            terminal = argv[++i];
            here     = false;
            term_set = true;
        } else if ( !strcmp(argv[i], TARGS) || !strcmp(argv[i], STARGS) ) {
            if ( starg_set ) return MULTIPLE_ASSIGN;
            else if ( ! term_set ) return TARGS_WITHOUT_TERM;
            term_args = argv[++i];
            starg_set = true;
        } else if ( !strcmp(argv[i], WIDTH) || !strcmp(argv[i], SWIDTH) ) {
            if ( wdth_set ) return MULTIPLE_ASSIGN;
            long int w;
            try {
                w = std::stoi(argv[++i]);
            } catch ( std::invalid_argument )
                { return INVALID_ARGUMENT;
            } catch ( std::out_of_range )
                { return INVALID_ARGUMENT; }
            if ( w < 0 ) return INVALID_ARGUMENT;
            width = w;
            wdth_set = true;
        } else if ( !strcmp(argv[i], HIGHT) || !strcmp(argv[i], SHIGHT) ) {
            if ( hght_set ) return MULTIPLE_ASSIGN;
            long int h;
            try {
                h = std::stoi(argv[++i]);
            } catch ( std::invalid_argument )
                { return INVALID_ARGUMENT;
            } catch ( std::out_of_range )
                { return INVALID_ARGUMENT; }
            if ( h < 0 ) return INVALID_ARGUMENT;
            height = h;
            hght_set = true;
        } else if ( !strcmp(argv[i], BOMBS) || !strcmp(argv[i], SBOMBS) ) {
            if ( bmbs_set ) return MULTIPLE_ASSIGN;
            long int b;
            try {
                b = std::stoi(argv[++i]);
            } catch ( std::invalid_argument )
                { return INVALID_ARGUMENT;
            } catch ( std::out_of_range )
                { return INVALID_ARGUMENT; }
            if ( b < 0 ) return INVALID_ARGUMENT;
            bombs = b; 
            bmbs_set = true;
        } else {
            return UNKNOWN_OPTION;
        }
    }

    return NOERROR;
};

void fork ( int argc, char *argv[] ) {
    std::string path = argv[0];
    std::string args;
    for ( int i = 1 ; i < argc ; i++ ) {
        // std::cout << i << ' ' << argv[i] << std::endl;
        if ( strcmp(argv[i], TERM) && strcmp(argv[i], STERM) && strcmp(argv[i], TARGS) && strcmp(argv[i], STARGS) ) {
            args += argv[i];
            args += ' ';
        } else i++;
    } args += HERE;
    std::string cmd = "setsid " + terminal + ' ' + term_args + ' ' + path + ' ' + args + ' ' + " 0>/dev/null";
    if ( system(cmd.data()) != 0 ) {
        std::cerr << "ERROR: Couldn't fork a process" << std::endl;
        exit(1);
    }
    exit(0);
}

int main ( int argc, char* argv[] ) {
    int i;
    std::string option;
    switch ( parseArgs(argc, argv, i) ) {
        case NOERROR:
            break;
        case INVALID_ARGUMENT:
            option = argv[i-1];
            std::cerr << "ERROR: Invalid argument passed for " << option << " option" << std::endl;
            exit(1);
        case TERM_WITH_HERE:
            std::cerr << "ERROR: Options " << TERM << " and " << HERE  << " can't be used together" << std::endl;
            exit(1);
        case MULTIPLE_ASSIGN:
            option = argv[i];
            std::cerr << "ERROR: Option " << option << " passed multiple times" << std::endl;
            exit(1);
        case UNKNOWN_OPTION:
            option = argv[i];
            std::cerr << "ERROR: Unknown option """ << option << '"' << std::endl;
            exit(1);
        case TARGS_WITHOUT_TERM:
            std::cerr << "ERROR: Option " << TARGS << " passed before the Option " << TERM << std::endl;
            exit(1);
    }
    if ( !here ) fork(argc, argv);

    Field field ( width, height, bombs );
    field.printField();
    std::cout << "Launched game successfully!" << std::endl;
}
