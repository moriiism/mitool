BINS =  micsv2tree  milcinfo  minfold  milcwin  \
	mifunc  miselcol  milcsim  miselimgline \
	migetsigda1d  migetsigimg  miselimg_zeroline \
	mimkimg_enmask  miselcubeframe  miimgsmooth \
	milcsmooth  migetsighd1d  rad4d2img
# mipow

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
