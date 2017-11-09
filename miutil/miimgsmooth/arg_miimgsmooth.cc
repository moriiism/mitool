#include "arg_miimgsmooth.h"

// public

void ArgValMiimgsmooth::Init(int argc, char* argv[])
{
    progname_ = "miimgsmooth";

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
    infile_       = argv[iarg]; iarg++;
    infile_mask_  = argv[iarg]; iarg++;
    func_         = argv[iarg]; iarg++;
    par_file_     = argv[iarg]; iarg++;
    nbin_kernel_half_  = atoi(argv[iarg]); iarg++;
    outdir_       = argv[iarg]; iarg++;
    outfile_head_ = argv[iarg]; iarg++;    
}

void ArgValMiimgsmooth::Print(FILE* fp) const
{
    fprintf(fp, "%s: g_flag_debug   : %d\n", __func__, g_flag_debug);
    fprintf(fp, "%s: g_flag_help    : %d\n", __func__, g_flag_help);
    fprintf(fp, "%s: g_flag_verbose : %d\n", __func__, g_flag_verbose);
    
    fprintf(fp, "%s: progname_      : %s\n", __func__, progname_.c_str());
    fprintf(fp, "%s: infile_        : %s\n", __func__, infile_.c_str());
    fprintf(fp, "%s: infile_mask_   : %s\n", __func__, infile_mask_.c_str());
    fprintf(fp, "%s: func_          : %s\n", __func__, func_.c_str());
    fprintf(fp, "%s: par_file_      : %s\n", __func__, par_file_.c_str());
    fprintf(fp, "%s: nbin_kernel_half_   : %d\n", __func__, nbin_kernel_half_);
    fprintf(fp, "%s: outdir_        : %s\n", __func__, outdir_.c_str());
    fprintf(fp, "%s: outfile_head_  : %s\n", __func__, outfile_head_.c_str());    
}

void ArgValMiimgsmooth::Null()
{
    progname_     = "";
    infile_       = "";
    infile_mask_  = "";
    func_         = "";
    par_file_     = "";
    nbin_kernel_half_ = 0;
    outdir_       = "";
    outfile_head_ = "";    
}

void ArgValMiimgsmooth::SetOption(int argc, char* argv[], option* long_options)
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

void ArgValMiimgsmooth::Usage(FILE* fp) const
{
    fprintf(fp,
            "usage: %s [--help (0)] [--verbose (0)] [--debug (0)] "
            "infile  infile_mask  func  par_file  nbin_kernel_half  outdir  outfile_head \n",
            progname_.c_str());
    exit(1);
}
