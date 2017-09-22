#ifndef MXKWTOOL_MXKWTIMING_GTI_ARG_H_
#define MXKWTOOL_MXKWTIMING_GTI_ARG_H_

#include <getopt.h>
#include "mxkw_base.h"

//
// GtiTconv
//

class ArgValGtiTconv : public MxkwArgBase{
public:
    explicit ArgValGtiTconv(string title = "") :
        MxkwArgBase("ArgValGtiTconv", title),
        progname_(""),
        gti_in_(""),
        telescope_in_(""),
        tunit_in_(""),
        gti_out_(""),
        telescope_out_(""),
        tunit_out_("") {}
    ~ArgValGtiTconv(){}
    void Init(int argc, char* argv[]);
    void Print(FILE* fp) const;
    void Usage(FILE* fp) const;
    void SetOption(int argc, char* argv[], option* long_options);

    string GetProgname() const {return progname_;};

    string GetGtiIn() const {return gti_in_;};
    string GetTelescopeIn() const {return telescope_in_;};
    string GetTunitIn() const {return tunit_in_;};

    string GetGtiOut() const {return gti_out_;};
    string GetTelescopeOut() const {return telescope_out_;};
    string GetTunitOut() const {return tunit_out_;};

private:
    string progname_;
    string gti_in_;
    string telescope_in_;
    string tunit_in_;

    string gti_out_;
    string telescope_out_;
    string tunit_out_;
};

//
// GtiSplit
//

class ArgValGtiSplit : public MxkwArgBase{
public:
    explicit ArgValGtiSplit(string title = "") :
        MxkwArgBase("ArgValGtiSplit", title),
        progname_(""),
        tstart_(0.0),
        tstop_(0.0),
        telescope_(""),
        tunit_(""),
        nsplit_(0),
        gti_out_("") {}
    ~ArgValGtiSplit(){}
    int Init(int argc, char* argv[]);
    int Print(FILE* fp) const;
    void Usage(FILE* fp) const;
    void SetOption(int argc, char* argv[], option* long_options);

    string GetProgname() const {return progname_;};
    double GetTstart() const {return tstart_;};
    double GetTstop() const {return tstop_;};
    string GetTelescope() const {return telescope_;};
    string GetTunit() const {return tunit_;};
    long   GetNsplit() const {return nsplit_;};
    string GetGtiOut() const {return gti_out_;};

private:
    string progname_;
    double tstart_;
    double tstop_;
    string telescope_;
    string tunit_;
    long   nsplit_;
    string gti_out_;
};


//
// PlotGti
//

class ArgValPlotGti : public MxkwArgBase{
public:
    explicit ArgValPlotGti(string title = "") :
        MxkwArgBase("ArgValPlotGti", title),
        progname_(""),
        gti_file_(""),
        telescope_(""),
        tunit_(""),
        outdir_(""),
        outfile_head_(""),
        offset_tag_(""),
        plotmode_(""),
        printmode_(""),
        root_style_("") {}
    ~ArgValPlotGti(){}
    int Init(int argc, char* argv[]);
    int Print(FILE* fp) const;
    void Usage(FILE* fp) const;
    void SetOption(int argc, char* argv[], option* long_options);

    string GetProgname() const {return progname_;};
    string GetGtiFile() const {return gti_file_;};
    string GetTelescope() const {return telescope_;};
    string GetTunit() const {return tunit_;};
    string GetOutdir() const {return outdir_;};
    string GetOutfileHead() const {return outfile_head_;};
    string GetOffsetTag() const {return offset_tag_;};
    string GetPlotmode() const {return plotmode_;};
    string GetPrintmode() const {return printmode_;};
    string GetRootStyle() const {return root_style_;};
private:
    string progname_;
    string gti_file_;
    string telescope_;
    string tunit_;

    string outdir_;
    string outfile_head_;
    string offset_tag_;

    string plotmode_;
    string printmode_;
    string root_style_;
};


//
// GtiRmGap
//


class ArgValGtiRmGap : public MxkwArgBase{
public:
    explicit ArgValGtiRmGap(string title = "") :
        MxkwArgBase("ArgValGtiRmGap", title),
        progname_(""),
        gti_file_(""),
        telescope_(""),
        tunit_(""),
        time_gap_(0.0),
        gtiout_(""),
        outdir_(""),
        outfile_head_(""),
        offset_tag_("") {}
    ~ArgValGtiRmGap(){}
    int Init(int argc, char* argv[]);
    int Print(FILE* fp) const;
    void Usage(FILE* fp) const;
    void SetOption(int argc, char* argv[], option* long_options);

