#include "mir_func_par.h"

// public

void MirFuncPar::Init(int npar)
{
    Null();
    
    npar_ = npar;
    par_name_ = new string [npar];
    par_      = new double [npar];
}

void MirFuncPar::Set(int npar,
                      const string* const par_name,
                      const double* const par)
{
    if(npar_ != npar){
        abort();
    }
    for(int ipar = 0; ipar < npar; ipar++){
        par_name_[ipar] = par_name[ipar];
        par_[ipar]      = par[ipar];
    }
}

void MirFuncPar::SetElm(int ipar,
                         string par_name,
                         double par)
{
    par_name_[ipar] = par_name;
    par_[ipar] = par;
}

void MirFuncPar::InitSet(int npar,
                          const string* const par_name,
                          const double* const par)
{
    Init(npar);
    Set(npar, par_name, par);
}


void MirFuncPar::Load(string file)
{
    Null();
    
    string* line_arr = NULL;
    long nline = 0;
    MiIolib::GenReadFileSkipComment(file, &line_arr, &nline);
    Init(nline);
    for(long iline = 0; iline < nline; iline ++){
        int ncolumn = MiStr::GetNcolumn(line_arr[iline]);
        if(2 != ncolumn){
            MPrintWarnClass("ncolumn != 2");
        }
        istringstream iss(line_arr[iline]);
        string par_name_tmp;
        double par_tmp;
        iss >> par_name_tmp >> par_tmp;
        SetElm(iline, par_name_tmp, par_tmp);
    }
    MiIolib::DelReadFile(line_arr);
    if(0 < g_flag_verbose){
        MPrintInfoClass("done.");
    }
}


void MirFuncPar::Copy(const MirFuncPar* const org)
{
    if(this == org) {abort();}
    if(NULL == org) {abort();}
    
    CopyTitle(org);
    InitSet(org->GetNpar(),
            org->GetParName(),
            org->GetPar());
}

MirFuncPar* const MirFuncPar::Clone() const
{
    MirFuncPar* obj_new = new MirFuncPar;
    obj_new->Copy(this);
    return obj_new;
}


void MirFuncPar::Print(FILE* fp) const
{
    fprintf(fp, "%s: npar = %d\n",
            GetClassName().c_str(), npar_);
    for(int ipar = 0; ipar < GetNpar(); ipar ++){
        fprintf(fp, "%s: par_name_[%d] = %s\n",
                GetClassName().c_str(),
                ipar, GetParNameElm(ipar).c_str());
        fprintf(fp, "%s: par_[%d]      = %e\n",
                GetClassName().c_str(),
                ipar, GetParElm(ipar));
    }
}

void MirFuncPar::CopyPar(const MirFuncPar* const func_par,
                          TF1* const tf1)
{
    // check number of parameters
    if(func_par->GetNpar() != tf1->GetNpar()){
        char msg[kLineSize];
        sprintf(msg, "func_par->GetNpar()(=%d) != tf1->GetNpar()(=%d)",
                func_par->GetNpar(), tf1->GetNpar());
        MPrintErr(msg);
        abort();
    }
    for(int ipar = 0; ipar < func_par->GetNpar(); ipar++){
        tf1->SetParName(ipar, func_par->GetParNameElm(ipar).c_str());
        tf1->SetParameter(ipar, func_par->GetParElm(ipar));
    }
}

//
// private
//

void MirFuncPar::Null()
{
    npar_ = 0;
    if(NULL != par_name_) {delete [] par_name_; par_name_ = NULL;}
    if(NULL != par_) {delete [] par_; par_ = NULL;}
}
