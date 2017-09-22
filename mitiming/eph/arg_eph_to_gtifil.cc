#include <iostream> 
using std::string;

#include "mxkw_par.h"
#include "mxkw_iolib.h"

#include "arg.h"

//
// GtiTconv
//

int ArgValGtiTconv::Init(int argc, char* argv[])
{
    int status = kRetNormal;
    progname_ = "gti_tconv";

    option long_options[] = {
        {"debug",      no_argument,       NULL, 'd'},
        {"help",       no_argument,       NULL, 'h'},
        {"verbose",    no_argument,       NULL, 'v'},
        {0, 0, 0, 0}
    };

    SetOptionBase(argc, argv, long_options);
    optind = 0;
    SetOption(argc, argv, long_options);

    printf("ArgValGtiTconv::Init: # of arg = %d\n", argc - optind);
    int narg = 6;
    if (argc - optind != narg){
        printf("# of arguments must be %d.\n", narg);
        Usage(stdout);
    }
    int iarg = optind;
    gti_in_        = argv[iarg];       iarg++;
    telescope_in_  = argv[iarg];       iarg++;
    tunit_in_      = argv[iarg];       iarg++;

    gti_out_       = argv[iarg];       iarg++;
    telescope_out_ = argv[iarg];       iarg++;
    tunit_out_     = argv[iarg];       iarg++;

    return status;
}



void ArgValGtiTconv::SetOption(int argc, char* argv[], option* long_options)
{
    while (1) {
        int option_index = 0;
        int retopt = getopt_long(argc, argv, "dhv",
                                 long_options, &option_index);
        // printf("%s: retopt = %d\n", long_options[option_index].name, retopt);
        
        if(-1 == retopt)
            break;
        switch (retopt) {
        case 0:
            // long option
            break;
        case 'd':
            break;
        case 'h':
            break;
        case 'v':
            break;
        case '?':
            // getopt_long already printed an error message.
            break;
        default:
            printf("?? getopt returned character code 0%o ??\n", retopt);
            abort();
        }
    }
}

int ArgValGtiTconv::Print(FILE* fp) const
{
    int status = kRetNormal;
    fprintf(fp, "input par> gti_in_        : %s\n", gti_in_.c_str());
    fprintf(fp, "input par> telescope_in_  : %s\n", telescope_in_.c_str());
    fprintf(fp, "input par> tunit_in_      : %s\n", tunit_in_.c_str());
    fprintf(fp, "input par> gti_out_       : %s\n", gti_out_.c_str());
    fprintf(fp, "input par> telescope_out_ : %s\n", telescope_out_.c_str());
    fprintf(fp, "input par> tunit_out_     : %s\n", tunit_out_.c_str());
    return status;
}

void ArgValGtiTconv::Usage(FILE* fp) const
{
    fprintf(fp,
            "usage: %s [--help] [--verbose] [--debug] "
            "gti_in  telescope_in  tunit_in  "
            "gti_out  telescope_out  tunit_out  \n",
            progname_.c_str());
    abort();
}

//
// GtiSplit
//

int ArgValGtiSplit::Init(int argc, char* argv[])
{
    int status = kRetNormal;
    progname_ = "gti_split";

    option long_options[] = {
        {"debug",      no_argument,       NULL, 'd'},
        {"help",       no_argument,       NULL, 'h'},
        {"verbose",    no_argument,       NULL, 'v'},
        {0, 0, 0, 0}
    };

    SetOptionBase(argc, argv, long_options);
    optind = 0;
    SetOption(argc, argv, long_options);

    printf("ArgValGtiTconv::Init: # of arg = %d\n", argc - optind);
    int narg = 6;
    if (argc - optind != narg){
        printf("# of arguments must be %d.\n", narg);
        Usage(stdout);
    }
    int iarg = optind;
    tstart_        = atof(argv[iarg]); iarg++;
    tstop_         = atof(argv[iarg]); iarg++;
    telescope_     = argv[iarg];       iarg++;
    tunit_         = argv[iarg];       iarg++;
    nsplit_        = atoi(argv[iarg]); iarg++;
    gti_out_       = argv[iarg];       iarg++;

    return status;
}



