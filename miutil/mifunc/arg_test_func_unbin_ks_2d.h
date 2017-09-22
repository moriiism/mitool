#ifndef MORIIISM_MITOOL_MIUTIL_MIFUNC_ARG_TEST_FUNC_UNBIN_KS_1D_H_
#define MORIIISM_MITOOL_MIUTIL_MIFUNC_ARG_TEST_FUNC_UNBIN_KS_1D_H_

#include "mi_base.h"

class ArgValTestFuncUnbinKs1d : public MiArgBase{
public:
    ArgValTestFuncUnbinKs1d() :
        MiArgBase(),
        progname_(""),
        data_file_(""),
        func_name_(""),
        func_par_(""),
        hist_mask_(""),
        plot_conf_file_(""),
        outdir_(""),
        outfile_head_(""),
        npoint_func_(0),
        plotmode_(""),
        printmode_(""),
        root_style_("") {}
    ~ArgValTestFuncUnbinKs1d(){
        Null();
    }
    void Init(int argc, char* argv[]);
    void Print(FILE* fp) const;

    string GetProgname() const {return progname_;};
    string GetDataFile() const {return data_file_;};
    string GetFuncName() const {return func_name_;};
    string GetFuncPar()  const {return func_par_;};
    string GetHistMask() const {return hist_mask_;};
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
    string func_par_;
    string hist_mask_;
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

#endif // MORIIISM_MITOOL_MIUTIL_MIFUNC_ARG_TEST_FUNC_UNBIN_KS_1D_H_
