#ifndef MORIIISM_MITOOL_MIUTIL_MINFOLD_ARG_MINFOLD_H_
#define MORIIISM_MITOOL_MIUTIL_MINFOLD_ARG_MINFOLD_H_

#include "mi_base.h"

class ArgValMinfold : public MiArgBase{
public:
    ArgValMinfold() :
        MiArgBase(),
        progname_(""),
        num_(0),
        nfold_(0) {}
    ~ArgValMinfold(){
        Null();
    }
    void Init(int argc, char* argv[]);
    void Print(FILE* fp) const;

    string GetProgname() const {return progname_;};
    long   GetNum()      const {return num_;};
    long   GetNfold()    const {return nfold_;};

private:
    string progname_;
    long   num_;
    long   nfold_;

    void Null();
    void SetOption(int argc, char* argv[], option* long_options);    
    void Usage(FILE* fp) const;
};

#endif // MORIIISM_MITOOL_MIUTIL_MINFOLD_ARG_MINFOLD_H_
