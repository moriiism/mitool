#include "arg.h"

int ArgValMklc::Init(int argc, char* argv[])
{
    int status = kRetNormal;
    progname_ = "mklc";
    
    option long_options[] = {
        {"debug",      no_argument,       NULL, 'd'},
        {"help",       no_argument,       NULL, 'h'},
        {"verbose",    no_argument,       NULL, 'v'},
        {"plotmode",   required_argument, NULL, 0},
        {"printmode",  required_argument, NULL, 0},
        {"root_style", required_argument, NULL, 0},
        {0, 0, 0, 0}
    };

    // long option default
    plotmode_  = "on";
    printmode_ = "on";
    root_style_ = "def";

    SetOptionBase(argc, argv, long_options);
    optind = 0;
    SetOption(argc, argv, long_options);

    printf("ArgValMklc::Init: # of arg = %d\n", argc - optind);
    int narg = 12;
    if (argc - optind != narg){
        printf("# of arguments must be %d.\n", narg);
        Usage(stdout);
    }
    int iarg = optind;
    func_name_      = argv[iarg];       iarg++;
    func_par_file_  = argv[iarg];       iarg++;
    telescope_      = argv[iarg];       iarg++; // telescope or MJD
    lc_tunit_       = argv[iarg];       iarg++; // lc tunit: "sec" or "day"
    tbinfwidth_     = atof(argv[iarg]); iarg++; 
    gti_file_       = argv[iarg];       iarg++; 
    ephfile_        = argv[iarg];       iarg++; // ephemeris file
    time_mjd_st_    = atof(argv[iarg]); iarg++; 
    time_mjd_ed_    = atof(argv[iarg]); iarg++; 
    outdir_         = argv[iarg];       iarg++;
    outfile_head_   = argv[iarg];       iarg++;
    seed_           = atoi(argv[iarg]); iarg++;
  
    return status;
}


void ArgValMklc::SetOption(int argc, char* argv[], option* long_options)
{
    while (1) {
        int option_index = 0;
        int retopt = getopt_long(argc, argv, "dhv",
                                 long_options, &option_index);
        // printf("%s: retopt = %d\n", long_options[option_index].name, retopt);
        
        if(-1 == retopt)
            break;
        switch (retopt) {
        case 0:
            // long option
            if("plotmode" == long_options[option_index].name){
                plotmode_  = optarg;
            } else if ("printmode" == long_options[option_index].name){
                printmode_ = optarg;
            } else if ("root_style" == long_options[option_index].name){
               root_style_ = optarg;
            }
            break;
        case 'd':
            break;
        case 'h':
            break;
        case 'v':
            break;
        case '?':
            // getopt_long already printed an error message.
            break;
        default:
            printf("?? getopt returned character code 0%o ??\n", retopt);
            abort();
        }
    }
}


int ArgValMklc::Print(FILE* fp) const
{
    int status = kRetNormal;
    fprintf(fp, "input par> func_name_     : %s\n", func_name_.c_str());
    fprintf(fp, "input par> func_par_file_ : %s\n", func_par_file_.c_str());
    fprintf(fp, "input par> telescope_     : %s\n", telescope_.c_str());
    fprintf(fp, "input par> lc_tunit_      : %s\n", lc_tunit_.c_str());
    fprintf(fp, "input par> tbinfwidth_    : %f\n", tbinfwidth_);
    fprintf(fp, "input par> gti_file_      : %s\n", gti_file_.c_str());
    fprintf(fp, "input par> ephfile_       : %s\n", ephfile_.c_str());
    fprintf(fp, "input par> time_mjd_st_   : %f\n", time_mjd_st_);
    fprintf(fp, "input par> time_mjd_ed_   : %f\n", time_mjd_ed_);
    fprintf(fp, "input par> outdir_        : %s\n", outdir_.c_str());
    fprintf(fp, "input par> outfile_head_  : %s\n", outfile_head_.c_str());
    fprintf(fp, "input par> seed_          : %d\n", seed_);
  
    return status;
}


void ArgValMklc::Usage(FILE* fp) const
{
    fprintf(fp,
            "usage: %s [--help] [--verbose] [--debug] "
            "[--plotmode on/off] [--printmode on/off] [--root_style def/std/pub/detail] "
            "func_name  func_par_file  "
            "telescope  lc_tunit  tbinfwidth "
            "gti_file   "
            "ephfile  time_mjd_st  time_mjd_ed  "
            "outdir  outfile_head  seed\n",
            progname_.c_str());
    abort();
}


//
// ArgValMklcMaxi
//


