#!/usr/bin/perl

#
# template for a simple script
#
# 2014.10.22  M.Morii
#

use strict;
use warnings;
use POSIX;
no warnings qw(once);

$ENV{'LANG'} = "C";

my $mxkwpllib = sprintf("%s/script/mxkwpllib/mxkwpllib.pl",
			$ENV{'MXKWTOOL'});
require($mxkwpllib);
$mxkwpllib::sevar{'progname'} = "simple.pl";

# main
{
    printf("#--- %s: START ---#\n", $mxkwpllib::sevar{'progname'});

    my $cmd;
    # -- argument
    my $NARG = 1;
    my($value);
    printf("# of arg = %d\n", $#ARGV + 1);
    if( $#ARGV == $NARG - 1){
	my $iarg = 0;
	$value    = $ARGV[$iarg]; $iarg ++;
    }else{
        printf("# of arg must be %d.\n", $NARG);
	&Usage();
    }
    my $prompt_arg = "arg";
    printf("%s: %s: value  = %s\n", $mxkwpllib::sevar{'progname'}, $prompt_arg, $value);
    # == argument

    printf("#=== %s: END ===#\n", $mxkwpllib::sevar{'progname'});
} # main


sub Usage
{
    printf("usage: %s " .
	   "value\n", $mxkwpllib::sevar{'progname'});
    exit;
}
