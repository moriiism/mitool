#include "mifc_hist2d.h"

//
// function made from HistData2d
//

void Hd2dFunc::InitSetHd2d(const HistData2d* const hd2d)
{
    Null();

    hd2d_ = dynamic_cast<HistData2d*>(hd2d->Clone());
}

void Hd2dFunc::Copy(const Hd2dFunc* const org)
{
    if(this == org) {return;}
    if(NULL == org) {return;}
    
    CopyTitle(org);
    CopyMirFunc(org);
    InitSetHd2d(org->GetHd2d());
}

Hd2dFunc* const Hd2dFunc::Clone() const
{
    Hd2dFunc* obj_new = new Hd2dFunc;
    obj_new->Copy(this);
    return obj_new;
}


double Hd2dFunc::Eval(const double* const xval,
                      const double* const par) const
{
    double ans = GetHd2d()->GetOvalIntPolLin(xval[0], xval[1]);
    return ans;
}

void Hd2dFunc::Null()
{
    if(NULL != hd2d_){delete hd2d_; hd2d_ = NULL;}
}