void ArgValGtiSplit::SetOption(int argc, char* argv[], option* long_options)
{
    while (1) {
        int option_index = 0;
        int retopt = getopt_long(argc, argv, "dhv",
                                 long_options, &option_index);
        // printf("%s: retopt = %d\n", long_options[option_index].name, retopt);
        
        if(-1 == retopt)
            break;
        switch (retopt) {
        case 0:
            // long option
            break;
        case 'd':
            break;
        case 'h':
            break;
        case 'v':
            break;
        case '?':
            // getopt_long already printed an error message.
            break;
        default:
            printf("?? getopt returned character code 0%o ??\n", retopt);
            abort();
        }
    }
}

int ArgValGtiSplit::Print(FILE* fp) const
{
    int status = kRetNormal;
    fprintf(fp, "input par> tstart_        : %e\n", tstart_);
    fprintf(fp, "input par> tstop_         : %e\n", tstop_);
    fprintf(fp, "input par> telescope_     : %s\n", telescope_.c_str());
    fprintf(fp, "input par> tunit_         : %s\n", tunit_.c_str());
    fprintf(fp, "input par> nsplit_        : %ld\n", nsplit_);
    fprintf(fp, "input par> gti_out_       : %s\n", gti_out_.c_str());
    return status;
}

void ArgValGtiSplit::Usage(FILE* fp) const
{
    fprintf(fp,
            "usage: %s [--help] [--verbose] [--debug] "
            "tstart  tstop  telescope  tunit  "
            "nsplit  gti_out  \n",
            progname_.c_str());
    abort();
}


//
// PlotGti
//

int ArgValPlotGti::Init(int argc, char* argv[])
{
    int status = kRetNormal;
    progname_ = "plot_gti";

    option long_options[] = {
        {"debug",      no_argument,       NULL, 'd'},
        {"help",       no_argument,       NULL, 'h'},
        {"verbose",    no_argument,       NULL, 'v'},
        {"plotmode",   required_argument, NULL, 0},
        {"printmode",  required_argument, NULL, 0},
        {"root_style", required_argument, NULL, 0},
        {0, 0, 0, 0}
    };

    // long option default
    plotmode_  = "on";
    printmode_ = "on";
    root_style_ = "def";

    SetOptionBase(argc, argv, long_options);
    optind = 0;
    SetOption(argc, argv, long_options);

    printf("ArgValPlotGti::Init: # of arg = %d\n", argc - optind);
    int narg = 6;
    if (argc - optind != narg){
        printf("# of arguments must be %d.\n", narg);
        Usage(stdout);
    }
    int iarg = optind;
    gti_file_     = argv[iarg];       iarg++;
    telescope_    = argv[iarg];       iarg++;
    tunit_        = argv[iarg];       iarg++;

    outdir_       = argv[iarg];       iarg++;
    outfile_head_ = argv[iarg];       iarg++;
    offset_tag_   = argv[iarg];       iarg++;

    return status;
}



void ArgValPlotGti::SetOption(int argc, char* argv[], option* long_options)
{
    while (1) {
        int option_index = 0;
        int retopt = getopt_long(argc, argv, "dhv",
                                 long_options, &option_index);
        // printf("%s: retopt = %d\n", long_options[option_index].name, retopt);
        
        if(-1 == retopt)
            break;
        switch (retopt) {
        case 0:
            // long option
            if("plotmode" == long_options[option_index].name){
                plotmode_  = optarg;
            } else if ("printmode" == long_options[option_index].name){
                printmode_ = optarg;
            } else if ("root_style" == long_options[option_index].name){
               root_style_ = optarg;
            }
            break;
        case 'd':
            break;
        case 'h':
            break;
        case 'v':
            break;
        case '?':
            // getopt_long already printed an error message.
            break;
        default:
            printf("?? getopt returned character code 0%o ??\n", retopt);
            abort();
        }
    }
}

int ArgValPlotGti::Print(FILE* fp) const
{
    int status = kRetNormal;
    fprintf(fp, "input par> gti_file_    : %s\n", gti_file_.c_str());
    fprintf(fp, "input par> telescope_   : %s\n", telescope_.c_str());
    fprintf(fp, "input par> tunit_       : %s\n", tunit_.c_str());
    fprintf(fp, "input par> outdir_      : %s\n", outdir_.c_str());
    fprintf(fp, "input par> outfile_head_: %s\n", outfile_head_.c_str());
    fprintf(fp, "input par> offset_tag_  : %s\n", offset_tag_.c_str());
    return status;
}

