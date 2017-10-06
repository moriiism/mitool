#ifndef MORIIISM_MITOOL_MIUTIL_MILCSIM_ARG_MILCSIM_H_
#define MORIIISM_MITOOL_MIUTIL_MILCSIM_ARG_MILCSIM_H_

#include "mi_base.h"

class ArgValMilcsim : public MiArgBase{
public:
    ArgValMilcsim() :
        MiArgBase(),
        progname_(""),
        gti_file_(""),
        hist_info_file_(""),
        trig_func_info_file_(""),
        delta_time_(0.0),
        seed_(0),
        outdir_(""),
        outfile_head_("") {}
    ~ArgValMilcsim(){
        Null();
    }
    void Init(int argc, char* argv[]);
    void Print(FILE* fp) const;

    string GetProgname() const {return progname_;};
    string GetGtiFile()   const {return gti_file_;};
    string GetHistInfoFile()   const {return hist_info_file_;};
    string GetTrigFuncInfoFile()   const {return trig_func_info_file_;};
    double GetDeltaTime() const {return delta_time_;};
    int    GetSeed() const {return seed_;};
    string GetOutdir()   const {return outdir_;};
    string GetOutfileHead()   const {return outfile_head_;};

private:
    string progname_;
    string gti_file_;
    string hist_info_file_;
    string trig_func_info_file_;
    double delta_time_;
    int    seed_;
    string outdir_;
    string outfile_head_;

    void Null();
    void SetOption(int argc, char* argv[], option* long_options);    
    void Usage(FILE* fp) const;
};

#endif // MORIIISM_MITOOL_MIUTIL_MILCSIM_ARG_MILCSIM_H_