    string GetProgname() const {return progname_;};
    string GetGtiFile() const {return gti_file_;};
    string GetTelescope() const {return telescope_;};
    string GetTunit() const {return tunit_;};
    double GetTimeGap() const {return time_gap_;};
    string GetGtiOut() const {return gtiout_;};
    string GetOutdir() const {return outdir_;};
    string GetOutfileHead() const {return outfile_head_;};
    string GetOffsetTag() const {return offset_tag_;};
    
private:
    string progname_;
    string gti_file_;
    string telescope_;
    string tunit_;
    double time_gap_;
    string gtiout_;
    string outdir_;
    string outfile_head_;
    string offset_tag_;
};


//
// ArgValLcThr
//

class ArgValLcthr : public MxkwArgBase{
public:
    explicit ArgValLcthr(string title = "") :
        MxkwArgBase("ArgValLcthr", title),
        progname_(""),
        file_(""),
        format_(""),
        threshold_(0.0),
        gtiout_(""),
        outdir_(""),
        outfile_head_(""),
        offset_tag_("") {}
    ~ArgValLcthr(){}
    int Init(int argc, char* argv[]);
    int Print(FILE* fp) const;
    void Usage(FILE* fp) const;
    void SetOption(int argc, char* argv[], option* long_options);

    string GetProgname() const {return progname_;};
    string GetFile() const {return file_;};
    string GetFormat() const {return format_;};
    double GetThreshold() const {return threshold_;};
    string GetGtiOut() const {return gtiout_;};
    string GetOutdir() const {return outdir_;};
    string GetOutfileHead() const {return outfile_head_;};
    string GetOffsetTag() const {return offset_tag_;};
  
private:
    string progname_;
    string file_;
    string format_;
    double threshold_;
    string gtiout_;
    string outdir_;
    string outfile_head_;
    string offset_tag_;
};


//
// ArgValLcthrHist
//

class ArgValLcthrHist : public MxkwArgBase{
public:
    explicit ArgValLcthrHist(string title = "") :
        MxkwArgBase("ArgValLcthrHist", title),
        progname_(""),
        file_(""),
        format_(""),
        threshold_(0.0),
        nbin_time_(0),
        time_lo_(0.0),
        time_up_(0.0),
        gtiout_(""),
        outdir_(""),
        outfile_head_(""),
        offset_tag_("") {}
    ~ArgValLcthrHist(){}
    int Init(int argc, char* argv[]);
    int Print(FILE* fp) const;
    void Usage(FILE* fp) const;
    void SetOption(int argc, char* argv[], option* long_options);

    string GetProgname() const {return progname_;};
    string GetFile() const {return file_;};
    string GetFormat() const {return format_;};
    double GetThreshold() const {return threshold_;};
    long   GetNbinTime() const {return nbin_time_;};
    double GetTimeLo() const {return time_lo_;};
    double GetTimeUp() const {return time_up_;};
    string GetGtiOut() const {return gtiout_;};
    string GetOutdir() const {return outdir_;};
    string GetOutfileHead() const {return outfile_head_;};
    string GetOffsetTag() const {return offset_tag_;};
  
private:
    string progname_;
    string file_;
    string format_;
    double threshold_;
    long   nbin_time_;
    double time_lo_;
    double time_up_;
    string gtiout_;
    string outdir_;
    string outfile_head_;
    string offset_tag_;
};


//
// ArgValAndOrN
//

class ArgValAndOrN : public MxkwArgBase{
public:
    explicit ArgValAndOrN(string title = "") :
        MxkwArgBase("ArgValAndOrN", title),
        progname_(""),
        andor_(""),
        gti_file_list_(""),
        telescope_(""),
        tunit_(""),
        outdir_(""),
        outfile_head_(""),
        offset_tag_("") {}
    ~ArgValAndOrN(){}
    int Init(int argc, char* argv[]);
    int Print(FILE* fp) const;
    void Usage(FILE* fp) const;
    void SetOption(int argc, char* argv[], option* long_options);

    string GetProgname() const {return progname_;};
    string GetAndOr() const {return andor_;};
    string GetGtiFileList() const {return gti_file_list_;};
    string GetTelescope() const {return telescope_;};
    string GetTunit() const {return tunit_;};
    string GetOutdir() const {return outdir_;};
    string GetOutfileHead() const {return outfile_head_;};
    string GetOffsetTag() const {return offset_tag_;};
  
private:
    string progname_;
    string andor_;
    string gti_file_list_;
    string telescope_;
    string tunit_;
    string outdir_;
    string outfile_head_;
    string offset_tag_;
};

//
// ArgValAndOr2
//

