#!/usr/bin/perl

#
# util lib
#

use strict;
use warnings;
use POSIX;
use File::Spec;
use File::Temp;
use File::Basename;
no warnings qw(once);


sub GetParPointsFromBinningInfo
{
    if(1 != $#_){
        die;
    }
    my($binning_info, $par_arr_ref) = @_;

    my $nbin = 0;
    my $lo = 0.0;
    my $up = 0.0;
    my $linlog = "";
    &GetBinningInfo($binning_info,
		    \$nbin, \$lo, \$up, \$linlog);
    my @par_arr = ();
    &GetParPoints($nbin, $lo, $up, $linlog, \@par_arr);

    @$par_arr_ref = @par_arr;
}

sub GetBinningInfo
{
    if(4 != $#_){
        die;
    }
    my($binning_info,
       $nbin_ref, $lo_ref, $up_ref, $linlog_ref) = @_;

    my $nbin = 0;
    my $lo = 0.0;
    my $up = 0.0;
    my $linlog = "";
    open(BIN_INFO, "<$binning_info") or die;
    while(my $line = <BIN_INFO>){
        chomp($line);
        if($line =~ /^\s*$/ or $line =~ /^\s*\#/ or $line =~ /^\s*\!/) {
            next;
        }
        ($nbin, $lo, $up, $linlog) = split(' ', $line);
    }
    close(BIN_INFO);

    $$nbin_ref = $nbin;
    $$lo_ref = $lo;
    $$up_ref = $up;
    $$linlog_ref = $linlog;
}

sub GetParPoints
{
    if(4 != $#_){
        die;
    }
    my($nbin, $lo, $up, $linlog, $par_arr_ref) = @_;

    my @par_arr = ();
    for(my $ibin = 0; $ibin < $nbin; $ibin ++){
        $par_arr[$ibin] = 0.0;
        if("lin" eq $linlog){
            my $delta_par = ($up - $lo) / $nbin;
            $par_arr[$ibin] = $lo + $delta_par * ($ibin + 0.5);
        } elsif("log" eq $linlog){
            my $delta_log_par = &POSIX::log10($up / $lo) / $nbin;
            my $log_lo = &POSIX::log10($lo);
            my $log_par = $log_lo + $delta_log_par * ($ibin + 0.5);
            $par_arr[$ibin] = &POSIX::pow(10, $log_par);
        } else {
            die;
        }
    }
    @$par_arr_ref = @par_arr;
}


sub GetLatexNumStr
{
    my $func_name = "mipllib:GetLatexNumStr";
    printf("%s start ...\n", $func_name) if $mipllib::sevar{'verbose'};

    # ndigit: the number of digits after the decimal point
    my($num, $ndigit);
    if(0 > $#_){
	printf("%s: error.\n", $func_name);
	die;
    } elsif(0 == $#_){
	($num) = @_;
	$ndigit = 2;
    } elsif(1 == $#_){
	($num, $ndigit) = @_;
    } else {
	printf("%s: error.\n", $func_name);
	die;
    }
    my $format1 = sprintf("%%\.%de", $ndigit);
    my $num_str_tmp = sprintf($format1, $num);
    my($num_val1, $num_val2) = split("e", $num_str_tmp);
    my $format2 = sprintf("\$%%\.%df \\times 10^\{%%\.0f\}\$",
			  $ndigit);
    my $num_str = sprintf($format2, $num_val1, $num_val2);

    return $num_str;
}


sub GetLatexNumOrderStr
{
    my $func_name = "mipllib:GetLatexNumOrderStr";
    printf("%s start ...\n", $func_name) if $mipllib::sevar{'verbose'};

    # ndigit: the number of digits after the decimal point
    my($num, $order, $ndigit);
    if(1 > $#_){
	printf("%s: error.\n", $func_name);
	die;
    } elsif(1 == $#_){
	($num, $order) = @_;
	$ndigit = 2;
    } elsif(2 == $#_){
	($num, $order, $ndigit) = @_;
    } else {
	printf("%s: error.\n", $func_name);
	die;
    }

    my $num_norm = $num / 10**$order;
    my $format1 = sprintf("%%\.%df", $ndigit);
    my $num_str_tmp = sprintf($format1, $num_norm);
    my $format2 = sprintf("\$%%s \\times 10^\{%%\.0f\}\$",
			  $ndigit);
    my $num_str = sprintf($format2, $num_str_tmp, $order);

    return $num_str;
}




