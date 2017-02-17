#ifndef MORIIISM_MITOOL_MIUTIL_MILCINFO_ARG_MILCINFO_H_
#define MORIIISM_MITOOL_MIUTIL_MILCINFO_ARG_MILCINFO_H_

#include "mi_base.h"

class ArgValMilcinfo : public MiArgBase{
public:
    ArgValMilcinfo() :
        MiArgBase(),
        progname_(""),
        infile_("") {}
    ~ArgValMilcinfo(){
        Null();
    }
    void Init(int argc, char* argv[]);
    void Print(FILE* fp) const;

    string GetProgname() const {return progname_;};
    string GetInfile()   const {return infile_;};    

private:
    string progname_;
    string infile_;

    void Null();
    void SetOption(int argc, char* argv[], option* long_options);    
    void Usage(FILE* fp) const;
};

#endif // MORIIISM_MITOOL_MIUTIL_MILCINFO_ARG_MILCINFO_H_
