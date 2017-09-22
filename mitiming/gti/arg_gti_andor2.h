#ifndef MXKWTOOL_MXKWTIMING_GTI_ARG_GTI_ANDOR2_H_
#define MXKWTOOL_MXKWTIMING_GTI_ARG_GTI_ANDOR2_H_

#include "mxkw_base.h"

class ArgValAndOr2 : public MxkwArgBase{
public:
    explicit ArgValAndOr2(string title = "") :
        MxkwArgBase("ArgValAndOr2", title),
        progname_(""),
        andor_(""),
        gti1_(""),
        gti2_(""),
        outdir_(""),
        outfile_head_(""),
        offset_tag_("") {}
    ~ArgValAndOr2(){
        Null();
    }
    void Init(int argc, char* argv[]);
    void Print(FILE* fp) const;

    string GetProgname() const {return progname_;};
    string GetAndOr() const {return andor_;};
    string GetGti1() const {return gti1_;};
    string GetGti2() const {return gti2_;};
    string GetOutdir() const {return outdir_;};
    string GetOutfileHead() const {return outfile_head_;};
    string GetOffsetTag() const {return offset_tag_;};
  
private:
    string progname_;
    string andor_;
    string gti1_;
    string gti2_;
    string outdir_;
    string outfile_head_;
    string offset_tag_;

    void Null();
    void Usage(FILE* fp) const;
    void SetOption(int argc, char* argv[], option* long_options);
};


#endif // MXKWTOOL_MXKWTIMING_GTI_ARG_GTI_ANDOR2_H_
