#ifndef MXKWTOOL_MXKWTIMING_MKLCPLS_BY_HIST_ARG_SIM_LCPLS_RATE_H_
#define MXKWTOOL_MXKWTIMING_MKLCPLS_BY_HIST_ARG_SIM_LCPLS_RATE_H_

#include "mxkw_base.h"

class ArgValSimLcplsRate : public MxkwArgBase{
public:
    explicit ArgValSimLcplsRate(string title = "") :
        MxkwArgBase("ArgValSimLcplsRate", title),
        progname_(""),
        hist_pls_(""),
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
        plotmode_(""),
        printmode_(""),
        root_style_("") {}
    ~ArgValSimLcplsRate(){
        Null();
    }
    void Init(int argc, char* argv[]);
    void Print(FILE* fp) const;

    string GetProgname() const {return progname_;};
    string GetHistPls() const {return hist_pls_;};
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
    string GetPlotmode() const {return plotmode_;};
    string GetPrintmode() const {return printmode_;};
    string GetRootStyle() const {return root_style_;};

private:
    string progname_;
    string hist_pls_;
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
    string plotmode_;
    string printmode_;
    string root_style_;

    void Null();
    void Usage(FILE* fp) const;
    void SetOption(int argc, char* argv[], option* long_options);
};

#endif // MXKWTOOL_MXKWTIMING_MKLCPLS_BY_HIST_ARG_SIM_LCPLS_RATE_H_
