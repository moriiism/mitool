#ifndef MORIIISM_MITOOL_MIUTIL_RAD4D2IMG_ARG_RAD4D2IMG_H_
#define MORIIISM_MITOOL_MIUTIL_RAD4D2IMG_ARG_RAD4D2IMG_H_

#include "mi_base.h"

class ArgValRad4d2img : public MiArgBase{
public:
    ArgValRad4d2img() :
        MiArgBase(),
        progname_(""),
        infile_(""),
        subimg_dat_(""),
        outdir_(""),
        outfile_head_("") {}
    ~ArgValRad4d2img(){
        Null();
    }
    void Init(int argc, char* argv[]);
    void Print(FILE* fp) const;

    string GetProgname() const {return progname_;};
    string GetInfile() const {return infile_;};
    string GetSubimgDat() const {return subimg_dat_;};
    string GetOutdir() const {return outdir_;};
    string GetOutfileHead() const {return outfile_head_;};

private:
    string progname_;
    string infile_;
    string subimg_dat_;
    string outdir_;
    string outfile_head_;

    void Null();
    void SetOption(int argc, char* argv[], option* long_options);
    void Usage(FILE* fp) const;
};

#endif // MORIIISM_MITOOL_MIUTIL_RAD4D2IMG_ARG_RAD4D2IMG_H_
