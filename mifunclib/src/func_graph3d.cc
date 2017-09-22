#include "mifc_graph3d.h"

//
// function made from GraphData3d
//

void Gd3dFunc::InitSetGd3d(const GraphData3d* const gd3d)
{
    Null();
    
    gd3d_ = dynamic_cast<GraphData3d*>(gd3d->Clone());
}

void Gd3dFunc::Copy(const Gd3dFunc* const org)
{
    if(this == org) {return;}
    if(NULL == org) {return;}
    
    CopyTitle(org);
    InitSetGd3d(org->GetGd3d());
}

Gd3dFunc* const Gd3dFunc::Clone() const
{
    Gd3dFunc* obj_new = new Gd3dFunc;
    obj_new->Copy(this);
    return obj_new;
}

double Gd3dFunc::Eval(const double* const xval,
                      const double* const par) const
{
    // double ans = GetGd3d()->GetOvalIntPolLin(xval[0], xval[1]);
    printf("Error: not implemented, yet.\n");
    abort();
    double ans = 0.0;
    return ans;
}

void Gd3dFunc::Null()
{
    if(NULL != gd3d_){delete gd3d_; gd3d_ = NULL;}
}