sub GetBasenameWithoutExt
{
    my $func_name = "mipllib:GetBasenameWithoutExt";
    printf("%s start ...\n", $func_name) if $mipllib::sevar{'verbose'};
    if(0 != $#_){
	printf("%s: error.\n", $func_name);
	die;
    }
    my($file) = @_;
    my $file_base = basename($file);
    my $file_head = substr($file_base, 0, rindex($file_base, "."));
    printf("%s end.\n", $func_name) if $mipllib::sevar{'verbose'};
    return $file_head;
}


# Get basename without last string
sub GetBasenameWithoutLastStr
{
    my $func_name = "mipllib:GetBasenameWithoutLastStr";
    printf("%s start ...\n", $func_name) if $mipllib::sevar{'verbose'};
    if(1 != $#_){
	printf("%s: error.\n", $func_name);
	die;
    }
    my($file, $last_str) = @_;
    my $file_base = basename($file);
    my $file_head = substr($file_base, 0, rindex($file_base, $last_str));
    printf("%s end.\n", $func_name) if $mipllib::sevar{'verbose'};
    return $file_head;
}


sub IsFullpath
{
    my $func_name = "mipllib:IsFullpath";
    printf("%s start ...\n", $func_name) if $mipllib::sevar{'verbose'};
    if(0 != $#_){
	printf("%s: error.\n", $func_name);
	die;
    }
    my($path) = @_;
    my $status = 0;
    if(substr($path, 0, 1) ne "/"){
	printf("%s: error: not full path (= %s).\n",
	       $func_name, $path);
	$status = 0;
    } else {
	$status = 1;
    }
    printf("%s end.\n", $func_name) if $mipllib::sevar{'verbose'};
    return $status;
}

sub GetNline
{
    my $func_name = "mipllib:GetNline";
    printf("%s start ...\n", $func_name) if $mipllib::sevar{'verbose'};
    if(0 != $#_){
	printf("%s: error.\n", $func_name);
	die;
    }
    my($file) = @_;
    my @tmp = split(' ', `wc $file`);
    my $nline = $tmp[0];
    printf("%s end.\n", $func_name) if $mipllib::sevar{'verbose'};
    return $nline;
}

sub GetNlineSkipComment
{
    my $func_name = "mipllib:GetNlineSkipComment";
    printf("%s start ...\n", $func_name) if $mipllib::sevar{'verbose'};
    if(0 != $#_){
	printf("%s: error.\n", $func_name);
	die;
    }
    my($file) = @_;

    my $nline = 0;
    open(IN, "<$file") or die;
    while(my $line = <IN>){
        chomp($line);
	if($line =~ /^\s*$/ or $line =~ /^\s*\#/ or $line =~ /^\s*\!/) {
            next;
        }
	$nline ++;
    }
    close(IN);
    printf("%s end.\n", $func_name) if $mipllib::sevar{'verbose'};
    return $nline;
}

sub DelNullFile
{
    my $func_name = "mipllib:DelNullFile";
    printf("%s start ...\n", $func_name) if $mipllib::sevar{'verbose'};
    if(0 != $#_){
	printf("%s: error.\n", $func_name);
	die;
    }
    my($file) = @_;
    my @tmp = split(' ', `wc $file`);
    my $nline = $tmp[0];
    if(0 == $nline){
	my $cmd = sprintf("rm %s", $file);
	printf("cmd = %s\n", $cmd);
	system($cmd);
    }
    printf("%s end.\n", $func_name) if $mipllib::sevar{'verbose'};
}

sub CheckOutflag
{
    my $func_name = "mipllib:CheckOutflag";
    printf("%s start ...\n", $func_name) if $mipllib::sevar{'verbose'};
    if(0 != $#_){
	printf("%s: error.\n", $func_name);
	die;
    }
    my($outfname) = @_;
    my $flag_skip = 0;

    # skip, if outfname exists.
    # overwrite, even if outfname exists.
    # die, if outfname exists.

    if(-e $outfname){
	if("skip" eq $mipllib::sevar{'outflag'}){
	    printf("%s: outfile already exists, then skip: %s\n", $func_name, $outfname);
	    $flag_skip = 1;
	} elsif ("overwrite" eq $mipllib::sevar{'outflag'}){
	    printf("%s: outfile will be overwritten: %s\n", $func_name, $outfname);
	    my $cmd = sprintf("rm %s", $outfname);
	    printf("cmd = %s\n", $cmd);
	    system($cmd);
	} elsif ("die" eq $mipllib::sevar{'outflag'}){
	    printf("%s: outfile already exists, then die: %s\n", $func_name, $outfname);
	    die;
	} else {
	    printf("bad outflag.\n");
	    exit;
	}
    }
    printf("%s end.\n", $func_name) if $mipllib::sevar{'verbose'};
    return $flag_skip;
}




