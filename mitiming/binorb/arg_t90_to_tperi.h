#ifndef MXKWTOOL_MXKWTIMING_BINORB_ARG_T90_TO_TPERI_H_
#define MXKWTOOL_MXKWTIMING_BINORB_ARG_T90_TO_TPERI_H_

#include "mxkw_base.h"

class ArgValT90ToTperi : public MxkwArgBase{
public:
    explicit ArgValT90ToTperi(string title = "") :
        MxkwArgBase("ArgValT90ToTperi", title),
        progname_(""),
        time_90_(0.0),
        period_(0.0) {}
    ~ArgValT90ToTperi(){
        Null();
    }
    void Init(int argc, char* argv[]);
    void Print(FILE* fp) const;

    string GetProgname() const {return progname_;};
    double GetTime90() const {return time_90_;};
    double GetPeriod() const {return period_;};

private:
    string progname_;
    double time_90_;    // mjd
    double period_;     // day

    void Null();
    void Usage(FILE* fp) const;
    void SetOption(int argc, char* argv[], option* long_options);
};

#endif // MXKWTOOL_MXKWTIMING_BINORB_ARG_T90_TO_TPERI_H_
