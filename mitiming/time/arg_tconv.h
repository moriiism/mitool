#ifndef MXKWTOOL_MXKWTIMING_TIME_ARG_TCONV_H_
#define MXKWTOOL_MXKWTIMING_TIME_ARG_TCONV_H_

#include "mxkw_base.h"

class ArgValTconv : public MxkwArgBase{
public:
    explicit ArgValTconv(string title = "") :
        MxkwArgBase("ArgValTconv", title),
        progname_(""),
        time_(0.0),
        telescope_in_(""),
        tunit_in_(""),
        telescope_out_(""),
        tunit_out_("") {}
    ~ArgValTconv(){
        Null();
    }
    void Init(int argc, char* argv[]);
    void Print(FILE* fp) const;
    
    string GetProgname() const {return progname_;};
    double GetTime() const {return time_;};
    string GetTelescopeIn() const {return telescope_in_;};
    string GetTunitIn() const {return tunit_in_;};
    string GetTelescopeOut() const {return telescope_out_;};
    string GetTunitOut() const {return tunit_out_;};

private:
    string progname_;
    double time_;
    string telescope_in_;
    string tunit_in_;
    string telescope_out_;
    string tunit_out_;

    void Null();
    void Usage(FILE* fp) const;
    void SetOption(int argc, char* argv[], option* long_options);
};


#endif // MXKWTOOL_MXKWTIMING_TIME_ARG_TCONV_H_
