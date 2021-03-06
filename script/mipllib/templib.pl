#!/usr/bin/perl

#
# temporary lib
#

use strict;
use warnings;
use POSIX;
use File::Spec;
use File::Temp;
use File::Basename;
no warnings qw(once);

$ENV{'LANG'} = "C";

#
# make temporary unique string 
#
# $$: process ID
# max of pid is shown in /proc/sys/kernel/pid_max
#

sub GetTempStr
{
    my $func_name = "mipllib:GetTempStr";
    if(0 != $#_){
	printf("%s: error.\n", $func_name);
	die;
    }
    my ($mode) = @_; # "long", "short"

    my $tmp_str = "";
    if("long" eq $mode){
	my ($sec,$min,$hour,$mday,$mon,$year,$wday,$yday,$isdst) = localtime(time);
	$year += 1900;
	$mon += 1;
	my $date = sprintf("%4.4d%2.2d%2.2d-%2.2d%2.2d%2.2d",
			   $year, $mon, $mday, $hour, $min, $sec);
	$tmp_str = mktemp(sprintf("%s_p%5.5d_%s.XXXXXX", $date, $$, $ENV{'USER'}));
	$tmp_str =~ s/\./_/g;
    } elsif ("short" eq $mode){
	$tmp_str = mktemp(sprintf("p%5.5d.XXXXXX", $$));
	$tmp_str =~ s/\./_/g;
    } else {
	printf("bad mode\n");
	die;
    }
    return $tmp_str;
}


#
# make temporary file
#

#
# MkTempFile: 
#     make a temporary file in a temporary directory in your home (or /tmp) directory
# RmTempFile: 
#     remove the temporary file and the temporary directory
# These two function must be used in pair.
# 
#
# for xselect, suffix is necessary.
#

sub MkTempFile
{
    my $func_name = "mipllib:MkTempFile";
    if(2 != $#_){
	printf("%s: error.\n", $func_name);
	die;
    }
    my ($temp_dir_head, $temp_file_head, $suffix) = @_;

    my $temp_dir_full = sprintf("%s/%s_%s",
				$ENV{'MI_TMPDIR'}, $temp_dir_head,
				&mipllib::GetTempStr("short"));
    my $cmd = sprintf("/bin/mkdir -p %s", $temp_dir_full);
    printf("%s: cmd = %s\n", $func_name, $cmd) if $mipllib::sevar{'verbose'};
    system($cmd);
    my $temp_file_full = sprintf("%s/%s_%s.%s",
				 $temp_dir_full, $temp_file_head,
				 &mipllib::GetTempStr("short"), $suffix);
    return $temp_file_full;
}

sub RmTempFile
{
    my $func_name = "mipllib:RmTempFile";
    if(0 != $#_){
	printf("%s: error.\n", $func_name);
	die;
    }
    my ($temp_file) = @_; # rel-path or full-path
    my $procdir_full   = File::Spec->rel2abs($mipllib::sevar{'procdir'});
    my $temp_file_full = File::Spec->rel2abs($temp_file, $procdir_full);

    my $cmd = sprintf("/bin/rm %s", $temp_file_full);
    printf("%s: cmd = %s\n", $func_name, $cmd) if $mipllib::sevar{'verbose'};
    system($cmd);

    my $dirname = dirname($temp_file_full);
    $cmd = sprintf("/bin/rmdir %s", $dirname);
    printf("%s: cmd = %s\n", $func_name, $cmd) if $mipllib::sevar{'verbose'};
    system($cmd);
}

#
# make temporary directory
#

sub MkTempDir
{
    my $func_name = "mipllib:MkTempDir";
    if(0 != $#_){
	printf("%s: error.\n", $func_name);
	die;
    }
    my ($temp_dir_head) = @_;
    my $temp_dir_full = sprintf("%s/%s_%s",
				$ENV{'MI_TMPDIR'}, $temp_dir_head,
				&mipllib::GetTempStr("short"));
    my $cmd = sprintf("/bin/mkdir -p %s", $temp_dir_full);
    printf("%s: cmd = %s\n", $func_name, $cmd) if $mipllib::sevar{'verbose'};
    system($cmd);
    return $temp_dir_full;
}

sub RmTempDir
{
    my $func_name = "mipllib:RmTempDir";
    if(0 != $#_){
	printf("%s: error.\n", $func_name);
	die;
    }
    my ($temp_dir) = @_; # rel-path or full-path
    my $procdir_full   = File::Spec->rel2abs($mipllib::sevar{'procdir'});
    my $temp_dir_full  = File::Spec->rel2abs($temp_dir, $procdir_full);

    my $cmd = sprintf("/bin/rm -R %s", $temp_dir_full);
    printf("%s: cmd = %s\n", $func_name, $cmd) if $mipllib::sevar{'verbose'};
    system($cmd);
}

1;
