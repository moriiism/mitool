
include ../../Makefile.in
include ../../milib/Makefile.in
include ../../mirootlib/Makefile.in
include ../../mitiminglib/Makefile.in

INCLUDE := $(MITIMINGLIB_INC) $(MIROOTLIB_INC) $(HEADAS_INC) $(ROOT_INC) \
	$(MIROOTLIB_INC) $(MILIB_INC) $(MT_INC)
LDLIBS  := $(MITIMINGLIB_LIB) $(MIROOTLIB_LIB) $(HEADAS_LIB) $(ROOT_ALLLIBS) \
	$(MIROOTLIB_LIB) $(MILIB_LIB) $(LIB)

TARGET =  plot_lc_da1d  plot_lc_hd1d  plot_lc_gd2d  \
        select_da1d_by_gti  \
        binning

all: $(TARGET) 

select_da1d_by_gti: select_da1d_by_gti.o  arg_select_da1d_by_gti.o
	$(CXXN) $@.o arg_$@.o ${LDLIBS} -o $@

select_hd1d_by_gti: select_hd1d_by_gti.o  arg_select_hd1d_by_gti.o
	$(CXXN) $@.o arg_$@.o ${LDLIBS} -o $@

select_gd2d_by_gti: select_gd2d_by_gti.o  arg_select_gd2d_by_gti.o
	$(CXXN) $@.o arg_$@.o ${LDLIBS} -o $@

binning: binning.o  arg_binning.o
	$(CXXN) $@.o  arg_$@.o  ${LDLIBS} -o $@

plot_lc_da1d: plot_lc_da1d.o  arg_plot_lc_da1d.o
	$(CXXN) $@.o  arg_$@.o  ${LDLIBS} -o $@

plot_lc_hd1d: plot_lc_hd1d.o  arg_plot_lc_hd1d.o
	$(CXXN) $@.o  arg_$@.o  ${LDLIBS} -o $@

plot_lc_gd2d: plot_lc_gd2d.o  arg_plot_lc_gd2d.o
	$(CXXN) $@.o  arg_$@.o  ${LDLIBS} -o $@


tconv: tconv.o ${OBJ}
	$(CXXN) $@.o ${OBJ} ${LDLIBS} -o $@

binrate2bincount: binrate2bincount.o ${OBJ}
	$(CXXN) $@.o ${OBJ} ${LDLIBS} -o $@

split_by_gti: split_by_gti.o ${OBJ}
	$(CXXN) $@.o ${OBJ} ${LDLIBS} -o $@


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
