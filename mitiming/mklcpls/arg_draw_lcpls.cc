#include "arg_draw_lcpls.h"

// public

void ArgValDrawLcpls::Init(int argc, char* argv[])
{
    progname_ = "draw_lcpls";
    
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

    printf("ArgVal::Init: # of arg = %d\n", argc - optind);
    int narg = 10;
    if (argc - optind != narg){
        printf("# of arguments must be %d.\n", narg);
        Usage(stdout);
    }
    int iarg = optind;
    func_name_      = argv[iarg];       iarg++;
    par_file_       = argv[iarg];       iarg++;
    hist_info_      = argv[iarg];       iarg++;
    telescope_      = argv[iarg];       iarg++; // telescope or MJD
    tunit_          = argv[iarg];       iarg++; // lc tunit: "sec" or "day"
    ephfile_        = argv[iarg];       iarg++; // ephemeris file
    gtifile_        = argv[iarg];       iarg++;
    plot_conf_file_ = argv[iarg];       iarg++;
    outdir_         = argv[iarg];       iarg++;
    outfile_head_   = argv[iarg];       iarg++;
}

void ArgValDrawLcpls::Print(FILE* fp) const
{
    fprintf(fp, "%s: g_flag_debug   : %d\n", __func__, g_flag_debug);
    fprintf(fp, "%s: g_flag_help    : %d\n", __func__, g_flag_help);
    fprintf(fp, "%s: g_flag_verbose : %d\n", __func__, g_flag_verbose);
    
    fprintf(fp, "%s: func_name_     : %s\n", __func__, func_name_.c_str());
    fprintf(fp, "%s: par_file_      : %s\n", __func__, par_file_.c_str());
    fprintf(fp, "%s: hist_info_     : %s\n", __func__, hist_info_.c_str());
    fprintf(fp, "%s: telescope_     : %s\n", __func__, telescope_.c_str());
    fprintf(fp, "%s: tunit_         : %s\n", __func__, tunit_.c_str());
    fprintf(fp, "%s: ephfile_       : %s\n", __func__, ephfile_.c_str());
    fprintf(fp, "%s: gtifile_       : %s\n", __func__, gtifile_.c_str());
    fprintf(fp, "%s: plot_conf_file_: %s\n", __func__, plot_conf_file_.c_str());
    fprintf(fp, "%s: outdir_        : %s\n", __func__, outdir_.c_str());
    fprintf(fp, "%s: outfile_head_  : %s\n", __func__, outfile_head_.c_str());
}

// private

void ArgValDrawLcpls::Null()
{
    progname_     = "";
    func_name_    = "";
    par_file_     = "";
    hist_info_    = "";
    telescope_    = "";
    tunit_        = "";
    ephfile_      = "";
    gtifile_      = "";
    plot_conf_file_ = "";
    outdir_       = "";
    outfile_head_ = "";
}


void ArgValDrawLcpls::SetOption(int argc, char* argv[], option* long_options)
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
            printf("%s: error: getopt returned character code 0%o ??\n", __func__, retopt);
            abort();
        }
    }
    if(0 < g_flag_verbose){
        MPrintInfoClass("done.");
    }
}


void ArgValDrawLcpls::Usage(FILE* fp) const
{
    fprintf(fp,
            "usage: %s [--help (0)] [--verbose (0)] [--debug (0)] "
            "[--plotmode on/off] [--printmode on/off] [--root_style def/std/pub/detail] "
            "func_name  par_file  hist_info "
            "telescope  tunit  ephfile  gtifile  plot_conf_file  "
            "outdir  outfile_head\n",
            progname_.c_str());
    abort();
}
