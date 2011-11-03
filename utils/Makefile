LIBNAME=utils.a

# Executables
AR=ar
CC=gcc
CPP=g++
RANLIB=ranlib

# Flags
CFLAGS=-fno-implicit-templates -Wall -I../utils/inc

# Files
SRCS=\
  src/log.cpp \
  src/metrix.cpp \
  src/rand.cpp
OBJS=$(SRCS:.cpp=.o)

.SUFFIXES: .cpp

.cpp.o:
	$(CPP) -c $(CFLAGS) -o $@ $<

all:	$(OBJS) $(LIBNAME)

$(LIBNAME): $(OBJS)
	$(AR) rvu $(LIBNAME) $(OBJS)
	$(RANLIB) $(LIBNAME)

clean:
	rm -f src/*.o *.a
