include ../../Makefile.in
include ../../milib/Makefile.in
include ../../mirootlib/Makefile.in

INCLUDE := $(MIROOTLIB_INC) $(MILIB_INC) $(ROOT_INC) $(MT_INC)
LDLIBS  := $(MIROOTLIB_LIB) $(MILIB_LIB) $(ROOT_ALLLIBS) $(MT_LIB) $(LIB)

TARGET = migetsigda1d

all: $(TARGET) 

migetsigda1d: migetsigda1d.o  arg_migetsigda1d.o
	$(CXXN) $@.o arg_$@.o ${LDLIBS} -o $@

.SUFFIXES:
.SUFFIXES: .o .c .f .F .cc

.c.o:
	$(CCN) -c $<

.F.o : 
	$(FCN) -c $<

.f.o:
	$(FCN) -c $<

.cc.o:
	${CXXN} -c $<

clean:
	-rm -f *.o

cleaner: clean
	-rm -f ${TARGET} *% *~ core
