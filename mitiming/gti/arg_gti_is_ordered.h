#ifndef MORIIISM_MITOOL_MITIMING_GTI_ARG_GTI_IS_ORDERED_H_
#define MORIIISM_MITOOL_MITIMING_GTI_ARG_GTI_IS_ORDERED_H_

#include "mi_base.h"

class ArgValGtiIsOrdered : public MiArgBase{
public:
    ArgValGtiIsOrdered() :
        MiArgBase(),
        progname_(""),
        gti_("") {}
    ~ArgValGtiIsOrdered(){
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

#endif // MORIIISM_MITOOL_MITIMING_GTI_ARG_GTI_IS_ORDERED_H_
