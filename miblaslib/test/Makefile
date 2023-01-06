include ../../Makefile.in
include ../../milib/Makefile.in
include ../../miblaslib/Makefile.in

INCLUDE := $(MIBLASLIB_INC) $(MILIB_INC) $(MT_INC)
LDLIBS  := $(MIBLASLIB_LIB) $(MILIB_LIB) $(MT_LIB) $(OPENBLAS_LIB) $(LIB) -lgfortran
# LDLIBS  := $(MIBLASLIB_LIB) $(MILIB_LIB) $(MT_LIB) $(BLAS_LIB) $(LIB) -lgfortran

TARGET = elm_wise_mul  init

all: $(TARGET) 

elm_wise_mul: elm_wise_mul.o
	$(CXXN) $@.o ${LDLIBS} -o $@

init: init.o
	$(CXXN) $@.o ${LDLIBS} -o $@

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
