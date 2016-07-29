CC=gcc
override CFLAGS+=-c -Wall -lX11 -lXtst -lXext
override LDFLAGS+=-lX11 -lXtst -lXext

SOURCES=main.c

OBJECTS=$(SOURCES:.cpp=.o)
	EXECUTABLE=magic

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

.PHONY: clean

clean:
	$(RM) $(OBJECTS) $(EXECUTABLE)
	$(RM) *.svg

