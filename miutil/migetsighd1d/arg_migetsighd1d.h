#ifndef MORIIISM_MITOOL_MIUTIL_MIGETSIGHD1D_ARG_MIGETSIGHD1D_H_
#define MORIIISM_MITOOL_MIUTIL_MIGETSIGHD1D_ARG_MIGETSIGHD1D_H_

#include "mi_base.h"

class ArgValMigetsighd1d : public MiArgBase{
public:
    ArgValMigetsighd1d() :
        MiArgBase(),
        progname_(""),
        infile_(""),
        infile_mask_(""),
        significance_src_(0.0),
        significance_bg_(0.0),
        nclip_(0),
        outdir_(""),
        outfile_head_("") {}
    ~ArgValMigetsighd1d(){
        Null();
    }
    void Init(int argc, char* argv[]);
    void Print(FILE* fp) const;

    string GetProgname() const {return progname_;};
    string GetInfile()   const {return infile_;};
    string GetInfileMask()   const {return infile_mask_;};
    double GetSignificanceSrc() const {return significance_src_;};
    double GetSignificanceBg() const {return significance_bg_;};
    int    GetNclip() const {return nclip_;};
    string GetOutdir() const {return outdir_;};
    string GetOutfileHead()   const {return outfile_head_;};

private:
    string progname_;
    string infile_;
    string infile_mask_;
    double significance_src_;
    double significance_bg_;
    int    nclip_;
    string outdir_;
    string outfile_head_;

    void Null();
    void SetOption(int argc, char* argv[], option* long_options);    
    void Usage(FILE* fp) const;
};

#endif // MORIIISM_MITOOL_MIUTIL_MIGETSIGHD1D_ARG_MIGETSIGHD1D_H_
