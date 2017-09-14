#ifndef MORIIISM_MITOOL_MIUTIL_MILCWIN_ARG_MILCWIN_H_
#define MORIIISM_MITOOL_MIUTIL_MILCWIN_ARG_MILCWIN_H_

#include "mi_base.h"

class ArgValMilcwin : public MiArgBase{
public:
    ArgValMilcwin() :
        MiArgBase(),
        progname_(""),
        infile_(""),
        format_(""),
        time_st_(0.0),
        time_ed_(0.0),
        outdir_(""),
        outfile_head_("") {}
    ~ArgValMilcwin(){
        Null();
    }
    void Init(int argc, char* argv[]);
    void Print(FILE* fp) const;

    string GetProgname() const {return progname_;};
    string GetInfile()   const {return infile_;};
    string GetFormat()   const {return format_;};
    double GetTimeSt()   const {return time_st_;};
    double GetTimeEd()   const {return time_ed_;};
    string GetOutdir()   const {return outdir_;};
    string GetOutfileHead()   const {return outfile_head_;};

private:
    string progname_;
    string infile_;
    string format_;
    double time_st_;
    double time_ed_;
    string outdir_;
    string outfile_head_;

    void Null();
    void SetOption(int argc, char* argv[], option* long_options);    
    void Usage(FILE* fp) const;
};

#endif // MORIIISM_MITOOL_MIUTIL_MILCWIN_ARG_MILCWIN_H_
