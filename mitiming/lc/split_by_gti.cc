#include "mxkw_hist1d_serr.h"
#include "mxkw_timing_telescope.h"
#include "mxkw_timing_gti.h"

#include "arg.h"

// global variable 
int g_flag_debug = 0;
int g_flag_help = 0;
int g_flag_verbose = 0;

int main(int argc, char* argv[]){
    int status = kRetNormal;
  
    ArgValSplitByGti* argval = new ArgValSplitByGti;
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

    MxkwGti* gti = new MxkwGti;
    gti->Load(argval->GetGtiFile());
    gti->SetInfo(argval->GetGtiTunit(),
                 Telescope::GetMjdref(argval->GetGtiTelescope()));
    gti->TimeConv(argval->GetLcTunit(),
                  Telescope::GetMjdref(argval->GetLcTelescope()));
    
    DataArray1d* data_arr = NULL;
    GraphDataSerr2d* g2d  = NULL;

    if("x" == argval->GetLcFormat()){
        data_arr = new DataArray1d;
        data_arr->Load(argval->GetLcFile());
        data_arr->Sort();

        DataArray1d** data_arr_split_arr = NULL;
        data_arr->GenSelectByInterval(gti->GetInterval(),
                                      &data_arr_split_arr);
        for(long iterm = 0; iterm < gti->GetNterm(); iterm++){
            char outfile[kLineSize];
            sprintf(outfile, "%s/%s_%2.2ld.dat",
                    argval->GetOutdir().c_str(),
                    argval->GetOutfileHead().c_str(),
                    iterm);
            data_arr_split_arr[iterm]->Save(outfile, 0);

            char outqdp[kLineSize];
            sprintf(outqdp, "%s/%s_%2.2ld.qdp",
                    argval->GetOutdir().c_str(),
                    argval->GetOutfileHead().c_str(),
                    iterm);
            data_arr_split_arr[iterm]->MkQdp(outqdp);
        }

        for(long iterm = 0; iterm < gti->GetNterm(); iterm++){
            delete data_arr_split_arr[iterm];
        }
        delete [] data_arr_split_arr;
    } else {
        g2d = new GraphDataSerr2d;
        g2d->Load(argval->GetLcFile(), argval->GetLcFormat());
        g2d->Sort();

        GraphDataSerr2d** g2d_split_arr = NULL;
        g2d->GenSelectByInterval(gti->GetInterval(),
                                 &g2d_split_arr);
        for(long iterm = 0; iterm < gti->GetNterm(); iterm++){
            char outfile[kLineSize];
            sprintf(outfile, "%s/%s_%2.2ld.dat",
                    argval->GetOutdir().c_str(),
                    argval->GetOutfileHead().c_str(),
                    iterm);
            g2d_split_arr[iterm]->Save(outfile);

            char outqdp[kLineSize];
            sprintf(outqdp, "%s/%s_%2.2ld.qdp",
                    argval->GetOutdir().c_str(),
                    argval->GetOutfileHead().c_str(),
                    iterm);
            g2d_split_arr[iterm]->MkQdp(outqdp);
        }

        for(long iterm = 0; iterm < gti->GetNterm(); iterm++){
            delete g2d_split_arr[iterm];
        }
        delete [] g2d_split_arr;
    }
    
    // cleaning
    fclose(fp_log);
    delete argval;
    delete gti;
    if(NULL != data_arr) { delete data_arr;}
    if(NULL != g2d) {delete g2d;}

    return status;
}

