#include "mi_iolib.h"
#include "mir_root_tool.h"
#include "mir_hist2d_nerr.h"
#include "mir_qdp_tool.h"
#include "arg_miparmap.h"

// global variable 
int g_flag_debug = 0;
int g_flag_help = 0;
int g_flag_verbose = 0;

int main(int argc, char* argv[]){
    int status = kRetNormal;
  
    ArgValMiparmap* argval = new ArgValMiparmap;
    argval->Init(argc, argv);

    MirRootTool* root_tool = new MirRootTool;
    root_tool->InitTCanvas("pub");
    if( MiIolib::TestFileExist(argval->GetOutdir()) ){
        char cmd[kLineSize];
        sprintf(cmd, "mkdir -p %s", argval->GetOutdir().c_str());
        system(cmd);
    }


    string* lines_arr = NULL;
    long nline = 0;
    MiIolib::GenReadFileSkipComment(argval->GetInfile(),
                                    &lines_arr,
                                    &nline);
    double* mu_arr = new double [nline];
    double* beta_arr = new double [nline];
    double* ave_arr = new double [nline];
    for(long iline = 0; iline < nline; iline ++){
        int nsplit = 0;
        string* split_arr = NULL;
        MiStr::GenSplit(lines_arr[iline], &nsplit, &split_arr);

        mu_arr[iline]   = atof(split_arr[0].c_str());
        beta_arr[iline] = atof(split_arr[1].c_str());
        ave_arr[iline]  = atof(split_arr[2].c_str());
        MiStr::DelSplit(split_arr);

        printf("%e %e %e\n", mu_arr[iline], beta_arr[iline], ave_arr[iline]);
    }
    
    HistInfo2d* hi2d = new HistInfo2d;
    hi2d->Load(argval->GetHistInfoFile());
    HistDataNerr2d* hd2d = new HistDataNerr2d;
    hd2d->Init(hi2d);
    for(long iline = 0; iline < nline; iline ++){
        hd2d->Fill(mu_arr[iline], beta_arr[iline], ave_arr[iline]);
    }
    char outfig[kLineSize];
    sprintf(outfig, "%s/%s.png",
            argval->GetOutdir().c_str(),
            argval->GetOutfileHead().c_str());
    hd2d->MkTH2FigZrange(outfig, root_tool,
                         7.2e-2, 7.4e-2,
                         0.0, 0.0, 0.0,
                         "mu", "beta", "ave");
    
    delete argval;
    
    return status;
}