void ArgValPlotGti::Usage(FILE* fp) const
{
    fprintf(fp,
            "usage: %s [--help] [--verbose] [--debug] "
            "[--plotmode on/off] [--printmode on/off] [--root_style def/std/pub/detail] "
            "gti_file  telescope  tunit  "
            "outdir  outfile_head  offset_tag\n",
            progname_.c_str());
    abort();
}

//
// GtiRmGap
//

int ArgValGtiRmGap::Init(int argc, char* argv[])
{
    int status = kRetNormal;
    progname_ = "gti_rmgap";

    option long_options[] = {
        {"debug",      no_argument,       NULL, 'd'},
        {"help",       no_argument,       NULL, 'h'},
        {"verbose",    no_argument,       NULL, 'v'},
        {0, 0, 0, 0}
    };

    // long option default

    SetOptionBase(argc, argv, long_options);
    optind = 0;
    SetOption(argc, argv, long_options);

    printf("ArgValPlotGti::Init: # of arg = %d\n", argc - optind);
    int narg = 8;
    if (argc - optind != narg){
        printf("# of arguments must be %d.\n", narg);
        Usage(stdout);
    }
    int iarg = optind;
    gti_file_     = argv[iarg];       iarg++;
    telescope_    = argv[iarg];       iarg++;
    tunit_        = argv[iarg];       iarg++;

    time_gap_     = atof(argv[iarg]); iarg++;
    gtiout_       = argv[iarg];       iarg++;
    outdir_       = argv[iarg];       iarg++;
    outfile_head_ = argv[iarg];       iarg++;
    offset_tag_   = argv[iarg];       iarg++;

    return status;
}


void ArgValGtiRmGap::SetOption(int argc, char* argv[], option* long_options)
{
    while (1) {
        int option_index = 0;
        int retopt = getopt_long(argc, argv, "dhv",
                                 long_options, &option_index);
        // printf("%s: retopt = %d\n", long_options[option_index].name, retopt);
        
        if(-1 == retopt)
            break;
        switch (retopt) {
        case 0:
            // long option
            break;
        case 'd':
            break;
        case 'h':
            break;
        case 'v':
            break;
        case '?':
            // getopt_long already printed an error message.
            break;
        default:
            printf("?? getopt returned character code 0%o ??\n", retopt);
            abort();
        }
    }
}

int ArgValGtiRmGap::Print(FILE* fp) const
{
    int status = kRetNormal;
    fprintf(fp, "input par> gti_file_    : %s\n", gti_file_.c_str());
    fprintf(fp, "input par> telescope_   : %s\n", telescope_.c_str());
    fprintf(fp, "input par> tunit_       : %s\n", tunit_.c_str());

    fprintf(fp, "input par> time_gap_    : %e\n", time_gap_);
    fprintf(fp, "input par> gtiout_      : %s\n", gtiout_.c_str());
    
    fprintf(fp, "input par> outdir_      : %s\n", outdir_.c_str());
    fprintf(fp, "input par> outfile_head_: %s\n", outfile_head_.c_str());
    fprintf(fp, "input par> offset_tag_  : %s\n", offset_tag_.c_str());
    return status;
}

void ArgValGtiRmGap::Usage(FILE* fp) const
{
    fprintf(fp,
            "usage: %s [--help] [--verbose] [--debug] "
            "gti_file  telescope  tunit  "
            "time_gap  gtiout  "
            "outdir  outfile_head  offset_tag\n",
            progname_.c_str());
    abort();
}


//
// ArgValLcthr
//

int ArgValLcthr::Init(int argc, char* argv[])
{
    int status = kRetNormal;
    progname_ = "gti_lcthr";

    option long_options[] = {
        {"debug",      no_argument,       NULL, 'd'},
        {"help",       no_argument,       NULL, 'h'},
        {"verbose",    no_argument,       NULL, 'v'},
        {0, 0, 0, 0}
    };

    SetOptionBase(argc, argv, long_options);
    optind = 0;
    SetOption(argc, argv, long_options);

    printf("ArgValLcthr::Init: # of arg = %d\n", argc - optind);
    int narg = 7;
    if (argc - optind != narg){
        printf("# of arguments must be %d.\n", narg);
        Usage(stdout);
    }
    int iarg = optind;
    file_         = argv[iarg];       iarg++; // file
    format_       = argv[iarg];       iarg++;
    threshold_    = atof(argv[iarg]); iarg++;
    gtiout_       = argv[iarg];       iarg++;
    outdir_       = argv[iarg];       iarg++;
    outfile_head_ = argv[iarg];       iarg++;
    offset_tag_   = argv[iarg];       iarg++;

    return status;
}


