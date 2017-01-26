#
# setup.sh
#
# setup script for mitool
#
# 2016.07.19 M. Morii
#

# This script must be loaded by "source" command of bash.

##
## mitool 
##

export MITOOL=/home/morii/work/github/moriiism/mitool
export LD_LIBRARY_PATH=/soft/root/6.08.02/lib:/soft/gsl/2.3/lib:${LD_LIBRARY_PATH}
export PATH=/soft/root/6.08.02/bin:${PATH}

alias root="root -l"

################################################################
################################################################
############ Don't Edit Below. #################################

##
## change the terminal title
##

termtitle="mitool"
PROMPT_COMMAND='echo -ne "\033]0;${termtitle}\007"'
