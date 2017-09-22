#ifndef MXKWTOOL_MXKWTIMING_EST_ARG_EST_BY_LC_H_
#define MXKWTOOL_MXKWTIMING_EST_ARG_EST_BY_LC_H_

#include "mxkw_base.h"

class ArgValEstByLc : public MxkwArgBase{
public:
    explicit ArgValEstByLc(string title = "") :
        MxkwArgBase("ArgValEstByLc", title),
        progname_(""),
        lc_file_(""),
        lc_tunit_(""),
        lc_format_("") {}
    ~ArgValEstByLc(){
        Null();
    }
    void Init(int argc, char* argv[]);
    void Print(FILE* fp) const;

    string GetProgname() const {return progname_;};
    string GetLcFile() const {return lc_file_;};
    string GetLcTunit() const {return lc_tunit_;};
    string GetLcFormat() const {return lc_format_;};

private:
    string progname_;
    string lc_file_;
    string lc_tunit_;
    string lc_format_;

    void Null();
    void Usage(FILE* fp) const;
    void SetOption(int argc, char* argv[], option* long_options);
};


#endif // MMXKWTOOL_MXKWTIMING_EST_ARG_EST_BY_LC_H_