int ArgValMklcMaxi::Init(int argc, char* argv[])
{
    int status = kRetNormal;
    progname_ = "mklc";
    
    option long_options[] = {
        {"debug",      no_argument,       NULL, 'd'},
        {"help",       no_argument,       NULL, 'h'},
        {"verbose",    no_argument,       NULL, 'v'},
        {"plotmode",   required_argument, NULL, 0},
        {"printmode",  required_argument, NULL, 0},
        {"root_style", required_argument, NULL, 0},
        {0, 0, 0, 0}
    };

    // long option default
    plotmode_  = "on";
    printmode_ = "on";
    root_style_ = "def";

    SetOptionBase(argc, argv, long_options);
    optind = 0;
    SetOption(argc, argv, long_options);

    printf("ArgValMklcMaxi::Init: # of arg = %d\n", argc - optind);
    int narg = 12;
    if (argc - optind != narg){
        printf("# of arguments must be %d.\n", narg);
        Usage(stdout);
    }
    int iarg = optind;
    func_name_      = argv[iarg];       iarg++;
    func_par_file_  = argv[iarg];       iarg++;
    telescope_      = argv[iarg];       iarg++; // telescope or MJD
    lc_tunit_       = argv[iarg];       iarg++; // lc tunit: "sec" or "day"
    tbinfwidth_     = atof(argv[iarg]); iarg++; 
    gti_file_       = argv[iarg];       iarg++; 
    ephfile_        = argv[iarg];       iarg++; // ephemeris file
    time_mjd_st_    = atof(argv[iarg]); iarg++; 
    time_mjd_ed_    = atof(argv[iarg]); iarg++; 
    outdir_         = argv[iarg];       iarg++;
    outfile_head_   = argv[iarg];       iarg++;
    seed_           = atoi(argv[iarg]); iarg++;
  
    return status;
}


void ArgValMklcMaxi::SetOption(int argc, char* argv[], option* long_options)
{
    while (1) {
        int option_index = 0;
        int retopt = getopt_long(argc, argv, "dhv",
                                 long_options, &option_index);
        // printf("%s: retopt = %d\n", long_options[option_index].name, retopt);
        
        if(-1 == retopt)
            break;
        switch (retopt) {
        case 0:
            // long option
            if("plotmode" == long_options[option_index].name){
                plotmode_  = optarg;
            } else if ("printmode" == long_options[option_index].name){
                printmode_ = optarg;
            } else if ("root_style" == long_options[option_index].name){
               root_style_ = optarg;
            }
            break;
        case 'd':
            break;
        case 'h':
            break;
        case 'v':
            break;
        case '?':
            // getopt_long already printed an error message.
            break;
        default:
            printf("?? getopt returned character code 0%o ??\n", retopt);
            abort();
        }
    }
}


int ArgValMklcMaxi::Print(FILE* fp) const
{
    int status = kRetNormal;
    fprintf(fp, "input par> func_name_     : %s\n", func_name_.c_str());
    fprintf(fp, "input par> func_par_file_ : %s\n", func_par_file_.c_str());
    fprintf(fp, "input par> telescope_     : %s\n", telescope_.c_str());
    fprintf(fp, "input par> lc_tunit_      : %s\n", lc_tunit_.c_str());
    fprintf(fp, "input par> tbinfwidth_    : %f\n", tbinfwidth_);
    fprintf(fp, "input par> gti_file_      : %s\n", gti_file_.c_str());
    fprintf(fp, "input par> ephfile_       : %s\n", ephfile_.c_str());
    fprintf(fp, "input par> time_mjd_st_   : %f\n", time_mjd_st_);
    fprintf(fp, "input par> time_mjd_ed_   : %f\n", time_mjd_ed_);
    fprintf(fp, "input par> outdir_        : %s\n", outdir_.c_str());
    fprintf(fp, "input par> outfile_head_  : %s\n", outfile_head_.c_str());
    fprintf(fp, "input par> seed_          : %d\n", seed_);
  
    return status;
}


void ArgValMklcMaxi::Usage(FILE* fp) const
{
    fprintf(fp,
            "usage: %s [--help] [--verbose] [--debug] "
            "[--plotmode on/off] [--printmode on/off] [--root_style def/std/pub/detail] "
            "func_name  func_par_file  "
            "telescope  lc_tunit  tbinfwidth "
            "gti_file   "
            "ephfile  time_mjd_st  time_mjd_ed  "
            "outdir  outfile_head  seed\n",
            progname_.c_str());
    abort();
}




//
// ArgValMklcPulsarBinaryMaxi
//


