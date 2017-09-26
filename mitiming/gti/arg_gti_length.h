#ifndef MORIIISM_MITOOL_MITIMING_GTI_ARG_GTI_LENGTH_H_
#define MORIIISM_MITOOL_MITIMING_GTI_ARG_GTI_LENGTH_H_

#include "mi_base.h"

class ArgValGtiLength : public MiArgBase{
public:
    ArgValGtiLength() :
        MiArgBase(),
        progname_(""),
        gti_("") {}
    ~ArgValGtiLength(){
        Null();
    }
    void Init(int argc, char* argv[]);
    void Print(FILE* fp) const;

    string GetProgname() const {return progname_;};
    string GetGti() const {return gti_;};

private:
    string progname_;
    string gti_;

    void Null();
    void Usage(FILE* fp) const;
    void SetOption(int argc, char* argv[], option* long_options);
};

#endif // MORIIISM_MITOOL_MITIMING_GTI_ARG_GTI_LENGTH_H_
