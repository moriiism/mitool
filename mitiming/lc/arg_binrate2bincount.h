#ifndef MORIIISM_MITOOL_MITIMING_LC_ARG_BINRATE2BINCOUNT_H_
#define MORIIISM_MITOOL_MITIMING_LC_ARG_BINRATE2BINCOUNT_H_

#include "mi_base.h"

class ArgValBinRate2BinCount : public MiArgBase{
public:
    ArgValBinRate2BinCount() :
        MiArgBase(),
        progname_(""),
        telescope_(""),
        lc_file_(""),
        lc_tunit_(""),
        lc_format_(""),
        tbinfwidth_str_(""),
        outdir_(""),
        outfile_head_("") {}
    ~ArgValBinRate2BinCount(){
        Null();
    }
    void Init(int argc, char* argv[]);
    void Print(FILE* fp) const;

    string GetProgname() const {return progname_;};
    string GetTelescope() const {return telescope_;};
    string GetLcFile() const {return lc_file_;};
    string GetLcTunit() const {return lc_tunit_;};
    string GetLcFormat() const {return lc_format_;};
    string GetTbinfwidthStr() const {return tbinfwidth_str_;};

    string GetOutdir() const {return outdir_;};
    string GetOutfileHead() const {return outfile_head_;};

private:
    string progname_;
    string telescope_;
    string lc_file_;
    string lc_tunit_;
    string lc_format_;
    string tbinfwidth_str_; // "none" or double
    
    string outdir_;
    string outfile_head_;

    void Null();
    void Usage(FILE* fp) const;
    void SetOption(int argc, char* argv[], option* long_options);
};

#endif // MORIIISM_MITOOL_MITIMING_LC_ARG_BINRATE2BINCOUNT_H_

