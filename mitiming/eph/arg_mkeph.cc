#include "arg_mkeph.h"

// public

void ArgValMkEph::Init(int argc, char* argv[])
{
    progname_ = "mkeph";
  
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
    int narg = 6;
    if (argc - optind != narg){
        printf("# of arguments must be %d.\n", narg);
        Usage(stdout);
    }
    int iarg = optind;
    period_       = atof(argv[iarg]); iarg++;
    p_dot_        = atof(argv[iarg]); iarg++;
    epoch_mjd_    = atof(argv[iarg]); iarg++;
    start_mjd_    = atof(argv[iarg]); iarg++;
    end_mjd_      = atof(argv[iarg]); iarg++;
    ephfile_out_  = argv[iarg];       iarg++;
}


void ArgValMkEph::Print(FILE* fp) const
{
    fprintf(fp, "%s: g_flag_debug   : %d\n", __func__, g_flag_debug);
    fprintf(fp, "%s: g_flag_help    : %d\n", __func__, g_flag_help);
    fprintf(fp, "%s: g_flag_verbose : %d\n", __func__, g_flag_verbose);
    
    fprintf(fp, "%s: period_        : %e\n", __func__, period_);
    fprintf(fp, "%s: p_dot_         : %e\n", __func__, p_dot_);   
    fprintf(fp, "%s: epoch_mjd_     : %e\n", __func__, epoch_mjd_);
    fprintf(fp, "%s: start_mjd_     : %e\n", __func__, start_mjd_);
    fprintf(fp, "%s: end_mjd_       : %e\n", __func__, end_mjd_);
    fprintf(fp, "%s: ephfile_out_   : %s\n", __func__, ephfile_out_.c_str());
}

// private

void ArgValMkEph::Null()
{
    progname_     = "";
    period_       = 0.0;
    p_dot_        = 0.0;
    epoch_mjd_    = 0.0;
    start_mjd_    = 0.0;
    end_mjd_      = 0.0;
    ephfile_out_  = "";
}

void ArgValMkEph::SetOption(int argc, char* argv[], option* long_options)
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


void ArgValMkEph::Usage(FILE* fp) const
{
    fprintf(fp,
            "usage: %s [--help (0)] [--verbose (0)] [--debug (0)] "
            "period  p_dot  epoch_mjd  start_mjd  end_mjd  ephfile_out\n" ,
            progname_.c_str());
    abort();
}
