#ifndef MXKWTOOL_MXKWTIMING_TIME_ARG_TCONV_GD2D_H_
#define MXKWTOOL_MXKWTIMING_TIME_ARG_TCONV_GD2D_H_

#include "mxkw_base.h"

class ArgValTconvGd2d : public MxkwArgBase{
public:
    explicit ArgValTconvGd2d(string title = "") :
        MxkwArgBase("ArgValTconvGd2d", title),
        progname_(""),
        lc_gd2d_(""),
        format_(""),
        telescope_in_(""),
        tunit_in_(""),
        telescope_out_(""),
        tunit_out_(""),
        lc_gd2d_out_("") {}
    ~ArgValTconvGd2d(){
        Null();
    }
    void Init(int argc, char* argv[]);
    void Print(FILE* fp) const;

    string GetProgname() const {return progname_;};
    string GetLcGd2d() const {return lc_gd2d_;};
    string GetFormat() const {return format_;};
    string GetTelescopeIn() const {return telescope_in_;};
    string GetTunitIn() const {return tunit_in_;};
    string GetTelescopeOut() const {return telescope_out_;};
    string GetTunitOut() const {return tunit_out_;};
    string GetLcGd2dOut() const {return lc_gd2d_out_;};

private:
    string progname_;
    string lc_gd2d_;
    string format_;
    string telescope_in_;
    string tunit_in_;
    string telescope_out_;
    string tunit_out_;
    string lc_gd2d_out_;
    
    void Null();
    void Usage(FILE* fp) const;
    void SetOption(int argc, char* argv[], option* long_options);
};

#endif // MXKWTOOL_MXKWTIMING_TIME_ARG_TCONV_GD2D_H_
