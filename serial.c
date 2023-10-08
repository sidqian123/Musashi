// Note:  only working with asynchronous mode, not HDLC or synchronous


/* ----------------------- TO DO ------------------------------------------------

1.  make functions that control reads/writes to control + status registers (do in forms of macros)
2.  circular buffer

(maybe: emulate interrupts)

*/
#include <ctype.h> // for toupper
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>

// circular buffer struct
struct circular_buffer{
    unsigned char buffer[16];
    // read and write pointers point to the index of the buffer
    int readPointer;
    int writePointer;
};

void buffer_init(struct circular_buffer* buffer){
    // initialize read and write pointers point to the index of the buffer
    buffer->readPointer = 0;
    buffer->writePointer = 0;
    // initialize buffer to 0
    for(int i=0; i<16; ++i){
        buffer->buffer[i] = 0;
    }
}

// circular buffer functions
// read from buffer at read pointer
unsigned char buffer_read(struct circular_buffer* buffer){
    // if buffer is empty, return -1
    if(buffer->readPointer == buffer->writePointer){
        return -1;
    }
    // else, read value at read pointer and increment read pointer
    else{
        unsigned char val = buffer->buffer[buffer->readPointer];
        buffer->readPointer = (buffer->readPointer + 1) % 16;
        return val;
    }
}

// write to buffer
void buffer_write(struct circular_buffer* buffer, unsigned char val){
    // if buffer is full, return -1
    if((buffer->writePointer + 1) % 16 == buffer->readPointer){
        return -1;
    }
    // else, write value to write pointer and increment write pointer
    else{
        buffer->buffer[buffer->writePointer] = val;
        buffer->writePointer = (buffer->writePointer + 1) % 16;
    }
}

// print existing items in buffer, empty spaces are represented by 0 so don't print those
void buffer_print(struct circular_buffer* buffer){
    for(int i=0; i<16; ++i){
        if(buffer->buffer[i] != 0){
            printf("%c", buffer->buffer[i]);
        } else {
            break;
        }
    }
}

// struct definition: represents each of the 4 registers that are used for serial communication
// most likely that we'll only be reading to one channel from the microprocessor, but I'm just keeping
// this in there
struct serial_chip{

    /* ---------- SIO BUFFERS ------------------------------------------
     
    these buffers should be circular buffers
    make sure that reading/writing only happen if there is space within buffer
    if read/write pointers overlap, buffer is full -> don't write anymore to buffer
    if read/write are one apart, buffer is empty

    ---------------------------------------------------------------------*/

    struct circular_buffer aReceive; 
    struct circular_buffer aTransmit;
    struct circular_buffer bReceive;
    struct circular_buffer bTransmit;

    //---------- CONTROL AND STATUS REGISTERS ------------------------------------- 
    // each channel has their own set of registers that act almost exactly the same
    // channel B one extra status register SR[2], whose contents are then used in control register CR[2]
    // channel A status register SR[2] is unused, however I'm keeping the sizes of the registers the same for
    // consistency

    unsigned char controlRegisterA[8];
    unsigned char statusRegisterA[5];

    unsigned char controlRegisterB[8];
    unsigned char statusRegisterB[5];

    unsigned int TxA_byte_count;
    unsigned int TxB_byte_count;

};

// Unlike C++ structs in C can't have member functions, so it will be a global variable
// that is called by functions below, also have to specify that serial_chip is struct in
// declaration
struct serial_chip chip;

// ------------------------------CONTROL REGISTER MACROS ------------------------------------


// status: can be 's' or 'c' for set and clear respectively
#define RECEIVE_ENABLE(CHANNEL, STATUS) (
    if(CHANNEL == 'A'){
        if(status == 's'){
            chip.controlRegisterA[0] |= (1<<0);
        }
        else if(status == 'c'){
            chip.controlRegisterA[0] &= ~(1<<0);
        }
    }
    else if(CHANNEL == 'B'){
        if(status == 's'){
            chip.controlRegisterB[0] |= (1<<0);
        }
        else if(status == 'c'){
            chip.controlRegisterB[0] &= ~(1<<0);
        }
    }
)


// ----------------------- STATUS REGISTER MACROS --------------------------------


// ----------------------- STATUS REGISTER 0 ---------------------------------------


// Receive Char Available - Status Register 0, bit 0 
#define RECEIVE_CHAR_AVAILABLE(CHANNEL, STATUS) (
    if(CHANNEL == 'A'){
        if(status == 's'){
            chip.statusRegisterA[0] |= (1<<0);
        }
        else if(status == 'c'){
            chip.statusRegisterA[0] &= ~(1<<0);
        }
    }
    else if(CHANNEL == 'B'){
        if(status == 's'){
            chip.statusRegisterB[0] |= (1<<0);
        }
        else if(status == 'c'){
            chip.statusRegisterB[0] &= ~(1<<0);
        }
    }
)

// Interrupt Pending - Status Register 0, bit 1 (CHANNEL A ONLY)
#define INTERRUPT_PENDING(STATUS) (
    if(status == 's'){
        chip.statusRegisterA[0] |= (1<<1);
    }
    else if(status == 'c'){
        chip.statusRegisterA[0] &= ~(1<<1);
    }
)

// Transmitter Buffer Empty - Status Register 0, bit 2
#define TRANSMITTER_BUFFER_EMPTY(CHANNEL, STATUS) (
    if(CHANNEL == 'A'){
        if(status == 's'){
            chip.statusRegisterA[0] |= (1<<2);
        }
        else if(status == 'c'){
            chip.statusRegisterA[0] &= ~(1<<2);
        }
    }
    else if(CHANNEL == 'B'){
        if(status == 's'){
            chip.statusRegisterB[0] |= (1<<2);
        }
        else if(status == 'c'){
            chip.statusRegisterB[0] &= ~(1<<2);
        }
    }
)

