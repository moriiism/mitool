
include ../../Makefile.in

INCLUDE = $(MILIB_INC) $(MT_INC)
LDLIBS  = $(MILIB_LIB) $(MT_LIB) $(LIB)

TARGET = test_base  test_iolib  test_rand  \
	test_sort  test_str  test_time

all: $(TARGET) 

test_base: test_base.o
	$(CXXN) $@.o ${LDLIBS} -o $@
test_iolib: test_iolib.o
	$(CXXN) $@.o ${LDLIBS} -o $@
test_rand: test_rand.o
	$(CXXN) $@.o ${LDLIBS} -o $@
test_sort: test_sort.o
	$(CXXN) $@.o ${LDLIBS} -o $@
test_str: test_str.o
	$(CXXN) $@.o ${LDLIBS} -o $@
test_time: test_time.o
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
