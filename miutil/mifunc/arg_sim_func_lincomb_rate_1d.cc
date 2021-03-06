#include "arg_sim_func_lincomb_rate_1d.h"

// public

void ArgValSimFuncLincombRate1d::Init(int argc, char* argv[])
{
    progname_ = "sim_func_lincomb_rate_1d";

    option long_options[] = {
        {"debug",       required_argument, NULL, 'd'},
        {"help",        required_argument, NULL, 'h'},
        {"verbose",     required_argument, NULL, 'v'},
        {"hist_info_out", required_argument, NULL, 0},
        {"npoint_func", required_argument, NULL, 0},
        {0, 0, 0, 0}
    };

    // long option default
    hist_info_out_  = "none";
    npoint_func_    = 500;
    
    SetOption(argc, argv, long_options);
    
    printf("ArgVal::Init: # of arg = %d\n", argc - optind);
    int narg = 6;
    if (argc - optind != narg){
        printf("# of arguments must be %d.\n", narg);
        Usage(stdout);
    }
    int iarg = optind;
    func_par_norm_list_  = argv[iarg]; iarg++;
    hist_info_sim_  = argv[iarg]; iarg++;
    outdir_         = argv[iarg]; iarg++;
    outfile_head_   = argv[iarg]; iarg++;
    sim_mode_       = argv[iarg]; iarg++;    
    rand_seed_      = atoi(argv[iarg]); iarg++;
}

void ArgValSimFuncLincombRate1d::Print(FILE* fp) const
{
    fprintf(fp, "%s: g_flag_debug   : %d\n", __func__, g_flag_debug);
    fprintf(fp, "%s: g_flag_help    : %d\n", __func__, g_flag_help);
    fprintf(fp, "%s: g_flag_verbose : %d\n", __func__, g_flag_verbose);

    fprintf(fp, "%s: progname_      : %s\n", __func__, progname_.c_str());
    fprintf(fp, "%s: func_par_norm_list_ : %s\n", __func__, func_par_norm_list_.c_str());
    fprintf(fp, "%s: hist_info_sim_ : %s\n", __func__, hist_info_sim_.c_str());
    fprintf(fp, "%s: outdir_        : %s\n", __func__, outdir_.c_str());
    fprintf(fp, "%s: outfile_head_  : %s\n", __func__, outfile_head_.c_str());
    fprintf(fp, "%s: sim_mode_      : %s\n", __func__, sim_mode_.c_str());
    fprintf(fp, "%s: rand_seed_     : %d\n", __func__, rand_seed_);

    fprintf(fp, "%s: hist_info_out_ : %s\n", __func__, hist_info_out_.c_str());    
    fprintf(fp, "%s: npoint_func_   : %d\n", __func__, npoint_func_);
}

// private

void ArgValSimFuncLincombRate1d::Null()
{
    progname_ = "";
    func_par_norm_list_ = "";
    hist_info_sim_ = "";
    hist_info_out_ = "";
    outdir_ = "";
    outfile_head_ = "";
    sim_mode_ = "";    
    rand_seed_ = 0;
    npoint_func_ = 0;
}

void ArgValSimFuncLincombRate1d::SetOption(int argc, char* argv[], option* long_options)
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
            if(0 == strcmp("hist_info_out", long_options[option_index].name) ){
                hist_info_out_ = optarg;
            } else if(0 == strcmp("npoint_func", long_options[option_index].name) ){
                npoint_func_ = atoi(optarg);
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


void ArgValSimFuncLincombRate1d::Usage(FILE* fp) const
{
    fprintf(fp,
            "usage: %s [--help (0)] [--verbose (0)] [--debug (0)] "
            "[--npoint_func (500)] [--hist_info_out (none)/file_name] "
            "func_par_norm_list  hist_info_sim  "
            "outdir  outfile_head  sim_mode  rand_seed\n",
            progname_.c_str());
    fprintf(fp, "sim_mode:  bin/evt/evt+bin\n");
    fprintf(fp, "rand_seed: 0:       different simulations in every run.\n");
    fprintf(fp, "           integer: all the simulations are the same, "
            "meaning that the simulation is reproducible.\n");
    abort();
}
