include ../../Makefile.in
include ../../milib/Makefile.in
include ../../mirootlib/Makefile.in
include ../../mifunclib/Makefile.in
include ../../miminuitlib/Makefile.in

INCLUDE := $(MIMINUITLIB_INC) $(MIFUNCLIB_INC) \
	$(MIROOTLIB_INC) $(MILIB_INC) $(ROOT_INC) $(MT_INC)

TARGET := libmiminuitlib.a

OBJ := func_par_index.o \
	chi2plot.o  fitfunc.o \
	fitparam.o  fitstat.o \
	fitstat_hg.o  \
	link.o  ls.o \
	minfcn.o  search_par.o \
	tie.o  qdp_tool.o

all: $(TARGET)

LIB_DEST := ../lib
libmiminuitlib.a: ${OBJ}
	$(AR) -r $@ $(OBJ)
	ranlib $@
	if [ ! -d $(LIB_DEST) ]; then mkdir $(LIB_DEST); fi
	cp $@ ${LIB_DEST}
	ranlib ${LIB_DEST}/$@

libmiminuitlib.so: ${OBJ}
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