class ArgValAndOr2 : public MxkwArgBase{
public:
    explicit ArgValAndOr2(string title = "") :
        MxkwArgBase("ArgValAndOr2", title),
        progname_(""),
        andor_(""),
        gti1_(""),
        gti2_(""),
        telescope_(""),
        tunit_(""),
        outdir_(""),
        outfile_head_(""),
        offset_tag_("") {}
    ~ArgValAndOr2(){}
    int Init(int argc, char* argv[]);
    int Print(FILE* fp) const;
    void Usage(FILE* fp) const;
    void SetOption(int argc, char* argv[], option* long_options);

    string GetProgname() const {return progname_;};
    string GetAndOr() const {return andor_;};
    string GetGti1() const {return gti1_;};
    string GetGti2() const {return gti2_;};
    string GetTelescope() const {return telescope_;};
    string GetTunit() const {return tunit_;};
    string GetOutdir() const {return outdir_;};
    string GetOutfileHead() const {return outfile_head_;};
    string GetOffsetTag() const {return offset_tag_;};
  
private:
    string progname_;
    string andor_;
    string gti1_;
    string gti2_;
    string telescope_;
    string tunit_;
    string outdir_;
    string outfile_head_;
    string offset_tag_;
};


//
//  -------------------------
//


//
//
//class ArgValMkGti : public MxkwArgBase{
//public:
//    explicit ArgValMkGti(string title = "") :
//        MxkwArgBase("ArgValMkGti", title),
//        progname_(""),
//        gti_file_(""),
//        telescope_(""),
//        tunit_(""),
//        outdir_(""),
//        outfile_head_(""),
//        offset_tag_(""),
//        plotmode_(""),
//        printmode_(""),
//        root_style_("") {}
//    ~ArgValMkGti(){}
//    int Init(int argc, char* argv[]);
//    int Print(FILE* fp) const;
//    void Usage(FILE* fp) const;
//    void SetOption(int argc, char* argv[], option* long_options);
//
//    string GetProgname() const {return progname_;};
//    string GetGtiFile() const {return gti_file_;};
//    string GetTelescope() const {return telescope_;};
//    string GetTunit() const {return tunit_;};
//    string GetOutdir() const {return outdir_;};
//    string GetOutfileHead() const {return outfile_head_;};
//    string GetOffsetTag() const {return offset_tag_;};
//    string GetPlotmode() const {return plotmode_;};
//    string GetPrintmode() const {return printmode_;};
//    string GetRootStyle() const {return root_style_;};
//private:
//    string progname_;
//    string gti_file_;
//    string telescope_;
//    string tunit_;
//
//    string outdir_;
//    string outfile_head_;
//    string offset_tag_;
//
//    string plotmode_;
//    string printmode_;
//    string root_style_;
//};
//
//
//
//
//
//
//
////
//// obsolete
////
//
//
//class ArgValMergin{
//public:
//    ArgValMergin(){}
//    ~ArgValMergin(){}
//    int Init(int argc, char *argv[]);
//    int Print(FILE *fp) const;
//
//    string GetProgname() const {return progname_;};
//    string GetGtiFile() const {return gti_file_;};
//    string GetTelescope() const {return telescope_;};
//    string GetTunit() const {return tunit_;};
//    double GetTimeMergin() const {return time_mergin_;};
//    string GetGtiOut() const {return gtiout_;};
//    string GetOutdir() const {return outdir_;};
//    string GetOutfileHead() const {return outfile_head_;};
//    string GetOffsetTag() const {return offset_tag_;};
//  
//private:
//    string progname_;
//    string gti_file_;
//    string telescope_;
//    string tunit_;
//    double time_mergin_;
//    string gtiout_;  
//    string outdir_;
//    string outfile_head_;
//    string offset_tag_;
//};
//
//
//class ArgValEph{
//public:
//    ArgValEph(){}
//    ~ArgValEph(){}
//    int Init(int argc, char *argv[]);
//    int Print(FILE *fp) const;
//
//    string GetProgname() const {return progname_;};
//    string GetEphfile() const {return ephfile_;};
//    string GetPhaseGti() const {return phase_gti_;};
//    string GetTelescope() const {return telescope_;};
//    double GetTimeMjdSt() const {return time_mjd_st_;};
//    double GetTimeMjdEd() const {return time_mjd_ed_;};
//    string GetOutfileHead() const {return outfile_head_;};  
//    string GetOutdir() const {return outdir_;};
//    string GetOffsetTag() const {return offset_tag_;};
//
//private:
//    string progname_;
//    string ephfile_;
//    string phase_gti_;
//    string telescope_;
//    double time_mjd_st_;
//    double time_mjd_ed_;
//    string outfile_head_;
//    string outdir_;
//    string offset_tag_;
//};
//


#endif // MXKWTOOL_MXKWTIMING_GTI_ARG_H_
