#!/usr/bin/perl

#
# template script
#
# 2016.07.19  M.Morii
#

use strict;
use warnings;
use Cwd;
use File::Basename;
use File::Temp;
use File::Spec;
use POSIX;
use Getopt::Long;
no warnings qw(once);

$ENV{'LANG'} = "C";

my $mipllib = sprintf("%s/script/mipllib/mipllib.pl",
		      $ENV{'MITOOL'});
require($mipllib);
$mipllib::sevar{'progname'} = "std.pl";

# main
{
    my $cmd;
    &SetSeVarLocal;
    GetOptions(\%mipllib::sevar,
	       'help=i', 'verbose=i', 'debug=i',
	       'outflag=s', 'procdir=s',
	       'localvar0=s', 'localvar1=s') or &Usage();
    if(0 != $mipllib::sevar{'help'}){
	&Usage();
    }
    if(-1 < $mipllib::sevar{'verbose'}){
	printf("#--- %s: START ---#\n", $mipllib::sevar{'progname'});
	if(0 < $mipllib::sevar{'verbose'}){
	    &mipllib::PrintEnv;
	    &mipllib::PrintVar;
	}
	&mipllib::PrintSeVar;
	&PrintSeVarLocal;
    }

    # -- argument
    my $NARG = 1;
    my($infile);  # relpath from $procdir or fullpath
    if(-1 < $mipllib::sevar{'verbose'}){
	printf("# of arg = %d\n", $#ARGV + 1);
    }
    if( $#ARGV == $NARG - 1){
	my $iarg = 0;
	$infile    = $ARGV[$iarg]; $iarg ++;
    }else{
        printf("# of arg must be %d.\n", $NARG);
	&Usage();
    }
    my $prompt_arg = "arg";
    if(-1 < $mipllib::sevar{'verbose'}){
	printf("%s: %s: infile  = %s\n",
	       $mipllib::sevar{'progname'}, $prompt_arg,
	       $infile);
    }
    # == argument

    chdir($mipllib::sevar{'procdir'});
    my $procdir_full = cwd;
    my $infile_full = File::Spec->rel2abs($infile, $procdir_full);
    #    my $infile_full_clean = Cwd::realpath($infile_full);

    if(-1 < $mipllib::sevar{'verbose'}){
	printf("infile_full = %s\n", $infile_full);
    }

    # read file
    #    open(IN, "<$infile_full") or die "$!";
    # don't use 'die "$!"', because the error message is not English and
    # the standard error message "Died at ... line **." is not used.
    open(IN, "<$infile_full") or die;
    while(my $line = <IN>){
	chomp($line);

	# 1. skip blank line
	#    "\s" is "[ \n\r\f\t]".
	#    * is used for 0<=.
	# 2. skip comment line (#)
	# 3. skip comment line (!)
	if($line =~ /^\s*$/ or $line =~ /^\s*\#/ or $line =~ /^\s*\!/) {
	    next;
	}
	if(-1 < $mipllib::sevar{'verbose'}){
	    printf("%s\n", $line);
	}
    }
    close(IN);

    if(-1 < $mipllib::sevar{'verbose'}){
	printf("#=== %s: END ===#\n", $mipllib::sevar{'progname'});
    }
} # main


sub Usage
{
    my $func_name = "Usage";
    if(-1 != $#_){
        printf("%s: %s: error.\n", $mipllib::sevar{'progname'}, $func_name);
        die;
    }
    printf("usage: %s [--help=(0)] [--verbose=(0)] [--debug=(0)] " .
	   "[--outflag=(overwrite)] [--procdir=(.)] " .
	   "[--localvar0=(aaa)] [--localvar1=(bbb)] " .
	   " -- " .
	   "infile\n",
	   $mipllib::sevar{'progname'});
    exit;
}

sub SetSeVarLocal
{
    my $func_name = "SetSeVarLocal";
    $mipllib::sevar{'localvar0'}  = "aaa";
    $mipllib::sevar{'localvar1'}  = "bbb";
}

sub PrintSeVarLocal
{
    my $func_name = "PrintSeVarLocal";
    my $prompt_sevar = "sevar";

    printf("%s: %s: localvar0       = %s\n",
           $mipllib::sevar{'progname'}, $prompt_sevar,
           $mipllib::sevar{'localvar0'});
    printf("%s: %s: localvar1       = %s\n",
           $mipllib::sevar{'progname'}, $prompt_sevar,
           $mipllib::sevar{'localvar1'});
}
