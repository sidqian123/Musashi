#include "m68k.h"
#include "sim.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <gtk/gtk.h>
#include <cairo.h>
#include <math.h>


#define MAX_ROM 0xfff                           /* Memory size for rom */
#define MAX_RAM 0xffffff                            /* Memory size for ram */
#define MAX_MEM (MAX_ROM+MAX_RAM)               /* ROM and RAM sizes */

#define BLOCK_SIZE 1  // Size of each memory block in pixels



/* Read/write macros */
#define READ_8(BASE, ADDR) (BASE)[ADDR]
#define READ_16(BASE, ADDR) (((BASE)[ADDR] << 8) | (BASE)[(ADDR) + 1])
#define READ_32(BASE, ADDR) (                            \
    ((BASE)[ADDR] << 24) |                               \
    ((BASE)[(ADDR) + 1] << 16) |                         \
    ((BASE)[(ADDR) + 2] << 8) |                          \
    (BASE)[(ADDR) + 3]                                   \
)

#define WRITE_8(BASE, ADDR, VAL) (BASE)[ADDR] = (VAL)&0xff
#define WRITE_16(BASE, ADDR, VAL) do {                   \
    (BASE)[ADDR] = ((VAL) >> 8) & 0xff;                  \
    (BASE)[(ADDR) + 1] = (VAL) & 0xff;                   \
} while(0)
#define WRITE_32(BASE, ADDR, VAL) do {                   \
    (BASE)[ADDR] = ((VAL) >> 24) & 0xff;                 \
    (BASE)[(ADDR) + 1] = ((VAL) >> 16) & 0xff;           \
    (BASE)[(ADDR) + 2] = ((VAL) >> 8) & 0xff;            \
    (BASE)[(ADDR) + 3] = (VAL) & 0xff;                   \
} while(0)


/* Prototypes */
void exit_error(char* fmt, ...);
unsigned int  m68k_read_memory_8(unsigned int address);
unsigned int  m68k_read_memory_16(unsigned int address);
unsigned int  m68k_read_memory_32(unsigned int address);
void m68k_write_memory_8(unsigned int address, unsigned int value);
void m68k_write_memory_16(unsigned int address, unsigned int value);
void m68k_write_memory_32(unsigned int address, unsigned int value);
void data_bus_recorder(const char *string, unsigned int address);

/* initiallize memory array to 0 */
unsigned char g_mem[MAX_MEM+1] = {0};                 /* Memory in one array */

GtkWidget *drawing_area;
GQueue *modified_addresses;
unsigned int last_accessed_address = -1;

unsigned int grid_width;
unsigned int grid_height;

/* struct definition */
struct section {
    const char* name;
    unsigned int address;
    unsigned int size;
};

/* Exit with an error message.  Use printf syntax. */
void exit_error(char* fmt, ...) {
    va_list args;
    // Start processing variable arguments
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    fprintf(stderr, "\n");
    va_end(args);
    exit(EXIT_FAILURE);
}

