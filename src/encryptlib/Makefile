CC=g++
LIB=
LIBPATH=
INCLUDE= 
CFLAGS= -g -Wall -O2 $(INCLUDE) -fPIC
INSTALLPATH=../../lib
SOLIB=libencrypt.so
STATICLIB=libencrypt.a
RUNLIBPATH=./

OBJS=base64.o padlock.o  vsha256.o

DLEXT=so

all: static shared 

static: libencrypt.a

shared: libencrypt.$(DLEXT)

$(STATICLIB): $(OBJS)
	echo "AR    $@"
	ar r $@ $(OBJS)

$(SOLIB): $(OBJS)
	echo "LD    $@"
	$(CC) -fPIC -shared -Wl,-soname,$@ -o $@ $(OBJS)
install:
	cp -r $(STATICLIB) $(INSTALLPATH)/$(STATICLIB)
	cp -r $(SOLIB) $(INSTALLPATH)/$(SOLIB)
clean:
	rm -f *.o $(SOLIB) $(STATICLIB) test
