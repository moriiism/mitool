#include "mi_iolib.h"
#include "mir_plot_conf.h"
#include "mir_root_tool.h"
#include "mir_data1d_serr.h"
#include "mir_data1d_terr.h"
#include "mir_graph2d_serr.h"
#include "mir_graph2d_terr.h"
#include "mir_func_ope.h"
#include "mir_qdp_tool.h"
#include "func_user.h"
#include "arg_draw_func_list_1d.h"


// global variable 
int g_flag_debug = 0;
int g_flag_help = 0;
int g_flag_verbose = 0;

int main(int argc, char* argv[]){

    int status = kRetNormal;
    
    ArgValDrawFuncList1d* argval = new ArgValDrawFuncList1d;
    argval->Init(argc, argv);
    argval->Print(stdout);

    char logfile[kLineSize];
    if( MiIolib::TestFileExist(argval->GetOutdir()) ){
        char cmd[kLineSize];
        sprintf(cmd, "mkdir -p %s", argval->GetOutdir().c_str());
        int ret = system(cmd);
        (void) ret;
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

    //
    // function & parfile
    //
    long nfunc;
    string* func_list_line_arr = NULL;
    string* func_name_arr = NULL;
    string* par_file_arr = NULL;
    int* func_line_style_arr = NULL;
    int* func_line_color_arr  = NULL;
    string* func_range_lo_arr = NULL;
    string* func_range_up_arr = NULL;
    MiIolib::GenReadFileSkipComment(argval->GetFuncParList(), &func_list_line_arr, &nfunc);
    func_name_arr = new string [nfunc];
    par_file_arr = new string [nfunc];
    func_line_style_arr = new int [nfunc];
    func_line_color_arr = new int [nfunc];
    func_range_lo_arr = new string [nfunc];
    func_range_up_arr = new string [nfunc];
    for(int ifunc = 0; ifunc < nfunc; ifunc ++){
        int ncolumn = MiStr::GetNcolumn(func_list_line_arr[ifunc]);
        if(6 != ncolumn){
            MPrintErr("ncolumn != 6");
            abort();
        }
        char func_name_tmp[kLineSize];
        char par_file_tmp[kLineSize];
        char func_range_lo_tmp[kLineSize];
        char func_range_up_tmp[kLineSize];
        sscanf(func_list_line_arr[ifunc].c_str(), "%s %s %d %d %s %s",
               func_name_tmp, par_file_tmp,
               &func_line_style_arr[ifunc], &func_line_color_arr[ifunc],
               func_range_lo_tmp, func_range_up_tmp);
        func_name_arr[ifunc] = func_name_tmp;
        par_file_arr[ifunc] = par_file_tmp;
        func_range_lo_arr[ifunc] = func_range_lo_tmp;
        func_range_up_arr[ifunc] = func_range_up_tmp;        
        printf("func_name, par_file = %s  %s\n", func_name_arr[ifunc].c_str(), par_file_arr[ifunc].c_str());
    }
    MiIolib::DelReadFile(func_list_line_arr);

    //
    // plot configuration
    //
    MirPlotConf* plot_conf = new MirPlotConf;
    plot_conf->Load(argval->GetPlotConfFile());
    plot_conf->Print(stdout);
    root_tool->SetPlotConf(plot_conf);

    //
    // draw func model
    //
    MirFunc** func_arr = new MirFunc* [nfunc];
    TF1** tf1_func_arr  = new TF1* [nfunc];
    for(int ifunc = 0; ifunc < nfunc; ifunc ++){
        func_arr[ifunc] = FuncUser::GenFunc(func_name_arr[ifunc]);
        MirFuncPar* func_par = new MirFuncPar;
        func_par->Load(par_file_arr[ifunc]);
        double func_range_lo = 0.0;
        double func_range_up = 0.0;
        if("none" == func_range_lo_arr[ifunc]){
            func_range_lo = atof(plot_conf->GetLoStrElm(0).c_str());
        } else {
            func_range_lo = atof(func_range_lo_arr[ifunc].c_str());
        }
        if("none" == func_range_up_arr[ifunc]){
            func_range_up = atof(plot_conf->GetUpStrElm(0).c_str());
        } else {
            func_range_up = atof(func_range_up_arr[ifunc].c_str());
        }
        tf1_func_arr[ifunc] = MirFuncOpe::GenTF1(func_arr[ifunc], func_range_lo, func_range_up);
        MirFuncPar::CopyPar(func_par, tf1_func_arr[ifunc]);
        tf1_func_arr[ifunc]->SetLineStyle(func_line_style_arr[ifunc]);
        tf1_func_arr[ifunc]->SetLineColor(func_line_color_arr[ifunc]);

        printf("ifunc = %d: %s\n", ifunc, func_arr[ifunc]->GetClassName().c_str());
        
        tf1_func_arr[ifunc]->Draw("SAME");
        tf1_func_arr[ifunc]->Draw("sameaxis");

        delete func_par;
    }
    
    char outfig[kLineSize];
    sprintf(outfig, "%s/%s.png",
            argval->GetOutdir().c_str(),
            argval->GetOutfileHead().c_str());
    root_tool->GetTCanvas()->Update();
    root_tool->GetTCanvas()->Print(outfig);

    delete argval;
    fclose(fp_log);
    delete [] func_name_arr;
    delete [] par_file_arr;
    delete [] func_line_style_arr;
    delete [] func_line_color_arr;
    delete [] func_range_lo_arr;
    delete [] func_range_up_arr;
    delete plot_conf;

    for(int ifunc = 0; ifunc < nfunc; ifunc ++){
        delete func_arr[ifunc];
        delete tf1_func_arr[ifunc];
    }
    delete [] func_arr;
    delete [] tf1_func_arr;
    
    return status;
}