static gboolean on_draw_event(GtkWidget *widget, cairo_t *cr, gpointer user_data) {
    while (!g_queue_is_empty(modified_addresses)) {
        unsigned int i = (unsigned int)g_queue_pop_head(modified_addresses);

        unsigned int x = i % grid_width;
        unsigned int y = i / grid_width;

        // Decide color based on segment
        if (i >= 0x0000c000 && i < 0x00201c00) {         // .text
            cairo_set_source_rgb(cr, 0.8, 0.2, 0.2);  // Red for .text
        }
        else if (i >= 0x00201c00 && i < 0x00231488) {  // .rodata
            cairo_set_source_rgb(cr, 0.2, 0.8, 0.2);  // Green for .rodata
        }
        else if (i >= 0x00231488 && i < 0x00231550) {  // link_set_sys...
            cairo_set_source_rgb(cr, 0.2, 0.2, 0.8);  // Blue for link_set_sys...
        }
        else if (i >= 0x00231550 && i < 0x00231658) {  // link_set_modules
            cairo_set_source_rgb(cr, 0.8, 0.8, 0.2);  // Yellow for link_set_modules
        }
        else if (i >= 0x00231658 && i < 0x00231678) {  // link_set_domains
            cairo_set_source_rgb(cr, 0.8, 0.2, 0.8);  // Magenta for link_set_domains
        }
        else if (i >= 0x00231678 && i < 0x002316c0) {  // link_set_evcnts
            cairo_set_source_rgb(cr, 0.2, 0.8, 0.8);  // Cyan for link_set_evcnts
        }
        else if (i >= 0x002316c0 && i < 0x002316c4) {  // link_set_dkw...
            cairo_set_source_rgb(cr, 0.4, 0.4, 0.4);  // Grey for link_set_dkw...
        }
        else if (i >= 0x002316c4 && i < 0x002316e4) {  // link_set_pro...
            cairo_set_source_rgb(cr, 0.6, 0.3, 0.3);  // Brown-ish for link_set_pro...
        }
        else if (i >= 0x002316e4 && i < 0x00231740) {  // .eh_frame
            cairo_set_source_rgb(cr, 0.5, 0.5, 0.8);  // Light Blue for .eh_frame
        }
        else if (i >= 0x00231740 && i < 0x00248300) {  // .data
            cairo_set_source_rgb(cr, 0.7, 0.7, 0.7);  // Light Grey for .data
        }
        else if (i >= 0x00248300) {  // .bss and anything beyond
            cairo_set_source_rgb(cr, 0.3, 0.7, 0.3);  // Some shade of green for .bss
        }
        else if (i == last_accessed_address) {
            cairo_set_source_rgb(cr, 1, 0, 0);  // Red for recently accessed
        } else {
            double shade = g_mem[i] / 255.0;
            cairo_set_source_rgb(cr, shade, shade, shade);  // Shade by byte value
        }
        printf("Drawing %08x at (%d, %d)\n", i, x, y);
        cairo_rectangle(cr, x * BLOCK_SIZE, y * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE);
        cairo_fill(cr);
    }

    return FALSE;
}

void visualize_range(unsigned int start_address, unsigned int end_address) {
    last_accessed_address = end_address;
    for (unsigned int addr = start_address; addr <= end_address; addr++) {
        g_queue_push_tail(modified_addresses, GUINT_TO_POINTER(addr));
    }
    gtk_widget_queue_draw(drawing_area);
}

/* reads in 8 bits from memory array */
unsigned int m68k_read_memory_8(unsigned int address) {
    if (address >= MAX_MEM) {
        exit_error("Attempted to read byte from address %08x beyond memory size", address);
    }
    data_bus_recorder("m68k_read_memory_8", address);
    return READ_8(g_mem, address);
}

/* reads in 16 bits from memory array */
unsigned int m68k_read_memory_16(unsigned int address) {
    if (address >= MAX_MEM) {
        exit_error("Attempted to read byte from address %08x beyond memory size", address);
    }
    data_bus_recorder("m68k_read_memory_16", address);
    return READ_16(g_mem, address);
}

/* reads in 32 bits from memory array */
unsigned int m68k_read_memory_32(unsigned int address) {
    if (address >= MAX_MEM) {
        exit_error("Attempted to read byte from address %08x beyond memory size", address);
    }
    data_bus_recorder("m68k_read_memory_32", address);
    return READ_32(g_mem, address);
}

/* write in 8 bits to memory array */
void m68k_write_memory_8(unsigned int address, unsigned int value) {
    if (address > MAX_MEM) {
        exit_error("Attempted to write byte to address %08x beyond memory size", address);
    }
    // Check if the address is within the ROM range
    if (address <= MAX_ROM) {
        exit_error("Attempted to write byte to ROM address %08x", address);
    }
    data_bus_recorder("m68k_write_memory_8", address);
    WRITE_8(g_mem, address, value);
    //visualize_range(address, address + 1);
}

/* write in 16 bits to memory array */
void m68k_write_memory_16(unsigned int address, unsigned int value) {
    if (address > MAX_MEM) {
        exit_error("Attempted to write byte to address %08x beyond memory size", address);
    }
    // Check if the address is within the ROM range
    if (address <= MAX_ROM) {
        exit_error("Attempted to write byte to ROM address %08x", address);
    }
    data_bus_recorder("m68k_write_memory_16", address);
    WRITE_16(g_mem, address, value);
    //visualize_range(address, address + 2);
}