sub MkDirlist
{
    # substitution of "ls -1 dir/* > list.txt"
    #
    # $dir    :  full-path or rel-path
    # $outlist:  full-path or rel-path, "none"
    # $regexp_arr_ref: reference of regexp_arr
    #                  Here, regexp_arr is array of regexp_arg.
    #
    #    regexp_arg must be "SEL=XXXXX" or "DEL=XXXXX".
    #    Here, "XXXXX" is a regular expression.
    #    "SEL" and "DEL" means selection and delete, respectively.
    #
    # $flag: "full-path", "rel-path", "no-path"

    my $func_name = "mipllib:MkDirlist";
    printf("%s start ...\n", $func_name) if $mipllib::sevar{'verbose'};
    if(3 != $#_){
	printf("%s: error.\n", $func_name);
	die;
    }
    my($dir, $outlist, $regexp_arr_ref, $flag) = @_;
    my $procdir_full = File::Spec->rel2abs($mipllib::sevar{'procdir'});
    my $dir_full     = File::Spec->rel2abs($dir, $procdir_full);

    my @regexp_arr = @$regexp_arr_ref;

    opendir(DIR, $dir_full) or die;
    my @file_list = readdir(DIR);
    closedir(DIR);
    my @file_list_sort = sort(@file_list);

    # remove "." & ".."
    my @file_list_sel = ();
    for(my $ifile = 0; $ifile <= $#file_list_sort; $ifile ++){
	my $file_base = basename($file_list_sort[$ifile]);
	if($file_base eq "."){
	    next;
	}
	if($file_base eq ".."){
	    next;
	}
	push(@file_list_sel, $file_list_sort[$ifile]);
    }
    for(my $iregexp = 0; $iregexp <= $#regexp_arr; $iregexp ++){
	printf("iregexp = %d: regexp = %s\n", $iregexp, $regexp_arr[$iregexp]) if $mipllib::sevar{'verbose'}; 
	my @file_list_sel_out_tmp = ();
	&sel_list_arr_by_regexp(\@file_list_sel, $regexp_arr[$iregexp], \@file_list_sel_out_tmp);
	printf("iregexp = %d: \# of sellist: %d\n", $iregexp, $#file_list_sel_out_tmp + 1) if $mipllib::sevar{'verbose'};
	@file_list_sel = @file_list_sel_out_tmp;
    }

    # output
    my @file_list_out = ();
    if("none" eq $outlist){
	if($flag eq "full-path"){
	    foreach my $file (@file_list_sel){
		chomp($file);
		my $file_out = sprintf("%s/%s", $dir_full, $file);
		push(@file_list_out, $file_out);
	    }
	} elsif($flag eq "rel-path"){
	    my $dir_rel = File::Spec->abs2rel($dir_full);
	    if($dir_rel eq ""){
		$dir_rel = ".";
	    }
	    foreach my $file (@file_list_sel){
		chomp($file);
		my $file_out = sprintf("%s/%s", $dir_rel, $file);
		push(@file_list_out, $file_out);
	    }
	} elsif($flag eq "no-path"){
	    foreach my $file (@file_list_sel){
		chomp($file);
		my $file_out = sprintf("%s", $file);
		push(@file_list_out, $file_out);
	    }
	} else {
	    printf("bad flag\n");
	    die;
	}
    } else {
	if($flag eq "full-path"){
	    open(OUTLIST, ">$outlist");
	    foreach my $file (@file_list_sel){
		chomp($file);
		my $file_out = sprintf("%s/%s", $dir_full, $file);
		push(@file_list_out, $file_out);
		printf(OUTLIST "%s\n", $file_out);
	    }
	    close(OUTLIST);
	} elsif($flag eq "rel-path"){
	    my $dir_rel = File::Spec->abs2rel($dir_full);
	    if($dir_rel eq ""){
		$dir_rel = ".";
	    }
	    open(OUTLIST, ">$outlist");
	    foreach my $file (@file_list_sel){
		chomp($file);
		my $file_out = sprintf("%s/%s", $dir_rel, $file);
		push(@file_list_out, $file_out);
		printf(OUTLIST "%s\n", $file_out);
	    }
	    close(OUTLIST);
	} elsif($flag eq "no-path"){
	    open(OUTLIST, ">$outlist");
	    foreach my $file (@file_list_sel){
		chomp($file);
		my $file_out = sprintf("%s", $file);
		push(@file_list_out, $file_out);
		printf(OUTLIST "%s\n", $file_out);
	    }
	    close(OUTLIST);
	} else {
	    printf("bad flag\n");
	    die;
	}
    }

    return @file_list_out;
}


sub sel_list_arr_by_regexp
{    
    # regexp_arg must be "SEL=XXXXX" or "DEL=XXXXX".
    # Here, "XXXXX" is regular expression.
    # "SEL" and "DEL" means selection and delete, respectively.

    my $func_name = "mipllib:sel_list_arr_by_regexp";
    if(2 != $#_){
	printf("%s: error.\n", $func_name);
	die;
    }
    my($list_arr_ref, $regexp_arg, $list_out_arr_ref) = @_;
    my @list_arr = @$list_arr_ref;
    my $sel_or_del = substr($regexp_arg, 0, 3);
    my $regexp     = substr($regexp_arg, 4);

    my @list_sel_arr = ();
    my @list_del_arr = ();
    foreach my $line (@list_arr){
        chomp($line);
	if($line =~ /$regexp/){
	    push(@list_sel_arr, $line);
	} else {
	    push(@list_del_arr, $line);
	}
    }

    if($sel_or_del eq "SEL"){
	@$list_out_arr_ref = @list_sel_arr;
    }elsif($sel_or_del eq "DEL"){
	@$list_out_arr_ref = @list_del_arr;
    }else{
	printf("mipllib.pl: sel_list_arr_by_regexp: bad sel_or_del flag: %s, then die.\n", $sel_or_del);
	die;
    }
}



sub StepEndCheck
{
    my $func_name = "mipllib:StepEndCheck";
    if(1 != $#_){
	printf("%s: error.\n", $func_name);
	die;
    }
    my($step_ed, $step_here) = @_;
    if($step_ed == $step_here){
	&mipllib::PfilesEnd();
	&mipllib::XselectEnd();
	exit;
    }
}


sub GetPlotLoUp{
    my($lo, $up, $lo_plot_ref, $up_plot_ref) = @_;
    my $width = $up - $lo;
    my $lo_plot = $lo - $width * 0.1;
    my $up_plot = $up + $width * 0.1;
    $$lo_plot_ref = $lo_plot;
    $$up_plot_ref = $up_plot;
}


sub get_func_name
{
    # by setting 1 as the argument of the caller function,
    # you can get the information of the calling function.
    my $this_func_name = (caller 1)[3];
    $this_func_name =~ s/.*:://;
    return $this_func_name; 
}




sub SleepIfMxfileBusy
{
    my $func_name = "mipllib::SleepIfMxfileBusy";
    while(-e $ENV{'MI_BUSY_FLAG'}){
	printf("%s: now mxfiles are updating. then sleep %d sec...\n",
	       $func_name, $mipllib::sleep_time);
	sleep($mipllib::sleep_time);
    }
}


sub ProcRunBegin
{
    my $cmd = "";
    if(! -e $mipllib::runfile_dir){
	$cmd = sprintf("mkdir %s", $mipllib::runfile_dir);
	printf("cmd = %s", $cmd);
	system($cmd);
    }
    $mipllib::seinvar{'runfile'} = sprintf("%s/%s_%s",
					     $mipllib::runfile_dir, $mipllib::sevar{'progname'},
					     &mipllib::GetTempStr("long"));
    $cmd = sprintf("touch %s", $mipllib::seinvar{'runfile'});
    printf("cmd = %s\n", $cmd);
    system($cmd);
}

sub IsProcRun
{
    if(-e $mipllib::seinvar{'runfile'}){
	return 1;
    } else {
	return 0;
    }
}

sub ProcRunEnd
{
    my $cmd = sprintf("rm %s", $mipllib::seinvar{'runfile'});
    printf("cmd = %s\n", $cmd);
    system($cmd);
}

sub IsInGtiMjd
{
    my $func_name = "mipllib:IsInGtiMjd";
    if(2 != $#_){
	printf("%s: error.\n", $func_name);
	die;
    }
    my($camid10, $mjd, $gti_mjd_list) = @_;

    my $flag_in = 0;
    if("none" eq $gti_mjd_list){
	$flag_in = 1;
	return $flag_in;
    } else {
	open(LIST, "<$gti_mjd_list") or die;
	while(my $line = <LIST>){
	    chomp($line);
	    if($line =~ /^\s*$/ or $line =~ /^\s*\#/ or $line =~ /^\s*\!/) {
		next;
	    }
	    my($camid_this, $mjd_st_str, $mjd_ed_str) = split(' ', $line);
	    my $mjd_st = 0.0;
	    my $mjd_ed = 0.0;
	    if("now" eq $mjd_ed_str){
		$mjd_ed = $mipllib::mxobs_mjd_ed;
	    } else {
		$mjd_ed = $mjd_ed_str;
	    }
	    $mjd_st = $mjd_st_str;
	    if($camid10 == $camid_this){
		if($mjd_st <= $mjd && $mjd <= $mjd_ed){
		    $flag_in = 1;
		}
	    }
	}
	close(LIST);
    }
    return $flag_in;
}

1;
