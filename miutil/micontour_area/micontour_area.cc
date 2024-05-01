#include "mi_str.h"
#include "mi_iolib.h"
#include "mir_root_tool.h"
#include "mir_hist2d_nerr.h"
#include "arg_micontour_area.h"

// global variable 
int g_flag_debug = 0;
int g_flag_help = 0;
int g_flag_verbose = 0;

int main(int argc, char* argv[])
{
    int status_prog = kRetNormal;
    
    ArgValMicontourArea* argval = new ArgValMicontourArea;
    argval->Init(argc, argv);
    argval->Print(stdout);

    MirRootTool* root_tool = new MirRootTool;
    root_tool->InitTCanvas("pub");
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

    double* valx1_arr = NULL;
    double* valx2_arr = NULL;
    long nline = 0;
    MiIolib::GenReadFile(argval->GetContFile(),
                         &valx1_arr,
                         &valx2_arr,
                         &nline);


    HistDataNerr2d* hd2d = new HistDataNerr2d;
    hd2d->Init(argval->GetNbinx(),
               argval->GetXlo(),
               argval->GetXup(),
               argval->GetNbiny(),
               argval->GetYlo(),
               argval->GetYup());
    for(int iline = 0; iline < nline - 1; iline ++){
        double delta_x = hd2d->GetBinWidthX()/10.0;
        double delta_y = hd2d->GetBinWidthY()/10.0;
        int nt_x = (int) fabs(
            ceil((valx1_arr[iline + 1] - valx1_arr[iline]) / delta_x));
        int nt_y = (int) fabs(
            ceil((valx2_arr[iline + 1] - valx2_arr[iline]) / delta_y));
        int nt = MirMath::GetMax(nt_x, nt_y);
        for(int it = 0; it < nt; it++){
            double ratio = double(it) / double(nt);
            double xval = valx1_arr[iline]
                + ratio * (valx1_arr[iline + 1] - valx1_arr[iline]);
            double yval = valx2_arr[iline]
                + ratio * (valx2_arr[iline + 1] - valx2_arr[iline]);
            hd2d->Fill(xval, yval);
        }
    }
    {
        double delta_x = hd2d->GetBinWidthX()/10.0;
        double delta_y = hd2d->GetBinWidthY()/10.0;
        int nt_x = (int) fabs(
            ceil((valx1_arr[0] - valx1_arr[nline - 1]) / delta_x));
        int nt_y = (int) fabs(
            ceil((valx2_arr[0] - valx2_arr[nline - 1]) / delta_y));
        int nt = MirMath::GetMax(nt_x, nt_y);
        for(int it = 0; it < nt; it++){
            double ratio = double(it) / double(nt);
            double xval = valx1_arr[nline - 1]
                + ratio * (valx1_arr[0] - valx1_arr[nline - 1]);
            double yval = valx2_arr[nline - 1]
                + ratio * (valx2_arr[0] - valx2_arr[nline - 1]);
            hd2d->Fill(xval, yval);
        }
    }

    // fill inner region
    for(int ibiny = 0; ibiny < hd2d->GetNbinY(); ibiny ++){
        int ibinx_max = -1;
        int ibinx_min = hd2d->GetNbinX();
        for(int ibinx = 0; ibinx < hd2d->GetNbinX(); ibinx ++){
            double oval = hd2d->GetOvalElm(ibinx, ibiny);
            if(fabs(oval) > 1e-10){
                if(ibinx < ibinx_min){
                    ibinx_min = ibinx;
                }
                if(ibinx > ibinx_max){
                    ibinx_max = ibinx;
                }
            }
        }
        for(int ibinx = ibinx_min; ibinx <= ibinx_max; ibinx ++){
            hd2d->SetOvalElm(ibinx, ibiny, 1.0);
        }
    }

    double oval_all = 0.0;
    for(int ibiny = 0; ibiny < hd2d->GetNbinY(); ibiny ++){
        for(int ibinx = 0; ibinx < hd2d->GetNbinX(); ibinx ++){
            double oval = hd2d->GetOvalElm(ibinx, ibiny);
            oval_all += oval;
        }
    }
    double area = hd2d->GetBinArea() * oval_all;
    printf("area = %f\n", area);

    char outfig[kLineSize];
    sprintf(outfig, "%s/%s.png",
            argval->GetOutdir().c_str(),
            argval->GetOutfileHead().c_str());
    hd2d->MkTH2Fig(outfig, root_tool);
    
    return status_prog;
}


