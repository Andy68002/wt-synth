CC=gcc
CFLAGS=-g -c -Wall -Werror
LDFLAGS=-g
SOURCES= synthesizer.c
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=synth

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) -o $@ $(OBJECTS) -lrt -lpthread

.c.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm *.o synth
