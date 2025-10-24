#pragma once

#include "bitvector.h"
#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <memory>
#include <string>

//COLORS//
#define RESET     "\e[0m"

#define EXPLODEBG "\e[41m"
#define UNKNWBG   "\e[48;5;250m"
#define ACKBG     "\e[48;5;243m"

#define BORDERC   "240m"
#define BORDER     "\e[4;38;5;" BORDERC "\e[48;5;" BORDERC " "

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
#define CUNKNOWN UNKNWBG     "__" BORDER 
#define CEMPTY   ACKBG       "__" BORDER 
#define CONE     ACKBG ONEFG "1_" BORDER 
#define CTWO     ACKBG TWOFG "2_" BORDER 
#define CTHREE   ACKBG TRIFG "3_" BORDER 
#define CFOUR    ACKBG FORFG "4_" BORDER 
#define CFIVE    ACKBG FIVFG "5_" BORDER 
#define CSIX     ACKBG SIXFG "6_" BORDER 
#define CSEVEN   ACKBG SEVFG "7_" BORDER 
#define CEIGHT   ACKBG EITFG "8_" BORDER 
#define CFLAG    ACKBG       "_" BORDER 
#define CWRNGFLG UNKNWBG     "X" BORDER 
#define CEXPLODE EXPLODEBG   "✶"  BORDER 

/**
 * Minesweeper game field
 */
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
private:
    size_t width, height, bombs;
    Cell* matrix;
    BitVector bomb_matrix;

    /**
     * Gives information about bomb in the given coordinates
     *
     * @param i First coordinate
     * @param j Second coordinate
     * @return Bool value, describes if there is a bomb at coordinates (i, j)
     */
    bool is_bomb( size_t i, size_t j ) {
        if ( i >= height || j >= width ) {
            std::cerr << "ERROR: Tried to get matrix element out of bounds";
            exit(1);
        };
        size_t n = ( i*width ) + j;
        return bomb_matrix[n];
    }
public:
    /**
     * Constructor of the class Field
     *
     * @param w Field width
     * @param h Field height
     * @param b Bombs count
     */
    Field ( int w, int h, int b )
    : width(w), height(h), bombs(b), bomb_matrix(w*h) {
        if ( width < 0 || height < 0 || bombs < 0 ) {
            std::cerr << "ERROR: Width, Height and Bombs count must be positive";
            exit(1);
        }
        size_t n = sizeof(Cell) * width*height;
        this->matrix = (Cell*)malloc(n);
        if ( matrix == NULL ) {
            std::cerr << "ERROR: Failed to allocate Field Matrix in memory" << std::endl;
            exit(2);
        }
        memset(matrix, UNKNOWN, n);
    }
    ~Field () {
        free(matrix);
    }

    /**
     * Gives a string formatted Cell
     *
     * @param cell A Cell value
     * @return A formatted string
     */
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
            default:
                return "ERR";
        }
    }

    /**
     * Get value from 2-Dimensional Field matrix
     *
     * @param i First coordinate
     * @param j Second coordinate
     * @return The Cell of coordinates (i, j)
     */
    Cell get( size_t i, size_t j ) {
        if ( i >= height || j >= width ) {
            std::cerr << "ERROR: Tried to get matrix element out of bounds";
            exit(1);
        };
        size_t n = ( i*width ) + j;
        return matrix[n];
    }

    /**
     * Print out the game Field
     */
    void printField () {
        for ( int i = 0 ; i < height ; i++ ) { // std::cout << BORDER;
        for ( int j = 0 ; j < width ; j++ ) {
            std::cout << Field::Cell_String(this->get(i, j));
        } std::cout << std::endl;
        } std::cout << RESET;
    }
};
