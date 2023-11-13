EXENAME = sim

MUSASHIFILES = m68kcpu.c m68kdasm.c softfloat/softfloat.c sim.c
MAINFILES = main.cpp
MUSASHIGENCFILES = m68kops.c
MUSASHIGENHFILES = m68kops.h
MUSASHIGENERATOR = m68kmake

CPPFILES = $(MAINFILES) serial_io.cpp obio_pio.cpp mem.cpp c_compat.cpp cpu.cpp

EXE =
EXEPATH = ./

CFILES = $(MUSASHIFILES) $(MUSASHIGENCFILES)
OFILES = $(CFILES:.c=.o)
CPP_OFILES = $(CPPFILES:.cpp=.o)
DFILES = $(CFILES:.c=.d) $(CPPFILES:.cpp=.d)

CC = gcc
CPPC = g++
WARNINGS = -Wall -Wextra -pedantic
CFLAGS = $(WARNINGS) -g -O0
CPPFLAGS = $(WARNINGS) -g -O0 -std=c++11
LFLAGS = $(WARNINGS)

TARGET = $(EXENAME)$(EXE)
DELETEFILES = $(OFILES) $(TARGET) $(MUSASHIGENERATOR)$(EXE) $(DFILES) $(CPP_OFILES)

all: $(TARGET)

clean:
	rm -f $(DELETEFILES)

$(TARGET): $(OFILES) $(CPP_OFILES) Makefile
	$(CPPC) -o $@ $(OFILES) $(CPP_OFILES) $(LFLAGS) -lm

$(OFILES): %.o: %.c
	$(CC) $(CFLAGS) -MM -MF $(@:.o=.d) -MT $@ $<
	$(CC) $(CFLAGS) -c $< -o $@

$(CPP_OFILES): %.o: %.cpp
	$(CPPC) $(CPPFLAGS) -MM -MF $(@:.o=.d) -MT $@ $<
	$(CPPC) $(CPPFLAGS) -c $< -o $@

$(MUSASHIGENCFILES) $(MUSASHIGENHFILES): $(MUSASHIGENERATOR)$(EXE)
	$(EXEPATH)$(MUSASHIGENERATOR)$(EXE)

$(MUSASHIGENERATOR)$(EXE): $(MUSASHIGENERATOR).c
	$(CC) -o $(MUSASHIGENERATOR)$(EXE) $(MUSASHIGENERATOR).c

-include $(DFILES)
