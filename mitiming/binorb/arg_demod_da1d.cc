#include "arg_demod_da1d.h"

// public

void ArgValDemodDa1d::Init(int argc, char* argv[])
{
    progname_ = "demod_da1d";
    
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
    int narg = 6;
    if (argc - optind != narg){
        printf("# of arguments must be %d.\n", narg);
        Usage(stdout);
    }
    int iarg = optind;
    telescope_    = argv[iarg];       iarg++; // telescope or MJD
    lc_file_      = argv[iarg];       iarg++;
    lc_tunit_     = argv[iarg];       iarg++; // lc tunit: "sec" or "day"
    binorb_file_  = argv[iarg];       iarg++;
    outdir_       = argv[iarg];       iarg++;
    outfile_head_ = argv[iarg];       iarg++;
}

void ArgValDemodDa1d::Print(FILE* fp) const
{
    fprintf(fp, "%s: g_flag_debug   : %d\n", __func__, g_flag_debug);
    fprintf(fp, "%s: g_flag_help    : %d\n", __func__, g_flag_help);
    fprintf(fp, "%s: g_flag_verbose : %d\n", __func__, g_flag_verbose);
    fprintf(fp, "%s: telescope_    : %s\n", __func__, telescope_.c_str());
    fprintf(fp, "%s: lc_file_      : %s\n", __func__, lc_file_.c_str());
    fprintf(fp, "%s: lc_tunit_     : %s\n", __func__, lc_tunit_.c_str());
    fprintf(fp, "%s: binorb_file_  : %s\n", __func__, binorb_file_.c_str());    
    fprintf(fp, "%s: outdir_       : %s\n", __func__, outdir_.c_str());
    fprintf(fp, "%s: outfile_head_ : %s\n", __func__, outfile_head_.c_str());
}

// private

void ArgValDemodDa1d::Null()
{
    progname_     = "";
    telescope_    = "";
    lc_file_      = "";
    lc_tunit_     = "";
    binorb_file_  = "";
    outdir_       = "";
    outfile_head_ = "";
}

void ArgValDemodDa1d::SetOption(int argc, char* argv[], option* long_options)
{
    if(0 < g_flag_verbose){
        MPrintInfo("start...");
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
            if(0 == strcmp("plotmode", long_options[option_index].name) ){
                plotmode_  = optarg;
            } else if (0 == strcmp("printmode", long_options[option_index].name) ){
                printmode_ = optarg;
            } else if (0 == strcmp("root_style", long_options[option_index].name) ){
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
        MPrintInfo("done.");
    }
}


void ArgValDemodDa1d::Usage(FILE* fp) const
{
    fprintf(fp,
            "usage: %s [--help (0)] [--verbose (0)] [--debug (0)] "
            "[--plotmode on/off] [--printmode on/off] [--root_style def/std/pub/detail] "
            "telescope  lc_file  lc_tunit  "
            "binorb_file  "
            "outdir  outfile_head\n",
            progname_.c_str());
    abort();
}

