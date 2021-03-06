#ifndef MORIIISM_MITOOL_MIUTIL_MIFUNC_ARG_FIT_FUNC_CSTAT_UNBIN_1D_H_
#define MORIIISM_MITOOL_MIUTIL_MIFUNC_ARG_FIT_FUNC_CSTAT_UNBIN_1D_H_

#include "mi_base.h"

class ArgValFitFuncCstatUnbin1d : public MiArgBase{
public:
    ArgValFitFuncCstatUnbin1d() :
        MiArgBase(),
        progname_(""),
        data_file_(""),
        func_name_(""),
        hist_mask_(""),
        fitpar_(""),
        chi2par_(""),
        chi2cont_par_(""),
        minfcn_name_(""),
        plot_conf_file_(""),
        outdir_(""),
        outfile_head_(""),
        npoint_func_(0),
        plotmode_(""),
        printmode_(""),
        root_style_("") {}
    ~ArgValFitFuncCstatUnbin1d(){
        Null();
    }
    void Init(int argc, char* argv[]);
    void Print(FILE* fp) const;

    string GetProgname() const {return progname_;};
    string GetDataFile() const {return data_file_;};
    string GetFuncName() const {return func_name_;};
    string GetHistMask() const {return hist_mask_;};
    string GetFitpar() const {return fitpar_;};
    string GetChi2par() const {return chi2par_;};
    string GetChi2contPar() const {return chi2cont_par_;};
    string GetMinfcnName() const {return minfcn_name_;};
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
    string func_name_;
    string hist_mask_;
    
    string fitpar_;
    string chi2par_;
    string chi2cont_par_;
    string minfcn_name_;

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

#endif // MORIIISM_MITOOL_MIUTIL_MIFUNC_ARG_FIT_FUNC_CSTAT_UNBIN_1D_H_