void ArgValLcthr::SetOption(int argc, char* argv[], option* long_options)
{
    while (1) {
        int option_index = 0;
        int retopt = getopt_long(argc, argv, "dhv",
                                 long_options, &option_index);
        // printf("%s: retopt = %d\n", long_options[option_index].name, retopt);
        
        if(-1 == retopt)
            break;
        switch (retopt) {
        case 0:
            // long option
            break;
        case 'd':
            break;
        case 'h':
            break;
        case 'v':
            break;
        case '?':
            // getopt_long already printed an error message.
            break;
        default:
            printf("?? getopt returned character code 0%o ??\n", retopt);
            abort();
        }
    }
}


int ArgValLcthr::Print(FILE* fp) const
{
    int status = kRetNormal;
    fprintf(fp, "ArgValLcthr::Print(): progname_    : %s\n", progname_.c_str());
    fprintf(fp, "ArgValLcthr::Print(): file_        : %s\n", file_.c_str());
    fprintf(fp, "ArgValLcthr::Print(): format_      : %s\n", format_.c_str());
    fprintf(fp, "ArgValLcthr::Print(): threshold_   : %f\n", threshold_);
    fprintf(fp, "ArgValLcthr::Print(): gtiout_      : %s\n", gtiout_.c_str());
    fprintf(fp, "ArgValLcthr::Print(): outdir_      : %s\n", outdir_.c_str());
    fprintf(fp, "ArgValLcthr::Print(): outfile_head_: %s\n", outfile_head_.c_str());
    fprintf(fp, "ArgValLcthr::Print(): offset_tag_  : %s\n", offset_tag_.c_str());
    return status;
}

void ArgValLcthr::Usage(FILE* fp) const
{
    fprintf(fp,
            "usage: %s [--help] [--verbose] [--debug] "
            "file  format  threshold  "
            "gtiout  outdir  outfile_head  offset_tag \n",
            progname_.c_str());
    abort();
}

//
// ArgValLcthrHist
//

int ArgValLcthrHist::Init(int argc, char* argv[])
{
    int status = kRetNormal;
    progname_ = "gti_lcthr_hist";

    option long_options[] = {
        {"debug",      no_argument,       NULL, 'd'},
        {"help",       no_argument,       NULL, 'h'},
        {"verbose",    no_argument,       NULL, 'v'},
        {0, 0, 0, 0}
    };

    SetOptionBase(argc, argv, long_options);
    optind = 0;
    SetOption(argc, argv, long_options);

    printf("ArgValLcthrHist::Init: # of arg = %d\n", argc - optind);
    int narg = 10;
    if (argc - optind != narg){
        printf("# of arguments must be %d.\n", narg);
        Usage(stdout);
    }
    int iarg = optind;
    file_         = argv[iarg];       iarg++; // file
    format_       = argv[iarg];       iarg++;
    threshold_    = atof(argv[iarg]); iarg++;
    nbin_time_    = atoi(argv[iarg]); iarg++;
    time_lo_      = atof(argv[iarg]); iarg++;
    time_up_      = atof(argv[iarg]); iarg++;
    gtiout_       = argv[iarg];       iarg++;
    outdir_       = argv[iarg];       iarg++;
    outfile_head_ = argv[iarg];       iarg++;
    offset_tag_   = argv[iarg];       iarg++;

    return status;
}


void ArgValLcthrHist::SetOption(int argc, char* argv[], option* long_options)
{
    while (1) {
        int option_index = 0;
        int retopt = getopt_long(argc, argv, "dhv",
                                 long_options, &option_index);
        // printf("%s: retopt = %d\n", long_options[option_index].name, retopt);
        
        if(-1 == retopt)
            break;
        switch (retopt) {
        case 0:
            // long option
            break;
        case 'd':
            break;
        case 'h':
            break;
        case 'v':
            break;
        case '?':
            // getopt_long already printed an error message.
            break;
        default:
            printf("?? getopt returned character code 0%o ??\n", retopt);
            abort();
        }
    }
}


