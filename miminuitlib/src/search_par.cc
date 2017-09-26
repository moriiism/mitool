#include "mim_search_par.h"

//
// public
//

void MimSearchPar::Init(long npar)
{
    Null();
    
    npar_ = npar;
    par_info_ = new HistInfo1d* [npar];
    for(long ipar = 0; ipar < npar; ipar ++){
        par_info_[ipar] = new HistInfo1d;
    }
    if(0 < g_flag_verbose){
        MPrintInfoClass("done.");
    }
}

void MimSearchPar::Load(string file)
{
    Null();

    string* line_arr = NULL;
    long npar = 0;
    MiIolib::GenReadFileSkipComment(file, &line_arr, &npar);
    Init(npar);
    for(long ipar = 0; ipar < npar_; ipar ++){
        HistInfo1d::SetHistInfo(line_arr[ipar], par_info_[ipar]);
    }
    MiIolib::DelReadFile(line_arr);
    if(0 < g_flag_verbose){
        MPrintInfoClass("done.");
    }
}

void MimSearchPar::Copy(const MimSearchPar* const org)
{
    if(this == org) {return;}
    if(NULL == org) {return;}
    
    CopyTitle(org);

    Null();
    Init(org->npar_);
    for(long ipar = 0; ipar < npar_; ipar++){
        par_info_[ipar]->Copy(org->par_info_[ipar]);
    }
    if(0 < g_flag_verbose){
        MPrintInfoClass("done.");
    }
}


MimSearchPar* const MimSearchPar::Clone() const
{
    MimSearchPar* obj_new = new MimSearchPar;
    obj_new->Copy(this);
    return obj_new;
}

void MimSearchPar::Print(FILE* fp) const
{
    fprintf(fp, "npar_ = %ld\n", npar_);
    for(int ipar = 0; ipar < npar_; ipar++){
        par_info_[ipar]->Print(fp);
    }
    if(0 < g_flag_verbose){
        MPrintInfoClass("done.");
    }
}

// private

void MimSearchPar::Null()
{
    if(NULL != par_info_){
        for(int ipar = 0; ipar < npar_; ipar ++){
            {delete par_info_[ipar]; par_info_[ipar] = NULL;}
        }
        delete [] par_info_; par_info_ = NULL;
    }
    npar_ = 0;
}
