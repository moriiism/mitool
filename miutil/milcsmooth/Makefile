include ../../Makefile.in
include ../../milib/Makefile.in
include ../../mifitslib/Makefile.in
include ../../mirootlib/Makefile.in
include ../../mifunclib/Makefile.in

INCLUDE := $(MIFUNCLIB_INC) $(MIROOTLIB_INC) $(MIFITSLIB_INC) $(MILIB_INC) $(ROOT_INC) $(CFITSIO_INC) $(MT_INC)
LDLIBS  := $(MIFUNCLIB_LIB) $(MIROOTLIB_LIB) $(MIFITSLIB_LIB) $(MILIB_LIB) $(ROOT_ALLLIBS) $(CFITSIO_LIB) $(MT_LIB) $(LIB)

TARGET = milcsmooth

all: $(TARGET) 

milcsmooth: milcsmooth.o  arg_milcsmooth.o
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
