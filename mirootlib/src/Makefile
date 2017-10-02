
include ../../Makefile.in
include ../../milib/Makefile.in
include ../../mirootlib/Makefile.in

INCLUDE := $(ROOT_INC) $(MIROOTLIB_INC) $(MILIB_INC) $(MT_INC)

TARGET := libmirootlib.a

OBJ := math.o  interval.o  stat1d.o  vect.o  geom.o \
	func.o  func_par.o \
	plot_conf.o  root_tool.o \
	data1d.o  data1d_nerr.o  data1d_serr.o  data1d_terr.o  \
	hist_info.o  \
	graph2d.o  graph2d_nerr.o  graph2d_serr.o  graph2d_terr.o \
	graph3d.o  graph3d_nerr.o  graph3d_serr.o  graph3d_terr.o \
	hist1d.o  hist1d_nerr.o  hist1d_serr.o  hist1d_terr.o \
	hist2d.o  hist2d_nerr.o  hist2d_serr.o  hist2d_terr.o \
	data1d_ope.o  graph2d_ope.o  hist1d_ope.o  hist2d_ope.o \
	hist_info_ope.o \
	qdp_tool.o  cont.o \
	solve.o  func_ope.o

all: $(TARGET)

LIB_DEST := ../lib
libmirootlib.a: ${OBJ}
	$(AR) -r $@ $(OBJ)
	ranlib $@
	if [ ! -d $(LIB_DEST) ]; then mkdir $(LIB_DEST); fi
	cp $@ ${LIB_DEST}
	ranlib ${LIB_DEST}/$@

libmirootlib.so: ${OBJ}
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
	-rm -R $(LIB_DEST)
