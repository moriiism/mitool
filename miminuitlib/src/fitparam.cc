#include "mim_fitparam.h"

//
// FitParam
//

void FitParam::Null()
{
    npar_ = 0;
    if(NULL != par_name_) {delete [] par_name_; par_name_ = NULL;}
    if(NULL != par_init_)      {delete [] par_init_; par_init_ = NULL;}
    if(NULL != par_serr_init_) {delete [] par_serr_init_; par_serr_init_ = NULL;}
    if(NULL != par_lo_str_) {delete [] par_lo_str_; par_lo_str_ = NULL;}
    if(NULL != par_up_str_) {delete [] par_up_str_; par_up_str_ = NULL;}
    if(NULL != flag_calc_terr_) {delete [] flag_calc_terr_; flag_calc_terr_ = NULL;}
    if(NULL != index_comp_) {delete [] index_comp_; index_comp_ = NULL;}
    if(NULL != par_)      {delete [] par_; par_ = NULL;}
    if(NULL != par_serr_) {delete [] par_serr_; par_serr_ = NULL;}
    if(NULL != par_terr_minus_) {delete [] par_terr_minus_; par_terr_minus_ = NULL;}
    if(NULL != par_terr_plus_) {delete [] par_terr_plus_; par_terr_plus_ = NULL;}
    if(NULL != valid_par_)  {delete [] valid_par_;  valid_par_ = NULL;}
    if(NULL != valid_terr_minus_)  {delete [] valid_terr_minus_;  valid_terr_minus_ = NULL;}
    if(NULL != valid_terr_plus_)  {delete [] valid_terr_plus_;  valid_terr_plus_ = NULL;}
}

void FitParam::Init(int npar)
{
    Null();
    
    npar_ = npar;
    par_name_       = new string [npar_];
    par_init_       = new double [npar_];
    par_serr_init_  = new double [npar_];
    par_lo_str_     = new string [npar_];
    par_up_str_     = new string [npar_];
    flag_calc_terr_ = new int [npar_];
    index_comp_     = new int [npar_];
    par_            = new double [npar_];
    par_serr_       = new double [npar_];
    par_terr_minus_ = new double [npar_];
    par_terr_plus_  = new double [npar_];
    valid_par_        = new int [npar_];
    valid_terr_minus_ = new int [npar_];
    valid_terr_plus_  = new int [npar_];
    
    for(int ipar = 0; ipar < npar_; ipar++){
        par_name_[ipar] = "";
        par_init_[ipar] = 0.0;
        par_serr_init_[ipar] = 0.0;
        par_lo_str_[ipar] = "";
        par_up_str_[ipar] = "";
        flag_calc_terr_[ipar] = 0;
        index_comp_[ipar] = 0;
        par_[ipar] = 0.0;
        par_serr_[ipar] = 0.0;        
        par_terr_minus_[ipar] = 0.0;
        par_terr_plus_[ipar] = 0.0;
        valid_par_[ipar] = 0;
        valid_terr_minus_[ipar] = 0;
        valid_terr_plus_[ipar]  = 0;
    }
    if(0 < g_flag_verbose){
        MPrintInfoClass("done");
    }
}


void FitParam::SetIn(int npar, const string* const par_name,
                     const double* const par_init, const double* const par_serr_init,
                     const string* const par_lo_str, const string* const par_up_str,
                     const int* const flag_calc_terr, const int* const index_comp)
{
    if(npar < 1){
        char msg[kLineSize];
        sprintf(msg, "bad npar(=%d)", npar);
        MPrintErrClass(msg);
        abort();
    }
    if(npar != npar_){
        char msg[kLineSize];
        sprintf(msg, "bad npar(=%d)", npar);
        MPrintErrClass(msg);
        abort();
    }
    for(int ipar = 0; ipar < npar_; ipar++){
        par_name_[ipar]       = par_name[ipar];
        par_init_[ipar]       = par_init[ipar];
        par_serr_init_[ipar]  = par_serr_init[ipar];
        par_lo_str_[ipar]     = par_lo_str[ipar];
        par_up_str_[ipar]     = par_up_str[ipar];
        flag_calc_terr_[ipar] = flag_calc_terr[ipar];
        index_comp_[ipar]     = index_comp[ipar];
    }
    if(0 < g_flag_verbose){
        MPrintInfoClass("done");
    }
}

