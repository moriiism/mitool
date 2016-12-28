
include ../../Makefile.in

INCLUDE = $(MILIB_INC) $(CFITSIO_INC) $(MT_INC)

TARGET = libmilib.a
# libmilib.so

OBJ = base.o  str.o  iolib.o  rand.o  math.o  linalg.o \
	img_info.o  fits.o  time.o  interval.o  stat1d.o \
	data1d.o  data1d_nerr.o  data1d_serr.o  data1d_terr.o

all: $(TARGET)

LIB_DEST = ../lib
libmilib.a: ${OBJ}
	$(AR) -r $@ $(OBJ)
	ranlib $@
	if [ ! -d $(LIB_DEST) ]; then mkdir $(LIB_DEST); fi
	cp $@ ${LIB_DEST}
	ranlib ${LIB_DEST}/$@

libmilib.so: ${OBJ}
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

install: all
	if [ ! -d $(INST_BIN_DIR) ]; then mkdir $(INST_BIN_DIR); fi
	install ${TARGET} ${INST_BIN_DIR}

clean:
	-rm -f *.o *.a *.so

cleaner: clean
	-rm -f ${TARGET} *% *~ core
