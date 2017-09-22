#include "mi_iolib.h"
#include "mir_plot_conf.h"
#include "mir_root_tool.h"
#include "mir_data1d_nerr.h"
#include "mir_data1d_serr.h"
#include "mir_data1d_terr.h"
#include "mir_graph2d_nerr.h"
#include "mir_graph2d_serr.h"
#include "mir_graph2d_terr.h"
#include "mir_qdp_tool.h"
#include "mir_solve.h"

#include "func_user.h"
#include "arg_solve_eq_1d.h"

// global variable 
int g_flag_debug = 0;
int g_flag_help = 0;
int g_flag_verbose = 0;

int main(int argc, char* argv[]){

    int status = kRetNormal;
    
    ArgValSolveEq1d* argval = new ArgValSolveEq1d;
    argval->Init(argc, argv);
    argval->Print(stdout);

    char logfile[kLineSize];
    if( MiIolib::TestFileExist(argval->GetOutdir()) ){
        char cmd[kLineSize];
        sprintf(cmd, "mkdir -p %s", argval->GetOutdir().c_str());
        system(cmd);
    }
    sprintf(logfile, "%s/%s_%s.log",
            argval->GetOutdir().c_str(),
            argval->GetOutfileHead().c_str(),
            argval->GetProgname().c_str());
    FILE* fp_log = fopen(logfile, "w");
    MiIolib::Printf2(fp_log, "-----------------------------\n");
    argval->Print(fp_log);
    
    MirRootTool* root_tool = new MirRootTool;
    root_tool->InitTCanvas(argval->GetRootStyle());

    MirPlotConf* plot_conf = new MirPlotConf;
    plot_conf->Load(argval->GetPlotConfFile());
    plot_conf->Print(stdout);
    root_tool->SetPlotConf(plot_conf);

    double xval_lo = atof(plot_conf->GetLoStrElm(0).c_str());
    double xval_up = atof(plot_conf->GetUpStrElm(0).c_str());
    double yval_lo = atof(plot_conf->GetLoStrElm(1).c_str());
    double yval_up = atof(plot_conf->GetUpStrElm(1).c_str());    

    MirFunc* func = FuncUser::GenFunc(argval->GetFuncName());
    MirFuncPar* func_par = new MirFuncPar;
    func_par->Load(argval->GetParFile());
    func_par->Print(stdout);


    char title[kLineSize];
    sprintf(title, "%s", argval->GetParFile().c_str());
//    TF1* tf1 = new TF1(title, func, &FuncUser::Eval,
//                       xval_lo, xval_up,
//                       func->GetNpar(), "FuncUser", "Eval");
    TF1* tf1 = new TF1(title, func, &MirFunc::Eval,
                       xval_lo, xval_up,
                       func->GetNpar(), "FuncUser", "Eval");

    
    MirFuncPar::CopyPar(func_par, tf1);
    tf1->SetLineStyle(1);
    tf1->SetLineColor(1);
    tf1->Draw("SAME");
    tf1->Draw("sameaxis");
   
    gStyle->SetPadTickX(1);
    gStyle->SetPadTickY(1);
    
    double root = MirSolve::GetRootBisectionEqC(func, func_par->GetPar(),
                                                 xval_lo, xval_up,
                                                 argval->GetConstant(),
                                                 argval->GetConstant() * 1e-3);
    printf("root = %e\n", root);

    //
    // draw lines
    //
    
    TLine* tline_hori = new TLine(xval_lo, argval->GetConstant(),
                                  xval_up, argval->GetConstant());
    tline_hori->SetLineStyle(2);
    tline_hori->Draw();

    TLine* tline_ver = new TLine(root, yval_lo,
                                 root, yval_up);
    tline_ver->SetLineStyle(2);
    tline_ver->Draw();
    
    //
    // save image
    //
    
    // dummy for x-axis
    char dummy_val[10];
    sprintf(dummy_val, "%e", yval_lo);
    TF1* tf1_dummy = new TF1("dummy", dummy_val, xval_lo, xval_up);
    tf1_dummy->SetLineColor(1);
    tf1_dummy->SetLineWidth(3);
    tf1_dummy->Draw("SAME");

    char outfig[kLineSize];    
    sprintf(outfig, "%s/%s.png",
            argval->GetOutdir().c_str(),
            argval->GetOutfileHead().c_str());
    root_tool->GetTCanvas()->Update();
    root_tool->GetTCanvas()->Print(outfig);
    
    return status;
}
