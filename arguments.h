#pragma once
#include <iostream>
#include <cstring>

//FULL//
#define HELP  "--help"
#define HERE  "--here"
#define TERM  "--term"
#define TARGS "--targs"
#define WIDTH "--width"
#define HIGHT "--height"
#define BOMBS "--bombs"

//SHORT//
#define SHELP  "-h"
#define STERM  "-t"
#define STARGS "-a"
#define SWIDTH "-W"
#define SHIGHT "-H"
#define SBOMBS "-B"

//VARIABLES//
extern std::string terminal;
extern std::string term_args;
extern bool here;
extern int width;
extern int height;
extern int bombs;

extern bool term_set;
extern bool targ_set;
extern bool here_set;
extern bool wdth_set;
extern bool hght_set;
extern bool bmbs_set;

enum ArgumentError {
NOERROR = 0,
INVALID_ARGUMENT = 1,
TERM_WITH_HERE = 2,
MULTIPLE_ASSIGN = 3,
UNKNOWN_OPTION = 4,
TARGS_WITHOUT_TERM = 5,
};

//FUNCTIONS//
extern ArgumentError parseArgs ( int argc, char* argv[], int &i );
