#include "arg_gti_tconv.h"

// public

void ArgValGtiTconv::Init(int argc, char* argv[])
{
    progname_ = "gti_tconv";

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
    gti_in_        = argv[iarg];       iarg++;
    telescope_in_  = argv[iarg];       iarg++;
    tunit_in_      = argv[iarg];       iarg++;
    gti_out_       = argv[iarg];       iarg++;
    telescope_out_ = argv[iarg];       iarg++;
    tunit_out_     = argv[iarg];       iarg++;
}


void ArgValGtiTconv::Print(FILE* fp) const
{
    fprintf(fp, "%s: g_flag_debug   : %d\n", __func__, g_flag_debug);
    fprintf(fp, "%s: g_flag_help    : %d\n", __func__, g_flag_help);
    fprintf(fp, "%s: g_flag_verbose : %d\n", __func__, g_flag_verbose);
    
    fprintf(fp, "%s: gti_in_        : %s\n", __func__, gti_in_.c_str());
    fprintf(fp, "%s: telescope_in_  : %s\n", __func__, telescope_in_.c_str());
    fprintf(fp, "%s: tunit_in_      : %s\n", __func__, tunit_in_.c_str());
    fprintf(fp, "%s: gti_out_       : %s\n", __func__, gti_out_.c_str());
    fprintf(fp, "%s: telescope_out_ : %s\n", __func__, telescope_out_.c_str());
    fprintf(fp, "%s: tunit_out_     : %s\n", __func__, tunit_out_.c_str());
}

// private

void ArgValGtiTconv::Null()
{
    progname_ = "";
    gti_in_ = "";
    telescope_in_ = "";
    tunit_in_ = "";
    gti_out_ = "";
    telescope_out_ = "";
    tunit_out_ = "";
}
    
void ArgValGtiTconv::SetOption(int argc, char* argv[], option* long_options)
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

void ArgValGtiTconv::Usage(FILE* fp) const
{
    fprintf(fp,
            "usage: %s [--help (0)] [--verbose (0)] [--debug (0)] "
            "gti_in  telescope_in  tunit_in  "
            "gti_out  telescope_out  tunit_out  \n",
            progname_.c_str());
    abort();
}

