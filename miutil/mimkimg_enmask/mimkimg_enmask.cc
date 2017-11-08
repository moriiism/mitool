#include "fitsio.h"
#include "mi_str.h"
#include "mi_iolib.h"
#include "mif_fits.h"
#include "mif_img_info.h"
#include "mir_root_tool.h"
#include "mir_hist1d_nerr.h"
#include "mir_hist2d_nerr.h"
#include "mir_hist2d_ope.h"
#include "arg_mimkimg_enmask.h"

// global variable 
int g_flag_debug = 0;
int g_flag_help = 0;
int g_flag_verbose = 0;

int main(int argc, char* argv[])
{
    int status_prog = kRetNormal;
    
    ArgValMimkimgEnmask* argval = new ArgValMimkimgEnmask;
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
    if(2 != naxis){
        printf("naxis(=%d) != 2\n", naxis);
        abort();
    }

    long dimx = MifFits::GetAxisSize(argval->GetInfile(), 0);
    long dimy = MifFits::GetAxisSize(argval->GetInfile(), 1);
    MifImgInfo* img_info = new MifImgInfo;
    long fpixel0 = 1;
    long fpixel1 = 1;
    long lpixel0 = dimx;
    long lpixel1 = dimy;    
    img_info->InitSetImg(fpixel0, fpixel1, lpixel0, lpixel1);
    img_info->PrintInfo();
    double* X_mat = NULL;
    int bitpix = 0;
    MifFits::InFitsImageD(argval->GetInfile(),
                          img_info, &bitpix, &X_mat);

    HistDataNerr2d* hd2d_mask = new HistDataNerr2d;
    hd2d_mask->Init(dimx, 0, dimx, dimy, 0, dimy);
    hd2d_mask->SetConst(1);
    for(long ibinx = 0; ibinx < dimx; ibinx ++){
        for(long ibiny = 0; ibiny < dimy; ibiny ++){
            double xval = hd2d_mask->GetHi2d()->GetBinCenterXFromIbinX(ibinx);
            double yval = hd2d_mask->GetHi2d()->GetBinCenterYFromIbinY(ibiny);
            double rad = sqrt( pow(xval - argval->GetCx(), 2) +
                               pow(yval - argval->GetCy(), 2) );
            if(rad > argval->GetRad()){
                hd2d_mask->SetOvalElm(ibinx, ibiny, 0);
            }
        }
    }

    MifFits::OutFitsImageD(argval->GetOutdir(),
                           argval->GetOutfileHead(),
                           "mask2d",
                           naxis,
                           bitpix,
                           img_info->GetNaxesArr(),
                           hd2d_mask->GetOvalArr()->GetVal());
    
    return status_prog;
}


