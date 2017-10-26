include ../../Makefile.in
include ../../milib/Makefile.in
include ../../mifitslib/Makefile.in

INCLUDE := $(MIFITSLIB_INC) $(MILIB_INC) $(MT_INC)
LDLIBS  := $(MIFITSLIB_LIB) $(MILIB_LIB) $(MT_LIB) $(LIB)

TARGET =

all: $(TARGET)

#test_base: test_base.o
#       $(CXXN) $@.o ${LDLIBS} -o $@


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