// DCD status - Status Register 

// DCD: Data Carrier Detect - input goes low to indicate the presence of valid serial data at RxD (in channels A or B)
// This one is kinda weird; Instead of saying just DCD, the datasheet says the inverse of the state !DCD. This is probably because the chip reads
// !DCD, and not DCD by itself). There are a lot of bits in the status register that behave like this. 

#define NOT_DCD(CHANNEL, STATUS) (
    if(CHANNEL == 'A'){
        if(status == 's'){
            chip.statusRegisterA[1] |= (1<<3);
        }
        else if(status == 'c'){
            chip.statusRegisterA[1] &= ~(1<<3);
        }
    }
    else if(CHANNEL == 'B'){
        if(status == 's'){
            chip.statusRegisterB[1] |= (1<<3);
        }
        else if(status == 'c'){
            chip.statusRegisterB[1] &= ~(1<<3);
        }
    }
)

// -------------------------------------------------------------------------------

// --------------------- STATUS REGISTER 1 ------------------------------------------

// All sent -  Status Register 0, bit 1
#define ALL_SENT(CHANNEL, STATUS) (
    if(CHANNEL == 'A'){
        if(status == 's'){
            chip.statusRegisterA[1] |= (1<<0);
        }
        else if(status == 'c'){
            chip.statusRegisterA[1] &= ~(1<<0);
        }
    }
    else if(CHANNEL == 'B'){
        if(status == 's'){
            chip.statusRegisterB[1] |= (1<<0);
        }
        else if(status == 'c'){
            chip.statusRegisterB[1] &= ~(1<<0);
        }
    }
)

// ---------------------------------------------------------------------------


// setting everything to 0
void chip_init(){
    // initialize the chip's registers to 0 by calling buffer_init on each of them
    buffer_init(&chip.aReceive);
    buffer_init(&chip.aTransmit);
    buffer_init(&chip.bReceive);
    buffer_init(&chip.bTransmit);

    // CONTROL INIT
    RECEIVE_ENABLE('A', 'c');
    RECEIVE_ENABLE('B', 'c');

    // STATUS INIT
    RECEIVE_CHAR_AVAILABLE('A', 'c');
    RECEIVE_CHAR_AVAILABLE('B', 'c');
    INTERRUPT_PENDING('A', 'c');
    INTERRUPT_PENDING('A', 'c');
    TRANSMITTER_BUFFER_EMPTY('A', 's');
    TRANSMITTER_BUFFER_EMPTY('B', 's');
    ALL_SENT('A', 'c');
    ALL_SENT('B', 'c');
    
    unsigned int TxA_byte_count = 0;
    unsigned int TxB_byte_count = 0;
}

// FUNCTION PARAMETERS:
// channel = decide between a and b channels
// val = new val to be written into said index

// function should be called only when Tx sent is equal to the number of bytes in the Tx buffer

// ---------- transmit: processor (m68k) -> serial chip's transmit buffer -> other separate devices [one byte at a time]----------------------------

void transmit_write(char channel, char val){
    if(toupper(channel) == 'A'){
        buffer_write(&chip.aTransmit, val);
    }
    else if(toupper(channel) == 'B'){
        buffer_write(&chip.bTransmit, val);
    }
    else{ // Only allowed to look at A and B channels
        printf("Invalid channel name. Use either 'A' or 'B'");
    }
}

unsigned char transmit_read(char channel){
    if(toupper(channel) == 'A'){
        return buffer_write(&chip.aTransmit);
    }
    else if(toupper(channel) == 'B'){
        return buffer_write(&chip.bTransmit);
    }
    else{ // Only allowed to look at A and B channels
        printf("Invalid channel name. Use either 'A' or 'B'");
    }
}

// ---------------------------------------------------------------------------------------------------

// -------------- RECEIVE: other separate devices -> serial chip's receive buffer -> processor (m68k) [one byte at a time] ---------------------
void receive_write(char channel, char val){
    if(toupper(channel) == 'A'){
        buffer_write(&chip.aReceive, val);
    }
    else if(toupper(channel) == 'B'){
        buffer_write(&chip.bReceive, val);
    }
    else{ // Only allowed to look at A and B channels
        printf("Invalid channel name. Use either 'A' or 'B'");
    }
}

unsigned char receive_read(char channel){
    if(toupper(channel) == 'A'){
        return buffer_write(&chip.aReceive);
    }
    else if(toupper(channel) == 'B'){
        return buffer_write(&chip.bReceive);
    }
    else{ // Only allowed to look at A and B channels
        printf("Invalid channel name. Use either 'A' or 'B'");
    }
}

// -------------------------------------------------------------------------------------------------------------------------------------

// for output purposes
void print_register(char channel, char type){
    if(toupper(channel) == 'A'){
        if(type == 't'){
            buffer_print(&chip.aTransmit);
        }
        else if(type == 'r'){
            buffer_print(&chip.aReceive);
        }
        else{
            printf("Invalid channel type");
        }
    }
    else if(toupper(channel) == 'B'){
        if(type == 't'){
            buffer_print(&chip.bTransmit);
        }
        else if(type == 'r'){
            buffer_print(&chip.bReceive);
        }
        else{
            printf("Invalid channel type. Use either 't' (transmit) or 'r' (receive)");
        }
    }  
    else{
        printf("Invalid channel name. Use either A or B");
    }
}