#include "arg.h"

int ArgValZn2Graph::Init(int argc, char* argv[])
{
    int status = kRetNormal;
    progname_ = "zn2_graph";
    
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

    printf("ArgValZn2Graph::Init: # of arg = %d\n", argc - optind);
    int narg = 9;
    if (argc - optind != narg){
        printf("# of arguments must be %d.\n", narg);
        Usage(stdout);
    }
    int iarg = optind;
    telescope_    = argv[iarg];       iarg++; // telescope or MJD
    lc_file_      = argv[iarg];       iarg++;
    lc_tunit_     = argv[iarg];       iarg++; // lc tunit: "sec" or "day"
    lc_format_    = argv[iarg];       iarg++;
    nharmonics_   = atoi(argv[iarg]); iarg++;
    epoch_mjd_    = atof(argv[iarg]); iarg++;
    search_dat_   = argv[iarg];       iarg++;

    outdir_       = argv[iarg];       iarg++;
    outfile_head_ = argv[iarg];       iarg++;
  
    return status;
}


void ArgValZn2Graph::SetOption(int argc, char* argv[], option* long_options)
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


int ArgValZn2Graph::Print(FILE* fp) const
{
    int status = kRetNormal;
    fprintf(fp, "input par> telescope_   : %s\n", telescope_.c_str());
    fprintf(fp, "input par> lc_file_     : %s\n", lc_file_.c_str());
    fprintf(fp, "input par> lc_tunit_    : %s\n", lc_tunit_.c_str());
    fprintf(fp, "input par> lc_format_   : %s\n", lc_format_.c_str());
    fprintf(fp, "input par> nharmonics_  : %d\n", nharmonics_);
    fprintf(fp, "input par> epoch_mjd_   : %e\n", epoch_mjd_);
    fprintf(fp, "input par> search_dat_  : %s\n", search_dat_.c_str());
    fprintf(fp, "input par> outdir_      : %s\n", outdir_.c_str());
    fprintf(fp, "input par> outfile_head_ : %s\n", outfile_head_.c_str());
  
    return status;
}


void ArgValZn2Graph::Usage(FILE* fp) const
{
    fprintf(fp,
            "usage: %s [--help] [--verbose] [--debug] "
            "[--plotmode on/off] [--printmode on/off] [--root_style def/std/pub/detail] "
            "telescope  lc_file  lc_tunit  lc_format "
            "nharmonics  epoch_mjd   search_dat  "
            "outdir  outfile_head\n",
            progname_.c_str());
    abort();
}


//
// ArgValZn2
//


int ArgValZn2::Init(int argc, char* argv[])
{
    int status = kRetNormal;
    progname_ = "zn2";
    
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

    printf("ArgValZn2::Init: # of arg = %d\n", argc - optind);
    int narg = 9;
    if (argc - optind != narg){
        printf("# of arguments must be %d.\n", narg);
        Usage(stdout);
    }
    int iarg = optind;
    telescope_    = argv[iarg];       iarg++; // telescope or MJD
    lc_file_      = argv[iarg];       iarg++;
    lc_tunit_     = argv[iarg];       iarg++; // lc tunit: "sec" or "day"
    lc_format_    = argv[iarg];       iarg++;
    nharmonics_   = atoi(argv[iarg]); iarg++;
    epoch_mjd_    = atof(argv[iarg]); iarg++;
    search_dat_   = argv[iarg];       iarg++;

    outdir_       = argv[iarg];       iarg++;
    outfile_head_ = argv[iarg];       iarg++;
  
    return status;
}


void ArgValZn2::SetOption(int argc, char* argv[], option* long_options)
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


int ArgValZn2::Print(FILE* fp) const
{
    int status = kRetNormal;
    fprintf(fp, "input par> telescope_   : %s\n", telescope_.c_str());
    fprintf(fp, "input par> lc_file_     : %s\n", lc_file_.c_str());
    fprintf(fp, "input par> lc_tunit_    : %s\n", lc_tunit_.c_str());
    fprintf(fp, "input par> lc_format_   : %s\n", lc_format_.c_str());
    fprintf(fp, "input par> nharmonics_  : %d\n", nharmonics_);
    fprintf(fp, "input par> epoch_mjd_   : %e\n", epoch_mjd_);
    fprintf(fp, "input par> search_dat_  : %s\n", search_dat_.c_str());
    fprintf(fp, "input par> outdir_      : %s\n", outdir_.c_str());
    fprintf(fp, "input par> outfile_head_ : %s\n", outfile_head_.c_str());
  
    return status;
}


void ArgValZn2::Usage(FILE* fp) const
{
    fprintf(fp,
            "usage: %s [--help] [--verbose] [--debug] "
            "[--plotmode on/off] [--printmode on/off] [--root_style def/std/pub/detail] "
            "telescope  lc_file  lc_tunit  lc_format "
            "nharmonics  epoch_mjd   search_dat  "
            "outdir  outfile_head\n",
            progname_.c_str());
    abort();
}



