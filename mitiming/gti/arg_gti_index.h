#ifndef MORIIISM_MITOOL_MITIMING_GTI_ARG_GTI_INDEX_H_
#define MORIIISM_MITOOL_MITIMING_GTI_ARG_GTI_INDEX_H_

#include "mi_base.h"

class ArgValGtiIndex : public MiArgBase{
public:
    ArgValGtiIndex() :
        MiArgBase(),
        progname_(""),
        gti_(""),
        time_(0.0) {}
    ~ArgValGtiIndex(){
        Null();
    }
    void Init(int argc, char* argv[]);
    void Print(FILE* fp) const;

    string GetProgname() const {return progname_;};
    string GetGti() const {return gti_;};
    double GetTime() const {return time_;};

private:
    string progname_;
    string gti_;
    double time_;
    
    void Null();
    void Usage(FILE* fp) const;
    void SetOption(int argc, char* argv[], option* long_options);
};

#endif // MORIIISM_MITOOL_MITIMING_GTI_ARG_GTI_INDEX_H_
