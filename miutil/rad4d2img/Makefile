include ../../Makefile.in
include ../../milib/Makefile.in
include ../../mifitslib/Makefile.in

INCLUDE = $(MIFITSLIB_INC) $(MILIB_INC) $(CFITSIO_INC) $(MT_INC)
LDLIBS  = $(MIFITSLIB_LIB) $(MILIB_LIB) $(CFITSIO_LIB) $(MT_LIB) $(LIB)

TARGET = rad4d2img

all: $(TARGET) 

rad4d2img: rad4d2img.o  arg_rad4d2img.o
	$(CXXN) $@.o arg_$@.o  ${LDLIBS} -o $@

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
