#ifndef MORIIISM_MITOOL_MITIMING_EFS_ARG_EFS_H_
#define MORIIISM_MITOOL_MITIMING_EFS_ARG_EFS_H_

#include "mi_base.h"

class ArgValEfs : public MiArgBase{
public:
    ArgValEfs() :
        MiArgBase(),
        progname_(""),
        file_(""),
        telescope_(""),
        tunit_(""),
        format_(""),
        epoch_mjd_(0.0),
        search_dat_(""),
        nbin_(0),
        outdir_(""),
        outfile_head_(""),
        plotmode_(""),
        printmode_(""),
        root_style_("") {}
    ~ArgValEfs(){
        Null();
    }
    void Init(int argc, char* argv[]);
    void Print(FILE* fp) const;

    string GetProgname() const {return progname_;};
    string GetFile() const {return file_;};
    string GetTelescope() const {return telescope_;};
    string GetTunit() const {return tunit_;};
    string GetFormat() const {return format_;};
    
    double GetEpochMjd() const {return epoch_mjd_;};
    string GetSearchDat() const {return search_dat_;};
    int GetNbin() const {return nbin_;};    
    
    string GetOutdir() const {return outdir_;};
    string GetOutfileHead() const {return outfile_head_;};

    string GetPlotmode() const {return plotmode_;};
    string GetPrintmode() const {return printmode_;};
    string GetRootStyle() const {return root_style_;};

private:
    string progname_;
    string file_;
    string telescope_;
    string tunit_;
    string format_;

    double epoch_mjd_;
    string search_dat_;
    int nbin_;
    
    string outdir_;
    string outfile_head_;

    string plotmode_;
    string printmode_;
    string root_style_;

    void Null();
    void Usage(FILE* fp) const;
    void SetOption(int argc, char* argv[], option* long_options);
};

#endif // MORIIISM_MITOOL_MITIMING_EFS_ARG_EFS_H_