int ArgValLcthrHist::Print(FILE* fp) const
{
    int status = kRetNormal;
    fprintf(fp, " progname_    : %s\n", progname_.c_str());
    fprintf(fp, " file_        : %s\n", file_.c_str());
    fprintf(fp, " format_      : %s\n", format_.c_str());
    fprintf(fp, " threshold_   : %e\n", threshold_);
    fprintf(fp, " nbin_time_   : %ld\n", nbin_time_);
    fprintf(fp, " time_lo_     : %e\n", time_lo_);
    fprintf(fp, " time_up_     : %e\n", time_up_);
    fprintf(fp, " gtiout_      : %s\n", gtiout_.c_str());
    fprintf(fp, " outdir_      : %s\n", outdir_.c_str());
    fprintf(fp, " outfile_head_: %s\n", outfile_head_.c_str());
    fprintf(fp, " offset_tag_  : %s\n", offset_tag_.c_str());
    return status;
}

void ArgValLcthrHist::Usage(FILE* fp) const
{
    fprintf(fp,
            "usage: %s [--help] [--verbose] [--debug] "
            "file  format  threshold  "
            "nbin_time  time_lo  time_up  "
            "gtiout  outdir  outfile_head  offset_tag \n",
            progname_.c_str());
    abort();
}



//
// ArgValAndOrN
//

int ArgValAndOrN::Init(int argc, char* argv[])
{
    int status = kRetNormal;
    progname_ = "gti_andorn";
    
    option long_options[] = {
        {"debug",      no_argument,       NULL, 'd'},
        {"help",       no_argument,       NULL, 'h'},
        {"verbose",    no_argument,       NULL, 'v'},
        {0, 0, 0, 0}
    };

    // long option default

    SetOptionBase(argc, argv, long_options);
    optind = 0;
    SetOption(argc, argv, long_options);

    printf("ArgValAndOrN::Init: # of arg = %d\n", argc - optind);
    int narg = 7;
    if (argc - optind != narg){
        printf("# of arguments must be %d.\n", narg);
        Usage(stdout);
    }
    int iarg = optind;
    andor_         = argv[iarg];       iarg++; // "and" or "or"
    gti_file_list_ = argv[iarg];       iarg++;
    telescope_     = argv[iarg];       iarg++; // telescope or MJD
    tunit_         = argv[iarg];       iarg++; // tunit: "sec" or "day"
    outdir_        = argv[iarg];       iarg++;
    outfile_head_  = argv[iarg];       iarg++;
    offset_tag_    = argv[iarg];       iarg++;

    return status;
}


void ArgValAndOrN::SetOption(int argc, char* argv[], option* long_options)
{
    while (1) {
        int option_index = 0;
        int retopt = getopt_long(argc, argv, "dhv",
                                 long_options, &option_index);
        // printf("%s: retopt = %d\n", long_options[option_index].name, retopt);
        
        if(-1 == retopt)
            break;
        switch (retopt) {
        case 0:
            // long option
            break;
        case 'd':
            break;
        case 'h':
            break;
        case 'v':
            break;
        case '?':
            // getopt_long already printed an error message.
            break;
        default:
            printf("?? getopt returned character code 0%o ??\n", retopt);
            abort();
        }
    }
}


int ArgValAndOrN::Print(FILE* fp) const
{
    int status = kRetNormal;
    fprintf(fp, "ArgValAndOrN::Print(): progname_    : %s\n", progname_.c_str());
    fprintf(fp, "ArgValAndOrN::Print(): andor_       : %s\n", andor_.c_str());
    fprintf(fp, "ArgValAndOrN::Print(): gti_file_list_ : %s\n", gti_file_list_.c_str());
    fprintf(fp, "ArgValAndOrN::Print(): telescope_   : %s\n", telescope_.c_str());
    fprintf(fp, "ArgValAndOrN::Print(): tunit_       : %s\n", tunit_.c_str());
    fprintf(fp, "ArgValAndOrN::Print(): outdir_      : %s\n", outdir_.c_str());
    fprintf(fp, "ArgValAndOrN::Print(): outfile_head_: %s\n", outfile_head_.c_str());
    fprintf(fp, "ArgValAndOrN::Print(): offset_tag_  : %s\n", offset_tag_.c_str());
    return status;
}


