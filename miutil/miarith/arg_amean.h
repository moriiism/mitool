#ifndef MORIIISM_MITOOL_MIUTIL_MIARITH_ARG_AMEAN_H_
#define MORIIISM_MITOOL_MIUTIL_MIARITH_ARG_AMEAN_H_

#include "mi_base.h"

class ArgValAmean : public MiArgBase{
public:
    ArgValAmean() :
        MiArgBase(),
        progname_(""),
        infile_(""),
        outfile_("") {}
    ~ArgValAmean(){
        Null();
    }
    void Init(int argc, char* argv[]);
    void Print(FILE* fp) const;

    string GetProgname() const {return progname_;};
    string GetInfile()   const {return infile_;};
    string GetOutfile()   const {return outfile_;};

private:
    string progname_;
    string infile_;
    string outfile_;

    void Null();
    void SetOption(int argc, char* argv[], option* long_options);    
    void Usage(FILE* fp) const;
};

#endif // MORIIISM_MITOOL_MIUTIL_MIARITH_ARG_AMEAN_H_
