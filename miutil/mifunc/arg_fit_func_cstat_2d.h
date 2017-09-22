#ifndef MORIIISM_MITOOL_MIUTIL_MIFUNC_ARG_FIT_FUNC_CSTAT_2D_H_
#define MORIIISM_MITOOL_MIUTIL_MIFUNC_ARG_FIT_FUNC_CSTAT_2D_H_

#include "mi_base.h"

class ArgValFitFuncCstat2d : public MiArgBase{
public:
    ArgValFitFuncCstat2d() :
        MiArgBase(),
        progname_(""),
        data_file_(""),
        data_fmt_(""),
        func_name_(""),
        fitpar_(""),
        chi2par_(""),
        chi2cont_par_(""),
        minfcn_name_(""),
        plot_conf_projx_file_(""),
        plot_conf_projy_file_(""),        
        outdir_(""),
        outfile_head_(""),
        plotmode_(""),
        printmode_(""),
        root_style_("") {}
    ~ArgValFitFuncCstat2d(){
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
    string data_fmt_;
    string func_name_;
    
    string fitpar_;
    string chi2par_;
    string chi2cont_par_;
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

#endif // MORIIISM_MITOOL_MIUTIL_MIFUNC_ARG_FIT_FUNC_CSTAT_2D_H_
