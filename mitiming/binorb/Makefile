include ../../Makefile.in
include ../../milib/Makefile.in
include ../../mirootlib/Makefile.in
include ../../mitiminglib/Makefile.in

INCLUDE := $(MITIMINGLIB_INC) $(HEADAS_INC) $(ROOT_INC) \
	$(MIROOTLIB_INC) $(MILIB_INC) $(MT_INC)
LDLIBS  := $(MITIMINGLIB_LIB) $(HEADAS_LIB) $(ROOT_ALLLIBS) \
	$(MIROOTLIB_LIB) $(MILIB_LIB) $(LIB)

TARGET = demod_da1d  plot_binorb  t90_to_tperi

all: $(TARGET) 

demod_da1d: demod_da1d.o  arg_demod_da1d.o
	$(CXXN) $@.o arg_$@.o ${LDLIBS} -o $@
plot_binorb: plot_binorb.o  arg_plot_binorb.o
	$(CXXN) $@.o arg_$@.o ${LDLIBS} -o $@
t90_to_tperi: t90_to_tperi.o  arg_t90_to_tperi.o
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
