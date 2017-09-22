ALL =  milib  miblaslib  mifitslib  mirootlib \
	mifunclib  miminuitlib  mitiminglib  \
	mitiming  miutil \
	script setup doc \
	try

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