void FitParam::SetInElm(int ipar, string par_name,
                        double par_init, double par_serr_init,
                        string par_lo_str, string par_up_str,
                        int flag_calc_terr, int index_comp)
{
    par_name_[ipar] = par_name;
    par_init_[ipar] = par_init;
    par_serr_init_[ipar] = par_serr_init;
    par_lo_str_[ipar]   = par_lo_str;
    par_up_str_[ipar]   = par_up_str;
    flag_calc_terr_[ipar] = flag_calc_terr;
    index_comp_[ipar] = index_comp;

    if(0 < g_flag_verbose){
        MPrintInfoClass("done");        
    }
}


void FitParam::LoadIn(string file)
{
    Null();
    
    string* line_arr = NULL;
    long npar_long = 0;
    MiIolib::GenReadFileSkipComment(file, &line_arr, &npar_long);
    int npar = (int) npar_long;
    Init(npar);
    for(int ipar = 0; ipar < npar; ipar ++){
        int ncolumn = MiStr::GetNcolumn(line_arr[ipar]);
        if(7 != ncolumn){
            MPrintWarnClass("ncolumn != 7");
        }
        istringstream iss(line_arr[ipar]);
        string par_name;
        double par_init, par_serr_init;
        string par_lo_str, par_up_str;
        int flag_calc_terr, index_comp;
        iss >> par_name >> par_init >> par_serr_init
            >> par_lo_str >> par_up_str >> flag_calc_terr >> index_comp;
        SetInElm(ipar, par_name, par_init, par_serr_init,
                 par_lo_str, par_up_str, flag_calc_terr, index_comp);
    }
    MiIolib::DelReadFile(line_arr);
    if(0 < g_flag_verbose){
        MPrintInfoClass("done");        
    }
}

void FitParam::FixPar(int ipar, double par_init)
{
    par_init_[ipar]      = par_init;
    par_serr_init_[ipar] = -1;
}

void FitParam::SetParInit(int npar, const double* const par_init)
{
    if(npar != npar_){
        char msg[kLineSize];
        sprintf(msg, "bad npar(=%d)", npar);
        MPrintErrClass(msg);
        abort();
    }
    for(int ipar = 0; ipar < npar_; ipar ++){
        par_init_[ipar] = par_init[ipar];
    }
}

void FitParam::SetFlagCalcTerrElm(int ipar, int flag_calc_terr)
{
    flag_calc_terr_[ipar] = flag_calc_terr;
}


//
// set results
//

void FitParam::SetPar(int npar, const double* const par)
{
    if(npar != npar_){
        char msg[kLineSize];
        sprintf(msg, "bad npar(=%d)", npar);
        MPrintErrClass(msg);
        abort();
    }
    for(int ipar = 0; ipar < npar_; ipar ++){
        par_[ipar] = par[ipar];
    }
}


void FitParam::SetParSerr(int npar, const double* const par_serr)
{
    if(npar != npar_){
        char msg[kLineSize];
        sprintf(msg, "bad npar(=%d)", npar);
        MPrintErrClass(msg);
        abort();
    }
    for(int ipar = 0; ipar < npar_; ipar ++){
        par_serr_[ipar] = par_serr[ipar];
    }
}

void FitParam::SetParElm(int ipar, double par)
{
    par_[ipar] = par;
}

void FitParam::SetParSerrElm(int ipar, double par_serr)
{
    par_serr_[ipar] = par_serr;
}

void FitParam::SetParTerrElm(int ipar, double terr_minus, double terr_plus)
{
    par_terr_minus_[ipar] = terr_minus;
    par_terr_plus_[ipar] = terr_plus;
}