void ArgValAndOrN::Usage(FILE* fp) const
{
    fprintf(fp,
            "usage: %s [--help] [--verbose] [--debug] "
            "andor  gti_file_list  "
            "telescope  tunit  "
            "outdir  outfile_head  offset_tag\n",
            progname_.c_str());
    abort();
}

//
// ArgValAndOr2
//

int ArgValAndOr2::Init(int argc, char* argv[])
{
    int status = kRetNormal;
    progname_ = "gti_andor2";
    
    option long_options[] = {
        {"debug",      no_argument,       NULL, 'd'},
        {"help",       no_argument,       NULL, 'h'},
        {"verbose",    no_argument,       NULL, 'v'},
        {0, 0, 0, 0}
    };

    // long option default

    SetOptionBase(argc, argv, long_options);
    optind = 0;
    SetOption(argc, argv, long_options);
   
    printf("ArgValAndOr2::Init: # of arg = %d\n", argc - optind);
    int narg = 8;
    if (argc - optind != narg){
        printf("# of arguments must be %d.\n", narg);
        Usage(stdout);
    }
    int iarg = optind;
    andor_         = argv[iarg];       iarg++; // "and" or "or"
    gti1_          = argv[iarg];       iarg++;
    gti2_          = argv[iarg];       iarg++;
    telescope_     = argv[iarg];       iarg++; // telescope or MJD
    tunit_         = argv[iarg];       iarg++; // tunit: "sec" or "day"
    outdir_        = argv[iarg];       iarg++;
    outfile_head_  = argv[iarg];       iarg++;
    offset_tag_    = argv[iarg];       iarg++;

    return status;
}

void ArgValAndOr2::SetOption(int argc, char* argv[], option* long_options)
{
    while (1) {
        int option_index = 0;
        int retopt = getopt_long(argc, argv, "dhv",
                                 long_options, &option_index);
        // printf("%s: retopt = %d\n", long_options[option_index].name, retopt);
        
        if(-1 == retopt)
            break;
        switch (retopt) {
        case 0:
            // long option
            break;
        case 'd':
            break;
        case 'h':
            break;
        case 'v':
            break;
        case '?':
            // getopt_long already printed an error message.
            break;
        default:
            printf("?? getopt returned character code 0%o ??\n", retopt);
            abort();
        }
    }
}


int ArgValAndOr2::Print(FILE* fp) const
{
    int status = kRetNormal;
    fprintf(fp, "ArgValAndOr2::Print(): progname_    : %s\n", progname_.c_str());
    fprintf(fp, "ArgValAndOr2::Print(): andor_       : %s\n", andor_.c_str());
    fprintf(fp, "ArgValAndOr2::Print(): gti1_        : %s\n", gti1_.c_str());
    fprintf(fp, "ArgValAndOr2::Print(): gti2_        : %s\n", gti2_.c_str());
    fprintf(fp, "ArgValAndOr2::Print(): telescope_   : %s\n", telescope_.c_str());
    fprintf(fp, "ArgValAndOr2::Print(): tunit_       : %s\n", tunit_.c_str());
    fprintf(fp, "ArgValAndOr2::Print(): outdir_      : %s\n", outdir_.c_str());
    fprintf(fp, "ArgValAndOr2::Print(): outfile_head_: %s\n", outfile_head_.c_str());
    fprintf(fp, "ArgValAndOr2::Print(): offset_tag_  : %s\n", offset_tag_.c_str());
    return status;
}


void ArgValAndOr2::Usage(FILE* fp) const
{
    fprintf(fp,
            "usage: %s [--help] [--verbose] [--debug] "
            "andor  gti1  gti2  "
            "telescope  tunit  "
            "outdir  outfile_head  offset_tag\n",
            progname_.c_str());
    abort();
}


/////////////////////




