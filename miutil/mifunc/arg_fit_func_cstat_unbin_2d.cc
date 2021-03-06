#include "arg_fit_func_cstat_unbin_2d.h"

// public

void ArgValFitFuncCstatUnbin2d::Init(int argc, char* argv[])
{
    progname_ = "fit_func_cstat_unbin_2d";

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
    plotmode_   = "on";
    printmode_  = "on";
    root_style_ = "def";
    
    SetOption(argc, argv, long_options);
    
    printf("ArgVal::Init: # of arg = %d\n", argc - optind);
    int narg = 12;
    if (argc - optind != narg){
        printf("# of arguments must be %d.\n", narg);
        Usage(stdout);
    }
    int iarg = optind;
    data_file_      = argv[iarg]; iarg++;
    func_name_      = argv[iarg]; iarg++;
    hist_mask_      = argv[iarg]; iarg++;

    fitpar_         = argv[iarg]; iarg++;
    chi2par_        = argv[iarg]; iarg++;
    chi2cont_par_   = argv[iarg]; iarg++;
    hist_info_      = argv[iarg]; iarg++;
    minfcn_name_    = argv[iarg]; iarg++;

    plot_conf_projx_file_ = argv[iarg]; iarg++;
    plot_conf_projy_file_ = argv[iarg]; iarg++;
    outdir_         = argv[iarg]; iarg++;
    outfile_head_   = argv[iarg]; iarg++;

}

void ArgValFitFuncCstatUnbin2d::Print(FILE* fp) const
{
    fprintf(fp, "%s: g_flag_debug   : %d\n", __func__, g_flag_debug);
    fprintf(fp, "%s: g_flag_help    : %d\n", __func__, g_flag_help);
    fprintf(fp, "%s: g_flag_verbose : %d\n", __func__, g_flag_verbose);

    fprintf(fp, "%s: progname_     : %s\n", __func__, progname_.c_str());
    fprintf(fp, "%s: data_file_    : %s\n", __func__, data_file_.c_str());
    fprintf(fp, "%s: func_name_    : %s\n", __func__, func_name_.c_str());
    fprintf(fp, "%s: hist_mask_    : %s\n", __func__, hist_mask_.c_str());    

    fprintf(fp, "%s: fitpar_       : %s\n", __func__, fitpar_.c_str());
    fprintf(fp, "%s: chi2par_      : %s\n", __func__, chi2par_.c_str());
    fprintf(fp, "%s: chi2cont_par_ : %s\n", __func__, chi2cont_par_.c_str());
    fprintf(fp, "%s: hist_info_    : %s\n", __func__, hist_info_.c_str());
    fprintf(fp, "%s: minfcn_name_  : %s\n", __func__, minfcn_name_.c_str());
    

    fprintf(fp, "%s: plot_conf_projx_file_ : %s\n", __func__, plot_conf_projx_file_.c_str());
    fprintf(fp, "%s: plot_conf_projy_file_ : %s\n", __func__, plot_conf_projy_file_.c_str());    
    fprintf(fp, "%s: outdir_       : %s\n", __func__, outdir_.c_str());
    fprintf(fp, "%s: outfile_head_ : %s\n", __func__, outfile_head_.c_str());

    fprintf(fp, "%s: plotmode_     : %s\n", __func__, plotmode_.c_str());
    fprintf(fp, "%s: printmode_    : %s\n", __func__, printmode_.c_str());
    fprintf(fp, "%s: root_style_   : %s\n", __func__, root_style_.c_str());
}

// private

void ArgValFitFuncCstatUnbin2d::Null()
{
    progname_ = "";
    data_file_ = "";
    func_name_ = "";
    hist_mask_ = "";

    fitpar_ = "";
    chi2par_ = "";
    chi2cont_par_ = "";
    hist_info_ = "";
    minfcn_name_ = "";

    plot_conf_projx_file_ = "";
    plot_conf_projy_file_ = "";    
    outdir_ = "";
    outfile_head_ = "";

    plotmode_ = "";
    printmode_ = "";
    root_style_ = "";
}

void ArgValFitFuncCstatUnbin2d::SetOption(int argc, char* argv[], option* long_options)
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
            printf("%s: error: getopt returned character code 0%o ??\n", __func__, retopt);
            abort();
        }
    }
    if(0 < g_flag_verbose){
        MPrintInfo("done.");
    }
}


void ArgValFitFuncCstatUnbin2d::Usage(FILE* fp) const
{
    fprintf(fp,
            "usage: %s [--help (0)] [--verbose (0)] [--debug (0)] "            
            "[--plotmode (on)/off] [--printmode (on)/off] [--root_style (def)/std/pub/detail] "
            "data_file  func_name  hist_mask  fitpar  chi2par  chi2cont_par  hist_info  minfcn_name  "
            "plot_conf_projx_file  plot_conf_projy_file  "
            "outdir  outfile_head\n",
            progname_.c_str());
    abort();
}
