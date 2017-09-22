#include "mifc_ctn.h"

//
// MifcCtn
//

//
// public
//

void MifcCtn::InitSet(int id,
                      string name,
                      const MirFunc* const func,
                      const MirFuncPar* const func_par)
{
    Null();

    id_ = id;
    name_ = name;
    func_ = dynamic_cast<MirFunc*>(func->Clone());
    func_par_ = new MirFuncPar;
    func_par_->Copy(func_par);
}

void MifcCtn::Copy(const MifcCtn* const org)
{
    if(this == org) {return;}
    if(NULL == org) {return;}
    
    CopyTitle(org);
    InitSet(org->GetId(),
            org->GetName(),
            org->GetFunc(),
            org->GetFuncPar());
}

MifcCtn* const MifcCtn::Clone() const
{
    MifcCtn* obj_new = new MifcCtn;
    obj_new->Copy(this);
    return obj_new;
}


void MifcCtn::Print(FILE* fp) const
{
    fprintf(fp, "id    = %d\n", id_);
    fprintf(fp, "name_ = %s\n", name_.c_str());
}


//
// private
//

void MifcCtn::Null()
{
    id_ = 0;
    name_ = "";
    if(NULL != func_) {delete func_; func_ = NULL;}
    if(NULL != func_par_) {delete func_par_; func_par_ = NULL;}
}



//
// MifcLincombCtn
//

//
// public
//

void MifcLincombCtn::InitSet(int nfunc,
                             const int* const id_arr,
                             const string* const name_arr,
                             const MirFunc* const* const func_arr,
                             const MirFuncPar* const* const func_par_arr,
                             const double* const coeff_arr)
{
    Null();

    nfunc_ = nfunc;
    id_arr_       = new int [nfunc];
    name_arr_     = new string [nfunc];
    func_arr_     = new MirFunc* [nfunc];
    func_par_arr_ = new MirFuncPar* [nfunc];
    coeff_arr_    = new double [nfunc];
    for(int ifunc = 0; ifunc < nfunc; ifunc ++){
        id_arr_[ifunc] = id_arr[ifunc];
        name_arr_[ifunc] = name_arr[ifunc];
        func_arr_[ifunc] = dynamic_cast<MirFunc*>(func_arr[ifunc]->Clone());
        func_par_arr_[ifunc] = new MirFuncPar;
        func_par_arr_[ifunc]->Copy(func_par_arr[ifunc]);
        coeff_arr_[ifunc] = coeff_arr[ifunc];
    }
}


void MifcLincombCtn::SetCoeffArrElm(int ifunc, double coeff)
{
    coeff_arr_[ifunc] = coeff;
}

void MifcLincombCtn::Copy(const MifcLincombCtn* const org)
{
    if(this == org) {return;}
    if(NULL == org) {return;}
    
    CopyTitle(org);
    InitSet(org->GetNfunc(),
            org->GetIdArr(),
            org->GetNameArr(),
            org->GetFuncArr(),
            org->GetFuncParArr(),
            org->GetCoeffArr());
}

MifcLincombCtn* const MifcLincombCtn::Clone() const
{
    MifcLincombCtn* obj_new = new MifcLincombCtn;
    obj_new->Copy(this);
    return obj_new;
}

void MifcLincombCtn::Print(FILE* fp) const
{
    printf("nfunc = %d\n", GetNfunc());
    for(int ifunc = 0; ifunc < GetNfunc(); ifunc ++){
        printf("func_id: %d , func_name: %s , coeff: %e\n",
               GetIdArrElm(ifunc),
               GetNameArrElm(ifunc).c_str(),
               GetCoeffArrElm(ifunc));
    }
}

LinCombFunc* const MifcLincombCtn::GenFuncLincomb() const
{
    LinCombFunc* func_lincomb = new LinCombFunc;
    func_lincomb->InitSet(GetNfunc(), GetFuncArr());
    return func_lincomb;
}

MirFuncPar* const MifcLincombCtn::GenFuncLincombPar() const
{
    MirFuncPar* func_lincomb_par = new MirFuncPar;
    int npar = LinCombFunc::GetNparTotalLincomb(GetNfunc(), GetFuncArr());
    func_lincomb_par->Init( npar );

    int ipar_tot = 0;
    for(int ifunc = 0; ifunc < GetNfunc(); ifunc ++){
        for(int ipar = 0; ipar < GetFuncParArrElm(ifunc)->GetNpar() ; ipar ++){
            char func_par_name_this[kLineSize];
            sprintf(func_par_name_this, "func%2.2d_%s_%s",
                    GetIdArrElm(ifunc),
                    GetNameArrElm(ifunc).c_str(),
                    GetFuncParArrElm(ifunc)->GetParNameElm(ipar).c_str());
            func_lincomb_par->SetElm(ipar_tot,
                                     func_par_name_this,
                                     GetFuncParArrElm(ifunc)->GetParElm(ipar));
            ipar_tot ++;
        }
    }
    for(int ifunc = 0; ifunc < GetNfunc(); ifunc ++){
        char func_par_name_this[kLineSize];
        sprintf(func_par_name_this, "func%2.2d_%s_coeff",
                GetIdArrElm(ifunc),
                GetNameArrElm(ifunc).c_str());
        func_lincomb_par->SetElm(ipar_tot,
                                 func_par_name_this,
                                 GetCoeffArrElm(ifunc));
        ipar_tot ++;
    }
    return func_lincomb_par;
}


//
// private
//

void MifcLincombCtn::Null()
{
    if(NULL != id_arr_){ delete [] id_arr_; id_arr_ = NULL; }
    if(NULL != name_arr_){ delete [] name_arr_; name_arr_ = NULL; }
    if(NULL != func_arr_){
        for(int ifunc = 0; ifunc < nfunc_; ifunc ++){
            delete func_arr_[ifunc]; func_arr_[ifunc] = NULL;
        }
        delete [] func_arr_; func_arr_ = NULL;
    }
    if(NULL != func_par_arr_){
        for(int ifunc = 0; ifunc < nfunc_; ifunc ++){
            delete func_par_arr_[ifunc]; func_par_arr_[ifunc] = NULL;
        }
        delete [] func_par_arr_; func_par_arr_ = NULL;
    }
    if(NULL != coeff_arr_){ delete [] coeff_arr_; coeff_arr_ = NULL;}

    nfunc_ = 0;

}


