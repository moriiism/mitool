
include ../Makefile.in

INCLUDE = $(MILIB_INC) $(MT_INC)
LDLIBS  = $(MILIB_LIB) $(MT_LIB) $(LIB)

TARGET = test_hist2d_nerr

all: $(TARGET) 

test_hist2d_nerr: test_hist2d_nerr.o
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

install: all
	if [ ! -d $(INST_BIN_DIR) ]; then mkdir $(INST_BIN_DIR); fi
	install ${TARGET} ${INST_BIN_DIR}

clean:
	-rm -f *.o

cleaner: clean
	-rm -f ${TARGET} *% *~ core
