#ifndef MORIIISM_MITOOL_MITIMING_LC_ARG_SPLIT_BY_GTI_H_
#define MORIIISM_MITOOL_MITIMING_LC_ARG_SPLIT_BY_GTI_H_

#include "mi_base.h"

class ArgValSplitByGti : public MiObject{
public:
    ArgValSplitByGti() :
        MiObject(),
        progname_(""),
        lc_file_(""),
        lc_telescope_(""),
        lc_tunit_(""),
        lc_format_(""),
        gti_file_(""),
        gti_telescope_(""),
        gti_tunit_(""),
        outdir_(""),
        outfile_head_(""){}
    ~ArgValSplitByGti(){}
    int Init(int argc, char* argv[]);
    int Print(FILE* fp) const;
    void Usage(FILE* fp) const;
    void SetOption(int argc, char* argv[], option* long_options);

    string GetProgname() const {return progname_;};
    string GetLcFile() const {return lc_file_;};
    string GetLcTelescope() const {return lc_telescope_;};
    string GetLcTunit() const {return lc_tunit_;};
    string GetLcFormat() const {return lc_format_;};

    string GetGtiFile() const {return gti_file_;};
    string GetGtiTelescope() const {return gti_telescope_;};
    string GetGtiTunit() const {return gti_tunit_;};

    string GetOutdir() const {return outdir_;};
    string GetOutfileHead() const {return outfile_head_;};

private:
    string progname_;
    string lc_file_;
    string lc_telescope_;
    string lc_tunit_;
    string lc_format_;

    string gti_file_;
    string gti_telescope_;
    string gti_tunit_;

    string outdir_;
    string outfile_head_;
};

#endif // MORIIISM_MITOOL_MITIMING_LC_ARG_SPLIT_BY_GTI_H_
