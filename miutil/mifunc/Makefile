include ../../Makefile.in
include ../../milib/Makefile.in
include ../../mirootlib/Makefile.in
include ../../miminuitlib/Makefile.in
include ../../mifunclib/Makefile.in

INCLUDE = ${FFTW_INC} $(HEADAS_INC) $(ROOT_INC) \
	$(MIMINUITLIB_INC) $(MIFUNCLIB_INC) $(MIROOTLIB_INC) $(MILIB_INC) 
LDLIBS  = $(MIMINUITLIB_LIB) $(MIFUNCLIB_LIB)  $(MIROOTLIB_LIB) $(MILIB_LIB) \
	$(HEADAS_LIB) $(ROOT_ALLLIBS) ${FFTW_LIB} $(LIB)

OBJ = func_user.o

TARGET = eval_1d  eval_2d \
	draw_func_1d  \
	draw_func_2d  \
	draw_func_list_1d  draw_func_list_2d \
	draw_func_data_1d  \
	draw_func_data_list_1d  \
	sim_func_1d  sim_func_2d \
	sim_func_rate_1d  sim_func_rate_2d \
	fit_func_chi2_1d  fit_func_chi2_2d \
	fit_func_cstat_1d  fit_func_cstat_2d \
	fit_func_cstat_unbin_1d  fit_func_cstat_unbin_2d \
	draw_spec_data  draw_spec_data_list \
	solve_eq_1d \
	test_func_unbin_ks_1d \
	fit_func_chi2_multi_1d \
	fit_func_chi2_svd_1d \
	fit_func_chi2_qp_1d \
	sim_func_lincomb_rate_1d \
	fit_func_cstat_unbin_qp_1d \
	fit_func_cstat_unbin_em_1d

#	fit_func_cstat_unbin_qp_multi_1d \



##test_func_unbin_ks_2d \


all: $(TARGET) 

eval_1d: eval_1d.o arg_eval_1d.o  ${OBJ}
	$(CXXN) $@.o arg_$@.o ${OBJ} ${LDLIBS} -o $@

eval_2d: eval_2d.o arg_eval_2d.o ${OBJ}
	$(CXXN) $@.o arg_$@.o ${OBJ} ${LDLIBS} -o $@

draw_func_1d: draw_func_1d.o arg_draw_func_1d.o  ${OBJ}
	$(CXXN) $@.o arg_$@.o ${OBJ} ${LDLIBS} -o $@

draw_func_2d: draw_func_2d.o arg_draw_func_2d.o ${OBJ}
	$(CXXN) $@.o arg_$@.o ${OBJ} ${LDLIBS} -o $@

draw_func_list_1d: draw_func_list_1d.o  arg_draw_func_list_1d.o ${OBJ}
	$(CXXN) $@.o arg_$@.o ${OBJ} ${LDLIBS} -o $@

draw_func_list_2d: draw_func_list_2d.o  arg_draw_func_list_2d.o ${OBJ}
	$(CXXN) $@.o arg_$@.o ${OBJ} ${LDLIBS} -o $@

draw_func_data_1d: draw_func_data_1d.o  arg_draw_func_data_1d.o ${OBJ}
	$(CXXN) $@.o arg_$@.o ${OBJ} ${LDLIBS} -o $@

draw_func_data_2d: draw_func_data_2d.o  arg_draw_func_data_2d.o ${OBJ}
	$(CXXN) $@.o arg_$@.o ${OBJ} ${LDLIBS} -o $@

draw_func_data_list_1d: draw_func_data_list_1d.o  arg_draw_func_data_list_1d.o ${OBJ}
	$(CXXN) $@.o arg_$@.o ${OBJ} ${LDLIBS} -o $@

draw_func_data_list_2d: draw_func_data_list_2d.o  arg_draw_func_data_list_2d.o ${OBJ}
	$(CXXN) $@.o arg_$@.o ${OBJ} ${LDLIBS} -o $@

sim_func_1d: sim_func_1d.o  arg_sim_func_1d.o ${OBJ}
	$(CXXN) $@.o arg_$@.o ${OBJ} ${LDLIBS} -o $@

sim_func_2d: sim_func_2d.o  arg_sim_func_2d.o  ${OBJ}
	$(CXXN) $@.o arg_$@.o ${OBJ} ${LDLIBS} -o $@

sim_func_rate_1d: sim_func_rate_1d.o  arg_sim_func_rate_1d.o ${OBJ}
	$(CXXN) $@.o arg_$@.o ${OBJ} ${LDLIBS} -o $@

sim_func_lincomb_rate_1d: sim_func_lincomb_rate_1d.o  arg_sim_func_lincomb_rate_1d.o  ${OBJ}
	$(CXXN) $@.o arg_$@.o ${OBJ} ${LDLIBS} -o $@

