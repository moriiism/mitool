include ../../Makefile.in
include ../../milib/Makefile.in
include ../../mirootlib/Makefile.in
include ../../mifunclib/Makefile.in

INCLUDE := $(MIFUNCLIB_INC) $(MIROOTLIB_INC) \
	$(MILIB_INC) $(ROOT_INC) $(MT_INC)
LDLIBS  := $(MIFUNCLIB_LIB) $(MIROOTLIB_LIB) \
	$(MILIB_LIB) $(ROOT_ALLLIBS) $(LIB)

TARGET = milcsim

all: $(TARGET) 

milcsim: milcsim.o  arg_milcsim.o
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
