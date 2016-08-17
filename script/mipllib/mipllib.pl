#!/usr/bin/perl

# For example, you can load this script by
# $mipllib_dir = "/opt/mitool/pro/script/mipllib";
# require("$mipllib_dir/mipllib.pl");

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

package mipllib;

my $varlib    = sprintf("%s/script/mipllib/varlib.pl", $ENV{'MITOOL'});
my $templib   = sprintf("%s/script/mipllib/templib.pl", $ENV{'MITOOL'});
my $utillib   = sprintf("%s/script/mipllib/utillib.pl", $ENV{'MITOOL'});

require($varlib);
require($templib);
require($utillib);

1;
