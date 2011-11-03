LIBNAME=libuni.a

# Executables
AR=ar
CC=gcc
CPP=g++
RANLIB=ranlib

# Flags
CFLAGS=-Wall -I../utils/inc -I../libvm/inc -Iinc

# Files
SRCS=\
  src/box.cpp \
  src/camera.cpp \
  src/envmap.cpp \
  src/light.cpp \
  src/lightsphere.cpp \
  src/lightrect.cpp \
  src/object.cpp \
  src/plane.cpp \
  src/shader.cpp \
  src/sphere.cpp \
  src/surfaceobject.cpp \
  src/unicontext.cpp \
  src/universe.cpp
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
