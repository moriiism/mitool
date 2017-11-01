BINS =  micsv2tree  milcinfo  minfold  milcwin  \
	mifunc rad4d2img  miselcol  milcsim  miselimgline

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
