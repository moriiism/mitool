
include ../../Makefile.in
include ../../mirootlib/Makefile.in
include ../../mitiminglib/Makefile.in

INCLUDE := $(MITIMINGLIB_INC) $(HEADAS_INC) $(ROOT_INC) \
	$(MIROOTLIB_INC) $(MILIB_INC) $(MT_INC)
LDLIBS  := $(MITIMINGLIB_LIB) $(HEADAS_LIB) $(ROOT_ALLLIBS) \
	$(MIROOTLIB_LIB) $(MILIB_LIB) $(LIB)

TARGET = mklc

all: $(TARGET) 

mklc: mklc.o  arg_mklc.o
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
