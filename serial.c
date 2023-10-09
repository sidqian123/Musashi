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


// Instead of having to memorize all of the bits of each of the registers, I have decided to write a bunch of macros
// that set and clear the bits instead

// status: can be 's' or 'c' for set and clear respectively


// -------------------------------------------------------------------------------- CONTROL REGISTER MACROS ----------------------------------------------------------

// --------------- STATUS REGISTER 3 ------------------------

// Receiver Enable - Control Register 3, bit 0
#define RECEIVE_ENABLE(CHANNEL, STATUS) \
    if(CHANNEL == 'A'){\
        if(STATUS == 's'){\
            chip.controlRegisterA[3] |= (1<<0);\
        }\
        else if(STATUS == 'c'){\
            chip.controlRegisterA[3] &= ~(1<<0);\
        }\
    }\
    else if(CHANNEL == 'B'){\
        if(STATUS == 's'){\
            chip.controlRegisterB[3] |= (1<<0);\
        }\
        else if(STATUS == 'c'){\
            chip.controlRegisterB[0] &= ~(1<<0);\
        }\
    }


// ----------------------------------------------------------

// --------------- STATUS REGISTER 5 -----------------

// Transmitter Enable - Status Register 5, bit 3

#define TRANSMITTER_ENABLE(CHANNEL, STATUS) \
    if(CHANNEL == 'A'){\
        if(STATUS == 's'){\
            chip.controlRegisterA[5] |= (1<<3);\
        }\
        else if(STATUS == 'c'){\
            chip.controlRegisterA[5] &= ~(1<<3);\
        }\
    }\
    else if(CHANNEL == 'B'){\
        if(STATUS == 's'){\
            chip.controlRegisterB[5] |= (1<<3);\
        }\
        else if(STATUS == 'c'){\
            chip.controlRegisterB[5] &= ~(1<<3);\
        }\
    }


// ---------------------------------------------------

// ------------------------------------------------------------------------------ STATUS REGISTER MACROS ------------------------------------------------------------------------------------------------------------


// ----------------------- STATUS REGISTER 0 ---------------------------------------


// Receive Char Available - Status Register 0, bit 0 
#define RECEIVE_CHAR_AVAILABLE(CHANNEL, STATUS) \
    if(CHANNEL == 'A'){\
        if(STATUS == 's'){\
            chip.statusRegisterA[0] |= (1<<0);\
        }\
        else if(STATUS == 'c'){\
            chip.statusRegisterA[0] &= ~(1<<0);\
        }\
    }\
    else if(CHANNEL == 'B'){\
        if(STATUS == 's'){\
            chip.statusRegisterB[0] |= (1<<0);\
        }\
        else if(STATUS == 'c'){\
            chip.statusRegisterB[0] &= ~(1<<0);\
        }\
    }


// Interrupt Pending - Status Register 0, bit 1 (CHANNEL A ONLY)
#define INTERRUPT_PENDING(STATUS) \
    if(STATUS == 's'){\
        chip.statusRegisterA[0] |= (1<<1);\
    }\
    else if(STATUS == 'c'){\
        chip.statusRegisterA[0] &= ~(1<<1);\
    }


// Transmitter Buffer Empty - Status Register 0, bit 2
#define TRANSMITTER_BUFFER_EMPTY(CHANNEL, STATUS) \
    if(CHANNEL == 'A'){\
        if(STATUS == 's'){\
            chip.statusRegisterA[0] |= (1<<2);\
        }\
        else if(STATUS == 'c'){\
            chip.statusRegisterA[0] &= ~(1<<2);\
        }\
    }\
    else if(CHANNEL == 'B'){\
        if(STATUS == 's'){\
            chip.statusRegisterB[0] |= (1<<2);\
        }\
        else if(STATUS == 'c'){\
            chip.statusRegisterB[0] &= ~(1<<2);\
        }\
    }


// DCD status - Status Register 0, bit 3

// DCD: Data Carrier Detect - input goes low to indicate the presence of valid serial data at RxD (in channels A or B)
// This one is kinda weird; Instead of saying just DCD, the datasheet says that it inverts the state of !DCD input. This is because the chip reads
// !DCD, and not DCD by itself). There are a lot of bits in the status register that behave like this. 

#define DCD_STATUS(CHANNEL, STATUS) \
    if(CHANNEL == 'A'){\
        if(STATUS == 's'){\
            chip.statusRegisterA[0] |= (1<<3);\
        }\
        else if(STATUS == 'c'){\
            chip.statusRegisterA[0] &= ~(1<<3);\
        }\
    }\
    else if(CHANNEL == 'B'){\
        if(STATUS == 's'){\
            chip.statusRegisterB[0] |= (1<<3);\
        }\
        else if(STATUS == 'c'){\
            chip.statusRegisterB[0] &= ~(1<<3);\
        }\
    }


