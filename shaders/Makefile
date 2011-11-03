LIBNAME=shaders.a

# Executables
AR=ar
CC=gcc
CPP=g++
RANLIB=ranlib

# Flags
CFLAGS=-Wall -I../utils/inc -I../libvm/inc -I../libuni/inc -Iinc

# Files
SRCS=\
  src/chessshader.cpp \
  src/glassshader.cpp \
  src/mirrorshader.cpp \
  src/noisetest.cpp \
  src/snookershader.cpp
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
