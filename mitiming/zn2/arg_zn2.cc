#include "arg_zn2.h"

// public

void ArgValZn2::Init(int argc, char* argv[])
{
    progname_ = "zn2";
    
    option long_options[] = {
        {"debug",      required_argument, NULL, 'd'},
        {"help",       required_argument, NULL, 'h'},
        {"verbose",    required_argument, NULL, 'v'},
        {"plotmode",   required_argument, NULL, 0},
        {"printmode",  required_argument, NULL, 0},
        {"root_style", required_argument, NULL, 0},
        {0, 0, 0, 0}
    };

    // long option default
    plotmode_  = "on";
    printmode_ = "on";
    root_style_ = "def";

    SetOption(argc, argv, long_options);

    if(0 < g_flag_verbose){
        printf("ArgVal::Init: # of arg = %d\n", argc - optind);
    }
    int narg = 9;
    if (argc - optind != narg){
        printf("# of arguments must be %d.\n", narg);
        Usage(stdout);
    }
    int iarg = optind;
    file_         = argv[iarg];       iarg++;
    telescope_    = argv[iarg];       iarg++; // telescope or MJD    
    tunit_        = argv[iarg];       iarg++; // lc tunit: "sec" or "day"
    format_       = argv[iarg];       iarg++;
    epoch_mjd_    = atof(argv[iarg]); iarg++;
    search_dat_   = argv[iarg];       iarg++;
    nharmonics_   = atoi(argv[iarg]); iarg++;    
    outdir_       = argv[iarg];       iarg++;
    outfile_head_ = argv[iarg];       iarg++;
}

void ArgValZn2::Print(FILE* fp) const
{
    fprintf(fp, "%s: g_flag_debug   : %d\n", __func__, g_flag_debug);
    fprintf(fp, "%s: g_flag_help    : %d\n", __func__, g_flag_help);
    fprintf(fp, "%s: g_flag_verbose : %d\n", __func__, g_flag_verbose);

    fprintf(fp, "%s: file_         : %s\n", __func__, file_.c_str());    
    fprintf(fp, "%s: telescope_    : %s\n", __func__, telescope_.c_str());
    fprintf(fp, "%s: tunit_        : %s\n", __func__, tunit_.c_str());
    fprintf(fp, "%s: format_       : %s\n", __func__, format_.c_str());
    fprintf(fp, "%s: epoch_mjd_    : %e\n", __func__, epoch_mjd_);
    fprintf(fp, "%s: search_dat_   : %s\n", __func__, search_dat_.c_str());
    fprintf(fp, "%s: nharmonics_   : %d\n", __func__, nharmonics_);    
    fprintf(fp, "%s: outdir_       : %s\n", __func__, outdir_.c_str());
    fprintf(fp, "%s: outfile_head_ : %s\n", __func__, outfile_head_.c_str());
}

// private

void ArgValZn2::Null()
{
    progname_     = "";
    file_         = "";    
    telescope_    = "";
    tunit_        = "";
    format_       = "";
    epoch_mjd_    = 0.0;
    search_dat_   = "";
    nharmonics_   = 0;    
    outdir_       = "";
    outfile_head_ = "";
}

void ArgValZn2::SetOption(int argc, char* argv[], option* long_options)
{
    if(0 < g_flag_verbose){
        MPrintInfoClass("start...");
    }
    // option default
    g_flag_debug   = 0;
    g_flag_help    = 0;
    g_flag_verbose = 0;
    while (1) {
        int option_index = 0;
        int retopt = getopt_long(argc, argv, "dhv",
                                 long_options, &option_index);
        
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
            g_flag_debug = atoi(optarg);
            printf("%s: g_flag_debug = %d\n", __func__, g_flag_debug);
            break;
        case 'h':
            g_flag_help = atoi(optarg);
            printf("%s: g_flag_help = %d\n", __func__, g_flag_help);
            if(0 != g_flag_help){
                Usage(stdout);
            }
            break;
        case 'v':
            g_flag_verbose = atoi(optarg);
            printf("%s: g_flag_verbose = %d\n", __func__, g_flag_verbose);
            break;
        case '?':
            printf("%s: retopt (= %c) is invalid flag.\n",
                   __func__, retopt);
            Usage(stdout);
            break;

        default:
            printf("%s: error: getopt returned character code 0%o ??\n",
                   __func__, retopt);
            abort();
        }
    }
    if(0 < g_flag_verbose){
        MPrintInfoClass("done.");
    }
}


void ArgValZn2::Usage(FILE* fp) const
{
    fprintf(fp,
            "usage: %s [--help (0)] [--verbose (0)] [--debug (0)] "
            "[--plotmode on/off] [--printmode on/off] [--root_style def/std/pub/detail] "
            "file  telescope  tunit  format  "
            "epoch_mjd  search_dat  nharmonics  "
            "outdir  outfile_head\n",
            progname_.c_str());
    abort();
}

