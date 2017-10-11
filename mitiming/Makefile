ALL = binorb efs eph est \
	fold gls gti hist_info \
	lc lomb mklcpls \
	mklcpls_by_hist pow time zn2

all:
	for dir in $(ALL); do \
	(cd $$dir; ${MAKE} all); \
	done

install: all
	for dir in $(ALL); do \
	(cd $$dir; ${MAKE} install); \
	done

clean:
	for dir in $(ALL); do \
	(cd $$dir; ${MAKE} clean); \
	done

cleaner:
	-rm -f *~
	for dir in $(ALL); do \
	(cd $$dir; ${MAKE} cleaner); \
	done
