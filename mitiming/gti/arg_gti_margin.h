#ifndef MXKWTOOL_MXKWTIMING_GTI_ARG_GTI_MARGIN_H_
#define MXKWTOOL_MXKWTIMING_GTI_ARG_GTI_MARGIN_H_

#include "mxkw_base.h"

class ArgValMargin : public MxkwArgBase{
public:
    explicit ArgValMargin(string title = "") :
        MxkwArgBase("ArgValMargin", title),
        progname_(""),
        gti_file_(""),
        telescope_(""),
        tunit_(""),
        time_margin_(0.0),
        gtiout_(""),
        outdir_(""),
        outfile_head_(""),
        offset_tag_("") {}
    ~ArgValMargin(){
        Null();
    }
    void Init(int argc, char* argv[]);
    void Print(FILE* fp) const;

    string GetProgname() const {return progname_;};
    string GetGtiFile() const {return gti_file_;};
    string GetTelescope() const {return telescope_;};
    string GetTunit() const {return tunit_;};
    double GetTimeMargin() const {return time_margin_;};
    string GetGtiOut() const {return gtiout_;};
    string GetOutdir() const {return outdir_;};
    string GetOutfileHead() const {return outfile_head_;};
    string GetOffsetTag() const {return offset_tag_;};
  
private:
    string progname_;
    string gti_file_;
    string telescope_;
    string tunit_;
    double time_margin_;
    string gtiout_;  
    string outdir_;
    string outfile_head_;
    string offset_tag_;

    void Null();
    void Usage(FILE* fp) const;
    void SetOption(int argc, char* argv[], option* long_options);
};

#endif // MXKWTOOL_MXKWTIMING_GTI_ARG_GTI_MARGIN_H_

