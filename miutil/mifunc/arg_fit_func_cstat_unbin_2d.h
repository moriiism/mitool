#ifndef MORIIISM_MITOOL_MIUTIL_MIFUNC_ARG_FIT_FUNC_CSTAT_UNBIN_2D_H_
#define MORIIISM_MITOOL_MIUTIL_MIFUNC_ARG_FIT_FUNC_CSTAT_UNBIN_2D_H_

#include "mi_base.h"

class ArgValFitFuncCstatUnbin2d : public MiArgBase{
public:
    ArgValFitFuncCstatUnbin2d() :
        MiArgBase(),
        progname_(""),
        data_file_(""),
        func_name_(""),
        hist_mask_(""),
        fitpar_(""),
        chi2par_(""),
        chi2cont_par_(""),
        hist_info_(""),
        minfcn_name_(""),
        plot_conf_projx_file_(""),
        plot_conf_projy_file_(""),        
        outdir_(""),
        outfile_head_(""),
        plotmode_(""),
        printmode_(""),
        root_style_("") {}
    ~ArgValFitFuncCstatUnbin2d(){
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
    string GetHistInfo() const {return hist_info_;};
    string GetMinfcnName() const {return minfcn_name_;};

    string GetPlotConfProjxFile() const {return plot_conf_projx_file_;};
    string GetPlotConfProjyFile() const {return plot_conf_projy_file_;};    
    string GetOutdir() const {return outdir_;};    
    string GetOutfileHead() const {return outfile_head_;};

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
    string hist_info_;
    string minfcn_name_;

    string plot_conf_projx_file_;
    string plot_conf_projy_file_;    
    string outdir_;
    string outfile_head_;

    string plotmode_;
    string printmode_;
    string root_style_;

    void Null();
    void SetOption(int argc, char* argv[], option* long_options);
    void Usage(FILE* fp) const;    
};

#endif // MORIIISM_MITOOL_MIUTIL_MIFUNC_ARG_FIT_FUNC_CSTAT_UNBIN_2D_H_
