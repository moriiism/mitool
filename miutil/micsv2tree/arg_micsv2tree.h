#ifndef MORIIISM_MITOOL_MIUTIL_MICSV2TREE_ARG_MICSV2TREE_H_
#define MORIIISM_MITOOL_MIUTIL_MICSV2TREE_ARG_MICSV2TREE_H_

#include "mi_base.h"

class ArgValMicsv2tree : public MiArgBase{
public:
    ArgValMicsv2tree() :
        MiArgBase(),
        progname_(""),
        infile_(""),
        format_(""),
        outfile_(""),
        delimit_("") {}
    ~ArgValMicsv2tree(){
        Null();
    }
    void Init(int argc, char* argv[]);
    void Print(FILE* fp) const;

    string GetProgname() const {return progname_;};
    string GetInfile()   const {return infile_;};    
    string GetFormat()   const {return format_;};
    string GetOutfile()  const {return outfile_;};
    string GetDelimit()  const {return delimit_;};

private:
    string progname_;
    string infile_;    
    string format_;
    string outfile_;
    string delimit_;

    void Null();
    void SetOption(int argc, char* argv[], option* long_options);    
    void Usage(FILE* fp) const;
};

#endif // MORIIISM_MITOOL_MIUTIL_MICSV2TREE_ARG_MICSV2TREE_H_

