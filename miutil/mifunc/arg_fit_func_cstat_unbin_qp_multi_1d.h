#ifndef MORIIISM_MITOOL_MIUTIL_MIFUNC_ARG_FIT_FUNC_CSTAT_UNBIN_QP_MULTI_1D_H_
#define MORIIISM_MITOOL_MIUTIL_MIFUNC_ARG_FIT_FUNC_CSTAT_UNBIN_QP_MULTI_1D_H_

#include "mi_base.h"

class ArgValFitFuncCstatUnbinQpMulti1d : public MiArgBase{
public:
    ArgValFitFuncCstatUnbinQpMulti1d() :
        MiArgBase(),
        progname_(""),
        data_file_list_(""),
        func_par_id_list_(""),
        func_id_list_(""),
        tie_coeff_list_(""),
        plot_conf_file_(""),
        outdir_(""),
        outfile_head_(""),
        npoint_func_(0),
        plotmode_(""),
        printmode_(""),
        root_style_("") {}
    ~ArgValFitFuncCstatUnbinQpMulti1d(){
        Null();
    }
    void Init(int argc, char* argv[]);
    void Print(FILE* fp) const;

    string GetProgname() const {return progname_;};
    string GetDataFileList() const {return data_file_list_;};
    string GetFuncParIdList() const {return func_par_id_list_;};
    string GetFuncIdList() const {return func_id_list_;};
    string GetTieCoeffList() const {return tie_coeff_list_;};
    string GetPlotConfFile() const {return plot_conf_file_;};
    string GetOutdir() const {return outdir_;};    
    string GetOutfileHead() const {return outfile_head_;};

    int    GetNpointFunc() const {return npoint_func_;};
    string GetPlotmode() const {return plotmode_;};
    string GetPrintmode() const {return printmode_;};
    string GetRootStyle() const {return root_style_;};

private:
    string progname_;
    string data_file_list_;
    string func_par_id_list_;
    string func_id_list_;
    string tie_coeff_list_;
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

#endif // MORIIISM_MITOOL_MIUTIL_MIFUNC_ARG_FIT_FUNC_CSTAT_UNBIN_QP_MULTI_1D_H_
