#pragma once

#include <algorithm>
#include <bitset>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <memory>
#include <string>

//COLORS//
#define UNKNWBG   "\e[48;5;250m"
#define ACKBG     "\e[48;5;243m"
#define BORDER    "\e[48;5;240m"
#define EXPLODEBG "\e[41m"

#define FLAGFG  "\e[31m"
#define ONEFG   "\e[1;38;21m"
#define TWOFG   "\e[1;38;76m"
#define TRIFG   "\e[1;31m"
#define FORFG   "\e[1;38;5;17m"
#define FIVFG   "\e[1;38;5;52m"
#define SIXFG   "\e[1;38;5;45m"
#define SEVFG   "\e[1;38;5;16m"
#define EITFG   "\e[1;38;5;250m"

//FIELDS
#define CUNKNOWN UNKNWBG     "  " BORDER " "
#define CEMPTY   ACKBG       "  " BORDER " "
#define CONE     ACKBG ONEFG "1 " BORDER " "
#define CTWO     ACKBG TWOFG "2 " BORDER " "
#define CTHREE   ACKBG TRIFG "3 " BORDER " "
#define CFOUR    ACKBG FORFG "4 " BORDER " "
#define CFIVE    ACKBG FIVFG "5 " BORDER " "
#define CSIX     ACKBG SIXFG "6 " BORDER " "
#define CSEVEN   ACKBG SEVFG "7 " BORDER " "
#define CEIGHT   ACKBG EITFG "8 " BORDER " "
#define CFLAG    ACKBG       " " BORDER " "
#define CWRNGFLG UNKNWBG     "X" BORDER " "
#define CEXPLODE EXPLODEBG   "✶"  BORDER " "

//FIELD
template<size_t N>
class Field {
public:
    enum Cell {
    EXPLODED   = -4,
    WRONG_FLAG = -3,
    FLAG       = -2,
    UNKNOWN    = -1,

    EMPTY = 0,
    ONE   = 1,
    TWO   = 2,
    THREE = 3,
    FOUR  = 4,
    FIVE  = 5,
    SIX   = 6,
    SEVEN = 7,
    EIGHT = 8,
    };

    int get( int i, int j, bool bomb ) {
        if ( i >= height || j >= width || i < 0 || j < 0 ) {
            std::cerr << "ERROR: Tried to get matrix element out of bounds";
            exit(1);
        };
        size_t n = ( i*width ) + j;
        return bomb ? bomb_matrix[n] : matrix[n];
    }

    void printField () {
        for ( int i = 0 ; i < height ; i++ ) { std::cout << BORDER;
        for ( int j = 0 ; j < width ; j++ ) {
            std::cout << Field::Cell_String(this->get(i, j, 0));
        } std::cout << BORDER << std::endl;
        }
    }

    static std::string Cell_String ( Cell cell ) {
        switch ( cell ) {
            case EMPTY:
                return CEMPTY;
            case ONE:
                return CONE;
            case TWO:
                return CTWO;
            case THREE:
                return CTHREE;
            case FOUR:
                return CFOUR;
            case FIVE:
                return CFIVE;
            case SIX:
                return CSIX;
            case SEVEN:
                return CSEVEN;
            case EIGHT:
                return CEIGHT;
            case UNKNOWN:
                return CUNKNOWN;
            case FLAG:
                return CFLAG;
            case WRONG_FLAG:
                return CWRNGFLG;
            case EXPLODED:
                return CEXPLODE;
        }
    }

    Field ( int w, int h, int b )
    : width(w), height(h), bombs(b) {
        if ( width < 0 || height < 0 || bombs < 0 ) {
            std::cerr << "ERROR: Width, Height and Bombs count must be positive";
            exit(1);
        }
        size_t n = sizeof(int) * width*height;
        this->matrix = (int*)malloc(n);
        if ( matrix == NULL ) {
            std::cerr << "ERROR: Failed to allocate Field Matrix in memory" << std::endl;
            exit(2);
        }
        bomb_matrix = std::make_unique<std::bitset<N>>(n);
        memset(matrix, UNKNOWN, n);
    }
    ~Field () {
        delete[] matrix;
    }
private:
    int width, height, bombs;
    int* matrix;
    std::unique_ptr<std::bitset<N>> bomb_matrix;
};
