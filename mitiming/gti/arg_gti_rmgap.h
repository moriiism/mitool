#ifndef MORIIISM_MITOOL_MITIMING_GTI_ARG_GTI_RMGAP_H_
#define MORIIISM_MITOOL_MITIMING_GTI_ARG_GTI_RMGAP_H_

#include "mi_base.h"

class ArgValGtiRmGap : public MiArgBase{
public:
    ArgValGtiRmGap() :
        MiArgBase(),
        progname_(""),
        gti_file_(""),
        time_gap_(0.0),
        gtiout_(""),
        outdir_(""),
        outfile_head_(""),
        offset_tag_("") {}
    ~ArgValGtiRmGap(){
        Null();
    }
    void Init(int argc, char* argv[]);
    void Print(FILE* fp) const;

    string GetProgname() const {return progname_;};
    string GetGtiFile() const {return gti_file_;};
    double GetTimeGap() const {return time_gap_;};
    string GetGtiOut() const {return gtiout_;};
    string GetOutdir() const {return outdir_;};
    string GetOutfileHead() const {return outfile_head_;};
    string GetOffsetTag() const {return offset_tag_;};
    
private:
    string progname_;
    string gti_file_;
    double time_gap_;
    string gtiout_;
    string outdir_;
    string outfile_head_;
    string offset_tag_;

    void Null();
    void Usage(FILE* fp) const;
    void SetOption(int argc, char* argv[], option* long_options);
};

#endif // MORIIISM_MITOOL_MITIMING_GTI_ARG_GTI_RMGAP_H_
