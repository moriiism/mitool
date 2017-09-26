#include "mir_hist1d_serr.h"
#include "mir_qdp_tool.h"

#include "arg_plot_lc_da1d.h"

// global variable 
int g_flag_debug = 0;
int g_flag_help = 0;
int g_flag_verbose = 0;

int main(int argc, char* argv[]){
    int status = kRetNormal;
  
    ArgValPlotLcDa1d* argval = new ArgValPlotLcDa1d;
    argval->Init(argc, argv);
    argval->Print(stdout);

    if(MiIolib::TestFileExist(argval->GetOutdir())){
        char cmd[kLineSize];
        sprintf(cmd, "mkdir -p %s", argval->GetOutdir().c_str());
        system(cmd);
    }
    FILE* fp_log;
    fp_log = fopen((argval->GetOutdir() + "/"
                    + argval->GetProgname() + ".log").c_str(), "w");
    
    DataArray1d* data_arr = new DataArrayNerr1d;
    data_arr->Load(argval->GetFile());
    data_arr->Sort();

    HistInfo1d* hist_info = new HistInfo1d;
    hist_info->Load(argval->GetHistInfo());

    HistDataSerr1d* hd1d_count = new HistDataSerr1d;
    hd1d_count->Init(hist_info);
    for(long idata = 0; idata < data_arr->GetNdata(); idata ++){
        double time = data_arr->GetValElm(idata);
        hd1d_count->Fill(time);
    }

    HistDataSerr1d* hd1d_rate = new HistDataSerr1d;
    hd1d_rate->Scale(hd1d_count, 1./hd1d_count->GetBinWidth(), 0.0);

    string outqdp_count = argval->GetOutdir() + "/"
        + argval->GetOutfileHead() + "_count.qdp";
    MirQdpTool::MkQdp(hd1d_count, outqdp_count, "x,xe,y,ye");
    string outqdp_rate = argval->GetOutdir() + "/"
        + argval->GetOutfileHead() + "_rate.qdp";
    MirQdpTool::MkQdp(hd1d_rate, outqdp_rate, "x,xe,y,ye");

    //
    // cleaning
    //
    fclose(fp_log);
    delete argval;
    if(NULL != data_arr)  {delete data_arr;}
    if(NULL != hist_info) {delete hist_info;}
    if(NULL != hd1d_count) {delete hd1d_count;}
    if(NULL != hd1d_rate) {delete hd1d_rate;}

    return status;
}

