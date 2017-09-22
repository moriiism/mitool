#ifndef MXKWTOOL_MXKWTIMING_TIME_ARG_TCONV_HD1D_H_
#define MXKWTOOL_MXKWTIMING_TIME_ARG_TCONV_HD1D_H_

#include "mxkw_base.h"

class ArgValTconvHd1d : public MxkwArgBase{
public:
    explicit ArgValTconvHd1d(string title = "") :
        MxkwArgBase("ArgValTconvHd1d", title),
        progname_(""),
        lc_hd1d_(""),
        format_(""),
        telescope_in_(""),
        tunit_in_(""),
        telescope_out_(""),
        tunit_out_(""),
        lc_hd1d_out_("") {}
    ~ArgValTconvHd1d(){
        Null();
    }
    void Init(int argc, char* argv[]);
    void Print(FILE* fp) const;

    string GetProgname() const {return progname_;};
    string GetLcHd1d() const {return lc_hd1d_;};
    string GetFormat() const {return format_;};
    string GetTelescopeIn() const {return telescope_in_;};
    string GetTunitIn() const {return tunit_in_;};
    string GetTelescopeOut() const {return telescope_out_;};
    string GetTunitOut() const {return tunit_out_;};
    string GetLcHd1dOut() const {return lc_hd1d_out_;};

private:
    string progname_;
    string lc_hd1d_;
    string format_;
    string telescope_in_;
    string tunit_in_;
    string telescope_out_;
    string tunit_out_;
    string lc_hd1d_out_;
    
    void Null();
    void Usage(FILE* fp) const;
    void SetOption(int argc, char* argv[], option* long_options);
};

#endif // MXKWTOOL_MXKWTIMING_TIME_ARG_TCONV_HD1D_H_
