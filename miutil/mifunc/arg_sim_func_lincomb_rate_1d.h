#ifndef MORIIISM_MITOOL_MIUTIL_MIFUNC_ARG_SIM_FUNC_LINCOMB_RATE_1D_H_
#define MORIIISM_MITOOL_MIUTIL_MIFUNC_ARG_SIM_FUNC_LINCOMB_RATE_1D_H_

#include "mi_base.h"

class ArgValSimFuncLincombRate1d : public MiArgBase{
public:
    ArgValSimFuncLincombRate1d() :
        MiArgBase(),
        progname_(""),
        func_par_norm_list_(""),
        hist_info_sim_(""),
        hist_info_out_(""),
        outdir_(""),
        outfile_head_(""),
        sim_mode_(""),        
        rand_seed_(0),
        npoint_func_(0) {}
    ~ArgValSimFuncLincombRate1d(){
        Null();
    }
    void Init(int argc, char* argv[]);
    void Print(FILE* fp) const;

    string GetProgname() const {return progname_;};
    string GetFuncParNormList() const {return func_par_norm_list_;};
    string GetHistInfoSim() const {return hist_info_sim_;};
    string GetHistInfoOut() const {return hist_info_out_;};
    string GetOutdir() const {return outdir_;};
    string GetOutfileHead() const {return outfile_head_;};
    string GetSimMode() const {return sim_mode_;};    
    int    GetRandSeed() const {return rand_seed_;};
    int    GetNpointFunc() const {return npoint_func_;};
private:
    string progname_;
    string func_par_norm_list_;
    string hist_info_sim_;
    string hist_info_out_;
    string outdir_;
    string outfile_head_;
    string sim_mode_;    
    int    rand_seed_;
    int    npoint_func_;

    void Null(); 
    void SetOption(int argc, char* argv[], option* long_options);
    void Usage(FILE* fp) const;
};

#endif // MORIIISM_MITOOL_MIUTIL_MIFUNC_ARG_SIM_FUNC_LINCOMB_RATE_1D_H_
