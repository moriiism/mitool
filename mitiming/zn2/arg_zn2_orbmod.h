#ifndef MXKWTOOL_MXKWTIMING_ZN2_ARG_H_
#define MXKWTOOL_MXKWTIMING_ZN2_ARG_H_

#include <getopt.h>
#include "mxkw_base.h"

class ArgValZn2Graph : public MxkwObject{
public:
    explicit ArgValZn2Graph(string title = "") :
        MxkwObject("ArgValZn2Graph", title),
        progname_(""),
        telescope_(""),
        lc_file_(""),
        lc_tunit_(""),
        lc_format_(""),
        nharmonics_(0),
        epoch_mjd_(0.0),
        search_dat_(""),
        outdir_(""),
        outfile_head_(""),
        plotmode_(""),
        printmode_(""),
        root_style_("") {}
    ~ArgValZn2Graph(){}
    int Init(int argc, char* argv[]);
    int Print(FILE* fp) const;
    void Usage(FILE* fp) const;
    void SetOption(int argc, char* argv[], option* long_options);

    string GetProgname() const {return progname_;};
    string GetTelescope() const {return telescope_;};
    string GetLcFile() const {return lc_file_;};
    string GetLcTunit() const {return lc_tunit_;};
    string GetLcFormat() const {return lc_format_;};

    int GetNharmonics() const {return nharmonics_;};
    double GetEpochMjd() const {return epoch_mjd_;};
    string GetSearchDat() const {return search_dat_;};

    string GetOutdir() const {return outdir_;};
    string GetOutfileHead() const {return outfile_head_;};

    string GetPlotmode() const {return plotmode_;};
    string GetPrintmode() const {return printmode_;};
    string GetRootStyle() const {return root_style_;};

private:
    string progname_;
    string telescope_;
    string lc_file_;
    string lc_tunit_;
    string lc_format_;

    int nharmonics_;
    double epoch_mjd_;
    string search_dat_;
    
    string outdir_;
    string outfile_head_;

    string plotmode_;
    string printmode_;
    string root_style_;
};

class ArgValZn2 : public MxkwObject{
public:
    explicit ArgValZn2(string title = "") :
        MxkwObject("ArgValZn2", title),
        progname_(""),
        telescope_(""),
        lc_file_(""),
        lc_tunit_(""),
        lc_format_(""),
        nharmonics_(0),
        epoch_mjd_(0.0),
        search_dat_(""),
        outdir_(""),
        outfile_head_(""),
        plotmode_(""),
        printmode_(""),
        root_style_("") {}
    ~ArgValZn2(){}
    int Init(int argc, char* argv[]);
    int Print(FILE* fp) const;
    void Usage(FILE* fp) const;
    void SetOption(int argc, char* argv[], option* long_options);

    string GetProgname() const {return progname_;};
    string GetTelescope() const {return telescope_;};
    string GetLcFile() const {return lc_file_;};
    string GetLcTunit() const {return lc_tunit_;};
    string GetLcFormat() const {return lc_format_;};

    int GetNharmonics() const {return nharmonics_;};
    double GetEpochMjd() const {return epoch_mjd_;};
    string GetSearchDat() const {return search_dat_;};

    string GetOutdir() const {return outdir_;};
    string GetOutfileHead() const {return outfile_head_;};

    string GetPlotmode() const {return plotmode_;};
    string GetPrintmode() const {return printmode_;};
    string GetRootStyle() const {return root_style_;};

private:
    string progname_;
    string telescope_;
    string lc_file_;
    string lc_tunit_;
    string lc_format_;

    int nharmonics_;
    double epoch_mjd_;
    string search_dat_;
    
    string outdir_;
    string outfile_head_;

    string plotmode_;
    string printmode_;
    string root_style_;
};



#endif // MXKWTOOL_MXKWTIMING_ZN2_ARG_H_
