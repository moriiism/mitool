#ifndef MXKWTOOL_MXKWTIMING_EPH_ARG_EPHATT_H_
#define MXKWTOOL_MXKWTIMING_EPH_ARG_EPHATT_H_

#include "mxkw_base.h"

class ArgValEphatt : public MxkwArgBase{
public:
    explicit ArgValEphatt(string title = "") :
        MxkwArgBase("ArgValEphatt", title),
        progname_(""),
        ephfile_in_(""),
        time_mjd_(0.0),
        ephfile_out_("") {}
    ~ArgValEphatt(){
        Null();
    }
    void Init(int argc, char* argv[]);
    void Print(FILE* fp) const;

    string GetEphfileIn() const {return ephfile_in_;};
    double GetTimeMjd() const {return time_mjd_;};
    string GetEphfileOut() const {return ephfile_out_;};
  
private:
    string progname_;
    string ephfile_in_;
    double time_mjd_;
    string ephfile_out_;

    void Null();
    void Usage(FILE* fp) const;
    void SetOption(int argc, char* argv[], option* long_options);
};


#endif // MXKWTOOL_MXKWTIMING_EPH_ARG_EPHATT_H_
