#include "arg_binrate2bincount.h"

void ArgValBinRate2BinCount::Init(int argc, char* argv[])
{
    progname_ = "binrate2bincount";
    
    option long_options[] = {
        {"debug",      no_argument,       NULL, 'd'},
        {"help",       no_argument,       NULL, 'h'},
        {"verbose",    no_argument,       NULL, 'v'},
        {0, 0, 0, 0}
    };

    SetOptionBase(argc, argv, long_options);
    optind = 0;
    SetOption(argc, argv, long_options);

    printf("ArgValBinRate2BinCount::Init: # of arg = %d\n", argc - optind);
    int narg = 7;
    if (argc - optind != narg){
        printf("# of arguments must be %d.\n", narg);
        Usage(stdout);
    }
    int iarg = optind;
    telescope_    = argv[iarg];       iarg++;
    lc_file_      = argv[iarg];       iarg++;
    lc_tunit_     = argv[iarg];       iarg++;
    lc_format_    = argv[iarg];       iarg++;
    tbinfwidth_str_ = argv[iarg];       iarg++;

    outdir_        = argv[iarg];       iarg++;
    outfile_head_  = argv[iarg];       iarg++;
}


void ArgValBinRate2BinCount::SetOption(int argc, char* argv[], option* long_options)
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


void ArgValBinRate2BinCount::Print(FILE* fp) const
{
    fprintf(fp, "input par> telescope_   : %s\n", telescope_.c_str());
    fprintf(fp, "input par> lc_file_     : %s\n", lc_file_.c_str());
    fprintf(fp, "input par> lc_tunit_    : %s\n", lc_tunit_.c_str());
    fprintf(fp, "input par> lc_format_   : %s\n", lc_format_.c_str());
    fprintf(fp, "input par> tbinfwidth_str_ : %s\n", tbinfwidth_str_.c_str());

    fprintf(fp, "input par> outdir_        : %s\n", outdir_.c_str());
    fprintf(fp, "input par> outfile_head_  : %s\n", outfile_head_.c_str());
}


void ArgValBinRate2BinCount::Usage(FILE* fp) const
{
    fprintf(fp,
            "usage: %s [--help] [--verbose] [--debug] "
            "telescope  lc_file  lc_tunit  lc_format  tbinfwidth_str  "
            "outdir  outfile_head\n",
            progname_.c_str());
    abort();
}

