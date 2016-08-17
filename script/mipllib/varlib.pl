#!/usr/bin/perl

#
# varlib
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

our $mitool_bin_dir = "";
our $mitool_script_dir = "";

our %sevar = ();

&SetVar();
&InitSeVar();

sub PrintEnv
{
    my $func_name = "mxkwpllib::PrintEnv";
    printf("%s: PATH             = %s\n", $func_name, $ENV{'PATH'});
    printf("%s: LD_LIBRARY_PATH  = %s\n", $func_name, $ENV{'LD_LIBRARY_PATH'});
    printf("%s: PYTHONPATH       = %s\n", $func_name, $ENV{'PYTHONPATH'});
    printf("%s: HEADAS           = %s\n", $func_name, $ENV{'HEADAS'}); 
    printf("%s: ROOTSYS          = %s\n", $func_name, $ENV{'ROOTSYS'});
    printf("%s: PGPLOT_TYPE      = %s\n", $func_name, $ENV{'PGPLOT_TYPE'});

    printf("%s: MITOOL           = %s\n", $func_name, $ENV{'MITOOL'});
}

sub SetVar
{
    $mitool_bin_dir         = $ENV{'MITOOL'} . "/bin";
    $mitool_script_dir      = $ENV{'MITOOL'} . "/script";
}

sub PrintVar
{
    my $func_name = "mxkwpllib::PrintVar";

    printf("%s: mitool_bin_dir        = %s\n", $func_name, $mitool_bin_dir);
    printf("%s: mitool_script_dir   = %s\n", $func_name, $mitool_script_dir);
}


#
# init session variables
#
sub InitSeVar
{
    $sevar{'help'}        = 0;
    $sevar{'verbose'}     = 0;
    $sevar{'debug'}       = 0;
    $sevar{'outflag'}     = "overwrite"; # overwrite, skip, die
    $sevar{'procdir'}     = ".";         # relpath or fullpath
    $sevar{'progname'}    = "";
}

sub PrintSeVar
{
    my $prompt_sevar = "session_variable";
    printf("%s: help        = %s\n", $prompt_sevar, $sevar{'help'});
    printf("%s: verbose     = %s\n", $prompt_sevar, $sevar{'verbose'});
    printf("%s: debug       = %s\n", $prompt_sevar, $sevar{'debug'});
    printf("%s: outflag     = %s\n", $prompt_sevar, $sevar{'outflag'});
    printf("%s: procdir     = %s\n", $prompt_sevar, $sevar{'procdir'});
    printf("%s: progname    = %s\n", $prompt_sevar, $sevar{'progname'});
}

1;
