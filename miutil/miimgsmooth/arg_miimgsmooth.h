#ifndef MORIIISM_MITOOL_MIUTIL_MIIMGSMOOTH_ARG_MIIMGSMOOTH_H_
#define MORIIISM_MITOOL_MIUTIL_MIIMGSMOOTH_ARG_MIIMGSMOOTH_H_

#include "mi_base.h"

class ArgValMiimgsmooth : public MiArgBase{
public:
    ArgValMiimgsmooth() :
        MiArgBase(),
        progname_(""),
        infile_(""),
        infile_mask_(""),
        func_(""),
        par_file_(""),
        nbin_kernel_half_(0),
        outdir_(""),
        outfile_head_("") {}
    ~ArgValMiimgsmooth(){
        Null();
    }
    void Init(int argc, char* argv[]);
    void Print(FILE* fp) const;

    string GetProgname() const {return progname_;};
    string GetInfile()   const {return infile_;};
    string GetInfileMask()   const {return infile_mask_;};
    string GetFunc()   const {return func_;};
    string GetParFile()   const {return par_file_;};    
    int    GetNbinKernelHalf() const {return nbin_kernel_half_;};
    string GetOutdir() const {return outdir_;};
    string GetOutfileHead()   const {return outfile_head_;};

private:
    string progname_;
    string infile_;
    string infile_mask_;
    string func_;
    string par_file_;
    int    nbin_kernel_half_;
    string outdir_;
    string outfile_head_;

    void Null();
    void SetOption(int argc, char* argv[], option* long_options);    
    void Usage(FILE* fp) const;
};

#endif // MORIIISM_MITOOL_MIUTIL_MIIMGSMOOTH_ARG_MIIMGSMOOTH_H_
