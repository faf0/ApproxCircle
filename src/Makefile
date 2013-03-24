CC = gcc
CPP = g++
CPPFLAGS += -I./ -Wall -Wsign-compare -Wchar-subscripts -Werror -pedantic
CFLAGS += -std=c99
#CXXFLAGS += -O2
LDFLAGS  += -L./
LOADLIBES = -lm

.PHONY: all, clean

PROGNAME := approx_circle

all:	approx_circle
approx_circle:	approx_circle.o

clean:
	rm *.o approx_circle

