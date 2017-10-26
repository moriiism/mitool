include ../../Makefile.in
include ../../milib/Makefile.in
include ../../mirootlib/Makefile.in
include ../../mitiminglib/Makefile.in

INCLUDE := $(MITIMINGLIB_INC) $(MIROOTLIB_INC) $(MILIB_INC) \
        $(HEADAS_INC) $(ROOT_INC) $(MT_INC)
LDLIBS  := $(MITIMINGLIB_LIB) $(MIROOTLIB_LIB) $(MILIB_LIB) \
        $(HEADAS_LIB) $(ROOT_ALLLIBS) $(MT_LIB) $(LIB)

TARGET = efs efs_orbmod

all: $(TARGET) 

efs: efs.o  arg_efs.o sub.o
	$(CXXN) $@.o arg_$@.o sub.o ${LDLIBS} -o $@
efs_orbmod: efs_orbmod.o  arg_efs_orbmod.o sub.o
	$(CXXN) $@.o arg_$@.o sub.o ${LDLIBS} -o $@

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
