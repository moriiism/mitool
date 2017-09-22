#include "mifc_functional.h"

//
// ParallelShiftFunc
//

void ParallelShiftFunc::InitSet(const MirFunc* const func_obj)
{
    Null();

    func_obj_ = dynamic_cast<MirFunc*>(func_obj->Clone());
    int ndim = func_obj->GetNdim();
    int npar = func_obj->GetNpar() + ndim + 1;

    SetNdim(ndim);
    SetNpar(npar);
}

void ParallelShiftFunc::Copy(const ParallelShiftFunc* const org)
{
    if(this == org) {return;}
    if(NULL == org) {return;}
    
    CopyTitle(org);
    
    Null();
    func_obj_ = dynamic_cast<MirFunc*>(org->GetFuncObj()->Clone());
}


ParallelShiftFunc* const ParallelShiftFunc::Clone() const
{
    ParallelShiftFunc* obj_new = new ParallelShiftFunc;
    obj_new->Copy(this);
    return obj_new;
}


double ParallelShiftFunc::Eval(const double* const xval,
                               const double* const par) const
{
    double* par_org = new double [GetFuncObj()->GetNpar()];
    double* xval_org = new double [GetNdim()];

    for(int ipar = 0; ipar < GetFuncObj()->GetNpar(); ipar++){
        par_org[ipar] = par[ipar];
    }
  
    for(int idim = 0; idim < GetNdim(); idim++){
        xval_org[idim] = xval[idim] - par[GetFuncObj()->GetNpar() + idim];
    }
  
    double ans = func_obj_->Eval(xval_org, par_org)
        + par[GetFuncObj()->GetNpar() + GetNdim()];
    
    delete [] par_org;
    delete [] xval_org;
    return ans;
}

// private

void ParallelShiftFunc::Null()
{
    if(NULL != func_obj_){delete func_obj_; func_obj_ = NULL;}
}

//
// RotationFunc
//

void RotationFunc::InitSet(const MirFunc* const func_obj)
{
    Null();
    
    func_obj_ = dynamic_cast<MirFunc*>(func_obj->Clone());
    int ndim = func_obj->GetNdim();
    int npar = GetFuncObj()->GetNpar() + 1;

    SetNdim(ndim);
    SetNpar(npar);

    if(2 != GetNdim()){
        char msg[kLineSize];
        sprintf(msg, "bad ndim: %d\n", GetNdim());
        MPrintErrClass(msg);
        abort();
    }
}


void RotationFunc::Copy(const RotationFunc* const org)
{
    if(this == org) {return;}
    if(NULL == org) {return;}
    
    CopyTitle(org);

    Null();
    func_obj_ = dynamic_cast<MirFunc*>(org->GetFuncObj()->Clone());
}


RotationFunc* const RotationFunc::Clone() const
{
    RotationFunc* obj_new = new RotationFunc;
    obj_new->Copy(this);
    return obj_new;
}

double RotationFunc::Eval(const double* const xval,
                          const double* const par) const
{
    double* par_org = new double [GetFuncObj()->GetNpar()];
    double* xval_org = new double [GetNdim()];

    for(int ipar = 0; ipar < GetFuncObj()->GetNpar(); ipar++){
        par_org[ipar] = par[ipar];
    }
    double theta = par[GetFuncObj()->GetNpar()];
  
    xval_org[0] = cos(theta) * xval[0] + sin(theta) * xval[1];
    xval_org[1] = -sin(theta) * xval[0] + cos(theta) * xval[1];
  
    double ans = GetFuncObj()->Eval(xval_org, par_org);
    
    delete [] par_org;
    delete [] xval_org;
    return ans;
}

// private

void RotationFunc::Null()
{
    if(NULL != func_obj_){delete func_obj_; func_obj_ = NULL;}
}


//
// AddFunc
//

