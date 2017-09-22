#include "mir_func_ope.h"

TF1* const MirFuncOpe::GenTF1(const MirFunc* const func,
                               double x_low, double x_up)
{
    if(1 != func->GetNdim()){
        MPrintErr("1 != func->GetNdim()");
        abort();
    }
    string title;
    if("" == func->GetTitle()){
        title = func->GetClassName();
    } else {
        title = func->GetTitle();
    }
    TF1* tf1 = new TF1(title.c_str(), func, &MirFunc::Eval,
                       x_low, x_up, func->GetNpar(),
                       func->GetClassName().c_str(), "Eval");
    return tf1;
}

TF2* const MirFuncOpe::GenTF2(const MirFunc* const func,
                               double x_low, double x_up,
                               double y_low, double y_up)
{
    if(2 != func->GetNdim()){
        MPrintErr("2 != func->GetNdim()");
        abort();
    }
    
    string title;
    if("" == func->GetTitle()){
        title = func->GetClassName();
    } else {
        title = func->GetTitle();
    }
    TF2* tf2 = new TF2(title.c_str(), func, &MirFunc::Eval,
                       x_low, x_up, y_low, y_up,
                       func->GetNpar(),
                       func->GetClassName().c_str(), "Eval");
    return tf2;
}


void MirFuncOpe::DrawFunc(const MirFunc* const func,
                           const MirFuncPar* const func_par,
                           MirRootTool* const root_tool,
                           double x_low, double x_up,
                           string outfig)
{
    TF1* tf1 = GenTF1(func, x_low, x_up);
    MirFuncPar::CopyPar(func_par, tf1);
    tf1->Draw();
    root_tool->GetTCanvas()->Print(outfig.c_str());
    delete tf1;
}

void MirFuncOpe::DrawFunc(const MirFunc* const func,
                           const MirFuncPar* const func_par,
                           MirRootTool* const root_tool,
                           double x_low, double x_up,
                           double y_low, double y_up,
                           string outfig)
{
    TF2* tf2 = GenTF2(func, x_low, x_up, y_low, y_up);
    MirFuncPar::CopyPar(func_par, tf2);
    tf2->Draw("colz");
    root_tool->GetTCanvas()->Print(outfig.c_str());
    delete tf2;
}

double MirFuncOpe::GetRandom(const MirFunc* const func,
                              const MirFuncPar* const func_par,
                              double x_low, double x_up,
                              int rand_seed)
{
    TF1* tf1 = GenTF1(func, x_low, x_up);
    MirFuncPar::CopyPar(func_par, tf1);
    gRandom->SetSeed(rand_seed);
    double random = tf1->GetRandom();
    delete tf1;
    return random;
}

double MirFuncOpe::GetRandom(const MirFunc* const func,
                              const MirFuncPar* const func_par,
                              double x_low, double x_up,
                              double y_low, double y_up,
                              int rand_seed)
{
    TF2* tf2 = GenTF2(func, x_low, x_up, y_low, y_up);
    MirFuncPar::CopyPar(func_par, tf2);
    gRandom->SetSeed(rand_seed);
    double random = tf2->GetRandom();
    delete tf2;
    return random;
}
