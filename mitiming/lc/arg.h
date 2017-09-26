#ifndef MORIIISM_MITOOL_MITIMING_LC_ARG_H_
#define MORIIISM_MITOOL_MITIMING_LC_ARG_H_

#include <getopt.h>
#include "mi_base.h"

class ArgValTconv : public MiObject{
public:
    ArgValTconv() :
        MiObject(),
        progname_(""),
        telescope_(""),
        lc_file_(""),
        lc_tunit_(""),
        lc_format_(""),
        telescope_out_(""),
        lc_tunit_out_(""),
        outdir_(""),
        outfile_head_(""){}
    ~ArgValTconv(){}
    int Init(int argc, char* argv[]);
    int Print(FILE* fp) const;
    void Usage(FILE* fp) const;
    void SetOption(int argc, char* argv[], option* long_options);

    string GetProgname() const {return progname_;};
    string GetTelescope() const {return telescope_;};
    string GetLcFile() const {return lc_file_;};
    string GetLcTunit() const {return lc_tunit_;};
    string GetLcFormat() const {return lc_format_;};

    string GetTelescopeOut() const {return telescope_out_;};
    string GetLcTunitOut() const {return lc_tunit_out_;};
    string GetOutdir() const {return outdir_;};
    string GetOutfileHead() const {return outfile_head_;};

private:
    string progname_;
    string telescope_;
    string lc_file_;
    string lc_tunit_;
    string lc_format_;

    string telescope_out_;
    string lc_tunit_out_;
    string outdir_;
    string outfile_head_;
};


class ArgValBinRate2BinCount : public MiObject{
public:
    ArgValBinRate2BinCount() :
        MiObject(),
        progname_(""),
        telescope_(""),
        lc_file_(""),
        lc_tunit_(""),
        lc_format_(""),
        tbinfwidth_str_(""),
        outdir_(""),
        outfile_head_(""){}
    ~ArgValBinRate2BinCount(){}
    int Init(int argc, char* argv[]);
    int Print(FILE* fp) const;
    void Usage(FILE* fp) const;
    void SetOption(int argc, char* argv[], option* long_options);

    string GetProgname() const {return progname_;};
    string GetTelescope() const {return telescope_;};
    string GetLcFile() const {return lc_file_;};
    string GetLcTunit() const {return lc_tunit_;};
    string GetLcFormat() const {return lc_format_;};
    string GetTbinfwidthStr() const {return tbinfwidth_str_;};

    string GetOutdir() const {return outdir_;};
    string GetOutfileHead() const {return outfile_head_;};

private:
    string progname_;
    string telescope_;
    string lc_file_;
    string lc_tunit_;
    string lc_format_;
    string tbinfwidth_str_; // "none" or double
    
    string outdir_;
    string outfile_head_;
};


class ArgValPlotLc : public MiObject{
public:
    ArgValPlotLc() :
        MiObject(),
        progname_(""),
        file_(""),
        telescope_(""),
        tunit_(""),
        format_(""),
        tbinfwidth_str_(""),
        outdir_(""),
        outfile_head_(""){}
    ~ArgValPlotLc(){}
    int Init(int argc, char* argv[]);
    int Print(FILE* fp) const;
    void Usage(FILE* fp) const;
    void SetOption(int argc, char* argv[], option* long_options);

    string GetProgname() const {return progname_;};
    string GetFile() const {return file_;};
    string GetTelescope() const {return telescope_;};
    string GetTunit() const {return tunit_;};
    string GetFormat() const {return format_;};

    string GetTbinfwidthStr() const {return tbinfwidth_str_;};

    string GetOutdir() const {return outdir_;};
    string GetOutfileHead() const {return outfile_head_;};

private:
    string progname_;
    string file_;
    string telescope_;
    string tunit_;
    string format_;
    
    string tbinfwidth_str_;  // "none" or double

    string outdir_;
    string outfile_head_;
};



class ArgValBinning : public MiObject{
public:
    ArgValBinning() :
        MiObject(),
        progname_(""),
        file_(""),
        telescope_(""),
        tunit_(""),
        tbinfwidth_(0.0),
        outdir_(""),
        outfile_head_(""){}
    ~ArgValBinning(){}
    int Init(int argc, char* argv[]);
    int Print(FILE* fp) const;
    void Usage(FILE* fp) const;
    void SetOption(int argc, char* argv[], option* long_options);

    string GetProgname() const {return progname_;};
    string GetFile() const {return file_;};
    string GetTelescope() const {return telescope_;};
    string GetTunit() const {return tunit_;};
    double GetTbinfwidth() const {return tbinfwidth_;};
    string GetOutdir() const {return outdir_;};
    string GetOutfileHead() const {return outfile_head_;};

private:
    string progname_;
    string file_;
    string telescope_;
    string tunit_;
    double tbinfwidth_;
    string outdir_;
    string outfile_head_;
};


class ArgValSplitByGti : public MiObject{
public:
    ArgValSplitByGti() :
        MiObject(),
        progname_(""),
        lc_file_(""),
        lc_telescope_(""),
        lc_tunit_(""),
        lc_format_(""),
        gti_file_(""),
        gti_telescope_(""),
        gti_tunit_(""),
        outdir_(""),
        outfile_head_(""){}
    ~ArgValSplitByGti(){}
    int Init(int argc, char* argv[]);
    int Print(FILE* fp) const;
    void Usage(FILE* fp) const;
    void SetOption(int argc, char* argv[], option* long_options);

    string GetProgname() const {return progname_;};
    string GetLcFile() const {return lc_file_;};
    string GetLcTelescope() const {return lc_telescope_;};
    string GetLcTunit() const {return lc_tunit_;};
    string GetLcFormat() const {return lc_format_;};

    string GetGtiFile() const {return gti_file_;};
    string GetGtiTelescope() const {return gti_telescope_;};
    string GetGtiTunit() const {return gti_tunit_;};

    string GetOutdir() const {return outdir_;};
    string GetOutfileHead() const {return outfile_head_;};

private:
    string progname_;
    string lc_file_;
    string lc_telescope_;
    string lc_tunit_;
    string lc_format_;

    string gti_file_;
    string gti_telescope_;
    string gti_tunit_;

    string outdir_;
    string outfile_head_;
};

#endif // MORIIISM_MITOOL_MITIMING_LC_ARG_H_
