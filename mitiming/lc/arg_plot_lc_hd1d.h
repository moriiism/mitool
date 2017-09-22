#ifndef MXKWTOOL_MXKWTIMING_LC_ARG_PLOT_LC_HD1D_H_
#define MXKWTOOL_MXKWTIMING_LC_ARG_PLOT_LC_HD1D_H_

#include "mxkw_base.h"

class ArgValPlotLcHd1d : public MxkwArgBase{
public:
    explicit ArgValPlotLcHd1d(string title = "") :
        MxkwArgBase("ArgValPlotLcHd1d", title),
        progname_(""),
        file_in_(""),
        file_out_(""),
        plot_conf_file_(""),
        format_("") {}
    ~ArgValPlotLcHd1d(){
        Null();
    }
    void Init(int argc, char* argv[]);
    void Print(FILE* fp) const;

    string GetProgname() const {return progname_;};
    string GetFileIn() const {return file_in_;};
    string GetFileOut() const {return file_out_;};
    string GetPlotConfFile() const {return plot_conf_file_;};
    string GetFormat() const {return format_;};

private:
    string progname_;
    string file_in_;
    string file_out_;
    string plot_conf_file_;
    string format_;

    void Null();
    void Usage(FILE* fp) const;
    void SetOption(int argc, char* argv[], option* long_options);
};

#endif // MXKWTOOL_MXKWTIMING_LC_ARG_PLOT_LC_HD1D_H_
