include ../../Makefile.in
include ../../milib/Makefile.in

INCLUDE = $(MILIB_INC) $(MT_INC)
LDLIBS  = $(MILIB_LIB) $(MT_LIB) $(LIB)

TARGET = test_base  test_iolib \
	test_sort  test_str  test_time

all: $(TARGET) 

test_base: test_base.o
	$(CXXN) $@.o ${LDLIBS} -o $@
test_iolib: test_iolib.o
	$(CXXN) $@.o ${LDLIBS} -o $@
test_sort: test_sort.o
	$(CXXN) $@.o ${LDLIBS} -o $@
test_str: test_str.o
	$(CXXN) $@.o ${LDLIBS} -o $@
test_time: test_time.o
	$(CXXN) $@.o ${LDLIBS} -o $@

test_rand_mt: test_rand_mt.o
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
