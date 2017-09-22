#ifndef MXKWTOOL_MXKWTIMING_LC_ARG_PLOT_LC_GD2D_H_
#define MXKWTOOL_MXKWTIMING_LC_ARG_PLOT_LC_GD2D_H_

#include "mxkw_base.h"

class ArgValPlotLcGd2d : public MxkwArgBase{
public:
    explicit ArgValPlotLcGd2d(string title = "") :
        MxkwArgBase("ArgValPlotLcGd2d", title),
        progname_(""),
        file_in_(""),
        format_(""),
        plot_conf_file_(""),
        file_out_("") {}
    ~ArgValPlotLcGd2d(){
        Null();
    }
    void Init(int argc, char* argv[]);
    void Print(FILE* fp) const;

    string GetProgname() const {return progname_;};
    string GetFileIn() const {return file_in_;};
    string GetFormat() const {return format_;};
    string GetPlotConfFile() const {return plot_conf_file_;};
    string GetFileOut() const {return file_out_;};

private:
    string progname_;
    string file_in_;
    string format_;
    string plot_conf_file_;
    string file_out_;

    void Null();
    void Usage(FILE* fp) const;
    void SetOption(int argc, char* argv[], option* long_options);
};

#endif // MXKWTOOL_MXKWTIMING_LC_ARG_PLOT_LC_GD2D_H_
