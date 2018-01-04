#ifndef MORIIISM_MITOOL_MIUTIL_MIPOW_ARG_MIPOW_H_
#define MORIIISM_MITOOL_MIUTIL_MIPOW_ARG_MIPOW_H_

#include "mi_base.h"

class ArgValMipow : public MiArgBase{
public:
    ArgValMipow() :
        MiArgBase(),
        progname_(""),
        infile_(""),
        format_(""),
        outdir_(""),
        outfile_head_("") {}
    ~ArgValMipow(){
        Null();
    }
    void Init(int argc, char* argv[]);
    void Print(FILE* fp) const;

    string GetProgname() const {return progname_;};
    string GetInfile()   const {return infile_;};
    string GetFormat()   const {return format_;};
    string GetOutdir()   const {return outdir_;};
    string GetOutfileHead()   const {return outfile_head_;};

private:
    string progname_;
    string infile_;
    string format_;
    string outdir_;
    string outfile_head_;

    void Null();
    void SetOption(int argc, char* argv[], option* long_options);    
    void Usage(FILE* fp) const;
};

#endif // MORIIISM_MITOOL_MIUTIL_MIPOW_ARG_MIPOW_H_
