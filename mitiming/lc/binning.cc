#include "mxkw_data_ope.h"
#include "mxkw_hist1d_ope.h"

#include "arg_binning.h"

// global variable 
int g_flag_debug = 0;
int g_flag_help = 0;
int g_flag_verbose = 0;

int main(int argc, char* argv[]){
    int status = kRetNormal;
  
    ArgValBinning* argval = new ArgValBinning;
    argval->Init(argc, argv);
    argval->Print(stdout);

    if(MxkwIolib::TestFileExist(argval->GetOutdir())){
        char cmd[kLineSize];
        sprintf(cmd, "mkdir -p %s", argval->GetOutdir().c_str());
        system(cmd);
    }
    FILE* fp_log;
    fp_log = fopen((argval->GetOutdir() + "/"
                    + argval->GetProgname() + ".log").c_str(), "w");
    
    DataArray1d* data_arr = new DataArray1d;
    data_arr->Load(argval->GetFile());
    data_arr->Sort();


    //
    // hist_info
    //
    HistInfo1d* hist_info = new HistInfo1d;
    hist_info->Load(argval->GetHistInfo());
    
    //
    // count
    //

    HistDataSerr1d* hd1d_count = new HistDataSerr1d;
    hd1d_count->Init(hist_info);

    for(long idata = 0; idata < data_arr->GetNdata(); idata ++){
        double time = data_arr->GetValElm(idata);
        hd1d_count->Fill(time);
    }
    string outdat_count = argval->GetOutdir() + "/"
        + argval->GetOutfileHead() + "_count.dat";
    hd1d_count->Save(outdat_count, "x,xe,y,ye");

    //
    // rate (counts/sec)
    //

    HistDataSerr1d* hd1d_rate = new HistDataSerr1d;
    hd1d_rate->Scale(hd1d_count, 1./hd1d_count->GetBinWidth(), 0.0);

    string outdat_rate = argval->GetOutdir() + "/"
        + argval->GetOutfileHead() + "_rate.dat";
    hd1d_rate->Save(outdat_rate, "x,xe,y,ye");

    // cleaning
    fclose(fp_log);
    delete argval;
    if(NULL != data_arr) { delete data_arr;}
    delete hd1d_count;
    delete hd1d_rate;

    return status;
}

