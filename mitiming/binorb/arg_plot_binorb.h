#ifndef MXKWTOOL_MXKWTIMING_BINORB_ARG_PLOT_BINORB_H_
#define MXKWTOOL_MXKWTIMING_BINORB_ARG_PLOT_BINORB_H_

#include "mxkw_base.h"

class ArgValPlotBinorb : public MxkwArgBase{
public:
    explicit ArgValPlotBinorb(string title = "") :
        MxkwArgBase("ArgValPlotBinorb", title),
        progname_(""),
        mode_(""),
        binorb_file_(""),
        nbin_(0),
        mjd_lo_(0.0),
        outdir_(""),
        outfile_head_(""){}
    ~ArgValPlotBinorb(){
        Null();
    }
    void Init(int argc, char* argv[]);
    void Print(FILE* fp) const;

    string GetProgname() const {return progname_;};
    string GetMode() const {return mode_;};
    string GetBinorbFile() const {return binorb_file_;};
    int    GetNbin() const {return nbin_;};
    double GetMjdLo() const {return mjd_lo_;};
    string GetOutdir() const {return outdir_;};
    string GetOutfileHead() const {return outfile_head_;};

private:
    string progname_;
    string mode_;          // A or P
    string binorb_file_;
    int    nbin_;
    double mjd_lo_;
    string outdir_;
    string outfile_head_;

    void Null();
    void Usage(FILE* fp) const;
    void SetOption(int argc, char* argv[], option* long_options);
};

#endif // MXKWTOOL_MXKWTIMING_BINORB_ARG_PLOT_BINORB_H_
