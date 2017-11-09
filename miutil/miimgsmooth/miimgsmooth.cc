#include "fitsio.h"
#include "mi_iolib.h"
#include "mif_fits.h"
#include "mif_img_info.h"
#include "mir_root_tool.h"
#include "mir_hist2d_nerr.h"
#include "mir_qdp_tool.h"
#include "mifc_gen.h"
#include "arg_miimgsmooth.h"


// global variable 
int g_flag_debug = 0;
int g_flag_help = 0;
int g_flag_verbose = 0;

int main(int argc, char* argv[]){
    int status = kRetNormal;
  
    ArgValMiimgsmooth* argval = new ArgValMiimgsmooth;
    argval->Init(argc, argv);

    MirRootTool* root_tool = new MirRootTool;
    root_tool->InitTCanvas("pub");
    if( MiIolib::TestFileExist(argval->GetOutdir()) ){
        char cmd[kLineSize];
        sprintf(cmd, "mkdir -p %s", argval->GetOutdir().c_str());
        system(cmd);
    }

    // for image
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

    // for mask image
    int naxis_mask = MifFits::GetNaxis(argval->GetInfileMask());
    if(2 != naxis_mask){
        printf("naxis_mask(=%d) != 2\n", naxis_mask);
        abort();
    }
    long dimx_mask = MifFits::GetAxisSize(argval->GetInfileMask(), 0);
    long dimy_mask = MifFits::GetAxisSize(argval->GetInfileMask(), 1);
    if(dimx != dimx_mask || dimy != dimy_mask){
        abort();
    }
    double* X_mask_mat = NULL;
    int bitpix_mask = 0;
    MifFits::InFitsImageD(argval->GetInfileMask(),
                          img_info, &bitpix_mask, &X_mask_mat);

    // push image to 2d hist
    HistDataNerr2d* hd2d = new HistDataNerr2d;
    hd2d->Init(dimx, 0, dimx, dimy, 0, dimy);
    hd2d->SetOvalArr(dimx * dimy, X_mat);

    HistDataNerr2d* hd2d_mask = new HistDataNerr2d;
    hd2d_mask->Init(dimx, 0, dimx, dimy, 0, dimy);
    hd2d_mask->SetOvalArr(dimx * dimy, X_mask_mat);

    MirFunc* func = MifcGen::GenFunc(argval->GetFunc());
    MirFuncPar* func_par = new MirFuncPar;
    func_par->Load(argval->GetParFile());

    // kernel
    HistInfo2d* hi2d_kernel = new HistInfo2d;
    hi2d_kernel->InitSetByMidPoint(0.0, 1.0, argval->GetNbinKernelHalf(), "ceil",
                                   0.0, 1.0, argval->GetNbinKernelHalf(), "ceil");
    HistDataNerr2d* hd2d_kernel_tmp = new HistDataNerr2d;
    hd2d_kernel_tmp->Init(hi2d_kernel);
    hd2d_kernel_tmp->SetByFunc(func, func_par->GetPar());
    double sum = MirMath::GetSum(hd2d_kernel_tmp->GetNbin(), hd2d_kernel_tmp->GetOvalArr()->GetVal());
    HistDataNerr2d* hd2d_kernel = new HistDataNerr2d;
    HistData2dOpe::GetScale(hd2d_kernel_tmp, 1./sum, 0.0, hd2d_kernel);
    
    // smoothing
    HistDataNerr2d* hd2d_smooth = new HistDataNerr2d;
    hd2d_smooth->Init(dimx, 0, dimx, dimy, 0, dimy);
    for(long ibin = 0; ibin < hd2d->GetNbin(); ibin ++){
        double oval = hd2d->GetOvalArr()->GetValElm(ibin);
        double xval = hd2d->GetHi2d()->GetBinCenterXFromIbin(ibin);
        double yval = hd2d->GetHi2d()->GetBinCenterYFromIbin(ibin);
        for(long ibin_kernel = 0; ibin_kernel < hd2d_kernel->GetNbin(); ibin_kernel++){
            double oval_kernel = hd2d_kernel->GetOvalArr()->GetValElm(ibin_kernel);
            double xval_kernel = hd2d_kernel->GetHi2d()->GetBinCenterXFromIbin(ibin_kernel);
            double yval_kernel = hd2d_kernel->GetHi2d()->GetBinCenterYFromIbin(ibin_kernel);
            double xval_add = xval + xval_kernel;
            double yval_add = yval + yval_kernel;
            if(hd2d_smooth->GetHi2d()->GetLoX() <= xval_add &&
               hd2d_smooth->GetHi2d()->GetUpX() >= xval_add &&
               hd2d_smooth->GetHi2d()->GetLoY() <= yval_add &&
               hd2d_smooth->GetHi2d()->GetUpY() >= yval_add){
                hd2d_smooth->Fill(xval_add, yval_add, oval * oval_kernel);
            }
        }
    }
    HistData2dOpe::GetMul(hd2d_mask, hd2d_smooth, hd2d_smooth);
    
    MifFits::OutFitsImageD(argval->GetOutdir(),
                           argval->GetOutfileHead(),
                           "smooth",
                           naxis,
                           bitpix,
                           img_info->GetNaxesArr(),
                           hd2d_smooth->GetOvalArr()->GetVal());

    delete argval;
    
    return status;
}