//
//
//
//// --
//
//int ArgValMergin::Init(int argc, char *argv[]){
//    int status = kRetNormal;
//    printf("ArgValMergin::Init: # of arg (begin) = %d\n", argc - 1);
//    progname_ = "gti_mergin";
//  
//    int narg = 8;
//    if (argc != narg + 1){
//        printf("# of arguments must be %d.\n", narg);
//        exit(1);
//    }
//  
//    int iarg = 1;
//    gti_file_      = argv[iarg];       iarg++;
//    telescope_     = argv[iarg];       iarg++; // telescope or MJD
//    tunit_         = argv[iarg];       iarg++; // tunit: "sec" or "day"
//    time_mergin_   = atof(argv[iarg]); iarg++;
//    gtiout_        = argv[iarg];       iarg++;
//    outdir_        = argv[iarg];       iarg++;
//    outfile_head_  = argv[iarg];       iarg++;
//    offset_tag_    = argv[iarg];       iarg++;
//  
//    printf("ArgValMergin::Init: # of arg (last) = %d\n", iarg - 1);
//    return status;
//}
//
//int ArgValMergin::Print(FILE* fp) const
//{
//    int status = kRetNormal;
//    fprintf(fp, "ArgValMergin::Print(): progname_    : %s\n", progname_.c_str());
//    fprintf(fp, "ArgValMergin::Print(): gti_file_    : %s\n", gti_file_.c_str());
//    fprintf(fp, "ArgValMergin::Print(): telescope_   : %s\n", telescope_.c_str());
//    fprintf(fp, "ArgValMergin::Print(): tunit_       : %s\n", tunit_.c_str());
//    fprintf(fp, "ArgValMergin::Print(): time_mergin_ : %f\n", time_mergin_);
//    fprintf(fp, "ArgValMergin::Print(): gtiout_      : %s\n", gtiout_.c_str());
//    fprintf(fp, "ArgValMergin::Print(): outdir_      : %s\n", outdir_.c_str());
//    fprintf(fp, "ArgValMergin::Print(): outfile_head_: %s\n", outfile_head_.c_str());
//    fprintf(fp, "ArgValMergin::Print(): offset_tag_  : %s\n", offset_tag_.c_str());
//    return status;
//}
//
//
//// ---
//
//int ArgValEph::Init(int argc, char *argv[]){
//    int status = kRetNormal;
//    printf("ArgValEph::Init: # of arg (begin) = %d\n", argc - 1);
//    progname_ = "eph2gtifil";
//  
//    int narg = 8;
//    if (argc != narg + 1){
//        printf("# of arguments must be %d.\n", narg);
//        exit(1);
//    }
//
//    int iarg = 1;
//    ephfile_      = argv[iarg];       iarg++; // ephemeris file
//    phase_gti_    = argv[iarg];       iarg++; // phase_gti file
//    telescope_    = argv[iarg];       iarg++; // telescope or MJD
//    time_mjd_st_  = atof(argv[iarg]); iarg++; 
//    time_mjd_ed_  = atof(argv[iarg]); iarg++; 
//    outfile_head_ = argv[iarg];       iarg++;
//    outdir_       = argv[iarg];       iarg++;
//    offset_tag_   = argv[iarg];       iarg++;
//
//    printf("ArgValEph::Init: # of arg (last) = %d\n", iarg - 1);
//    return status;
//}
//
//int ArgValEph::Print(FILE* fp) const
//{
//    int status = kRetNormal;
//    fprintf(fp, "ArgValEph::Print(): progname_    : %s\n", progname_.c_str());
//    fprintf(fp, "ArgValEph::Print(): ephfile_     : %s\n", ephfile_.c_str());
//    fprintf(fp, "ArgValEph::Print(): phase_gti_   : %s\n", phase_gti_.c_str());  
//    fprintf(fp, "ArgValEph::Print(): telescope_   : %s\n", telescope_.c_str());
//    fprintf(fp, "ArgValEph::Print(): time_mjd_st_ : %f\n", time_mjd_st_);
//    fprintf(fp, "ArgValEph::Print(): time_mjd_ed_ : %f\n", time_mjd_ed_);
//    fprintf(fp, "ArgValEph::Print(): outfile_head_: %s\n", outfile_head_.c_str());
//    fprintf(fp, "ArgValEph::Print(): outdir_      : %s\n", outdir_.c_str());
//    fprintf(fp, "ArgValEph::Print(): offset_tag_  : %s\n", offset_tag_.c_str());
//    return status;
//}
//

