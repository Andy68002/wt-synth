CC=gcc
CFLAGS=-g -c -Wall -Werror 
LDFLAGS=-g 
SOURCES= synthesis.c synthesisTest.c
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=synth

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) -o $@ $(OBJECTS) -lrt

.c.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm *.o synth
