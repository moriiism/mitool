#ifndef MXKWTOOL_MXKWTIMING_EPH_ARG_MKEPH_H_
#define MXKWTOOL_MXKWTIMING_EPH_ARG_MKEPH_H_

#include "mxkw_base.h"

class ArgValMkEph : public MxkwArgBase{
public:
    explicit ArgValMkEph(string title = "") :
        MxkwArgBase("ArgValMkEph", title),
        progname_(""),
        period_(0.0),
        p_dot_(0.0),
        epoch_mjd_(0.0),
        start_mjd_(0.0),
        end_mjd_(0.0),
        ephfile_out_("") {}
    ~ArgValMkEph(){
        Null();
    }
    void Init(int argc, char* argv[]);
    void Print(FILE* fp) const;

    double GetPeriod() const {return period_;};
    double GetPDot() const {return p_dot_;};
    double GetEpochMjd() const {return epoch_mjd_;};
    double GetStartMjd() const {return start_mjd_;};
    double GetEndMjd() const {return end_mjd_;};
    string GetEphfileOut() const {return ephfile_out_;};
  
private:
    string progname_;
    double period_;
    double p_dot_;
    double epoch_mjd_;
    double start_mjd_;
    double end_mjd_;
    string ephfile_out_;

    void Null();
    void Usage(FILE* fp) const;
    void SetOption(int argc, char* argv[], option* long_options);
};


#endif // MXKWTOOL_MXKWTIMING_EPH_ARG_MKEPH_H_
