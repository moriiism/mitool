#ifndef MORIIISM_MITOOL_MIUTIL_MIFUNC_ARG_DRAW_FUNC_LIST_1D_H_
#define MORIIISM_MITOOL_MIUTIL_MIFUNC_ARG_DRAW_FUNC_LIST_1D_H_

#include "mi_base.h"

class ArgValDrawFuncList1d : public MiArgBase{
public:
    ArgValDrawFuncList1d() :
        MiArgBase(),
        progname_(""),
        func_par_list_(""),
        plot_conf_file_(""),
        outdir_(""),
        outfile_head_(""),
        plotmode_(""),
        printmode_(""),
        root_style_("") {}
    ~ArgValDrawFuncList1d(){
        Null();
    }
    void Init(int argc, char* argv[]);
    void Print(FILE* fp) const;
    
    string GetProgname() const {return progname_;};
    string GetFuncParList() const {return func_par_list_;};
    string GetPlotConfFile() const {return plot_conf_file_;};
    string GetOutdir() const {return outdir_;};
    string GetOutfileHead() const {return outfile_head_;};
    string GetPlotmode() const {return plotmode_;};
    string GetPrintmode() const {return printmode_;};
    string GetRootStyle() const {return root_style_;};

private:
    string progname_;
    string func_par_list_;
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


#endif // MORIIISM_MITOOL_MIUTIL_MIFUNC_ARG_DRAW_FUNC_LIST_1D_H_
