#ifndef MORIIISM_MITOOL_MITIMING_LC_ARG_PLOT_LC_H_
#define MORIIISM_MITOOL_MITIMING_LC_ARG_PLOT_LC_H_

#include "mi_base.h"

class ArgValPlotLc : public MiObject{
public:
    ArgValPlotLc() :
        MiObject(),
        progname_(""),
        file_(""),
        telescope_(""),
        tunit_(""),
        format_(""),
        tbinfwidth_str_(""),
        outdir_(""),
        outfile_head_(""){}
    ~ArgValPlotLc(){}
    int Init(int argc, char* argv[]);
    int Print(FILE* fp) const;
    void Usage(FILE* fp) const;
    void SetOption(int argc, char* argv[], option* long_options);

    string GetProgname() const {return progname_;};
    string GetFile() const {return file_;};
    string GetTelescope() const {return telescope_;};
    string GetTunit() const {return tunit_;};
    string GetFormat() const {return format_;};

    string GetTbinfwidthStr() const {return tbinfwidth_str_;};

    string GetOutdir() const {return outdir_;};
    string GetOutfileHead() const {return outfile_head_;};

private:
    string progname_;
    string file_;
    string telescope_;
    string tunit_;
    string format_;
    
    string tbinfwidth_str_;  // "none" or double

    string outdir_;
    string outfile_head_;
};

#endif // MORIIISM_MITOOL_MITIMING_LC_ARG_PLOT_LC_H_
