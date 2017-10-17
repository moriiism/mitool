#
# setup.sh
#
# setup script for moriiism/mitool
#
# 2017.02.03 M. Morii
#

#
# This script must be loaded by "source" command of bash,
# before using moriiism/mitool
#

##
## mitool 
##

export MITOOL=/home/morii/work/github/moriiism/mitool
export LD_LIBRARY_PATH=/soft/minuit2/5.34.14/lib:/soft/root/6.08.02/lib:/soft/gsl/2.3/lib:/usr/lib/gcc/x86_64-redhat-linux/4.4.4:${LD_LIBRARY_PATH}
export PATH=/soft/root/6.08.02/bin:${PATH}

alias root="root -l"

#
# HEADAS
#

HEADAS_VER=6.16
# export HEADAS=/soft/heasoft/heasoft-${HEADAS_VER}/x86_64-unknown-linux-gnu-libc2.12
export HEADAS=/soft/heasoft/${HEADAS_VER}/x86_64-unknown-linux-gnu-libc2.17
source $HEADAS/headas-init.sh
export PGPLOT_TYPE=/xw


<<<<<<< HEAD
=======
# debug
# export LD_LIBRARY_PATH=/soft/minuit2/5.34.14/lib:${LD_LIBRARY_PATH}


>>>>>>> 48c9309aed30e511adb1e474da0723fed144be8c

################################################################
################################################################
############ Don't Edit Below. #################################

##
## change the terminal title
##

termtitle="mitool"
PROMPT_COMMAND='echo -ne "\033]0;${termtitle}\007"'
