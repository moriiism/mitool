#include "mi_iolib.h"
#include "mir_root_tool.h"
#include "mir_data1d_nerr.h"
#include "mir_graph2d_serr.h"
#include "mir_qdp_tool.h"

#include "mit_timeconv.h"
#include "mit_telescope.h"
#include "mit_binary_orb.h"

#include "arg_demod_da1d.h"

// global variable 
int g_flag_debug = 0;
int g_flag_help = 0;
int g_flag_verbose = 0;

int main(int argc, char* argv[]){
    int status = kRetNormal;
  
    ArgValDemodDa1d* argval = new ArgValDemodDa1d;
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

    MirRootTool* root_tool = new MirRootTool;
    root_tool->InitTCanvas(argval->GetRootStyle());

    DataArrayNerr1d* data_arr = new DataArrayNerr1d;
    data_arr->Load(argval->GetLcFile());

    BinaryOrb1* binorb = new BinaryOrb1;
    binorb->Load(argval->GetBinorbFile());
    BinaryOrbObsTimeFunc* bin_orb_obs_time_func = new BinaryOrbObsTimeFunc;
    bin_orb_obs_time_func->Init(binorb);

    DataArray1d* data_mjd_arr
        = TimeConv::GenTimeToMjd(data_arr,
                                 Telescope::GetMjdref(argval->GetTelescope()),
                                 argval->GetLcTunit());

    DataArrayNerr1d* data_mjd_demod_arr = new DataArrayNerr1d;
    data_mjd_demod_arr->Init(data_mjd_arr->GetNdata());
    for(long idata = 0; idata < data_mjd_arr->GetNdata(); idata ++){
        double time_object = BinaryOrb1::GetTimeObj(bin_orb_obs_time_func,
                                                    data_mjd_arr->GetValElm(idata),
                                                    binorb->GetPeriod());
        data_mjd_demod_arr->SetValElm(idata, time_object);
    }
    string outfile_mjd_demod
        = argval->GetOutdir() + "/"
        + argval->GetOutfileHead() + "_demod_mjd.txt";
    data_mjd_demod_arr->Save(outfile_mjd_demod, 0, 0.0);


    DataArray1d* data_demod_arr
        = TimeConv::GenMjdToTime(data_mjd_demod_arr,
                                 Telescope::GetMjdref(argval->GetTelescope()),
                                 argval->GetLcTunit());
    string outfile_demod
        = argval->GetOutdir() + "/"
        + argval->GetOutfileHead() + "_demod.txt";
    data_demod_arr->Save(outfile_demod, 0, 0.0);


    // for presentation
    DataArrayNerr1d* diff_arr = new DataArrayNerr1d;
    DataArray1dOpe::GetSub(data_mjd_demod_arr, data_mjd_arr,
                           diff_arr);
    GraphDataNerr2d* g2d_diff = new GraphDataNerr2d;
    g2d_diff->Init(data_mjd_arr->GetNdata());
    g2d_diff->SetXvalArr(data_mjd_arr);
    g2d_diff->SetOvalArr(diff_arr);
    g2d_diff->SetFlagXvalSorted(1);
    
    string g2d_diff_out
        = argval->GetOutdir() + "/"
        + argval->GetOutfileHead() + "_g2d_mjd_diff.qdp";
    MirQdpTool::MkQdp(g2d_diff, g2d_diff_out, "x,y",
                       "mjd - 55000", "mjd_diff", 55000, 0.0);
    
    // cleaning
    fclose(fp_log);
    if(NULL != argval)   {delete argval;}
    if(NULL != data_arr) {delete data_arr;}
    if(NULL != binorb) {delete binorb;}
    if(NULL != data_mjd_arr) {delete data_mjd_arr;}
    if(NULL != data_mjd_demod_arr) {delete data_mjd_demod_arr;}
    if(NULL != data_demod_arr) {delete data_demod_arr;}
    if(NULL != diff_arr) {delete diff_arr;}
    if(NULL != g2d_diff) {delete g2d_diff;}

    return status;
}

