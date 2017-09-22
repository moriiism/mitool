include ../../Makefile.in
include ../../milib/Makefile.in
include ../../mirootlib/Makefile.in
include ../../mifunclib/Makefile.in

INCLUDE := $(MIFUNCLIB_INC) $(MILIB_INC) $(MT_INC)
LDLIBS  := $(MIFUNCLIB_LIB) $(MILIB_LIB) $(MT_LIB) $(LIB)

# test passed using assert
TARGET_PASS := 

TARGET := $(TARGET_PASS)

all: $(TARGET)

#test_vect: test_vect.o
#	$(CXXN) $@.o ${LDLIBS} -o $@

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
