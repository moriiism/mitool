#ifndef MXKWTOOL_MXKWTIMING_MKLC_ARG_H_
#define MXKWTOOL_MXKWTIMING_MKLC_ARG_H_

#include <getopt.h>
#include "mxkw_base.h"

class ArgValMklc : public MxkwObject{
public:
    explicit ArgValMklc(string title = "") :
        MxkwObject("ArgValMklc", title),
        progname_(""),
        func_name_(""),
        func_par_file_(""),
        telescope_(""),
        lc_tunit_(""),
        tbinfwidth_(0.0),
        gti_file_(""),
        ephfile_(""),
        time_mjd_st_(0.0),
        time_mjd_ed_(0.0),
        outdir_(""),
        outfile_head_(""),
        seed_(0),
        plotmode_(""),
        printmode_(""),
        root_style_("") {}
    ~ArgValMklc(){}
    int Init(int argc, char* argv[]);
    int Print(FILE* fp) const;
    void Usage(FILE* fp) const;
    void SetOption(int argc, char* argv[], option* long_options);

    string GetProgname() const {return progname_;};
    string GetFuncName() const {return func_name_;};
    string GetFuncParFile() const {return func_par_file_;};
    string GetTelescope() const {return telescope_;};
    string GetLcTunit() const {return lc_tunit_;};
    double GetTbinfwidth() const {return tbinfwidth_;};
    string GetGtiFile() const {return gti_file_;};
    string GetEphfile() const {return ephfile_;};
    double GetTimeMjdSt() const {return time_mjd_st_;};
    double GetTimeMjdEd() const {return time_mjd_ed_;};
    string GetOutdir() const {return outdir_;};
    string GetOutfileHead() const {return outfile_head_;};
    int    GetSeed() const {return seed_;};

    string GetPlotmode() const {return plotmode_;};
    string GetPrintmode() const {return printmode_;};
    string GetRootStyle() const {return root_style_;};

private:
    string progname_;
    string func_name_;
    string func_par_file_;
    string telescope_;
    string lc_tunit_;
    double tbinfwidth_;
    string gti_file_;
    string ephfile_;
    double time_mjd_st_;
    double time_mjd_ed_;
    string outdir_;
    string outfile_head_;
    int    seed_;

    string plotmode_;
    string printmode_;
    string root_style_;
};


class ArgValMklcMaxi : public MxkwObject{
public:
    explicit ArgValMklcMaxi(string title = "") :
        MxkwObject("ArgValMklcMaxi", title),
        progname_(""),
        func_name_(""),
        func_par_file_(""),
        telescope_(""),
        lc_tunit_(""),
        tbinfwidth_(0.0),
        gti_file_(""),
        ephfile_(""),
        time_mjd_st_(0.0),
        time_mjd_ed_(0.0),
        outdir_(""),
        outfile_head_(""),
        seed_(0),
        plotmode_(""),
        printmode_(""),
        root_style_("") {}
    ~ArgValMklcMaxi(){}
    int Init(int argc, char* argv[]);
    int Print(FILE* fp) const;
    void Usage(FILE* fp) const;
    void SetOption(int argc, char* argv[], option* long_options);

    string GetProgname() const {return progname_;};
    string GetFuncName() const {return func_name_;};
    string GetFuncParFile() const {return func_par_file_;};
    string GetTelescope() const {return telescope_;};
    string GetLcTunit() const {return lc_tunit_;};
    double GetTbinfwidth() const {return tbinfwidth_;};
    string GetGtiFile() const {return gti_file_;};
    string GetEphfile() const {return ephfile_;};
    double GetTimeMjdSt() const {return time_mjd_st_;};
    double GetTimeMjdEd() const {return time_mjd_ed_;};
    string GetOutdir() const {return outdir_;};
    string GetOutfileHead() const {return outfile_head_;};
    int    GetSeed() const {return seed_;};

    string GetPlotmode() const {return plotmode_;};
    string GetPrintmode() const {return printmode_;};
    string GetRootStyle() const {return root_style_;};

private:
    string progname_;
    string func_name_;
    string func_par_file_;
    string telescope_;
    string lc_tunit_;
    double tbinfwidth_;
    string gti_file_;
    string ephfile_;
    double time_mjd_st_;
    double time_mjd_ed_;
    string outdir_;
    string outfile_head_;
    int    seed_;

    string plotmode_;
    string printmode_;
    string root_style_;
};



class ArgValMklcPulsarBinaryMaxi : public MxkwObject{
public:
    explicit ArgValMklcPulsarBinaryMaxi(string title = "") :
        MxkwObject("ArgValMklcPulsarBinaryMaxi", title),
        progname_(""),
        func_name_(""),
        func_par_file_(""),
        telescope_(""),
        lc_tunit_(""),
        tbinfwidth_(0.0),
        gti_file_(""),
        ephfile_(""),
        orbfile_(""),
        time_mjd_st_(0.0),
        time_mjd_ed_(0.0),
        outdir_(""),
        outfile_head_(""),
        seed_(0),
        plotmode_(""),
        printmode_(""),
        root_style_("") {}
    ~ArgValMklcPulsarBinaryMaxi(){}
    int Init(int argc, char* argv[]);
    int Print(FILE* fp) const;
    void Usage(FILE* fp) const;
    void SetOption(int argc, char* argv[], option* long_options);

    string GetProgname() const {return progname_;};
    string GetFuncName() const {return func_name_;};
    string GetFuncParFile() const {return func_par_file_;};
    string GetTelescope() const {return telescope_;};
    string GetLcTunit() const {return lc_tunit_;};
    double GetTbinfwidth() const {return tbinfwidth_;};
    string GetGtiFile() const {return gti_file_;};
    string GetEphfile() const {return ephfile_;};
    string GetOrbfile() const {return orbfile_;};
    double GetTimeMjdSt() const {return time_mjd_st_;};
    double GetTimeMjdEd() const {return time_mjd_ed_;};
    string GetOutdir() const {return outdir_;};
    string GetOutfileHead() const {return outfile_head_;};
    int    GetSeed() const {return seed_;};

    string GetPlotmode() const {return plotmode_;};
    string GetPrintmode() const {return printmode_;};
    string GetRootStyle() const {return root_style_;};

private:
    string progname_;
    string func_name_;
    string func_par_file_;
    string telescope_;
    string lc_tunit_;
    double tbinfwidth_;
    string gti_file_;
    string ephfile_;
    string orbfile_;
    double time_mjd_st_;
    double time_mjd_ed_;
    string outdir_;
    string outfile_head_;
    int    seed_;

    string plotmode_;
    string printmode_;
    string root_style_;
};



#endif // MXKWTOOL_MXKWTIMING_MKLC_ARG_H_