void FitParam::SetValidParElm(int ipar, int valid_par)
{
    valid_par_[ipar] = valid_par;
}

void FitParam::SetValidTerrElm(int ipar, int valid_terr_minus, int valid_terr_plus)
{
    valid_terr_minus_[ipar] = valid_terr_minus;
    valid_terr_plus_[ipar]  = valid_terr_plus;
}

void FitParam::SetOut(const FitParam* const fitparam_in,
                      int npar, const double* const par, const double* const par_serr)
{
    if(npar != fitparam_in->GetNpar()){
        char msg[kLineSize];
        sprintf(msg, "bad npar(=%d)", npar);
        MPrintErrClass(msg);
        abort();
    }
    for(int ipar = 0; ipar < npar_; ipar++){
        par_name_[ipar]       = fitparam_in->GetParNameElm(ipar);
        par_init_[ipar]       = fitparam_in->GetParInitElm(ipar);
        par_serr_init_[ipar]  = fitparam_in->GetParSerrInitElm(ipar);
        par_lo_str_[ipar]     = fitparam_in->GetParLoStrElm(ipar);
        par_up_str_[ipar]     = fitparam_in->GetParUpStrElm(ipar);
        flag_calc_terr_[ipar] = fitparam_in->GetFlagCalcTerrElm(ipar);
        index_comp_[ipar]     = fitparam_in->GetIndexCompElm(ipar);
        par_[ipar]            = par[ipar];
        par_serr_[ipar]       = par_serr[ipar];
    }

    if(0 < g_flag_verbose){
        MPrintInfoClass("done.");
    }
}

void FitParam::Copy(const FitParam* const org)
{
    if(this == org) {return;}
    if(NULL == org) {return;}
    
    CopyTitle(org);
    Null();
    
    npar_ = org->npar_;
    par_name_       = new string [npar_];
    par_init_       = new double [npar_];
    par_serr_init_  = new double [npar_];
    par_lo_str_     = new string [npar_];
    par_up_str_     = new string [npar_];
    flag_calc_terr_ = new int [npar_];
    index_comp_     = new int [npar_];
    par_            = new double [npar_];
    par_serr_       = new double [npar_];
    par_terr_minus_ = new double [npar_];
    par_terr_plus_  = new double [npar_];
    valid_par_ = new int [npar_];
    valid_terr_minus_ = new int [npar_];
    valid_terr_plus_  = new int [npar_];

    for(int ipar = 0; ipar < npar_; ipar++){
        par_name_[ipar]       = org->par_name_[ipar];
        par_init_[ipar]       = org->par_init_[ipar];
        par_serr_init_[ipar]  = org->par_serr_init_[ipar];
        par_lo_str_[ipar]     = org->par_lo_str_[ipar];
        par_up_str_[ipar]     = org->par_up_str_[ipar];
        flag_calc_terr_[ipar] = org->flag_calc_terr_[ipar];
        index_comp_[ipar]     = org->index_comp_[ipar];
        par_[ipar]            = org->par_[ipar];
        par_serr_[ipar]       = org->par_serr_[ipar];        
        par_terr_minus_[ipar] = org->par_terr_minus_[ipar];
        par_terr_plus_[ipar]  = org->par_terr_plus_[ipar];
        valid_par_[ipar]      = org->valid_par_[ipar];        
        valid_terr_minus_[ipar] = org->valid_terr_minus_[ipar];
        valid_terr_plus_[ipar]  = org->valid_terr_plus_[ipar];
    }

    if(0 < g_flag_verbose){
        MPrintInfoClass("done.");
    }
}

FitParam* const FitParam::Clone() const
{
    FitParam* obj_new = new FitParam;
    obj_new->Copy(this);
    return obj_new;
}

