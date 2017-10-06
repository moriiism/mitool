#include "arg_milcsim.h"

// public

void ArgValMilcsim::Init(int argc, char* argv[])
{
    progname_ = "milcsim";

    option long_options[] = {
        {"debug",      required_argument, NULL, 'd'},
        {"help",       required_argument, NULL, 'h'},
        {"verbose",    required_argument, NULL, 'v'},
        {0, 0, 0, 0}
    };

    // long option default
    SetOption(argc, argv, long_options);

    if(0 < g_flag_verbose){
        printf("ArgVal::Init: # of arg = %d\n", argc - optind);
    }
    int narg = 7;
    if (argc - optind != narg){
        printf("# of arguments must be %d.\n", narg);
        Usage(stdout);
    }
    int iarg = optind;
    gti_file_       = argv[iarg]; iarg++; 
    hist_info_file_ = argv[iarg]; iarg++;
    trig_func_info_file_ = argv[iarg]; iarg++;
    delta_time_     = atof(argv[iarg]); iarg++;
    seed_           = atoi(argv[iarg]); iarg++;
    outdir_         = argv[iarg]; iarg++;
    outfile_head_   = argv[iarg]; iarg++;    
}

void ArgValMilcsim::Print(FILE* fp) const
{
    fprintf(fp, "%s: g_flag_debug   : %d\n", __func__, g_flag_debug);
    fprintf(fp, "%s: g_flag_help    : %d\n", __func__, g_flag_help);
    fprintf(fp, "%s: g_flag_verbose : %d\n", __func__, g_flag_verbose);
    
    fprintf(fp, "%s: progname_      : %s\n", __func__, progname_.c_str());
    fprintf(fp, "%s: gti_file_      : %s\n", __func__, gti_file_.c_str());
    fprintf(fp, "%s: hist_info_file_  : %s\n", __func__, hist_info_file_.c_str());
    fprintf(fp, "%s: trig_func_info_file_ : %s\n", __func__, trig_func_info_file_.c_str());
    fprintf(fp, "%s: delta_time_    : %e\n", __func__, delta_time_);
    fprintf(fp, "%s: seed_          : %d\n", __func__, seed_);
    fprintf(fp, "%s: outdir_        : %s\n", __func__, outdir_.c_str());
    fprintf(fp, "%s: outfile_head_  : %s\n", __func__, outfile_head_.c_str());    
}

void ArgValMilcsim::Null()
{
    progname_       = "";
    gti_file_       = "";
    hist_info_file_ = "";
    trig_func_info_file_ = "";
    delta_time_     = 0.0;
    seed_           = 0;
    outdir_         = "";
    outfile_head_   = "";    
}

void ArgValMilcsim::SetOption(int argc, char* argv[], option* long_options)
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

void ArgValMilcsim::Usage(FILE* fp) const
{
    fprintf(fp,
            "usage: %s [--help (0)] [--verbose (0)] [--debug (0)] "
            "gti_file  hist_info_file  trig_func_info_file  delta_time  seed  outdir  outfile_head \n",
            progname_.c_str());
    exit(1);
}
