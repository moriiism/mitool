#ifndef MXKWTOOL_MXKWTIMING_GTI_ARG_GTI_TCONV_H_
#define MXKWTOOL_MXKWTIMING_GTI_ARG_GTI_TCONV_H_

#include "mxkw_base.h"

class ArgValGtiTconv : public MxkwArgBase{
public:
    explicit ArgValGtiTconv(string title = "") :
        MxkwArgBase("ArgValGtiTconv", title),
        progname_(""),
        gti_in_(""),
        telescope_in_(""),
        tunit_in_(""),
        gti_out_(""),
        telescope_out_(""),
        tunit_out_("") {}
    ~ArgValGtiTconv(){
        Null();
    }
    void Init(int argc, char* argv[]);
    void Print(FILE* fp) const;

    string GetProgname() const {return progname_;};
    string GetGtiIn() const {return gti_in_;};
    string GetTelescopeIn() const {return telescope_in_;};
    string GetTunitIn() const {return tunit_in_;};
    string GetGtiOut() const {return gti_out_;};
    string GetTelescopeOut() const {return telescope_out_;};
    string GetTunitOut() const {return tunit_out_;};

private:
    string progname_;
    string gti_in_;
    string telescope_in_;
    string tunit_in_;
    string gti_out_;
    string telescope_out_;
    string tunit_out_;

    void Null();
    void Usage(FILE* fp) const;
    void SetOption(int argc, char* argv[], option* long_options);
};

#endif // MXKWTOOL_MXKWTIMING_GTI_ARG_GTI_TCONV_H_
