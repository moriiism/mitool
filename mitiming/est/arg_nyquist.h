#ifndef MXKWTOOL_MXKWTIMING_EST_ARG_NYQUIST_H_
#define MXKWTOOL_MXKWTIMING_EST_ARG_NYQUIST_H_

#include "mxkw_base.h"

class ArgValNyquist : public MxkwArgBase{
public:
    explicit ArgValNyquist(string title = "") :
        MxkwArgBase("ArgValNyquist", title),
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


#endif // MXKWTOOL_MXKWTIMING_EST_ARG_NYQUIST_H_