int ArgValMklcPulsarBinaryMaxi::Init(int argc, char* argv[])
{
    int status = kRetNormal;
    progname_ = "mklc_pulsar_binary_maxi";
    
    option long_options[] = {
        {"debug",      no_argument,       NULL, 'd'},
        {"help",       no_argument,       NULL, 'h'},
        {"verbose",    no_argument,       NULL, 'v'},
        {"plotmode",   required_argument, NULL, 0},
        {"printmode",  required_argument, NULL, 0},
        {"root_style", required_argument, NULL, 0},
        {0, 0, 0, 0}
    };

    // long option default
    plotmode_  = "on";
    printmode_ = "on";
    root_style_ = "def";

    SetOptionBase(argc, argv, long_options);
    optind = 0;
    SetOption(argc, argv, long_options);

    printf("ArgValMklcPulsarBinaryMaxi::Init: # of arg = %d\n", argc - optind);
    int narg = 13;
    if (argc - optind != narg){
        printf("# of arguments must be %d.\n", narg);
        Usage(stdout);
    }
    int iarg = optind;
    func_name_      = argv[iarg];       iarg++;
    func_par_file_  = argv[iarg];       iarg++;
    telescope_      = argv[iarg];       iarg++; // telescope or MJD
    lc_tunit_       = argv[iarg];       iarg++; // lc tunit: "sec" or "day"
    tbinfwidth_     = atof(argv[iarg]); iarg++; 
    gti_file_       = argv[iarg];       iarg++; 
    ephfile_        = argv[iarg];       iarg++; // ephemeris file
    orbfile_        = argv[iarg];       iarg++;
    time_mjd_st_    = atof(argv[iarg]); iarg++; 
    time_mjd_ed_    = atof(argv[iarg]); iarg++; 
    outdir_         = argv[iarg];       iarg++;
    outfile_head_   = argv[iarg];       iarg++;
    seed_           = atoi(argv[iarg]); iarg++;
  
    return status;
}


void ArgValMklcPulsarBinaryMaxi::SetOption(int argc, char* argv[], option* long_options)
{
    while (1) {
        int option_index = 0;
        int retopt = getopt_long(argc, argv, "dhv",
                                 long_options, &option_index);
        // printf("%s: retopt = %d\n", long_options[option_index].name, retopt);
        
        if(-1 == retopt)
            break;
        switch (retopt) {
        case 0:
            // long option
            if("plotmode" == long_options[option_index].name){
                plotmode_  = optarg;
            } else if ("printmode" == long_options[option_index].name){
                printmode_ = optarg;
            } else if ("root_style" == long_options[option_index].name){
               root_style_ = optarg;
            }
            break;
        case 'd':
            break;
        case 'h':
            break;
        case 'v':
            break;
        case '?':
            // getopt_long already printed an error message.
            break;
        default:
            printf("?? getopt returned character code 0%o ??\n", retopt);
            abort();
        }
    }
}


int ArgValMklcPulsarBinaryMaxi::Print(FILE* fp) const
{
    int status = kRetNormal;
    fprintf(fp, "input par> func_name_     : %s\n", func_name_.c_str());
    fprintf(fp, "input par> func_par_file_ : %s\n", func_par_file_.c_str());
    fprintf(fp, "input par> telescope_     : %s\n", telescope_.c_str());
    fprintf(fp, "input par> lc_tunit_      : %s\n", lc_tunit_.c_str());
    fprintf(fp, "input par> tbinfwidth_    : %f\n", tbinfwidth_);
    fprintf(fp, "input par> gti_file_      : %s\n", gti_file_.c_str());
    fprintf(fp, "input par> ephfile_       : %s\n", ephfile_.c_str());
    fprintf(fp, "input par> orbfile_       : %s\n", orbfile_.c_str());
    fprintf(fp, "input par> time_mjd_st_   : %f\n", time_mjd_st_);
    fprintf(fp, "input par> time_mjd_ed_   : %f\n", time_mjd_ed_);
    fprintf(fp, "input par> outdir_        : %s\n", outdir_.c_str());
    fprintf(fp, "input par> outfile_head_  : %s\n", outfile_head_.c_str());
    fprintf(fp, "input par> seed_          : %d\n", seed_);
  
    return status;
}


void ArgValMklcPulsarBinaryMaxi::Usage(FILE* fp) const
{
    fprintf(fp,
            "usage: %s [--help] [--verbose] [--debug] "
            "[--plotmode on/off] [--printmode on/off] [--root_style def/std/pub/detail] "
            "func_name  func_par_file  "
            "telescope  lc_tunit  tbinfwidth "
            "gti_file   "
            "ephfile  orbfile  time_mjd_st  time_mjd_ed  "
            "outdir  outfile_head  seed\n",
            progname_.c_str());
    abort();
}
