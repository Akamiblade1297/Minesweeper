#pragma once

#include <cstdint>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <stdint.h>
#include <cmath>
#include <tuple>

#define PROLOGUE auto [byte_index, bit_val] = index(i)

/**
 * Optimized array, where each element stored in 1 bit.
 */
class BitVector {
private:
    uint8_t* vec;
    size_t size_bits;
    size_t size_bytes;

    /**
     * Parse Byte Index and Bit Value from element index
     *
     * Bit Value is a 1 Byte value, with only 1 Bit set, that represents the position of the element
     *
     * @param i Index of an element
     * @return A tuple with Byte Index and Bit Value of an element
     */
    std::tuple<size_t, uint8_t> index ( size_t i ) const {
        if ( i >= size_bits ) {
            std::cerr << "ERROR: Tried to access element out of bounds" << std::endl;
            exit(1);
        }
        size_t byte_index = ceil((double)i/8);
        uint8_t bit_index = i%8;
        uint8_t bit_val   = 1 << bit_index;  

        return std::tuple(byte_index, bit_val);
    }

    /**
     * Get element value by Byte Index and Bit Value
     *
     * Parameters should be passed from an `index` function
     *
     * @param byte_index Byte Index of an element
     * @param bit_val Bit Value of an element
     * @return Boolean value of an element
     */
    bool get_indexed ( size_t byte_index, uint8_t bit_val ) const {
        return vec[byte_index]&bit_val;
    }

    /**
     * Flip an element value by Byte index and Bit Value
     *
     * Parameters should be passed from an `index` function
     *
     * @param byte_index Byte Index of an element
     * @param bit_val Bit Value of an element
     */
    void flip_indexed ( size_t byte_index, uint8_t bit_val ) {
        vec[byte_index] ^= bit_val;
    }
public:
    /**
     * Constructor for BitVector
     *
     * @param n Number of elements to contain
     * @param defult Default value of all elements
     */
    BitVector ( size_t n, bool defult = false ) 
    : size_bits(n), size_bytes(ceil((double)n/8)){ 
        vec = (uint8_t*)malloc(size_bytes);
        memset(vec, defult, size_bytes);
    }
    ~BitVector () {
        free(vec);
    }    

    /**
     * Get a value of i-th element
     *
     * @param i index of an element
     * @return Boolean value of an element
     */
    bool get ( size_t i ) const {
        PROLOGUE;
        return get_indexed(byte_index, bit_val);
    }

    /**
     * Flip a value of i-th element
     *
     * @param i Index of an element
     */
    void flip ( size_t i ) {
        PROLOGUE;
        flip_indexed(byte_index, bit_val);
    }

    /**
     * Set a value of i-th element to 1
     *
     * @param i Index of an element
     */
    void set ( size_t i ) {
        PROLOGUE;
        vec[byte_index] |= bit_val;
    }

    /**
     * Reset a value of i-th element to 0
     *
     * @param i Index of an element
     */
    void reset ( size_t i ) {
        PROLOGUE;
        vec[byte_index] &= ~bit_val;
    }

    /**
     * Set a value of i-th element
     *
     * @param i Index of an element
     * @param val Value to be set
     */
    void setValue ( size_t i, bool val ) {
        PROLOGUE;
        if ( val != get_indexed(byte_index, bit_val) )
            flip_indexed(byte_index, bit_val);
    }

    /**
     * Get a size of vector in bytes
     *
     * @return Size
     */
    size_t bsize () { return size_bytes; }

    /**
     * Get how many elements can be stored
     *
     * @return Size
     */
    size_t size () { return size_bits; }

    bool operator[] ( int i ) const { return this->get(i); }
};

