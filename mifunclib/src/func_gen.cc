#include "mifc_gen.h"

MirFunc* const MifcGen::GenFunc(string func_name)
{
    MirFunc* func = NULL;

    if(NULL != (func = GenFuncStd(func_name)) ){
        return func;
    }
    if(NULL != (func = GenFuncSpec(func_name)) ){
        return func;
    }
    if(NULL == func){
        char msg[kLineSize];
        sprintf(msg, "func_name (=%s) is not found.",
                func_name.c_str());
        MPrintErr(msg);
        abort();
    }
    return func;
}


MirFunc* const MifcGen::GenFuncStd(string func_name)
{
    MirFunc* func = NULL;
    if("Gauss1dFunc" == func_name){
        func = new Gauss1dFunc;
    } else if("Gauss1dPlusConstFunc" == func_name){
        func = new Gauss1dPlusConstFunc;
    } else if("Gauss1dAsymFunc" == func_name){
        func = new Gauss1dAsymFunc;
    } else if("Gauss2dFuncAtZero" == func_name){
        func = new Gauss2dFuncAtZero;
    } else if("Gauss2dFunc" == func_name){
        func = new Gauss2dFunc;
        dynamic_cast<Gauss2dFunc*>(func)->Init();
        
    } else if("Const1dFunc" == func_name){
        func = new Const1dFunc;
    } else if("Const2dFunc" == func_name){
        func = new Const2dFunc;

    } else if("LinFunc" == func_name){
        func = new LinFunc;
    } else if("LinMidFunc" == func_name){
        func = new LinMidFunc;
    } else if("LinMidSlopeFunc" == func_name){
        func = new LinMidSlopeFunc;
    } else if("LinMidSlopeErrFunc" == func_name){
        func = new LinMidSlopeErrFunc;
    } else if("ParabolaFunc" == func_name){
        func = new ParabolaFunc;
    } else if("PowerlawFunc" == func_name){
        func = new PowerlawFunc;
    } else if("PowerlawPegFunc" == func_name){
        func = new PowerlawPegFunc;
        
    } else {
        func = NULL;
    }
    return func;
}


FuncSpec* const MifcGen::GenFuncSpec(string func_name)
{
    FuncSpec* func = NULL;
    if("BlackbodyFunc" == func_name){
        func = new BlackbodyFunc;
    } else if("StdAccDiskFunc" == func_name){
        func = new StdAccDiskFunc;
    } else if("DustDiskFunc" == func_name){
        func = new DustDiskFunc;
    } else if("DustDiskWangFunc" == func_name){
        func = new DustDiskFunc;
    } else if("PowerlawSpecFunc" == func_name){
        func = new PowerlawSpecFunc;
    } else {
        func = NULL;
    }
    return func;
}

