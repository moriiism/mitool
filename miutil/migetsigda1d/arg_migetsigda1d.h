#ifndef MORIIISM_MITOOL_MIUTIL_MIGETSIGDA1D_ARG_MIGETSIGDA1D_H_
#define MORIIISM_MITOOL_MIUTIL_MIGETSIGDA1D_ARG_MIGETSIGDA1D_H_

#include "mi_base.h"

class ArgValMigetsigda1d : public MiArgBase{
public:
    ArgValMigetsigda1d() :
        MiArgBase(),
        progname_(""),
        infile_(""),
        infile_mask_(""),
        significance_(0.0),
        nclip_(0),
        outdir_(""),
        outfile_head_("") {}
    ~ArgValMigetsigda1d(){
        Null();
    }
    void Init(int argc, char* argv[]);
    void Print(FILE* fp) const;

    string GetProgname() const {return progname_;};
    string GetInfile()   const {return infile_;};
    string GetInfileMask()   const {return infile_mask_;};
    double GetSignificance() const {return significance_;};
    int    GetNclip() const {return nclip_;};
    string GetOutdir() const {return outdir_;};
    string GetOutfileHead()   const {return outfile_head_;};

private:
    string progname_;
    string infile_;
    string infile_mask_;
    double significance_;
    int    nclip_;
    string outdir_;
    string outfile_head_;

    void Null();
    void SetOption(int argc, char* argv[], option* long_options);    
    void Usage(FILE* fp) const;
};

#endif // MORIIISM_MITOOL_MIUTIL_MIGETSIGDA1D_ARG_MIGETSIGDA1D_H_