sim_func_rate_2d: sim_func_rate_2d.o  arg_sim_func_rate_2d.o ${OBJ}
	$(CXXN) $@.o arg_$@.o ${OBJ} ${LDLIBS} -o $@

fit_func_chi2_1d: fit_func_chi2_1d.o  arg_fit_func_chi2_1d.o ${OBJ}
	$(CXXN) $@.o arg_$@.o ${OBJ} ${LDLIBS} -o $@

fit_func_chi2_2d: fit_func_chi2_2d.o  arg_fit_func_chi2_2d.o ${OBJ}
	$(CXXN) $@.o arg_$@.o ${OBJ} ${LDLIBS} -o $@

fit_func_chi2_asym_1d: fit_func_chi2_asym_1d.o  arg_fit_func_chi2_asym_1d.o ${OBJ}
	$(CXXN) $@.o arg_$@.o ${OBJ} ${LDLIBS} -o $@

fit_func_chi2_asym_2d: fit_func_chi2_asym_2d.o  arg_fit_func_chi2_asym_2d.o ${OBJ}
	$(CXXN) $@.o arg_$@.o ${OBJ} ${LDLIBS} -o $@

fit_func_cstat_1d: fit_func_cstat_1d.o  arg_fit_func_cstat_1d.o ${OBJ}
	$(CXXN) $@.o arg_$@.o ${OBJ} ${LDLIBS} -o $@


fit_func_cstat_2d: fit_func_cstat_2d.o  arg_fit_func_cstat_2d.o ${OBJ}
	$(CXXN) $@.o arg_$@.o ${OBJ} ${LDLIBS} -o $@

fit_func_cstat_unbin_1d: fit_func_cstat_unbin_1d.o  arg_fit_func_cstat_unbin_1d.o ${OBJ}
	$(CXXN) $@.o arg_$@.o ${OBJ} ${LDLIBS} -o $@

fit_func_cstat_unbin_2d: fit_func_cstat_unbin_2d.o  arg_fit_func_cstat_unbin_2d.o  ${OBJ}
	$(CXXN) $@.o arg_$@.o ${OBJ} ${LDLIBS} -o $@

fit_func_cstat_unbin_qp_1d: fit_func_cstat_unbin_qp_1d.o  arg_fit_func_cstat_unbin_qp_1d.o ${OBJ}
	$(CXXN) $@.o arg_$@.o ${OBJ} ${LDLIBS} -lQuadp -o $@

fit_func_cstat_unbin_qp_multi_1d: fit_func_cstat_unbin_qp_multi_1d.o  arg_fit_func_cstat_unbin_qp_multi_1d.o ${OBJ}
	$(CXXN) $@.o arg_$@.o ${OBJ} ${LDLIBS} -lQuadp -o $@

fit_func_cstat_unbin_em_1d: fit_func_cstat_unbin_em_1d.o  arg_fit_func_cstat_unbin_em_1d.o ${OBJ}
	$(CXXN) $@.o arg_$@.o ${OBJ} ${LDLIBS} -o $@

draw_spec_data: draw_spec_data.o  arg_draw_spec_data.o ${OBJ}
	$(CXXN) $@.o arg_$@.o ${OBJ} ${LDLIBS} -o $@

draw_spec_data_list: draw_spec_data_list.o  arg_draw_spec_data_list.o ${OBJ}
	$(CXXN) $@.o arg_$@.o ${OBJ} ${LDLIBS} -o $@

solve_eq_1d: solve_eq_1d.o  arg_solve_eq_1d.o  ${OBJ}
	$(CXXN) $@.o arg_$@.o ${OBJ} ${LDLIBS} -o $@

test_func_unbin_ks_1d: test_func_unbin_ks_1d.o  arg_test_func_unbin_ks_1d.o ${OBJ}
	$(CXXN) $@.o arg_$@.o ${OBJ} ${LDLIBS} -o $@
test_func_unbin_ks_2d: test_func_unbin_ks_2d.o  arg_test_func_unbin_ks_2d.o ${OBJ}
	$(CXXN) $@.o arg_$@.o ${OBJ} ${LDLIBS} -o $@

fit_func_chi2_multi_1d: fit_func_chi2_multi_1d.o  arg_fit_func_chi2_multi_1d.o ${OBJ}
	$(CXXN) $@.o arg_$@.o ${OBJ} ${LDLIBS} -o $@

fit_func_chi2_svd_1d: fit_func_chi2_svd_1d.o  arg_fit_func_chi2_svd_1d.o ${OBJ}
	$(CXXN) $@.o arg_$@.o ${OBJ} ${LDLIBS} -o $@

fit_func_chi2_qp_1d: fit_func_chi2_qp_1d.o  arg_fit_func_chi2_qp_1d.o ${OBJ}
	$(CXXN) $@.o arg_$@.o ${OBJ} ${LDLIBS} -lQuadp -o $@


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
