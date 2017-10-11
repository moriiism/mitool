#ifndef MORIIISM_MITOOL_MITIMING_LC_ARG_TCONV_H_
#define MORIIISM_MITOOL_MITIMING_LC_ARG_TCONV_H_

#include "mi_base.h"

class ArgValTconv : public MiObject{
public:
    ArgValTconv() :
        MiObject(),
        progname_(""),
        telescope_(""),
        lc_file_(""),
        lc_tunit_(""),
        lc_format_(""),
        telescope_out_(""),
        lc_tunit_out_(""),
        outdir_(""),
        outfile_head_(""){}
    ~ArgValTconv(){}
    int Init(int argc, char* argv[]);
    int Print(FILE* fp) const;
    void Usage(FILE* fp) const;
    void SetOption(int argc, char* argv[], option* long_options);

    string GetProgname() const {return progname_;};
    string GetTelescope() const {return telescope_;};
    string GetLcFile() const {return lc_file_;};
    string GetLcTunit() const {return lc_tunit_;};
    string GetLcFormat() const {return lc_format_;};

    string GetTelescopeOut() const {return telescope_out_;};
    string GetLcTunitOut() const {return lc_tunit_out_;};
    string GetOutdir() const {return outdir_;};
    string GetOutfileHead() const {return outfile_head_;};

private:
    string progname_;
    string telescope_;
    string lc_file_;
    string lc_tunit_;
    string lc_format_;

    string telescope_out_;
    string lc_tunit_out_;
    string outdir_;
    string outfile_head_;
};

#endif // MORIIISM_MITOOL_MITIMING_LC_ARG_TCONV_H_
