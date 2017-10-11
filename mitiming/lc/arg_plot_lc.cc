#include "arg_plot_lc.h"

int ArgValPlotLc::Init(int argc, char* argv[])
{
    int status = kRetNormal;
    progname_ = "plot_lc";
    
    option long_options[] = {
        {"debug",      no_argument,       NULL, 'd'},
        {"help",       no_argument,       NULL, 'h'},
        {"verbose",    no_argument,       NULL, 'v'},
        {0, 0, 0, 0}
    };

    SetOptionBase(argc, argv, long_options);
    optind = 0;
    SetOption(argc, argv, long_options);

    printf("ArgValPlotLc::Init: # of arg = %d\n", argc - optind);
    int narg = 7;
    if (argc - optind != narg){
        printf("# of arguments must be %d.\n", narg);
        Usage(stdout);
    }
    int iarg = optind;
    file_           = argv[iarg];       iarg++;
    telescope_      = argv[iarg];       iarg++;
    tunit_          = argv[iarg];       iarg++;
    format_         = argv[iarg];       iarg++;
    tbinfwidth_str_ = argv[iarg];       iarg++;
    outdir_         = argv[iarg];       iarg++;
    outfile_head_   = argv[iarg];       iarg++;
    return status;
}


void ArgValPlotLc::SetOption(int argc, char* argv[], option* long_options)
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


int ArgValPlotLc::Print(FILE* fp) const
{
    int status = kRetNormal;
    fprintf(fp, "input par> file_           : %s\n", file_.c_str());
    fprintf(fp, "input par> telescope_      : %s\n", telescope_.c_str());
    fprintf(fp, "input par> tunit_          : %s\n", tunit_.c_str());
    fprintf(fp, "input par> format_         : %s\n", format_.c_str());
    fprintf(fp, "input par> tbinfwidth_str_ : %s\n", tbinfwidth_str_.c_str());
    fprintf(fp, "input par> outdir_         : %s\n", outdir_.c_str());
    fprintf(fp, "input par> outfile_head_   : %s\n", outfile_head_.c_str());
    return status;
}


void ArgValPlotLc::Usage(FILE* fp) const
{
    fprintf(fp,
            "usage: %s [--help] [--verbose] [--debug] "
            "file  telescope  tunit  format  tbinfwidth_str  "
            "outdir  outfile_head",
            progname_.c_str());
    abort();
}

