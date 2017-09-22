#ifndef MXKWTOOL_MXKWTIMING_FCS_ARG_FCS_H_
#define MXKWTOOL_MXKWTIMING_FCS_ARG_FCS_H_

#include "mxkw_base.h"

class ArgValFcs : public MxkwArgBase{
public:
    explicit ArgValFcs(string title = "") :
        MxkwArgBase("ArgValFcs", title),
        progname_(""),
        file_(""),
        telescope_(""),
        tunit_(""),
        format_(""),
        tbinfwidth_(0.0),
        outdir_(""),
        outfile_head_(""),
        plotmode_(""),
        printmode_(""),
        root_style_("") {}
    ~ArgValFcs(){
        Null();
    }
    void Init(int argc, char* argv[]);
    void Print(FILE* fp) const;

    string GetProgname() const {return progname_;};
    string GetFile() const {return file_;};
    string GetTelescope() const {return telescope_;};    
    string GetTunit() const {return tunit_;};
    string GetFormat() const {return format_;};
    double GetTbinfwidth() const {return tbinfwidth_;};
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
    double tbinfwidth_;  // in sec
    string outdir_;
    string outfile_head_;
    string plotmode_;
    string printmode_;
    string root_style_;

    void Null();    
    void Usage(FILE* fp) const;
    void SetOption(int argc, char* argv[], option* long_options);
};

#endif // MXKWTOOL_MXKWTIMING_FCS_ARG_FCS_H_
