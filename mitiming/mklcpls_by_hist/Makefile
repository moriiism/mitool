include ../../Makefile.in
include ../../milib/Makefile.in
include ../../mirootlib/Makefile.in
include ../../mitiminglib/Makefile.in

INCLUDE := $(MITIMINGLIB_INC) $(MIROOTLIB_INC) $(MILIB_INC) \
        $(HEADAS_INC) $(ROOT_INC) $(MT_INC)
LDLIBS  := $(MITIMINGLIB_LIB) $(MIROOTLIB_LIB) $(MILIB_LIB) \
        $(HEADAS_LIB) $(ROOT_ALLLIBS) $(MT_LIB) $(LIB)

TARGET = draw_lcpls  draw_lcpls_phflux  draw_lcpls_rate \
	sim_lcpls_phflux  sim_lcpls_phflux_gti  sim_lcpls_rate

all: $(TARGET) 

draw_lcpls: draw_lcpls.o  arg_draw_lcpls.o
	$(CXXN) $@.o arg_$@.o ${LDLIBS} -o $@

draw_lcpls_phflux: draw_lcpls_phflux.o  arg_draw_lcpls_phflux.o
	$(CXXN) $@.o arg_$@.o ${LDLIBS} -o $@

draw_lcpls_rate: draw_lcpls_rate.o  arg_draw_lcpls_rate.o
	$(CXXN) $@.o arg_$@.o ${LDLIBS} -o $@

sim_lcpls_phflux: sim_lcpls_phflux.o  arg_sim_lcpls_phflux.o
	$(CXXN) $@.o arg_$@.o ${LDLIBS} -o $@

sim_lcpls_phflux_gti: sim_lcpls_phflux_gti.o  arg_sim_lcpls_phflux_gti.o
	$(CXXN) $@.o arg_$@.o ${LDLIBS} -o $@

sim_lcpls_rate: sim_lcpls_rate.o  arg_sim_lcpls_rate.o
	$(CXXN) $@.o arg_$@.o ${LDLIBS} -o $@


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
