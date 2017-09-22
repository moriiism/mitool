#ifndef MORIIISM_MITOOL_MITIMING_MKLC_ARG_MKLC_H_
#define MORIIISM_MITOOL_MITIMING_MKLC_ARG_MKLC_H_

#include "mi_base.h"

class ArgValMklc : public MiArgBase{
public:
    ArgValMklc() :
        MiArgBase(),
        progname_(""),
        func_name_(""),
        par_file_(""),
        hist_info_disp_(""),
        telescope_(""),
        tunit_(""),
        ephfile_(""),
        outdir_(""),
        outfile_head_(""),
        delta_time_sim_(0.0),
        rand_seed_(0),
        plotmode_(""),
        printmode_(""),
        root_style_("") {}
    ~ArgValMklc(){
        Null();
    }
    void Init(int argc, char* argv[]);
    void Print(FILE* fp) const;

    string GetProgname() const {return progname_;};
    string GetFuncName() const {return func_name_;};
    string GetParFile() const {return par_file_;};
    string GetHistInfoDisp() const {return hist_info_disp_;};
    string GetTelescope() const {return telescope_;};
    string GetTunit() const {return tunit_;};
    string GetEphfile() const {return ephfile_;};
    string GetOutdir() const {return outdir_;};
    string GetOutfileHead() const {return outfile_head_;};
    double GetDeltaTimeSim() const {return delta_time_sim_;};
    int    GetRandSeed() const {return rand_seed_;};
    string GetPlotmode() const {return plotmode_;};
    string GetPrintmode() const {return printmode_;};
    string GetRootStyle() const {return root_style_;};

private:
    string progname_;
    string func_name_;
    string par_file_;
    string hist_info_disp_;
    string telescope_;
    string tunit_;
    string ephfile_;
    string outdir_;
    string outfile_head_;
    double delta_time_sim_;
    int    rand_seed_;
    string plotmode_;
    string printmode_;
    string root_style_;

    void Null();
    void SetOption(int argc, char* argv[], option* long_options);    
    void Usage(FILE* fp) const;
};

#endif // MORIIISM_MITOOL_MITIMING_MKLC_ARG_MKLC_H_
