#ifndef MORIIISM_MITOOL_MIUTIL_MISELCOL_ARG_MISELCOL_H_
#define MORIIISM_MITOOL_MIUTIL_MISELCOL_ARG_MISELCOL_H_

#include "mi_base.h"

class ArgValMiselcol : public MiArgBase{
public:
    ArgValMiselcol() :
        MiArgBase(),
        progname_(""),
        infile_(""),
        selcol_(""),
        outfile_("") {}
    ~ArgValMiselcol(){
        Null();
    }
    void Init(int argc, char* argv[]);
    void Print(FILE* fp) const;

    string GetProgname() const {return progname_;};
    string GetInfile()   const {return infile_;};
    string GetSelcol()   const {return selcol_;};
    string GetOutfile()   const {return outfile_;};

private:
    string progname_;
    string infile_;
    string selcol_;
    string outfile_;

    void Null();
    void SetOption(int argc, char* argv[], option* long_options);    
    void Usage(FILE* fp) const;
};

#endif // MORIIISM_MITOOL_MIUTIL_MISELCOL_ARG_MISELCOL_H_
