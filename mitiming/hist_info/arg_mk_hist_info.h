#ifndef MORIIISM_MITOOL_MITIMING_HIST_INFO_ARG_MK_HIST_INFO_H_
#define MORIIISM_MITOOL_MITIMING_HIST_INFO_ARG_MK_HIST_INFO_H_

#include "mi_base.h"

class ArgValMkHistInfo : public MiArgBase{
public:
    ArgValMkHistInfo() :
        MiArgBase(),
        progname_(""),
        start_mjd_(0.0),
        end_mjd_(0.0),
        delta_time_(0.0),
        delta_time_unit_(""),
        telescope_out_(""),
        tunit_out_(""),
        hist_info_out_("") {}
    ~ArgValMkHistInfo(){
        Null();
    }
    void Init(int argc, char* argv[]);
    void Print(FILE* fp) const;

    string GetProgname() const {return progname_;};
    double GetStartMjd() const {return start_mjd_;};
    double GetEndMjd() const {return end_mjd_;};
    double GetDeltaTime() const {return delta_time_;};
    string GetDeltaTimeUnit() const {return delta_time_unit_;};
    string GetTelescopeOut() const {return telescope_out_;};
    string GetTunitOut() const {return tunit_out_;};
    string GetHistInfoOut() const {return hist_info_out_;};
  
private:
    string progname_;
    double start_mjd_;
    double end_mjd_;
    double delta_time_;
    string delta_time_unit_;
    string telescope_out_;
    string tunit_out_;
    string hist_info_out_;

    void Null();
    void Usage(FILE* fp) const;
    void SetOption(int argc, char* argv[], option* long_options);
};

#endif // MORIIISM_MITOOL_MITIMING_HIST_INFO_ARG_MK_HIST_INFO_H_
