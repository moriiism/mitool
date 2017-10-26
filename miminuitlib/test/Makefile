include ../../Makefile.in
include ../../milib/Makefile.in
include ../../mirootlib/Makefile.in
include ../../mifunclib/Makefile.in
include ../../miminuitlib/Makefile.in

INCLUDE := $(MIMINUITLIB_INC) $(MIFUNCLIB_INC) \
	$(MIROOTLIB_INC) $(MILIB_INC) $(ROOT_INC) $(MT_INC)
LDLIBS  := $(MIMINUITLIB_LIB) $(MIFUNCLIB_LIB) \
	$(MIROOTLIB_LIB) $(MILIB_LIB) $(ROOT_ALLLIBS) $(MT_LIB) $(LIB)

TARGET := 

all: $(TARGET)

#test_vect: test_vect.o
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
	-rm -f *.o *.a *.so

cleaner: clean
	-rm -f ${TARGET} *% *~ core
	-rm -R $(LIB_DEST)
