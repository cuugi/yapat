LIBNAME=librend.a

# Executables
AR=ar
CC=gcc
CPP=g++
RANLIB=ranlib

# Flags
CFLAGS=-Wall -I../utils/inc -I../libvm/inc -I../libuni/inc -I../shaders/inc \
	-Iinc -I/usr/include/qt3

# Files
SRCS= \
  src/input.cpp \
  src/nulloutput.cpp \
  src/output.cpp \
  src/ptrenderer.cpp \
  src/qtptrenderer.cpp \
  src/renderer.cpp \
  src/testinput.cpp
#  magickoutput.cpp 
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
