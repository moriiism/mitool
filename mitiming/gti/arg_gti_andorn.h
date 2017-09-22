#ifndef MXKWTOOL_MXKWTIMING_GTI_ARG_GTI_ANDORN_H_
#define MXKWTOOL_MXKWTIMING_GTI_ARG_GTI_ANDORN_H_

#include "mxkw_base.h"

class ArgValAndOrN : public MxkwArgBase{
public:
    explicit ArgValAndOrN(string title = "") :
        MxkwArgBase("ArgValAndOrN", title),
        progname_(""),
        andor_(""),
        gti_file_list_(""),
        outdir_(""),
        outfile_head_(""),
        offset_tag_("") {}
    ~ArgValAndOrN(){
        Null();
    }
    void Init(int argc, char* argv[]);
    void Print(FILE* fp) const;

    string GetProgname() const {return progname_;};
    string GetAndOr() const {return andor_;};
    string GetGtiFileList() const {return gti_file_list_;};
    string GetOutdir() const {return outdir_;};
    string GetOutfileHead() const {return outfile_head_;};
    string GetOffsetTag() const {return offset_tag_;};
  
private:
    string progname_;
    string andor_;
    string gti_file_list_;
    string outdir_;
    string outfile_head_;
    string offset_tag_;

    void Null();
    void Usage(FILE* fp) const;
    void SetOption(int argc, char* argv[], option* long_options);
};

#endif // MXKWTOOL_MXKWTIMING_GTI_ARG_GTI_ANDORN_H_
