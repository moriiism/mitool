#include "mi_iolib.h"
#include "mir_plot_conf.h"
#include "mir_root_tool.h"
#include "mir_graph2d_nerr.h"
#include "mir_graph2d_serr.h"
#include "mir_graph2d_terr.h"
#include "mir_func_ope.h"
#include "mifc_gen.h"
#include "func_user.h"
#include "arg_draw_func_data_list_1d.h"

// global variable 
int g_flag_debug = 0;
int g_flag_help = 0;
int g_flag_verbose = 0;


int main(int argc, char* argv[]){

    int status = kRetNormal;
  
    ArgValDrawFuncDataList1d* argval = new ArgValDrawFuncDataList1d;
    argval->Init(argc, argv);
    argval->Print(stdout);

    MirRootTool* root_tool = new MirRootTool;
    root_tool->InitTCanvas(argval->GetRootStyle());

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

    //
    // data file
    //
    long nfile;
    string* data_file_line_arr = NULL;
    string* files_arr = NULL;
    string* data_fmt_arr = NULL;
    int* data_marker_style_arr = NULL;
    int* data_marker_color_arr = NULL;
    int* data_marker_size_arr = NULL;
    MiIolib::GenReadFileSkipComment(argval->GetDataFileList(), &data_file_line_arr, &nfile);
    files_arr = new string [nfile];
    data_fmt_arr = new string [nfile];    
    data_marker_style_arr = new int [nfile];
    data_marker_color_arr = new int [nfile];
    data_marker_size_arr = new int [nfile];    
    for(long ifile = 0; ifile < nfile; ifile ++){
        int ncolumn = MiStr::GetNcolumn(data_file_line_arr[ifile], " ");
        if(5 != ncolumn){
            MPrintWarn("ncolumn != 5");
        }
        char file_name_tmp[kLineSize];
        char data_fmt_tmp[kLineSize];
        sscanf(data_file_line_arr[ifile].c_str(), "%s %s %d %d %d",
               file_name_tmp, data_fmt_tmp,
               &data_marker_style_arr[ifile],
               &data_marker_color_arr[ifile],
               &data_marker_size_arr[ifile]);
        files_arr[ifile] = file_name_tmp;
        data_fmt_arr[ifile] = data_fmt_tmp;
    }
    MiIolib::DelReadFile(data_file_line_arr);
    
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
        int ncolumn = MiStr::GetNcolumn(func_list_line_arr[ifunc], " ");
        if(6 != ncolumn){
            MPrintWarn("ncolumn != 6");
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
    // data
    //
    GraphData2d** g2d_arr = new GraphData2d* [nfile];
    TGraph** tgraph_arr = new TGraph* [nfile];
    for(long ifile = 0; ifile < nfile; ifile ++){
        if("x" == data_fmt_arr[ifile]){
            MPrintErr("bad format");
            abort();
        } else if("x,y" == data_fmt_arr[ifile]){
            g2d_arr[ifile] = new GraphDataNerr2d;
        } else if("x,y,ye" == data_fmt_arr[ifile]){
            g2d_arr[ifile] = new GraphDataSerr2d;        
        } else if("x,xe,y,ye" == data_fmt_arr[ifile]){
            g2d_arr[ifile] = new GraphDataSerr2d;
        } else if("x,xe,y" == data_fmt_arr[ifile]){
            g2d_arr[ifile] = new GraphDataSerr2d;        
        } else if("x,y,ye+,ye-" == data_fmt_arr[ifile]){
            g2d_arr[ifile] = new GraphDataTerr2d;
        } else if("x,xe,y,ye+,ye-" == data_fmt_arr[ifile]){
            g2d_arr[ifile] = new GraphDataTerr2d;        
        } else if("x,xe+,xe-,y,ye+,ye-" == data_fmt_arr[ifile]){
            g2d_arr[ifile] = new GraphDataTerr2d;        
        } else {
            MPrintErr("bad format");
            abort();
        }
        g2d_arr[ifile]->Load(files_arr[ifile], data_fmt_arr[ifile]);
        tgraph_arr[ifile] = g2d_arr[ifile]->GenTGraph(0.0, 0.0);
    }
    
    //
    // plot configuration
    //
    
    MirPlotConf* plot_conf = new MirPlotConf;
    plot_conf->Load(argval->GetPlotConfFile());
    plot_conf->Print(stdout);
    root_tool->SetPlotConf(plot_conf);
    
    //
    // plot data
    // 
    
    for(int ifile = 0; ifile < nfile; ifile ++){    
        tgraph_arr[ifile]->SetMarkerStyle(data_marker_style_arr[ifile]);
        tgraph_arr[ifile]->SetMarkerColor(data_marker_color_arr[ifile]);
        tgraph_arr[ifile]->SetMarkerSize(data_marker_size_arr[ifile]);        
        printf("ifile = %d\n", ifile);
        tgraph_arr[ifile]->Draw("P SAME E");
    }

    //
    // draw func model
    //
    for(int ifunc = 0; ifunc < nfunc; ifunc ++){
        MirFunc* func = FuncUser::GenFunc(func_name_arr[ifunc]);
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
        TF1* tf1_func = MirFuncOpe::GenTF1(func, func_range_lo, func_range_up);
        MirFuncPar::CopyPar(func_par, tf1_func);
        tf1_func->SetLineStyle(func_line_style_arr[ifunc]);
        tf1_func->SetLineColor(func_line_color_arr[ifunc]);

        printf("ifunc = %d: %s\n", ifunc, func->GetClassName().c_str());
        
        tf1_func->Draw("SAME");
        tf1_func->Draw("sameaxis");
    }
    
    char outfig_func[kLineSize];
    sprintf(outfig_func, "%s/%s_func.png",
            argval->GetOutdir().c_str(),
            argval->GetOutfileHead().c_str());
    root_tool->GetTCanvas()->Update();
    root_tool->GetTCanvas()->Print(outfig_func);

    char outeps_func[kLineSize];
    sprintf(outeps_func, "%s/%s_func.eps",
            argval->GetOutdir().c_str(),
            argval->GetOutfileHead().c_str());
    root_tool->GetTCanvas()->Update();
    root_tool->GetTCanvas()->Print(outeps_func);    
    
    return status;
}
