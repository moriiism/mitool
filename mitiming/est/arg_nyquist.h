#ifndef MORIIISM_MITOOL_MITIMING_EST_ARG_NYQUIST_H_
#define MORIIISM_MITOOL_MITIMING_EST_ARG_NYQUIST_H_

#include "mi_base.h"

class ArgValNyquist : public MiArgBase{
public:
    ArgValNyquist() :
        MiArgBase(),
        progname_(""),
        delta_time_(0.0) {}
    ~ArgValNyquist(){
        Null();
    }
    void Init(int argc, char* argv[]);
    void Print(FILE* fp) const;

    string GetProgname() const {return progname_;};
    double GetDeltaTime() const {return delta_time_;};

private:
    string progname_;
    double delta_time_;

    void Null();
    void Usage(FILE* fp) const;
    void SetOption(int argc, char* argv[], option* long_options);
};


#endif // MORIIISM_MITOOL_MITIMING_EST_ARG_NYQUIST_H_
