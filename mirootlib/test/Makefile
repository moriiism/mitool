include ../../Makefile.in
include ../Makefile.in

#INCLUDE := $(MIROOTLIB_INC) $(ROOT_INC) $(MILIB_INC)  $(MT_INC)
#LDLIBS  := $(MIROOTLIB_LIB) $(ROOT_ALLLIBS)  $(MILIB_LIB) $(MT_LIB) $(LIB)

INCLUDE := $(MIROOTLIB_INC) $(ROOT_INC) $(MILIB_INC)  
LDLIBS  := $(MIROOTLIB_LIB) $(ROOT_ALLLIBS)  $(MILIB_LIB) $(LIB)


TARGET := test_math  test_data1d  test_data1d_copy  \
	test_data1d_nerr  test_data1d_serr  test_data1d_terr \
	test_hist_info \
	test_graph2d  test_graph2d_nerr \
	test_hist1d_nerr  test_hist1d_serr  \
	test_hist2d_serr  

all: $(TARGET) 

test_math: test_math.o
	$(CXXN) $@.o ${LDLIBS} -o $@

test_data1d: test_data1d.o
	$(CXXN) $@.o ${LDLIBS} -o $@
test_data1d_copy: test_data1d_copy.o
	$(CXXN) $@.o ${LDLIBS} -o $@
test_data1d_nerr: test_data1d_nerr.o
	$(CXXN) $@.o ${LDLIBS} -o $@
test_data1d_serr: test_data1d_serr.o
	$(CXXN) $@.o ${LDLIBS} -o $@
test_data1d_terr: test_data1d_terr.o
	$(CXXN) $@.o ${LDLIBS} -o $@
test_hist_info: test_hist_info.o
	$(CXXN) $@.o ${LDLIBS} -o $@
test_hist_info_ope: test_hist_info_ope.o
	$(CXXN) $@.o ${LDLIBS} -o $@
test_graph2d: test_graph2d.o
	$(CXXN) $@.o ${LDLIBS} -o $@
test_graph2d_nerr: test_graph2d_nerr.o
	$(CXXN) $@.o ${LDLIBS} -o $@
test_hist1d_nerr: test_hist1d_nerr.o
	$(CXXN) $@.o ${LDLIBS} -o $@
test_hist1d_serr: test_hist1d_serr.o
	$(CXXN) $@.o ${LDLIBS} -o $@

test_hist2d_serr: test_hist2d_serr.o
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
