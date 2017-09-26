include ../../Makefile.in
include ../../milib/Makefile.in
include ../../mirootlib/Makefile.in
include ../../mifunclib/Makefile.in

INCLUDE := $(MIFUNCLIB_INC) $(MIROOTLIB_INC) $(ROOT_INC) $(MILIB_INC)  $(MT_INC)
LDLIBS  := $(MIFUNCLIB_LIB) $(MIROOTLIB_LIB) $(ROOT_ALLLIBS)  $(MILIB_LIB) $(MT_LIB) $(LIB)

# test passed using assert
TARGET_PASS := test_vect  test_data1d_ope

# test passed (manual check)
TARGET_PASS_MANUAL := test_stat1d \
	test_data1d   test_data1d_copy \
	test_data1d_nerr  test_data1d_serr  test_data1d_terr \
	test_graph2d  test_graph2d_nerr  test_graph2d_serr  test_graph2d_terr \
	test_graph3d  test_graph3d_nerr  test_graph3d_serr  test_graph3d_terr \
	test_hist1d  test_hist1d_nerr  test_hist1d_serr  test_hist1d_terr \
	test_hist2d

TARGET_PASS_ALMOST := test_math

# under testing
TARGET_TESTING := test_plot_conf    \
	test_hist2d_nerr test_hist2d_serr \
	test_hist_info \
test_interval  \
test_hist2d_terr \
test_graph2d_ope \
test_qdp_tool

# not yet tested :
#	  test_hist_info_ope \
#	      
#	     \
#	      \
#	       \
#	    test_hist1d_ope  test_hist2d_ope \
#	test_func  
#	test_cont
#
# test_func_par

TARGET := $(TARGET_PASS) $(TARGET_PASS_MANUAL) $(TARGET_PASS_ALMOST) $(TARGET_TESTING)


all: $(TARGET)

test_vect: test_vect.o
	$(CXXN) $@.o ${LDLIBS} -o $@
test_stat1d: test_stat1d.o
	$(CXXN) $@.o ${LDLIBS} -o $@
test_plot_conf: test_plot_conf.o
	$(CXXN) $@.o ${LDLIBS} -o $@

test_math: test_math.o
	$(CXXN) $@.o ${LDLIBS} -o $@
test_interval: test_interval.o
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
test_graph2d_serr: test_graph2d_serr.o
	$(CXXN) $@.o ${LDLIBS} -o $@
test_graph2d_terr: test_graph2d_terr.o
	$(CXXN) $@.o ${LDLIBS} -o $@
test_graph3d: test_graph3d.o
	$(CXXN) $@.o ${LDLIBS} -o $@
test_graph3d_nerr: test_graph3d_nerr.o
	$(CXXN) $@.o ${LDLIBS} -o $@
test_graph3d_serr: test_graph3d_serr.o
	$(CXXN) $@.o ${LDLIBS} -o $@
test_graph3d_terr: test_graph3d_terr.o
	$(CXXN) $@.o ${LDLIBS} -o $@
test_hist1d: test_hist1d.o
	$(CXXN) $@.o ${LDLIBS} -o $@
test_hist1d_nerr: test_hist1d_nerr.o
	$(CXXN) $@.o ${LDLIBS} -o $@
test_hist1d_serr: test_hist1d_serr.o
	$(CXXN) $@.o ${LDLIBS} -o $@
test_hist1d_terr: test_hist1d_terr.o
	$(CXXN) $@.o ${LDLIBS} -o $@
test_hist2d: test_hist2d.o
	$(CXXN) $@.o ${LDLIBS} -o $@
test_hist2d_nerr: test_hist2d_nerr.o
	$(CXXN) $@.o ${LDLIBS} -o $@
test_hist2d_serr: test_hist2d_serr.o
	$(CXXN) $@.o ${LDLIBS} -o $@
test_hist2d_terr: test_hist2d_terr.o
	$(CXXN) $@.o ${LDLIBS} -o $@
test_data1d_ope: test_data1d_ope.o
	$(CXXN) $@.o ${LDLIBS} -o $@
test_graph2d_ope: test_graph2d_ope.o
	$(CXXN) $@.o ${LDLIBS} -o $@
test_graph3d_ope: test_graph3d_ope.o
	$(CXXN) $@.o ${LDLIBS} -o $@
test_hist1d_ope: test_hist1d_ope.o
	$(CXXN) $@.o ${LDLIBS} -o $@
test_hist2d_ope: test_hist2d_ope.o
	$(CXXN) $@.o ${LDLIBS} -o $@
test_func: test_func.o
	$(CXXN) $@.o ${LDLIBS} -o $@
test_func_par: test_func_par.o
	$(CXXN) $@.o ${LDLIBS} -o $@
test_qdp_tool: test_qdp_tool.o
	$(CXXN) $@.o ${LDLIBS} -o $@
test_cont: test_cont.o
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