/* write in 32 bits to memory array */
void m68k_write_memory_32(unsigned int address, unsigned int value) {
    if (address > MAX_MEM) {
        exit_error("Attempted to write byte to address %08x beyond memory size", address);
    }
    // Check if the address is within the ROM range
    if (address <= MAX_ROM) {
        exit_error("Attempted to write byte to ROM address %08x", address);
    }
    data_bus_recorder("m68k_write_memory_32", address);
    WRITE_32(g_mem, address, value);
    //visualize_range(address， address + 3);
}

unsigned int m68k_read_disassembler_16(unsigned int address)
{
    if(address > MAX_ROM)
        exit_error("Disassembler attempted to read word from ROM address %08x", address);
    data_bus_recorder("m68k_read_disassembler_16", address);
    return READ_16(g_mem, address);
}

unsigned int m68k_read_disassembler_32(unsigned int address)
{
    if(address > MAX_ROM)
        exit_error("Dasm attempted to read long from ROM address %08x", address);
    data_bus_recorder("m68k_read_disassembler_32", address);
    return READ_32(g_mem, address);
}

/* Print the address and data bus */
void data_bus_recorder(const char *string, unsigned int address) {
    if(address < MAX_RAM)
        printf("%s@RAM: %08x\n", string, address);
    else{
        printf("%s@ROM: %08x\n", string, address);
    }
}

/* The sections to load */
struct section sections[] = {
        {"text", 0x0000c000, 0x001f5bfc},
        {"rodata", 0x00201c00, 0x0002f885},
        {"link_set_sysctl_funcs", 0x00231488, 0x000000c8},
        {"link_set_modules", 0x00231550, 0x00000108},
        {"link_set_domains", 0x00231658, 0x00000020},
        {"link_set_evcnts", 0x00231678, 0x00000048},
        {"link_set_dkwedge_methods", 0x002316c0, 0x00000004},
        {"link_set_prop_linkpools", 0x002316c4, 0x00000020},
        {"data", 0x00231740, 0x00016b8c},
        {"bss", 0x00248300, 0x00018858},
};

/* Load a section from a file into memory */
void load_section(const struct section* sec) {
    char filepath[128];
    snprintf(filepath, sizeof(filepath), "./bins/%s.bin", sec->name);

    FILE *fhandle = fopen(filepath, "rb");
    if (!fhandle) {
        exit_error("Unable to open %s", filepath);
    }

    fread(&g_mem[sec->address], 1, sec->size, fhandle);
    fclose(fhandle);
}

static gboolean emulator_tick(gpointer user_data) {
    m68k_execute(100000);
    return TRUE; // return TRUE so it keeps getting called
}

int main(int argc, char* argv[]) {
    grid_width = (unsigned int) sqrt(MAX_MEM);
    grid_height = (MAX_MEM + grid_width - 1) / grid_width;

    modified_addresses = g_queue_new();

    gtk_init(&argc, &argv);

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Memory Visualization");
    gtk_window_set_default_size(GTK_WINDOW(window), grid_width * BLOCK_SIZE, grid_height * BLOCK_SIZE);

    drawing_area = gtk_drawing_area_new();
    gtk_container_add(GTK_CONTAINER(window), drawing_area);
    g_signal_connect(G_OBJECT(drawing_area), "draw", G_CALLBACK(on_draw_event), NULL);

    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    gtk_widget_show_all(window);

    unsigned int text_section_address = 0x0000c000;
    // Convert the address to bytes and store it at memory[4] to memory[7]
    WRITE_32(g_mem, 4, text_section_address);
    for (unsigned long i = 0; i < sizeof(sections) / sizeof(sections[0]); i++) {
        load_section(&sections[i]);
    }
    m68k_init();
    m68k_set_cpu_type(M68K_CPU_TYPE_68030);
    m68k_pulse_reset();

    g_timeout_add(16, emulator_tick, NULL);

    // Enter the main event loop. This will block until gtk_main_quit is called.
    gtk_main();

    g_queue_free(modified_addresses);

}
