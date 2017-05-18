#ifndef MORIIISM_MITOOL_MIUTIL_MILCINFO_ARG_MILCINFO_H_
#define MORIIISM_MITOOL_MIUTIL_MILCINFO_ARG_MILCINFO_H_

#include "mi_base.h"

class ArgValMilcinfo : public MiArgBase{
public:
    ArgValMilcinfo() :
        MiArgBase(),
        progname_(""),
        infile_(""),
        format_(""),
        hist_info_diff_time_file_(""),
        time_offset_(""),
        outdir_(""),
        outfile_head_("") {}
    ~ArgValMilcinfo(){
        Null();
    }
    void Init(int argc, char* argv[]);
    void Print(FILE* fp) const;

    string GetProgname() const {return progname_;};
    string GetInfile()   const {return infile_;};
    string GetFormat()   const {return format_;};
    string GetHistInfoDiffTimeFile() const {return hist_info_diff_time_file_;};
    string GetTimeOffset() const {return time_offset_;};
    string GetOutdir()   const {return outdir_;};
    string GetOutfileHead()   const {return outfile_head_;};

private:
    string progname_;
    string infile_;
    string format_;
    string hist_info_diff_time_file_;
    string time_offset_;
    string outdir_;
    string outfile_head_;

    void Null();
    void SetOption(int argc, char* argv[], option* long_options);    
    void Usage(FILE* fp) const;
};

#endif // MORIIISM_MITOOL_MIUTIL_MILCINFO_ARG_MILCINFO_H_
