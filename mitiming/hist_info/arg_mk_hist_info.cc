#include "arg_mk_hist_info.h"

// public

void ArgValMkHistInfo::Init(int argc, char* argv[])
{
    progname_ = "mk_hist_info";

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
    start_mjd_        = atof(argv[iarg]);   iarg++;
    end_mjd_          = atof(argv[iarg]);   iarg++;
    delta_time_       = atof(argv[iarg]);   iarg++;
    delta_time_unit_  = argv[iarg];   iarg++;
    telescope_out_    = argv[iarg];   iarg++;
    tunit_out_        = argv[iarg];   iarg++;
    hist_info_out_    = argv[iarg];   iarg++;
}

void ArgValMkHistInfo::Print(FILE* fp) const
{
    fprintf(fp, "%s: g_flag_debug   : %d\n", __func__, g_flag_debug);
    fprintf(fp, "%s: g_flag_help    : %d\n", __func__, g_flag_help);
    fprintf(fp, "%s: g_flag_verbose : %d\n", __func__, g_flag_verbose);

    fprintf(fp, "%s: start_mjd_       : %e\n", __func__, start_mjd_);
    fprintf(fp, "%s: end_mjd_         : %e\n", __func__, end_mjd_);
    fprintf(fp, "%s: delta_time_      : %e\n", __func__, delta_time_);
    fprintf(fp, "%s: delta_time_unit_ : %s\n", __func__, delta_time_unit_.c_str());
    fprintf(fp, "%s: telescope_out_   : %s\n", __func__, telescope_out_.c_str());
    fprintf(fp, "%s: tunit_out_       : %s\n", __func__, tunit_out_.c_str());
    fprintf(fp, "%s: hist_info_out_   : %s\n", __func__, hist_info_out_.c_str());
}

// private

void ArgValMkHistInfo::Null()
{
    progname_        = "";
    start_mjd_       = 0.0;
    end_mjd_         = 0.0;
    delta_time_      = 0.0;
    delta_time_unit_ = "";
    telescope_out_   = "";
    tunit_out_       = "";
    hist_info_out_   = "";
}

void ArgValMkHistInfo::SetOption(int argc, char* argv[], option* long_options)
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

void ArgValMkHistInfo::Usage(FILE* fp) const
{
    fprintf(fp,
            "usage: %s [--help (0)] [--verbose (0)] [--debug (0)] "
            "start_mjd  end_mjd  delta_time  delta_time_unit  "
            "telescope_out  tunit_out  hist_info_out\n",
            progname_.c_str());
    abort();
}