void AddFunc::InitSet(const MirFunc* const func_obj1,
                      const MirFunc* const func_obj2)
{
    Null();
    
    func_obj1_ = dynamic_cast<MirFunc*>(func_obj1->Clone());
    func_obj2_ = dynamic_cast<MirFunc*>(func_obj2->Clone());

    if(func_obj1->GetNdim() != func_obj2->GetNdim()){
        char msg[kLineSize];
        sprintf(msg, "ndim of func1(=%d) and func2(=%d) are different.\n",
                func_obj1->GetNdim(), func_obj2->GetNdim());
        MPrintErrClass(msg);
        abort();
    }
    int ndim = func_obj1->GetNdim();
    int npar = func_obj1->GetNpar() + func_obj2->GetNpar();
    SetNdim(ndim);
    SetNpar(npar);
}

void AddFunc::Copy(const AddFunc* const org)
{
    if(this == org) {return;}
    if(NULL == org) {return;}
    
    CopyTitle(org);

    Null();
    func_obj1_ = dynamic_cast<MirFunc*>(org->GetFuncObj1()->Clone());
    func_obj2_ = dynamic_cast<MirFunc*>(org->GetFuncObj2()->Clone());
}

AddFunc* const AddFunc::Clone() const
{
    AddFunc* obj_new = new AddFunc;
    obj_new->Copy(this);
    return obj_new;
}

double AddFunc::Eval(const double* const xval,
                     const double* const par) const
{
    double* par1 = new double [GetFuncObj1()->GetNpar()];
    double* par2 = new double [GetFuncObj2()->GetNpar()];

    for(int ipar = 0; ipar < GetFuncObj1()->GetNpar(); ipar++){
        par1[ipar] = par[ipar];
    }
    for(int ipar = 0; ipar < GetFuncObj2()->GetNpar(); ipar++){
        par2[ipar] = par[ipar + GetFuncObj1()->GetNpar()];
    }
    double ans = GetFuncObj1()->Eval(xval, par1)
        + GetFuncObj2()->Eval(xval, par2);
    delete [] par1;
    delete [] par2;
    return ans;
}

// private

void AddFunc::Null()
{
    if(NULL != func_obj1_) {delete func_obj1_; func_obj1_ = NULL;}
    if(NULL != func_obj2_) {delete func_obj2_; func_obj2_ = NULL;}
}

//
// AddNFunc
//

void AddNFunc::InitSet(int nfunc,
                       const MirFunc* const* const func_obj_arr)
{
    Null();

    nfunc_ = nfunc;
    func_obj_arr_ = new MirFunc* [nfunc];
    for(int ifunc = 0; ifunc < nfunc; ifunc ++){
        func_obj_arr_[ifunc] = dynamic_cast<MirFunc*>(func_obj_arr[ifunc]->Clone());
    }
    int ndim = func_obj_arr_[0]->GetNdim();
    int npar = 0;
    for(int ifunc = 0; ifunc < nfunc; ifunc ++){
        npar += func_obj_arr[ifunc]->GetNpar();
    }
    SetNdim(ndim);
    SetNpar(npar);
}

void AddNFunc::Copy(const AddNFunc* const org)
{
    if(this == org) {return;}
    if(NULL == org) {return;}
    
    CopyTitle(org);

    Null();

    nfunc_ = org->GetNfunc();
    func_obj_arr_ = new MirFunc* [nfunc_];
    for(int ifunc = 0; ifunc < nfunc_; ifunc ++){
        func_obj_arr_[ifunc] = dynamic_cast<MirFunc*>(org->GetFuncObjArrElm(ifunc)->Clone());
    }
}

AddNFunc* const AddNFunc::Clone() const
{
    AddNFunc* obj_new = new AddNFunc;
    obj_new->Copy(this);
    return obj_new;
}

double AddNFunc::Eval(const double* const xval,
                      const double* const par) const
{
    int ipar_tot = 0;
    double** par_arr = new double* [nfunc_];
    for(int ifunc = 0; ifunc < nfunc_; ifunc ++){
        int npar = GetFuncObjArrElm(ifunc)->GetNpar();
        par_arr[ifunc] = new double [npar];
        for(int ipar = 0; ipar < npar; ipar++){
            par_arr[ifunc][ipar] = par[ipar_tot];
            ipar_tot ++;
        }
    }

    printf("debug nfunc_ = %d\n", nfunc_);

    
    double ans = 0.0;
    for(int ifunc = 0; ifunc < nfunc_; ifunc ++){
        ans += GetFuncObjArrElm(ifunc)->Eval(xval, par_arr[ifunc]);

        printf("debug: ans = %e, par_arr[ifunc][0] = %e\n", ans, par_arr[ifunc][0]);
        
    }

    for(int ifunc = 0; ifunc < nfunc_; ifunc ++){
        delete [] par_arr[ifunc];
    }
    delete [] par_arr;
    return ans;
}

