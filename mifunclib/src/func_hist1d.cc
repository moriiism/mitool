#include "mifc_hist1d.h"

//
// function made from HistData1d
//

void Hd1dFunc::InitSetHd1d(const HistData1d* const hd1d)
{
    Null();

    hd1d_ = dynamic_cast<HistData1d*>(hd1d->Clone());
}

void Hd1dFunc::Copy(const Hd1dFunc* const org)
{
    if(this == org) {return;}
    if(NULL == org) {return;}
    
    CopyTitle(org);
    InitSetHd1d(org->GetHd1d());
}

Hd1dFunc* const Hd1dFunc::Clone() const
{
    Hd1dFunc* obj_new = new Hd1dFunc;
    obj_new->Copy(this);
    return obj_new;
}


double Hd1dFunc::Eval(const double* const xval,
                      const double* const par) const
{
    double ans = GetHd1d()->GetOvalIntPolLin(xval[0]);
    return ans;
}

void Hd1dFunc::Null()
{
    if(NULL != hd1d_){delete hd1d_; hd1d_ = NULL;}
}


//
// --- Hd1dInvFunc
//

void Hd1dInvFunc::InitSetHd1d(const HistData1d* const hd1d)
{
    Null();
    
    hd1d_ = dynamic_cast<HistData1d*>(hd1d->Clone());
    SetOvalArrSort();
}

void Hd1dInvFunc::Copy(const Hd1dInvFunc* const org)
{
    if(this == org) {return;}
    if(NULL == org) {return;}
    
    CopyTitle(org);
    InitSetHd1d(org->GetHd1d());
}

Hd1dInvFunc* const Hd1dInvFunc::Clone() const
{
    Hd1dInvFunc* obj_new = new Hd1dInvFunc;
    obj_new->Copy(this);
    return obj_new;
}


double Hd1dInvFunc::Eval(const double* const xval,
                         const double* const par) const
{
    int index_near = TMath::BinarySearch(
        GetHd1d()->GetNbinX(),
        GetOvalSortArr(),
        xval[0]);
    double ans = MirMath::IntPolLin(xval[0],
                                     GetHd1d()->GetOvalElm( GetIndexSortArrElm(index_near) ),
                                     GetHd1d()->GetOvalElm( GetIndexSortArrElm(index_near) + 1 ),
                                     GetHd1d()->GetBinCenter( GetIndexSortArrElm(index_near) ),
                                     GetHd1d()->GetBinCenter( GetIndexSortArrElm(index_near) + 1 ));
    return ans;
}

void Hd1dInvFunc::SetOvalArrSort()
{
    index_sort_arr_ = new long [GetHd1d()->GetNbinX()];  // to store sort result
    TMath::Sort(GetHd1d()->GetNbinX(),
                GetHd1d()->GetOvalArr()->GetVal(),
                index_sort_arr_, kFALSE);
    oval_sort_arr_ = new double [GetHd1d()->GetNbinX()];
    for(long idata = 0; idata < GetHd1d()->GetNbinX(); idata ++){
        oval_sort_arr_[idata] = GetHd1d()->GetOvalElm( index_sort_arr_[idata] );
    }

}

void Hd1dInvFunc::Null()
{
    if(NULL != hd1d_){delete hd1d_; hd1d_ = NULL;}
    if(NULL != index_sort_arr_){delete [] index_sort_arr_; index_sort_arr_ = NULL;}
    if(NULL != oval_sort_arr_){delete [] oval_sort_arr_; oval_sort_arr_ = NULL;}
}

