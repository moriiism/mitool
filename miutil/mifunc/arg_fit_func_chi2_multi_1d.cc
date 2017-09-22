#include "arg_fit_func_chi2_multi_1d.h"

// public

void ArgValFitFuncChi2Multi1d::Init(int argc, char* argv[])
{
    progname_ = "fit_func_chi2_multi_1d";

    option long_options[] = {
        {"debug",       required_argument, NULL, 'd'},
        {"help",        required_argument, NULL, 'h'},
        {"verbose",     required_argument, NULL, 'v'},
        {"npoint_func", required_argument, NULL, 0},
        {"plotmode",    required_argument, NULL, 0},
        {"printmode",   required_argument, NULL, 0},
        {"root_style",  required_argument, NULL, 0},
        {0, 0, 0, 0}
    };

    // long option default
    npoint_func_ = 500;
    plotmode_    = "on";
    printmode_   = "on";
    root_style_  = "def";

    SetOption(argc, argv, long_options);
    
    printf("ArgVal::Init: # of arg = %d\n", argc - optind);
    int narg = 8;
    if (argc - optind != narg){
        printf("# of arguments must be %d.\n", narg);
        Usage(stdout);
    }
    int iarg = optind;
    data_file_list_ = argv[iarg]; iarg++;
    func_name_      = argv[iarg]; iarg++;

    fitpar_         = argv[iarg]; iarg++;
    chi2par_        = argv[iarg]; iarg++;
    chi2cont_par_   = argv[iarg]; iarg++;

    plot_conf_file_ = argv[iarg]; iarg++;
    outdir_         = argv[iarg]; iarg++;
    outfile_head_   = argv[iarg]; iarg++;
}

void ArgValFitFuncChi2Multi1d::Print(FILE* fp) const
{
    fprintf(fp, "%s: g_flag_debug   : %d\n", __func__, g_flag_debug);
    fprintf(fp, "%s: g_flag_help    : %d\n", __func__, g_flag_help);
    fprintf(fp, "%s: g_flag_verbose : %d\n", __func__, g_flag_verbose);

    fprintf(fp, "%s: progname_     : %s\n", __func__, progname_.c_str());
    fprintf(fp, "%s: data_file_list_ : %s\n", __func__, data_file_list_.c_str());
    fprintf(fp, "%s: func_name_    : %s\n", __func__, func_name_.c_str());

    fprintf(fp, "%s: fitpar_       : %s\n", __func__, fitpar_.c_str());
    fprintf(fp, "%s: chi2par_      : %s\n", __func__, chi2par_.c_str());
    fprintf(fp, "%s: chi2cont_par_ : %s\n", __func__, chi2cont_par_.c_str());

    fprintf(fp, "%s: plot_conf_file_ : %s\n", __func__, plot_conf_file_.c_str());
    fprintf(fp, "%s: outdir_       : %s\n", __func__, outdir_.c_str());
    fprintf(fp, "%s: outfile_head_ : %s\n", __func__, outfile_head_.c_str());

    fprintf(fp, "%s: npoint_func_  : %d\n", __func__, npoint_func_);
    fprintf(fp, "%s: plotmode_     : %s\n", __func__, plotmode_.c_str());
    fprintf(fp, "%s: printmode_    : %s\n", __func__, printmode_.c_str());
    fprintf(fp, "%s: root_style_   : %s\n", __func__, root_style_.c_str());
}

// private

void ArgValFitFuncChi2Multi1d::Null()
{
    progname_ = "";
    data_file_list_ = "";
    func_name_ = "";

    fitpar_ = "";
    chi2par_ = "";
    chi2cont_par_ = "";

    plot_conf_file_ = "";
    outdir_ = "";
    outfile_head_ = "";

    npoint_func_ = 0;
    plotmode_ = "";
    printmode_ = "";
    root_style_ = "";
}

void ArgValFitFuncChi2Multi1d::SetOption(int argc, char* argv[], option* long_options)
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
            if(0 == strcmp("npoint_func", long_options[option_index].name) ){
                npoint_func_ = atoi(optarg);
            } else if(0 == strcmp("plotmode", long_options[option_index].name) ){
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
            printf("%s: error: getopt returned character code 0%o ??\n", __func__, retopt);
            abort();
        }
    }
    if(0 < g_flag_verbose){
        MPrintInfo("done.");
    }
}


void ArgValFitFuncChi2Multi1d::Usage(FILE* fp) const
{
    fprintf(fp,
            "usage: %s [--help (0)] [--verbose (0)] [--debug (0)] "
            "[--npoint_func (500)] "
            "[--plotmode (on)/off] [--printmode (on)/off] [--root_style (def)/std/pub/detail] "
            "data_file_list  func_name  fitpar  chi2par  chi2cont_par  "
            "plot_conf_file  outdir  outfile_head\n",
            progname_.c_str());
    abort();
}