// private

void AddNFunc::Null()
{
    if(NULL != func_obj_arr_){
        for(int ifunc = 0; ifunc < nfunc_; ifunc ++){
            delete func_obj_arr_[ifunc];
        }
        delete [] func_obj_arr_;
    }
    nfunc_ = 0;
}


//
// LinCombFunc
//

void LinCombFunc::InitSet(int nfunc,
                          const MirFunc* const* const func_obj_arr)
{
    Null();

    nfunc_ = nfunc;
    func_obj_arr_ = new MirFunc* [nfunc];
    for(int ifunc = 0; ifunc < nfunc; ifunc ++){
        func_obj_arr_[ifunc] = dynamic_cast<MirFunc*>(func_obj_arr[ifunc]->Clone());
    }
    int ndim = func_obj_arr_[0]->GetNdim();
    int npar = GetNparTotalLincomb(nfunc, func_obj_arr);
    
    SetNdim(ndim);
    SetNpar(npar);
}

void LinCombFunc::Copy(const LinCombFunc* const org)
{
    if(this == org) {return;}
    if(NULL == org) {return;}
    
    CopyTitle(org);

    Null();

    nfunc_ = org->GetNfunc();
    func_obj_arr_ = new MirFunc* [nfunc_];
    for(int ifunc = 0; ifunc < nfunc_; ifunc ++){
        func_obj_arr_[ifunc] = dynamic_cast<MirFunc*>(org->GetFuncObjArrElm(ifunc)->Clone());
    }
}

LinCombFunc* const LinCombFunc::Clone() const
{
    LinCombFunc* obj_new = new LinCombFunc;
    obj_new->Copy(this);
    return obj_new;
}

double LinCombFunc::Eval(const double* const xval,
                         const double* const par) const
{
    int ipar_tot = 0;
    double** par_arr = new double* [nfunc_];
    for(int ifunc = 0; ifunc < nfunc_; ifunc ++){
        int npar = GetFuncObjArrElm(ifunc)->GetNpar();
        par_arr[ifunc] = new double [npar];
        for(int ipar = 0; ipar < npar; ipar++){
            par_arr[ifunc][ipar] = par[ipar_tot];
            ipar_tot ++;
        }
    }
    double* norm_arr = new double [nfunc_];
    for(int ifunc = 0; ifunc < nfunc_; ifunc ++){
        norm_arr[ifunc] = par[ipar_tot];
        ipar_tot ++;
    }
    
    double ans = 0.0;
    for(int ifunc = 0; ifunc < nfunc_; ifunc ++){
        ans += norm_arr[ifunc] * GetFuncObjArrElm(ifunc)->Eval(xval, par_arr[ifunc]);
    }
    for(int ifunc = 0; ifunc < nfunc_; ifunc ++){
        delete [] par_arr[ifunc];
    }
    delete [] par_arr;
    delete [] norm_arr;
    return ans;
}

int LinCombFunc::GetNparTotalLincomb(int nfunc, const MirFunc* const* const func_arr)
{
    int npar_total = 0;
    for(int ifunc = 0; ifunc < nfunc; ifunc ++){
        npar_total += func_arr[ifunc]->GetNpar();
    }
    npar_total += nfunc;
    return npar_total;
}

// private

void LinCombFunc::Null()
{
    if(NULL != func_obj_arr_){
        for(int ifunc = 0; ifunc < nfunc_; ifunc ++){
            delete func_obj_arr_[ifunc];
        }
        delete [] func_obj_arr_;
    }
    nfunc_ = 0;
}


