#ifndef MXKWTOOL_MXKWTIMING_BINORB_ARG_DEMOD_DA1D_H_
#define MXKWTOOL_MXKWTIMING_BINORB_ARG_DEMOD_DA1D_H_

#include "mxkw_base.h"

class ArgValDemodDa1d : public MxkwArgBase{
public:
    explicit ArgValDemodDa1d(string title = "") :
        MxkwArgBase("ArgValDemodDa1d", title),
        progname_(""),
        telescope_(""),
        lc_file_(""),
        lc_tunit_(""),
        binorb_file_(""),
        outdir_(""),
        outfile_head_(""),
        plotmode_(""),
        printmode_(""),
        root_style_("") {}
    ~ArgValDemodDa1d(){
        Null();
    }
    void Init(int argc, char* argv[]);
    void Print(FILE* fp) const;

    string GetProgname() const {return progname_;};
    string GetTelescope() const {return telescope_;};
    string GetLcFile() const {return lc_file_;};
    string GetLcTunit() const {return lc_tunit_;};
    string GetBinorbFile() const {return binorb_file_;};
    string GetOutdir() const {return outdir_;};
    string GetOutfileHead() const {return outfile_head_;};
    string GetPlotmode() const {return plotmode_;};
    string GetPrintmode() const {return printmode_;};
    string GetRootStyle() const {return root_style_;};

private:
    string progname_;
    string telescope_;
    string lc_file_;
    string lc_tunit_;
    string binorb_file_;
    string outdir_;
    string outfile_head_;
    string plotmode_;
    string printmode_;
    string root_style_;

    void Null();
    void Usage(FILE* fp) const;
    void SetOption(int argc, char* argv[], option* long_options);
};

#endif // MXKWTOOL_MXKWTIMING_BINORB_ARG_DEMOD_DA1D_H_
