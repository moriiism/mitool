#include "fitsio.h"
#include "mi_str.h"
#include "mi_iolib.h"
#include "mif_fits.h"
#include "mif_img_info.h"
#include "mir_root_tool.h"
#include "mir_hist2d_nerr.h"
#include "arg_miselcubeframe.h"

// global variable 
int g_flag_debug = 0;
int g_flag_help = 0;
int g_flag_verbose = 0;

int main(int argc, char* argv[])
{
    int status_prog = kRetNormal;
    
    ArgValMiselcubeframe* argval = new ArgValMiselcubeframe;
    argval->Init(argc, argv);
    argval->Print(stdout);

    MirRootTool* root_tool = new MirRootTool;
    root_tool->InitTCanvas("pub");
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
    
    int naxis = MifFits::GetNaxis(argval->GetInfile());
    if(3 != naxis){
        printf("naxis(=%d) != 3\n", naxis);
        abort();
    }

    long dimx = MifFits::GetAxisSize(argval->GetInfile(), 0);
    long dimy = MifFits::GetAxisSize(argval->GetInfile(), 1);

    int nframe = argval->GetFrameEd() - argval->GetFrameSt() + 1;
    for(int iframe = 0; iframe < nframe; iframe++){
        int index_frame = argval->GetFrameSt() + iframe + 1;
        MifImgInfo* img_info = new MifImgInfo;
        long fpixel0 = 1;
        long fpixel1 = 1;
        long fpixel2 = index_frame;
        long lpixel0 = dimx;
        long lpixel1 = dimy;
        long lpixel2 = index_frame;
        img_info->InitSetCube(fpixel0, fpixel1, fpixel2,
                              lpixel0, lpixel1, lpixel2);
        img_info->PrintInfo();
        double* X_mat = NULL;
        int bitpix = 0;
        MifFits::InFitsCubeD(argval->GetInfile(),
                             img_info, &bitpix, &X_mat);
        long naxes[2];
        naxes[0] = dimx;
        naxes[1] = dimy;
        char tag[kLineSize];
        sprintf(tag, "frame_%3.3d", index_frame);
        MifFits::OutFitsImageD(argval->GetOutdir(),
                               argval->GetOutfileHead(),
                               tag, 2, bitpix,
                               naxes, X_mat);
    }
    
    return status_prog;
}


