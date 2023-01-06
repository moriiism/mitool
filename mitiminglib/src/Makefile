include ../../Makefile.in
include ../../milib/Makefile.in
include ../../mirootlib/Makefile.in
include ../../mifunclib/Makefile.in
include ../../mitiminglib/Makefile.in

INCLUDE := $(MITIMINGLIB_INC) $(MIFUNCLIB_INC) $(MIROOTLIB_INC) \
	$(MILIB_INC) $(HEADAS_INC)

TARGET := libmitiminglib.a

OBJ := telescope.o   ephemeris.o  ephemeris_calc.o \
	timeconv.o  folding.o  pulseprof_stat.o \
	zn2.o  estimate.o \
	gti.o lomb.o  gls.o
#  func_maxiobs.o
# func_pls.o
#	binaryorb.o \

all: $(TARGET)

LIB_DEST := ../lib
libmitiminglib.a: ${OBJ}
	$(AR) -r $@ $(OBJ)
	ranlib $@
	if [ ! -d $(LIB_DEST) ]; then mkdir $(LIB_DEST); fi
	cp $@ ${LIB_DEST}
	ranlib ${LIB_DEST}/$@

libmitiminglib.so: ${OBJ}
	$(CC) -shared -g -O2 -o $@ ${OBJ}
	if [ ! -d $(LIB_DEST) ]; then mkdir $(LIB_DEST); fi
	cp $@ ${LIB_DEST}

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
	-rm -f *.o *.a *.so

cleaner: clean
	-rm -f ${TARGET} *% *~ core
	-rm -R $(LIB_DEST)
