#ifndef MORIIISM_MITOOL_MITIMING_GTI_ARG_PLOT_GTI_H_
#define MORIIISM_MITOOL_MITIMING_GTI_ARG_PLOT_GTI_H_

#include "mi_base.h"

class ArgValPlotGti : public MiArgBase{
public:
    ArgValPlotGti() :
        MiArgBase(),
        progname_(""),
        gti_file_(""),
        outdir_(""),
        outfile_head_(""),
        offset_tag_(""),
        plotmode_(""),
        printmode_(""),
        root_style_("") {}
    ~ArgValPlotGti(){
        Null();
    }
    void Init(int argc, char* argv[]);
    void Print(FILE* fp) const;

    string GetProgname() const {return progname_;};
    string GetGtiFile() const {return gti_file_;};
    string GetOutdir() const {return outdir_;};
    string GetOutfileHead() const {return outfile_head_;};
    string GetOffsetTag() const {return offset_tag_;};
    string GetPlotmode() const {return plotmode_;};
    string GetPrintmode() const {return printmode_;};
    string GetRootStyle() const {return root_style_;};
private:
    string progname_;
    string gti_file_;
    string outdir_;
    string outfile_head_;
    string offset_tag_;
    string plotmode_;
    string printmode_;
    string root_style_;

    void Null();
    void Usage(FILE* fp) const;
    void SetOption(int argc, char* argv[], option* long_options);
};

#endif // MORIIISM_MITOOL_MITIMING_GTI_ARG_PLOT_GTI_H_