// Sync Status - Status Register 0, bit 4
// There are multiple sync modes that the serial chip can use: async, sync, monosync, bisync, HDLC. However, for this model, we will only be
// considering aysnc mode
// Like DCD, inverts state of !SYNC input, giving SYNC

#define SYNC_STATUS(CHANNEL, STATUS) \
    if(CHANNEL == 'A'){\
        if(STATUS == 's'){\
            chip.statusRegisterA[0] |= (1<<4);\
        }\
        else if(STATUS == 'c'){\
            chip.statusRegisterA[0] &= ~(1<<4);\
        }\
    }\
    else if(CHANNEL == 'B'){\
        if(STATUS == 's'){\
            chip.statusRegisterB[0] |= (1<<4);\
        }\
        else if(STATUS == 'c'){\
            chip.statusRegisterB[0] &= ~(1<<4);\
        }\
    }


// CTS Status - Status Register 0 , bit 5
// Inverts !CTS input, giving CTS input
// when thisbit is flipped, causes an external/status interrupt request

#define CTS_STATUS(CHANNEL, STATUS) \
    if(CHANNEL == 'A'){\
        if(STATUS == 's'){\
            chip.statusRegisterA[0] |= (1<<5);\
        }\
        else if(STATUS == 'c'){\
            chip.statusRegisterA[0] &= ~(1<<5);\
        }\
    }\
    else if(CHANNEL == 'B'){\
        if(STATUS == 's'){\
            chip.statusRegisterB[0] |= (1<<5);\
        }\
        else if(STATUS == 'c'){\
            chip.statusRegisterB[0] &= ~(1<<5);\
        }\
    }


// Idle/CRC - Status Register 0, bit 6
// only used in synchronous mode or HDLC mode, so we will be skipping the macro

// Break/Abort - Status Register 0, bit 7
// when this bit is flipped, causes an external/status interrupt
// set when break sequence is detected (null character plus framing error) when RxD is low, (spacing?), for
// more than one character at a time
// cleared when RxD returns to high

#define BREAK_STATUS(CHANNEL, STATUS) \
    if(CHANNEL == 'A'){\
        if(STATUS == 's'){\
            chip.statusRegisterA[0] |= (1<<7);\
        }\
        else if(STATUS == 'c'){\
            chip.statusRegisterA[0] &= ~(1<<7);\
        }\
    }\
    else if(CHANNEL == 'B'){\
        if(STATUS == 's'){\
            chip.statusRegisterB[0] |= (1<<7);\
        }\
        else if(STATUS == 'c'){\
            chip.statusRegisterB[0] &= ~(1<<7);\
        }\
    }


// -------------------------------------------------------------------------------

// --------------------- STATUS REGISTER 1 ------------------------------------------

// All sent -  Status Register 1, bit 0
#define ALL_SENT(CHANNEL, STATUS) \
    if(CHANNEL == 'A'){\
        if(STATUS == 's'){\
            chip.statusRegisterA[1] |= (1<<0);\
        }\
        else if(STATUS == 'c'){\
            chip.statusRegisterA[1] &= ~(1<<0);\
        }\
    }\
    else if(CHANNEL == 'B'){\
        if(STATUS == 's'){\
            chip.statusRegisterB[1] |= (1<<0);\
        }\
        else if(STATUS == 'c'){\
            chip.statusRegisterB[1] &= ~(1<<0);\
        }\
    }


// Residue Codes - Status Register 1, bits 1-3
// We can ignore these bits completely, since they are only used in an HDLC message :)

//--------------- Following bits have to do with special receive conditions, trigger an interrupt request -----------------

// Latched Bits will only be reset if a error reset command is sent, receiving new characters does not change its status

// Parity Error (LATCHED) - Status Register 1, bit 4 
#define PARITY_ERROR(CHANNEL, STATUS) \
    if(CHANNEL == 'A'){\
        if(STATUS == 's'){\
            chip.statusRegisterA[1] |= (1<<4);\
        }\
        else if(STATUS == 'c'){\
            chip.statusRegisterA[1] &= ~(1<<4);\
        }\
    }\
    else if(CHANNEL == 'B'){\
        if(STATUS == 's'){\
            chip.statusRegisterB[1] |= (1<<4);\
        }\
        else if(STATUS == 'c'){\
            chip.statusRegisterB[1] &= ~(1<<4);\
        }\
    }


