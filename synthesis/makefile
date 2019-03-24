CC=gcc
CFLAGS=-c -Wall
LDFLAGS=
SOURCES= synthesis.c synthesisTest.c
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=synth

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm *o synth
