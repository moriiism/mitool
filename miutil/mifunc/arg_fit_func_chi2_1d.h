#ifndef MORIIISM_MITOOL_MIUTIL_MIFUNC_ARG_FIT_FUNC_CHI2_1D_H_
#define MORIIISM_MITOOL_MIUTIL_MIFUNC_ARG_FIT_FUNC_CHI2_1D_H_

#include "mi_base.h"

class ArgValFitFuncChi21d : public MiArgBase{
public:
    ArgValFitFuncChi21d() :
        MiArgBase(),
        progname_(""),
        data_file_(""),
        data_fmt_(""),
        func_name_(""),
        fitpar_(""),
        chi2par_(""),
        chi2cont_par_(""),
        plot_conf_file_(""),
        outdir_(""),
        outfile_head_(""),
        npoint_func_(0),
        plotmode_(""),
        printmode_(""),
        root_style_("") {}
    ~ArgValFitFuncChi21d(){
        Null();
    }
    void Init(int argc, char* argv[]);
    void Print(FILE* fp) const;

    string GetProgname() const {return progname_;};
    string GetDataFile() const {return data_file_;};
    string GetDataFmt() const {return data_fmt_;};
    string GetFuncName() const {return func_name_;};
    
    string GetFitpar() const {return fitpar_;};
    string GetChi2par() const {return chi2par_;};
    string GetChi2contPar() const {return chi2cont_par_;};

    string GetPlotConfFile() const {return plot_conf_file_;};
    string GetOutdir() const {return outdir_;};    
    string GetOutfileHead() const {return outfile_head_;};

    int    GetNpointFunc() const {return npoint_func_;};
    string GetPlotmode() const {return plotmode_;};
    string GetPrintmode() const {return printmode_;};
    string GetRootStyle() const {return root_style_;};

private:
    string progname_;
    string data_file_;
    string data_fmt_;
    string func_name_;
    
    string fitpar_;
    string chi2par_;
    string chi2cont_par_;

    string plot_conf_file_;
    string outdir_;
    string outfile_head_;

    int    npoint_func_;
    string plotmode_;
    string printmode_;
    string root_style_;

    void Null();
    void SetOption(int argc, char* argv[], option* long_options);
    void Usage(FILE* fp) const;
};

#endif // MORIIISM_MITOOL_MIUTIL_MIFUNC_ARG_FIT_FUNC_CHI2_1D_H_
