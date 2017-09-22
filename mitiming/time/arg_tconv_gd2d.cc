#include "arg_tconv_gd2d.h"

// public

void ArgValTconvGd2d::Init(int argc, char* argv[])
{
    progname_ = "tconv_gd2d";
    
    option long_options[] = {
        {"debug",      required_argument, NULL, 'd'},
        {"help",       required_argument, NULL, 'h'},
        {"verbose",    required_argument, NULL, 'v'},        
        {0, 0, 0, 0}
    };

    // long option default
    SetOption(argc, argv, long_options);

    printf("ArgVal::Init: # of arg = %d\n", argc - optind);
    int narg = 7;
    if (argc - optind != narg){
        printf("# of arguments must be %d.\n", narg);
        Usage(stdout);
    }
    int iarg = optind;
    lc_gd2d_         = argv[iarg]; iarg++;
    format_          = argv[iarg]; iarg++;
    telescope_in_    = argv[iarg]; iarg++;
    tunit_in_        = argv[iarg]; iarg++;
    telescope_out_   = argv[iarg]; iarg++;
    tunit_out_       = argv[iarg]; iarg++;
    lc_gd2d_out_     = argv[iarg]; iarg++;
}

void ArgValTconvGd2d::Print(FILE* fp) const
{
    fprintf(fp, "%s: g_flag_debug   : %d\n", __func__, g_flag_debug);
    fprintf(fp, "%s: g_flag_help    : %d\n", __func__, g_flag_help);
    fprintf(fp, "%s: g_flag_verbose : %d\n", __func__, g_flag_verbose);

    fprintf(fp, "%s: lc_gd2d_        : %s\n", __func__, lc_gd2d_.c_str());
    fprintf(fp, "%s: format_         : %s\n", __func__, format_.c_str());
    fprintf(fp, "%s: telescope_in_   : %s\n", __func__, telescope_in_.c_str());
    fprintf(fp, "%s: tunit_in_       : %s\n", __func__, tunit_in_.c_str());
    fprintf(fp, "%s: telescope_out_  : %s\n", __func__, telescope_out_.c_str());
    fprintf(fp, "%s: tunit_out_      : %s\n", __func__, tunit_out_.c_str());
    fprintf(fp, "%s: lc_gd2d_out_    : %s\n", __func__, lc_gd2d_out_.c_str());
}

// private

void ArgValTconvGd2d::Null()
{
    progname_      = "";
    lc_gd2d_       = "";
    format_        = "";
    telescope_in_  = "";
    tunit_in_      = "";
    telescope_out_ = "";
    tunit_out_     = "";
    lc_gd2d_out_   = "";
}


void ArgValTconvGd2d::SetOption(int argc, char* argv[], option* long_options)
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
            printf("%s: error: getopt returned character code 0%o ??\n", __func__, retopt);
            abort();
        }
    }
    if(0 < g_flag_verbose){
        MPrintInfoClass("done.");
    }
}


void ArgValTconvGd2d::Usage(FILE* fp) const
{
    fprintf(fp,
            "usage: %s [--help (0)] [--verbose (0)] [--debug (0)] "
            "lc_gd2d_  format   telescope_in  tunit_in  "
            "telescope_out  tunit_out  lc_gd2d_out\n",
            progname_.c_str());
    abort();
}
