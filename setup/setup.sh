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

################################################################
################################################################
############ Don't Edit Below. #################################

##
## change the terminal title
##

termtitle="mitool"
PROMPT_COMMAND='echo -ne "\033]0;${termtitle}\007"'