void FitParam::Print(FILE* fp) const
{
    char prompt[kLineSize];
    sprintf(prompt, "%s::%s: %s:",
            GetClassName().c_str(), __func__, GetTitle().c_str());
    
    fprintf(fp, "%s: npar_ : %d\n", prompt, npar_);
    fprintf(fp, "%s: # ipar   name                par(init)   par_serr(init)   (+terr/-terr)   "
            "[lo up]  valid (+valid/-valid)  index_comp  flag_calc_terr \n", prompt);
    for(int ipar = 0; ipar < npar_; ipar++){
        fprintf(fp, "%s:  "
                "%2.2d: %-20s    %+e ( %+e )      %+e ( %+e )  "
                "( %+e / %+e )   "
                "[ %7s  %7s ]  %d   ( %d / %d )  %d  %d \n",
                prompt,
                ipar, par_name_[ipar].c_str(),
                par_[ipar], par_init_[ipar],
                par_serr_[ipar], par_serr_init_[ipar],
                par_terr_plus_[ipar], par_terr_minus_[ipar],
                par_lo_str_[ipar].c_str(), par_up_str_[ipar].c_str(),
                valid_par_[ipar], valid_terr_plus_[ipar], valid_terr_minus_[ipar], 
                index_comp_[ipar],                
                flag_calc_terr_[ipar]);
    }
}

int FitParam::GetNparFree() const
{
    int npar_fix = 0;
    for(int ipar = 0; ipar < npar_; ipar ++){
        if(par_serr_init_[ipar] < 0){
            npar_fix ++;
        }
    }
    int npar_free = npar_ - npar_fix;
    return npar_free;
}

int FitParam::IsCalcTerr() const
{
    int flag = 0;
    for(int ipar = 0; ipar < npar_; ipar ++){
        if(0 < flag_calc_terr_[ipar]){
            flag = 1;
            break;
        }
    }
    return flag;
}


void FitParam::CopyPar(const FitParam* const fitparam, TF1* const tf1)
{
    // check number of parameters
    if(fitparam->GetNpar() != tf1->GetNpar()){
        MPrintErr("different npar");
        abort();
    }
    for(int ipar = 0; ipar < fitparam->GetNpar(); ipar++){
        tf1->SetParName(ipar, fitparam->GetParNameElm(ipar).c_str());
        if(fitparam->GetParSerrInitElm(ipar) < 0){
            tf1->SetParameter(ipar, fitparam->GetParInitElm(ipar));
            tf1->FixParameter(ipar, fitparam->GetParInitElm(ipar));
        } else {
            tf1->SetParameter(ipar, fitparam->GetParElm(ipar));
            tf1->SetParError(ipar, fitparam->GetParSerrElm(ipar));
            if("none" != fitparam->GetParLoStrElm(ipar) &&
               "none" != fitparam->GetParUpStrElm(ipar) ){
                double par_lo = atof(fitparam->GetParLoStrElm(ipar).c_str());
                double par_up = atof(fitparam->GetParUpStrElm(ipar).c_str());
                tf1->SetParLimits(ipar, par_lo, par_up);
            }
        }
    }
}


MirFuncPar* const FitParam::GenFuncPar() const
{
    MirFuncPar* func_par = new MirFuncPar;
    func_par->InitSet(GetNpar(), GetParName(), GetPar());
    return func_par;
}


MirFuncPar* const FitParam::GenFuncParInit() const
{
    MirFuncPar* func_par = new MirFuncPar;
    func_par->InitSet(GetNpar(), GetParName(), GetParInit());
    return func_par;
}

int FitParam::GetIndexByName(string name) const
{
    int index_find = -1;
    int flag_find = 0;
    for(int ipar = 0; ipar < GetNpar(); ipar++){
        if(name == GetParNameElm(ipar)){
            index_find = ipar;
            flag_find = 1;
        }
    }
    if(0 == flag_find){
        char msg[kLineSize];
        sprintf(msg, "%s cannot be found.", name.c_str());
        MPrintErrClass(msg);
        abort();
    }
    return index_find;
}
