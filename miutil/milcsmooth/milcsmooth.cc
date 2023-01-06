#include "fitsio.h"
#include "mi_iolib.h"
#include "mif_fits.h"
#include "mif_img_info.h"
#include "mir_root_tool.h"
#include "mir_hist2d_nerr.h"
#include "mir_qdp_tool.h"
#include "mifc_gen.h"
#include "arg_milcsmooth.h"


// global variable 
int g_flag_debug = 0;
int g_flag_help = 0;
int g_flag_verbose = 0;

int main(int argc, char* argv[]){
    int status = kRetNormal;
  
    ArgValMilcsmooth* argval = new ArgValMilcsmooth;
    argval->Init(argc, argv);

    MirRootTool* root_tool = new MirRootTool;
    root_tool->InitTCanvas("pub");
    if( MiIolib::TestFileExist(argval->GetOutdir()) ){
        char cmd[kLineSize];
        sprintf(cmd, "mkdir -p %s", argval->GetOutdir().c_str());
        int ret = system(cmd);
        (void) ret;
    }

    //
    // load data
    //
    HistDataNerr1d* hd1d = new HistDataNerr1d;
    hd1d->Load(argval->GetInfile());
    HistDataNerr1d* hd1d_mask = new HistDataNerr1d;
    hd1d_mask->Load(argval->GetInfileMask());
    
    MirFunc* func = MifcGen::GenFunc(argval->GetFunc());
    MirFuncPar* func_par = new MirFuncPar;
    func_par->Load(argval->GetParFile());

    // kernel
    HistInfo1d* hi1d_kernel = new HistInfo1d;
    hi1d_kernel->InitSetByMidPoint(0.0, 1.0, argval->GetNbinKernelHalf(), "ceil");
    HistDataNerr1d* hd1d_kernel_tmp = new HistDataNerr1d;
    hd1d_kernel_tmp->Init(hi1d_kernel);
    hd1d_kernel_tmp->SetByFunc(func, func_par->GetPar());
    double sum = MirMath::GetSum(hd1d_kernel_tmp->GetNbinX(), hd1d_kernel_tmp->GetOvalArr()->GetVal());
    HistDataNerr1d* hd1d_kernel = new HistDataNerr1d;
    HistData1dOpe::GetScale(hd1d_kernel_tmp, 1./sum, 0.0, hd1d_kernel);
    
    // smoothing
    HistDataNerr1d* hd1d_smooth = new HistDataNerr1d;
    hd1d_smooth->Init(hd1d->GetHi1d());
    for(long ibin = 0; ibin < hd1d->GetNbinX(); ibin ++){
        double oval = hd1d->GetOvalArr()->GetValElm(ibin);
        double xval = hd1d->GetHi1d()->GetBinCenter(ibin);
        for(long ibin_kernel = 0; ibin_kernel < hd1d_kernel->GetNbinX(); ibin_kernel++){
            double oval_kernel = hd1d_kernel->GetOvalArr()->GetValElm(ibin_kernel);
            double xval_kernel = hd1d_kernel->GetHi1d()->GetBinCenter(ibin_kernel);
            double xval_add = xval + xval_kernel;
            if(hd1d_smooth->GetHi1d()->GetLo() <= xval_add &&
               hd1d_smooth->GetHi1d()->GetUp() >= xval_add ){
                hd1d_smooth->Fill(xval_add, oval * oval_kernel);
            }
        }
    }
    HistData1dOpe::GetMul(hd1d_mask, hd1d_smooth, hd1d_smooth);
    
    char outfile[kLineSize];
    sprintf(outfile, "%s/%s_smooth.dat",
            argval->GetOutdir().c_str(),
            argval->GetOutfileHead().c_str());
    hd1d_smooth->Save(outfile, "x,y");

    delete argval;
    
    return status;
}


