
include ../../Makefile.in
include ../../milib/Makefile.in
include ../../mirootlib/Makefile.in
include ../../miminuitlib/Makefile.in
include ../../mitiminglib/Makefile.in

INCLUDE := $(MITIMINGLIB_INC) $(MIMINUITLIB_INC) $(HEADAS_INC) $(ROOT_INC) \
	$(MIROOTLIB_INC) $(MILIB_INC) $(MT_INC)
LDLIBS  := $(MITIMINGLIB_LIB) $(MIMINUITLIB_LIB) $(HEADAS_LIB) $(ROOT_ALLLIBS) \
	$(MIROOTLIB_LIB) $(MILIB_LIB) $(LIB)

TARGET = est_by_lc  nyquist

all: $(TARGET) 

est_by_lc: est_by_lc.o  arg_est_by_lc.o
	$(CXXN) $@.o arg_$@.o ${LDLIBS} -o $@

nyquist: nyquist.o  arg_nyquist.o
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

install: all
	if [ ! -d $(INST_BIN_DIR) ]; then mkdir $(INST_BIN_DIR); fi
	install ${TARGET} ${INST_BIN_DIR}

clean:
	-rm -f *.o

cleaner: clean
	-rm -f ${TARGET} *% *~ core
