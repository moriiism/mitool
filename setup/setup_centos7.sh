#
# setup_centos7.sh
#
# setup script for moriiism/mitool
#
# 2024.06.03 M. Morii
#

#
# This script must be loaded by "source" command of bash,
# before using moriiism/mitool
#

##
## mitool 
##

export MITOOL=/home/morii/work/github/moriiism/mitool
export LD_LIBRARY_PATH=/soft/heasoft/6.33.2/x86_64-pc-linux-gnu-libc2.17/lib:\
/soft/blas/3.12.0/lib:\
/soft/lapack/3.12.0/lib:\
/soft/gsl/2.8/lib:\
/soft/root/6.24.08/lib:${LD_LIBRARY_PATH}
export PATH=/soft/root/6.24.08/bin:${PATH}

alias root="root -l"

#
# HEADAS
#

HEADAS_VER=6.33.2
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
