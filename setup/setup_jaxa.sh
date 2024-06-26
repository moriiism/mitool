#
# setup.sh
#
# setup script for moriiism/mitool
#
# 2022.05.11e M. Morii
#

#
# This script must be loaded by "source" command of bash,
# before using moriiism/mitool
#

##
## mitool 
##

export MITOOL=/home/morii/work/github/moriiism/mitool
export LD_LIBRARY_PATH=/soft/gcc/9.4.0/lib64:\
/soft/cfitsio/3410/lib:\
/soft/OpenBLAS/0.3.20/lib:\
/soft/lapack/3.10.1/lib:\
/soft/gsl/2.7.1/lib:\
/soft/root/6.24.06/lib/root:${LD_LIBRARY_PATH}
export PATH=/soft/root/6.24.06/bin:${PATH}

alias root="root -l"

#
# HEADAS
#

HEADAS_VER=6.30.1
export HEADAS=/soft/heasoft/${HEADAS_VER}/x86_64-pc-linux-gnu-libc2.17
source $HEADAS/headas-init.sh
export PGPLOT_TYPE=/xw
#export PGPLOT_PS_WIDTH=7500
#export PGPLOT_PS_HEIGHT=11000

export PGPLOT_PS_WIDTH=30000
export PGPLOT_PS_HEIGHT=44000


################################################################
################################################################
############ Don't Edit Below. #################################

##
## change the terminal title
##

termtitle="mitool"
PROMPT_COMMAND='echo -ne "\033]0;${termtitle}\007"'
