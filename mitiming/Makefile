BINS = binorb efs eph est \
	fold gls gti hist_info \
	lc lomb mklcpls \
	mklcpls_by_hist pow time zn2

SUBDIR = $(BINS)

ALL = $(BINS)

all:
	for dir in $(ALL); do \
	(cd $$dir; ${MAKE} all); \
	done

clean:
	for dir in $(SUBDIR); do \
	(cd $$dir; ${MAKE} clean); \
	done

cleaner:
	-rm -f *~
	for dir in $(SUBDIR); do \
	(cd $$dir; ${MAKE} cleaner); \
	done
