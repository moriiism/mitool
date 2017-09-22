#include "func_user.h"

MirFunc* const FuncUser::GenFunc(string func_name)
{
    MirFunc* func = NULL;

    if(NULL != (func = MifcGen::GenFuncStd(func_name)) ){
        return func;
    }
    if(NULL != (func = MifcGen::GenFuncSpec(func_name)) ){
        return func;
    }
    if(NULL != (func = GenFuncUser(func_name)) ){
        return func;
    }
    if(NULL == func){
        char msg[kLineSize];
        sprintf(msg, "func_name (=%s) is not found.", func_name.c_str());
        MPrintErr(msg);
        abort();
    }
    return func;
}

//
// You can add your own functions below
//

MirFunc* const FuncUser::GenFuncUser(string func_name)
{
    MirFunc* func = NULL;
    if ("TestFunc" == func_name){
        func = new TestFunc;
    } else {
        func = NULL;
    }
    
    return func;
}

//
// TestFunc
//

void TestFunc::Copy(const TestFunc* const org)
{
    CopyTitle(org);
}

TestFunc* const TestFunc::Clone() const
{
    TestFunc* obj_new = new TestFunc;
    obj_new->Copy(this);
    return obj_new;
}

double TestFunc::Eval(const double* const xval, const double* const par) const
{
    double freq    = xval[0]; // frequency
    double index   = par[0];  // power-law index

    double val = pow(freq, index);
    
    return val;
}