// Receiver Overrun Error (LATCHED) - Status Register 1, bit 5
// Occurs when receiver buffer already contains 3 characters and 4th is completely received, overwriting the last character in the buffer

// Likely that this will always remain at 0 in our code, since we are giving our buffers more memory, 16 characters

#define RECEIVER_OVERRUN(CHANNEL, STATUS) \
    if(CHANNEL == 'A'){\
        if(STATUS == 's'){\
            chip.statusRegisterA[1] |= (1<<5);\
        }\
        else if(STATUS == 'c'){\
            chip.statusRegisterA[1] &= ~(1<<5);\
        }\
    }\
    else if(CHANNEL == 'B'){\
        if(STATUS == 's'){\
            chip.statusRegisterB[1] |= (1<<5);\
        }\
        else if(STATUS == 'c'){\
            chip.statusRegisterB[1] &= ~(1<<5);\
        }\
    }


// CRC/Framing Error - Status Register 1, bit 6
// CRC - Cyclic Redundancy Check
// set when no stop bit is detected at the end of a character, when this occurs, chip waits additional one-half bit 
// before resampling so framing error is not interpreted as new start bit
#define CRC_ERROR(CHANNEL, STATUS) \
    if(CHANNEL == 'A'){\
        if(STATUS == 's'){\
            chip.statusRegisterA[1] |= (1<<6);\
        }\
        else if(STATUS == 'c'){\
            chip.statusRegisterA[1] &= ~(1<<6);\
        }\
    }\
    else if(CHANNEL == 'B'){\
        if(STATUS == 's'){\
            chip.statusRegisterB[1] |= (1<<6);\
        }\
        else if(STATUS == 'c'){\
            chip.statusRegisterB[1] &= ~(1<<6);\
        }\
    }


// End of HDLC Frame - Status Register 1, bit 7
// HDLC mode, ignore
// ---------------------------------------------------------------------------

// ------------- STATUS REGISTER 2B (CHANNEL A DOES NOT HAVE EQUIVALENT) -----------




// setting everything to 0
void chip_init(){
    // initialize the chip's registers to 0 by calling buffer_init on each of them
    buffer_init(&chip.aReceive);
    buffer_init(&chip.aTransmit);
    buffer_init(&chip.bReceive);
    buffer_init(&chip.bTransmit);

    // --------------- CONTROL INIT ----------------

    // CR0


    // CR1

    
    // CR2


    // CR3
    RECEIVE_ENABLE('A', 'c');
    RECEIVE_ENABLE('B', 'c');

    // CR5
    TRANSMITTER_ENABLE('A', 'c');
    TRANSMITTER_ENABLE('B', 'c');

    // CR6


    // CR7


    // -------------- STATUS INIT ----------------

    // SR0
    RECEIVE_CHAR_AVAILABLE('A', 'c');
    RECEIVE_CHAR_AVAILABLE('B', 'c');
    INTERRUPT_PENDING('A');
    INTERRUPT_PENDING('A');
    TRANSMITTER_BUFFER_EMPTY('A', 's');
    TRANSMITTER_BUFFER_EMPTY('B', 's');
    SYNC_STATUS('A', 'c');
    SYNC_STATUS('B', 'c');
    BREAK_STATUS('A', 'c');
    BREAK_STATUS('B', 'c');

    // SR1
    ALL_SENT('A', 'c');
    ALL_SENT('B', 'c');
    RECEIVER_OVERRUN('A', 'c');
    RECEIVER_OVERRUN('B', 'c');
    PARITY_ERROR('A', 'c');
    PARITY_ERROR('B', 'c');
    RECEIVER_OVERRUN('A', 'c');
    RECEIVER_OVERRUN('B', 'c');
    CRC_ERROR('A', 'c');
    CRC_ERROR('B', 'c');

    // SR2
    

    // SR3-4
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
        return buffer_read(&chip.aTransmit);
    }
    else if(toupper(channel) == 'B'){
        return buffer_read(&chip.bTransmit);
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
        RECEIVE_CHAR_AVAILABLE('A', 's');
    }
    else if(toupper(channel) == 'B'){
        buffer_write(&chip.bReceive, val);
        RECEIVE_CHAR_AVAILABLE('B', 's');
    }
    else{ // Only allowed to look at A and B channels
        printf("Invalid channel name. Use either 'A' or 'B'");
    }
}

unsigned char receive_read(char channel){
    if(toupper(channel) == 'A'){
        return buffer_read(&chip.aReceive);
    }
    else if(toupper(channel) == 'B'){
        return buffer_read(&chip.bReceive);
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
