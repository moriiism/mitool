include ../../Makefile.in
include ../../milib/Makefile.in
include ../../mirootlib/Makefile.in
include ../../mitiminglib/Makefile.in

INCLUDE := $(MITIMINGLIB_INC) $(MIROOTLIB_INC) $(MILIB_INC) \
        $(HEADAS_INC) $(ROOT_INC) $(MT_INC)
LDLIBS  := $(MITIMINGLIB_LIB) $(MIROOTLIB_LIB) $(MILIB_LIB) \
        $(HEADAS_LIB) $(ROOT_ALLLIBS) $(MT_LIB) $(LIB)

TARGET = tconv  tconv_da1d  tconv_gd2d  tconv_hd1d

all: $(TARGET) 

tconv: tconv.o  arg_tconv.o
	$(CXXN) $@.o arg_$@.o ${LDLIBS} -o $@

tconv_da1d: tconv_da1d.o  arg_tconv_da1d.o
	$(CXXN) $@.o arg_$@.o ${LDLIBS} -o $@

tconv_gd2d: tconv_gd2d.o  arg_tconv_gd2d.o
	$(CXXN) $@.o arg_$@.o ${LDLIBS} -o $@

tconv_hd1d: tconv_hd1d.o  arg_tconv_hd1d.o
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
