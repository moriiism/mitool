#ifndef MORIIISM_MITOOL_MIUTIL_MIFUNC_ARG_DRAW_FUNC_2D_H_
#define MORIIISM_MITOOL_MIUTIL_MIFUNC_ARG_DRAW_FUNC_2D_H_

#include "mi_base.h"

class ArgValDrawFunc2d : public MiArgBase{
public:
    ArgValDrawFunc2d() :
        MiArgBase(),
        progname_(""),
        func_name_(""),
        par_file_(""),
        plot_conf_projx_file_(""),
        plot_conf_projy_file_(""),
        outdir_(""),
        outfile_head_(""),
        npoint_func_(0),
        plotmode_(""),
        printmode_(""),
        root_style_("") {}
    ~ArgValDrawFunc2d(){
        Null();
    }
    void Init(int argc, char* argv[]);
    void Print(FILE* fp) const;
    
    string GetProgname() const {return progname_;};
    string GetFuncName() const {return func_name_;};
    string GetParFile() const {return par_file_;};
    string GetPlotConfProjxFile() const {return plot_conf_projx_file_;};
    string GetPlotConfProjyFile() const {return plot_conf_projy_file_;};
    string GetOutdir() const {return outdir_;};
    string GetOutfileHead() const {return outfile_head_;};
    int    GetNpointFunc() const {return npoint_func_;};    
    string GetPlotmode() const {return plotmode_;};
    string GetPrintmode() const {return printmode_;};
    string GetRootStyle() const {return root_style_;};

private:
    string progname_;
    string func_name_;
    string par_file_;
    string plot_conf_projx_file_;
    string plot_conf_projy_file_;
    string outdir_;
    string outfile_head_;
    int npoint_func_;
    string plotmode_;
    string printmode_;
    string root_style_;

    void Null();
    void Usage(FILE* fp) const;
    void SetOption(int argc, char* argv[], option* long_options);
};


#endif // MORIIISM_MITOOL_MIUTIL_MIFUNC_ARG_DRAW_FUNC_2D_H_
