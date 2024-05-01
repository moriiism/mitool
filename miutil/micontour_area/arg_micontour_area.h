#ifndef MORIIISM_MITOOL_MIUTIL_MICONTOUR_AREA_ARG_MICONTOUR_AREA_H_
#define MORIIISM_MITOOL_MIUTIL_MICONTOUR_AREA_ARG_MICONTOUR_AREA_H_

#include "mi_base.h"

class ArgValMicontourArea : public MiArgBase{
public:
    ArgValMicontourArea() :
        MiArgBase(),
        progname_(""),
        nbinx_(0),
        xlo_(0.0),
        xup_(0.0),
        nbiny_(0),
        ylo_(0.0),
        yup_(0.0),
        cont_file_(""),
        outdir_(""),
        outfile_head_("") {}
    ~ArgValMicontourArea(){
        Null();
    }
    void Init(int argc, char* argv[]);
    void Print(FILE* fp) const;

    string GetProgname() const {return progname_;};
    int GetNbinx() const {return nbinx_;};
    double GetXlo() const {return xlo_;};
    double GetXup() const {return xup_;};
    int GetNbiny() const {return nbiny_;};
    double GetYlo() const {return ylo_;};
    double GetYup() const {return yup_;};
    string GetContFile() const {return cont_file_;};
    string GetOutdir() const {return outdir_;};
    string GetOutfileHead() const {return outfile_head_;};

private:
    string progname_;
    int nbinx_;
    double xlo_;
    double xup_;
    int nbiny_;
    double ylo_;
    double yup_;
    string cont_file_;
    string outdir_;
    string outfile_head_;

    void Null();
    void SetOption(int argc, char* argv[], option* long_options);
    void Usage(FILE* fp) const;
};

#endif // MORIIISM_MITOOL_MIUTIL_MICONTOUR_AREA_ARG_MICONTOUR_AREA_H_
