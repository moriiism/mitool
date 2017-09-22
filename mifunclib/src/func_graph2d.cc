#include "mifc_graph2d.h"

//
// function made from GraphData2d
//

void Gd2dFunc::InitSetGd2d(const GraphData2d* const gd2d)
{
    Null();
    gd2d_ = dynamic_cast<GraphData2d*>(gd2d->Clone());
}

void Gd2dFunc::Copy(const Gd2dFunc* const org)
{
    if(this == org) {return;}
    if(NULL == org) {return;}
    
    CopyTitle(org);
    
    InitSetGd2d(org->GetGd2d());
}

Gd2dFunc* const Gd2dFunc::Clone() const
{
    Gd2dFunc* obj_new = new Gd2dFunc;
    obj_new->Copy(this);
    return obj_new;
}


double Gd2dFunc::Eval(const double* const xval,
                      const double* const par) const
{
    double ans = GetGd2d()->GetOvalIntPolLin(xval[0]);
    return ans;
}

void Gd2dFunc::Null()
{
    if(NULL != gd2d_){delete gd2d_; gd2d_ = NULL;}
}
