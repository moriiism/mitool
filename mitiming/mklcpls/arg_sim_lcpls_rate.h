#ifndef MORIIISM_MITOOL_MITIMING_MKLCPLS_ARG_SIM_LCPLS_RATE_H_
#define MORIIISM_MITOOL_MITIMING_MKLCPLS_ARG_SIM_LCPLS_RATE_H_

#include "mi_base.h"

class ArgValSimLcplsRate : public MiArgBase{
public:
    ArgValSimLcplsRate() :
        MiArgBase(),
        progname_(""),
        func_name_(""),
        par_file_(""),
        hist_info_(""),
        telescope_(""),
        tunit_(""),
        ephfile_(""),
        gtifile_(""),
        plot_conf_file_(""),
        outdir_(""),
        outfile_head_(""),
        sim_mode_(""),
        rand_seed_(0),
        npoint_func_(0),
        plotmode_(""),
        printmode_(""),
        root_style_("") {}
    ~ArgValSimLcplsRate(){
        Null();
    }
    void Init(int argc, char* argv[]);
    void Print(FILE* fp) const;

    string GetProgname() const {return progname_;};
    string GetFuncName() const {return func_name_;};
    string GetParFile() const {return par_file_;};
    string GetHistInfo() const {return hist_info_;};
    string GetTelescope() const {return telescope_;};
    string GetTunit() const {return tunit_;};
    string GetEphfile() const {return ephfile_;};
    string GetGtifile() const {return gtifile_;};
    string GetPlotConfFile() const {return plot_conf_file_;};
    string GetOutdir() const {return outdir_;};
    string GetOutfileHead() const {return outfile_head_;};
    string GetSimMode() const {return sim_mode_;};
    int    GetRandSeed() const {return rand_seed_;};
    int    GetNpointFunc() const {return npoint_func_;};
    string GetPlotmode() const {return plotmode_;};
    string GetPrintmode() const {return printmode_;};
    string GetRootStyle() const {return root_style_;};

private:
    string progname_;
    string func_name_;
    string par_file_;
    string hist_info_;
    string telescope_;
    string tunit_;
    string ephfile_;
    string gtifile_;
    string plot_conf_file_;
    string outdir_;
    string outfile_head_;
    string sim_mode_;
    int    rand_seed_;
    int    npoint_func_;
    string plotmode_;
    string printmode_;
    string root_style_;

    void Null();
    void Usage(FILE* fp) const;
    void SetOption(int argc, char* argv[], option* long_options);
};

#endif // MORIIISM_MITOOL_MITIMING_MKLCPLS_ARG_SIM_LCPLS_RATE_H_
