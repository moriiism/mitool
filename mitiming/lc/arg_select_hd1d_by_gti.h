#ifndef MXKWTOOL_MXKWTIMING_LC_ARG_SELECT_HD1D_BY_GTI_H_
#define MXKWTOOL_MXKWTIMING_LC_ARG_SELECT_HD1D_BY_GTI_H_

#include "mxkw_base.h"

class ArgValSelectHd1dByGti : public MxkwArgBase{
public:
    explicit ArgValSelectHd1dByGti(string title = "") :
        MxkwArgBase("ArgValSelectHd1dByGti", title),
        progname_(""),
        lc_file_(""),
        gti_file_(""),
        outdir_(""),
        outfile_head_(""){}
    ~ArgValSelectHd1dByGti(){}
    void Init(int argc, char* argv[]);
    void Print(FILE* fp) const;

    string GetProgname() const {return progname_;};
    string GetLcFile() const {return lc_file_;};
    string GetGtiFile() const {return gti_file_;};
    string GetOutdir() const {return outdir_;};
    string GetOutfileHead() const {return outfile_head_;};

private:
    string progname_;
    string lc_file_;
    string gti_file_;
    string outdir_;
    string outfile_head_;

    void Null();
    void Usage(FILE* fp) const;
    void SetOption(int argc, char* argv[], option* long_options);
};

#endif // MXKWTOOL_MXKWTIMING_LC_ARG_SELECT_HD1D_BY_GTI_H_
