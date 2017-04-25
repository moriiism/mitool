#include "arg_micsv2tree.h"

// public

void ArgValMicsv2tree::Init(int argc, char* argv[])
{
    progname_ = "micsv2tree";

    option long_options[] = {
        {"debug",      required_argument, NULL, 'd'},
        {"help",       required_argument, NULL, 'h'},
        {"verbose",    required_argument, NULL, 'v'},
        {"delimit",    required_argument, NULL, 0},
        {0, 0, 0, 0}
    };

    // long option default
    delimit_ = ",";
    SetOption(argc, argv, long_options);

    if(0 < g_flag_verbose){
        printf("ArgVal::Init: # of arg = %d\n", argc - optind);
    }
    int narg = 3;
    if (argc - optind != narg){
        printf("# of arguments must be %d.\n", narg);
        Usage(stdout);
    }
    int iarg = optind;
    infile_       = argv[iarg]; iarg++;
    format_       = argv[iarg]; iarg++;    
    outfile_      = argv[iarg]; iarg++;
}

void ArgValMicsv2tree::Print(FILE* fp) const
{
    fprintf(fp, "%s: g_flag_debug   : %d\n", __func__, g_flag_debug);
    fprintf(fp, "%s: g_flag_help    : %d\n", __func__, g_flag_help);
    fprintf(fp, "%s: g_flag_verbose : %d\n", __func__, g_flag_verbose);
    
    fprintf(fp, "%s: progname_      : %s\n", __func__, progname_.c_str());
    fprintf(fp, "%s: infile_        : %s\n", __func__, infile_.c_str());        
    fprintf(fp, "%s: format_        : %s\n", __func__, format_.c_str());
    fprintf(fp, "%s: outfile_       : %s\n", __func__, outfile_.c_str());

    fprintf(fp, "%s: delimit_       : %s\n", __func__, delimit_.c_str());
}

void ArgValMicsv2tree::Null()
{
    progname_     = "";
    infile_       = "";    
    format_       = "";    
    outfile_      = "";
    delimit_      = "";
}

void ArgValMicsv2tree::SetOption(int argc, char* argv[], option* long_options)
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
            if("delimit" == string(long_options[option_index].name) ){
                delimit_ = optarg;
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

void ArgValMicsv2tree::Usage(FILE* fp) const
{
    fprintf(fp,
            "usage: %s [--help (0)] [--verbose (0)] [--debug (0)] "
            "infile  format  outfile \n",
            progname_.c_str());
    exit(1);
}
