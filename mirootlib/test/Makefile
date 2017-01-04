
include ../../Makefile.in

INCLUDE = $(MIROOTLIB_INC) $(MILIB_INC) $(MT_INC)
LDLIBS  = $(MIROOTLIB_LIB) $(MILIB_LIB) $(MT_LIB) $(LIB)

TARGET = test_data1d  test_hist2d_nerr

all: $(TARGET) 

test_data1d: test_data1d.o
	$(CXXN) $@.o ${LDLIBS} -o $@

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
