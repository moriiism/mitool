#include "arg_split_by_gti.h"

int ArgValSplitByGti::Init(int argc, char* argv[])
{
    int status = kRetNormal;
    progname_ = "split_by_gti";
    
    option long_options[] = {
        {"debug",      no_argument,       NULL, 'd'},
        {"help",       no_argument,       NULL, 'h'},
        {"verbose",    no_argument,       NULL, 'v'},
        {0, 0, 0, 0}
    };

    SetOptionBase(argc, argv, long_options);
    optind = 0;
    SetOption(argc, argv, long_options);

    printf("ArgValSplitByGti::Init: # of arg = %d\n", argc - optind);
    int narg = 9;
    if (argc - optind != narg){
        printf("# of arguments must be %d.\n", narg);
        Usage(stdout);
    }
    int iarg = optind;
    lc_file_           = argv[iarg];       iarg++;
    lc_telescope_      = argv[iarg];       iarg++;
    lc_tunit_          = argv[iarg];       iarg++;
    lc_format_         = argv[iarg];       iarg++;
    gti_file_          = argv[iarg];       iarg++;
    gti_telescope_     = argv[iarg];       iarg++;
    gti_tunit_         = argv[iarg];       iarg++;
    outdir_         = argv[iarg];       iarg++;
    outfile_head_   = argv[iarg];       iarg++;
    return status;
}


void ArgValSplitByGti::SetOption(int argc, char* argv[], option* long_options)
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


int ArgValSplitByGti::Print(FILE* fp) const
{
    int status = kRetNormal;
    fprintf(fp, "input par> lc_file_        : %s\n", lc_file_.c_str());
    fprintf(fp, "input par> lc_telescope_   : %s\n", lc_telescope_.c_str());
    fprintf(fp, "input par> lc_tunit_       : %s\n", lc_tunit_.c_str());
    fprintf(fp, "input par> lc_format_      : %s\n", lc_format_.c_str());
    fprintf(fp, "input par> gti_file_       : %s\n", gti_file_.c_str());
    fprintf(fp, "input par> gti_telescope_  : %s\n", gti_telescope_.c_str());
    fprintf(fp, "input par> gti_tunit_      : %s\n", gti_tunit_.c_str());
    fprintf(fp, "input par> outdir_         : %s\n", outdir_.c_str());
    fprintf(fp, "input par> outfile_head_   : %s\n", outfile_head_.c_str());
    return status;
}


void ArgValSplitByGti::Usage(FILE* fp) const
{
    fprintf(fp,
            "usage: %s [--help] [--verbose] [--debug] "
            "lc_file  lc_telescope  lc_tunit  lc_format  "
            "gti_file  gti_telescope  gti_tunit  "
            "outdir  outfile_head",
            progname_.c_str());
    abort();
}

