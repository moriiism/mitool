#ifndef MORIIISM_MITOOL_MITIMING_BINORB_ARG_T90_TO_TPERI_H_
#define MORIIISM_MITOOL_MITIMING_BINORB_ARG_T90_TO_TPERI_H_

#include "mi_base.h"

class ArgValT90ToTperi : public MiArgBase{
public:
    ArgValT90ToTperi() :
        MiArgBase(),
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

#endif // MORIIISM_MITOOL_MITIMING_BINORB_ARG_T90_TO_TPERI_H_


