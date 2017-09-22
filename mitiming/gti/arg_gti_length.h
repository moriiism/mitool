#ifndef MXKWTOOL_MXKWTIMING_GTI_ARG_GTI_LENGTH_H_
#define MXKWTOOL_MXKWTIMING_GTI_ARG_GTI_LENGTH_H_

#include "mxkw_base.h"

class ArgValGtiLength : public MxkwArgBase{
public:
    explicit ArgValGtiLength(string title = "") :
        MxkwArgBase("ArgValGtiLength", title),
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

#endif // MXKWTOOL_MXKWTIMING_GTI_ARG_GTI_LENGTH_H_
