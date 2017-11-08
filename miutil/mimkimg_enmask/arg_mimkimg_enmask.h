#ifndef MORIIISM_MITOOL_MIUTIL_MIMKIMG_ENMASK_ARG_MIMKIMG_ENMASK_H_
#define MORIIISM_MITOOL_MIUTIL_MIMKIMG_ENMASK_ARG_MIMKIMG_ENMASK_H_

#include "mi_base.h"

class ArgValMimkimgEnmask : public MiArgBase{
public:
    ArgValMimkimgEnmask() :
        MiArgBase(),
        progname_(""),
        infile_(""),
        cx_(0.0),
        cy_(0.0),
        rad_(0.0),
        outdir_(""),
        outfile_head_("") {}
    ~ArgValMimkimgEnmask(){
        Null();
    }
    void Init(int argc, char* argv[]);
    void Print(FILE* fp) const;

    string GetProgname() const {return progname_;};
    string GetInfile() const {return infile_;};
    double GetCx() const {return cx_;};
    double GetCy() const {return cy_;};
    double GetRad() const {return rad_;};    
    string GetOutdir() const {return outdir_;};
    string GetOutfileHead() const {return outfile_head_;};

private:
    string progname_;
    string infile_;
    double cx_;
    double cy_;
    double rad_;    
    string outdir_;
    string outfile_head_;

    void Null();
    void SetOption(int argc, char* argv[], option* long_options);
    void Usage(FILE* fp) const;
};

#endif // MORIIISM_MITOOL_MIUTIL_MIMKIMG_ENMASK_ARG_MIMKIMG_ENMASK_H_
