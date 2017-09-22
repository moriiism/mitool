#ifndef MORIIISM_MITOOL_MIUTIL_MIFUNC_ARG_DRAW_SPEC_DATA_H_
#define MORIIISM_MITOOL_MIUTIL_MIFUNC_ARG_DRAW_SPEC_DATA_H_

#include "mi_base.h"

class ArgValDrawSpecData : public MiArgBase{
public:
    ArgValDrawSpecData() :
        MiArgBase(),
        progname_(""),
        data_file_(""),
        data_fmt_(""),
        func_name_(""),
        par_file_(""),
        spec_type_(""),
        plot_conf_file_(""),
        outdir_(""),
        outfile_head_(""),
        plotmode_(""),
        printmode_(""),
        root_style_("") {}
    ~ArgValDrawSpecData(){
        Null();
    }
    void Init(int argc, char* argv[]);
    void Print(FILE* fp) const;
    
    string GetProgname() const {return progname_;};
    string GetDataFile() const {return data_file_;};
    string GetDataFmt() const {return data_fmt_;};
    string GetFuncName() const {return func_name_;};
    string GetParFile() const {return par_file_;};
    string GetSpecType() const {return spec_type_;};    
    string GetPlotConfFile() const {return plot_conf_file_;};
    string GetOutdir() const {return outdir_;};
    string GetOutfileHead() const {return outfile_head_;};
    string GetPlotmode() const {return plotmode_;};
    string GetPrintmode() const {return printmode_;};
    string GetRootStyle() const {return root_style_;};

private:
    string progname_;
    string data_file_;
    string data_fmt_;
    string func_name_;
    string par_file_;
    string spec_type_;
    string plot_conf_file_;
    string outdir_;
    string outfile_head_;
    string plotmode_;
    string printmode_;
    string root_style_;

    void Null();
    void SetOption(int argc, char* argv[], option* long_options);
    void Usage(FILE* fp) const;    
};


#endif // MORIIISM_MITOOL_MIUTIL_MIFUNC_ARG_DRAW_SPEC_DATA_H_
