# Just a basic makefile to quickly test that everyting is working, it just
# compiles the .o and the generator
EXENAME          = sim

MUSASHIFILES = m68kcpu.c m68kdasm.c softfloat/softfloat.c
MAINFILES        = sim.c
MUSASHIGENCFILES = m68kops.c
MUSASHIGENHFILES = m68kops.h
MUSASHIGENERATOR = m68kmake

EXE =
EXEPATH = ./

.CFILES   = $(MAINFILES) $(OSDFILES) $(MUSASHIFILES) $(MUSASHIGENCFILES)
.OFILES   = $(.CFILES:%.c=%.o)

CC        = gcc
WARNINGS  = -Wall -Wextra -pedantic
CFLAGS    = $(WARNINGS) -g -O0
CFLAGS += -I/usr/local/Cellar/gtk+3/3.24.38/include/gtk-3.0 \
          -I/usr/local/Cellar/glib/2.78.0/include/glib-2.0 \
          -I/usr/local/Cellar/glib/2.78.0/lib/glib-2.0/include \
          -I/usr/local/Cellar/pango/1.50.14/include/pango-1.0 \
          -I/usr/local/Cellar/harfbuzz/8.2.0/include/harfbuzz \
          -I/usr/local/Cellar/cairo/1.16.0_5/include/cairo \
          -I/usr/local/Cellar/gdk-pixbuf/2.42.10_1/include/gdk-pixbuf-2.0 \
          -I/usr/local/Cellar/atk/2.38.0/include/atk-1.0
LFLAGS    = $(WARNINGS)
LFLAGS   += `pkg-config --libs gtk+-3.0 cairo gdk-pixbuf-2.0`

TARGET = $(EXENAME)$(EXE)
DELETEFILES = $(MUSASHIGENCFILES) $(MUSASHIGENHFILES) $(.OFILES) $(TARGET) $(MUSASHIGENERATOR)$(EXE)


all: $(TARGET)

clean:
	rm -f $(DELETEFILES)

$(TARGET): $(MUSASHIGENHFILES) $(.OFILES) Makefile
	$(CC) -o $@ $(.OFILES) $(LFLAGS) -lm


$(MUSASHIGENCFILES) $(MUSASHIGENHFILES): $(MUSASHIGENERATOR)$(EXE)
	$(EXEPATH)$(MUSASHIGENERATOR)$(EXE)

$(MUSASHIGENERATOR)$(EXE):  $(MUSASHIGENERATOR).c
	$(CC) -o  $(MUSASHIGENERATOR)$(EXE)  $(MUSASHIGENERATOR).c
