#ifndef MORIIISM_MITOOL_MIUTIL_MIFUNC_ARG_SIM_FUNC_1D_H_
#define MORIIISM_MITOOL_MIUTIL_MIFUNC_ARG_SIM_FUNC_1D_H_

#include "mi_base.h"

class ArgValSimFunc1d : public MiArgBase{
public:
    ArgValSimFunc1d() :
        MiArgBase(),
        progname_(""),
        func_name_(""),
        par_file_(""),
        hist_info_sim_(""),
        outdir_(""),
        outfile_head_(""),
        sim_mode_(""),
        rand_seed_(0),
        npoint_func_(0) {}
    ~ArgValSimFunc1d(){
        Null();
    }
    void Init(int argc, char* argv[]);
    void Print(FILE* fp) const;

    string GetProgname() const {return progname_;};
    string GetFuncName() const {return func_name_;};
    string GetParFile() const {return par_file_;};
    string GetHistInfoSim() const {return hist_info_sim_;};
    string GetOutdir() const {return outdir_;};
    string GetOutfileHead() const {return outfile_head_;};
    string GetSimMode() const {return sim_mode_;};
    int    GetRandSeed() const {return rand_seed_;};
    int    GetNpointFunc() const {return npoint_func_;};

private:
    string progname_;
    string func_name_;
    string par_file_;
    string hist_info_sim_;
    string outdir_;
    string outfile_head_;
    string sim_mode_;
    int    rand_seed_;
    int    npoint_func_;

    void Null();
    void SetOption(int argc, char* argv[], option* long_options);
    void Usage(FILE* fp) const;    
};

#endif // MORIIISM_MITOOL_MIUTIL_MIFUNC_ARG_SIM_FUNC_1D_H_
