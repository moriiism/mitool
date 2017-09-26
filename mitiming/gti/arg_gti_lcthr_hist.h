#ifndef MORIIISM_MITOOL_MITIMING_GTI_ARG_GTI_LCTHR_HIST_H_
#define MORIIISM_MITOOL_MITIMING_GTI_ARG_GTI_LCTHR_HIST_H_

#include "mi_base.h"

class ArgValLcthrHist : public MiArgBase{
public:
    ArgValLcthrHist() :
        MiArgBase(),
        progname_(""),
        file_(""),
        format_(""),
        threshold_(0.0),
        hist_info_(""),
        gtiout_(""),
        outdir_(""),
        outfile_head_(""),
        offset_tag_("") {}
    ~ArgValLcthrHist(){
        Null();
    }
    void Init(int argc, char* argv[]);
    void Print(FILE* fp) const;

    string GetProgname() const {return progname_;};
    string GetFile() const {return file_;};
    string GetFormat() const {return format_;};
    double GetThreshold() const {return threshold_;};
    string GetHistInfo() const {return hist_info_;};
    string GetGtiOut() const {return gtiout_;};
    string GetOutdir() const {return outdir_;};
    string GetOutfileHead() const {return outfile_head_;};
    string GetOffsetTag() const {return offset_tag_;};
  
private:
    string progname_;
    string file_;
    string format_;
    double threshold_;
    string hist_info_;
    string gtiout_;
    string outdir_;
    string outfile_head_;
    string offset_tag_;

    void Null();
    void Usage(FILE* fp) const;
    void SetOption(int argc, char* argv[], option* long_options);
};

#endif // MORIIISM_MITOOL_MITIMING_GTI_ARG_GTI_LCTHR_HIST_H_

