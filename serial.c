#include <ctype.h> // for toupper
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>

// from sim.c
// maybe change this later if we don't want the program to end whenver there is an error
// reading/writing to the serial chip
void exit_error(char* fmt, ...){
    va_list args;
    // Start processing variable arguments
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    fprintf(stderr, "\n");
    va_end(args);
    exit(EXIT_FAILURE);
}

// struct definition: represents each of the 4 registers that are used for serial communication
// most likely that we'll only be reading to one channel from the microprocessor, but I'm just keeping
// this in there
struct serial_chip{
    unsigned char aReceive[8];
    unsigned char aTransmit[8];
    unsigned char bReceive[8];
    unsigned char bTransmit[8];
};

// Unlike C++ structs in C can't have member functions, so it will be a global variable
// that is called by functions below, also have to specify that serial_chip is struct in
// declaration
struct serial_chip chip;

// zeroing out arrays for initialization (CALL THESE BEFORE USING CHIP)
void array_init(char* array){ // in C you have to use the char*, or fixed number in brackets when calling array
    for(unsigned int i=0; i<8; ++i){
        array[i] = 0;
    }
}

// FUNCTION PARAMETERS:
// channel = decide between a and b channels
// index = which index you want to write into
// val = new val to be written into said index

void serial_write(char channel, unsigned int index, char val){
    if(index < 0 || index >= 8){
        exit_error("writing to invalid index");
    }
    
    if(toupper(channel) == 'A'){
        chip.aTransmit[index] = val;
    }
    else if(toupper(channel) == 'B'){
        chip.bTransmit[index] = val;
    }
    else{ // Only allowed to look at A and B channels
        exit_error("Invalid channel name. Use either 'A' or 'B'");
    }
}

char serial_read(char channel, unsigned int index){
    if(index < 0 || index >= 8){
        exit_error("Attempting to read at an invalid index");
    }
    
    if(toupper(channel) == 'A'){
        return chip.aReceive[index];
    }
    else if(toupper(channel) == 'B'){
        return chip.bReceive[index];
    }
    else{ // Only allowed to look at A and B channels
        exit_error("Invalid channel name. Use either 'A' or 'B'");
    }
}

// for output purposes
void print_register(char channel, char type){
    if(toupper(channel) == 'A'){
        if(type == 't'){
            printf(chip.aTransmit);
        }
        else if(type == 'r'){
            printf(chip.aReceive);
        }
        else{
            exit_error("Invalid channel type");
        }
    }
    else if(toupper(channel) == 'B'){
        if(type == 't'){
            printf(chip.aTransmit);
        }
        else if(type == 'r'){
            printf(chip.aReceive);
        }
        else{
            exit_error("Invalid channel type. Use either 't' (transmit) or 'r' (receive)");
        }
    }  
    else{
        printf("Invalid channel name. Use either 'A' or 'B'");
    }
}

// FOR LATER: emulate interrupts


