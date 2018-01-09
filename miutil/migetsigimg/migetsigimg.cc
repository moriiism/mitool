#include "fitsio.h"
#include "mi_iolib.h"
#include "mif_fits.h"
#include "mif_img_info.h"
#include "mir_root_tool.h"
#include "mir_hist2d_nerr.h"
#include "mir_qdp_tool.h"
#include "arg_migetsigimg.h"


// global variable 
int g_flag_debug = 0;
int g_flag_help = 0;
int g_flag_verbose = 0;

int main(int argc, char* argv[]){
    int status = kRetNormal;

    ArgValMigetsigimg* argval = new ArgValMigetsigimg;
    argval->Init(argc, argv);

    MirRootTool* root_tool = new MirRootTool;
    root_tool->InitTCanvas("pub");
    if( MiIolib::TestFileExist(argval->GetOutdir()) ){
        char cmd[kLineSize];
        sprintf(cmd, "mkdir -p %s", argval->GetOutdir().c_str());
        system(cmd);
    }
    char logfile[kLineSize];
    sprintf(logfile, "%s/%s_%s.log",
            argval->GetOutdir().c_str(),
            argval->GetOutfileHead().c_str(),
            argval->GetProgname().c_str());
    FILE* fp_log = fopen(logfile, "w");
    MiIolib::Printf2(fp_log, "-----------------------------\n");
    argval->Print(fp_log);
    
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

    HistDataNerr2d* hd2d_mask_bg = new HistDataNerr2d;
    hd2d_mask_bg->Copy(hd2d_mask);

    double mean   = 0.0;
    double stddev = 0.0;
    int nclip = 30;
    for(int iclip = 0; iclip < nclip; iclip++){
        // get mean, stddev
        vector<double> val_vec;
        for(long ibin = 0; ibin < hd2d->GetNbin(); ibin++){
            if( hd2d_mask_bg->GetOvalArr()->GetValElm(ibin) > 0){
                val_vec.push_back(hd2d->GetOvalArr()->GetValElm(ibin));
            }
        }
        mean   = MirMath::GetAMean(val_vec);
        stddev = MirMath::GetSqrtOfUnbiasedVariance(val_vec);
        printf("iclip, mean, stddev, nsize = %d, %e, %e, %d\n",
               iclip, mean, stddev, (int) val_vec.size());

        for(long ibin = 0; ibin < hd2d->GetNbin(); ibin++){
            if( hd2d_mask_bg->GetOvalArr()->GetValElm(ibin) > 0){
                if( fabs(hd2d->GetOvalArr()->GetValElm(ibin) - mean) >  argval->GetSignificance() * stddev){
                    hd2d_mask_bg->SetOvalElm(hd2d_mask_bg->GetHi2d()->GetIbinX(ibin),
                                             hd2d_mask_bg->GetHi2d()->GetIbinY(ibin),
                                             0);
                } else{
                    hd2d_mask_bg->SetOvalElm(hd2d_mask_bg->GetHi2d()->GetIbinX(ibin),
                                             hd2d_mask_bg->GetHi2d()->GetIbinY(ibin),
                                             1);
                }
            }
        }

        long nbin_mask_bg = 0;
        for(long ibin = 0; ibin < hd2d->GetNbin(); ibin++){
            if( hd2d_mask_bg->GetOvalArr()->GetValElm(ibin) > 0){
                nbin_mask_bg ++;
            }
        }
        if(nbin_mask_bg == (int) val_vec.size()){
            break;
        }
    }

    MifFits::OutFitsImageD(argval->GetOutdir(),
                           argval->GetOutfileHead(),
                           "mask_bg",
                           naxis,
                           bitpix,
                           img_info->GetNaxesArr(),
                           hd2d_mask_bg->GetOvalArr()->GetVal());

    // select
    HistDataNerr2d* hd2d_mask_sel = new HistDataNerr2d;
    hd2d_mask_sel->Copy(hd2d_mask);
    for(long ibin = 0; ibin < hd2d->GetNbin(); ibin++){
        if( hd2d_mask->GetOvalArr()->GetValElm(ibin) > 0){
            if( fabs( hd2d->GetOvalArr()->GetValElm(ibin) - mean) < argval->GetSignificance() * stddev){
                hd2d_mask_sel->SetOvalElm(hd2d_mask_sel->GetHi2d()->GetIbinX(ibin),
                                          hd2d_mask_sel->GetHi2d()->GetIbinY(ibin),
                                          0);
            }
        }
    }
    MifFits::OutFitsImageD(argval->GetOutdir(),
                           argval->GetOutfileHead(),
                           "mask_sel",
                           naxis,
                           bitpix,
                           img_info->GetNaxesArr(),
                           hd2d_mask_sel->GetOvalArr()->GetVal());

    // make significance map
    HistDataNerr2d* hd2d_sig = new HistDataNerr2d;
    hd2d_sig->Init(dimx, 0, dimx, dimy, 0, dimy);
    for(long ibin = 0; ibin < hd2d_sig->GetNbin(); ibin++){
        if( hd2d_mask->GetOvalArr()->GetValElm(ibin) > 0){
            double sig = fabs( hd2d->GetOvalArr()->GetValElm(ibin) - mean) / stddev;
            hd2d_sig->SetOvalElm(hd2d_sig->GetHi2d()->GetIbinX(ibin),
                                 hd2d_sig->GetHi2d()->GetIbinY(ibin),
                                 sig);
        }
    }

    HistDataNerr2d* hd2d_sig_signed = new HistDataNerr2d;
    hd2d_sig_signed->Init(dimx, 0, dimx, dimy, 0, dimy);
    for(long ibin = 0; ibin < hd2d_sig_signed->GetNbin(); ibin++){
        if( hd2d_mask->GetOvalArr()->GetValElm(ibin) > 0){
            double sig = ( hd2d->GetOvalArr()->GetValElm(ibin) - mean) / stddev;
            hd2d_sig_signed->SetOvalElm(hd2d_sig->GetHi2d()->GetIbinX(ibin),
                                        hd2d_sig->GetHi2d()->GetIbinY(ibin),
                                        sig);
        }
    }

    
    MifFits::OutFitsImageD(argval->GetOutdir(),
                           argval->GetOutfileHead(),
                           "sigmap",
                           naxis,
                           bitpix,
                           img_info->GetNaxesArr(),
                           hd2d_sig->GetOvalArr()->GetVal());

    MifFits::OutFitsImageD(argval->GetOutdir(),
                           argval->GetOutfileHead(),
                           "sigmap_signed",
                           naxis,
                           bitpix,
                           img_info->GetNaxesArr(),
                           hd2d_sig_signed->GetOvalArr()->GetVal());

    
    // numbering
    char detsrcfile[kLineSize];
    sprintf(detsrcfile, "%s/%s_src.txt",
            argval->GetOutdir().c_str(),
            argval->GetOutfileHead().c_str());
    FILE* fp_src = fopen(detsrcfile, "w");

    char detsrcfile_signed[kLineSize];
    sprintf(detsrcfile_signed, "%s/%s_src_signed.txt",
            argval->GetOutdir().c_str(),
            argval->GetOutfileHead().c_str());
    FILE* fp_src_signed = fopen(detsrcfile_signed, "w");

    
    int niter = 10;
    HistDataNerr2d* hd2d_sig_with_mask = new HistDataNerr2d;
    hd2d_sig_with_mask->Copy(hd2d_sig);
    HistDataNerr2d* hd2d_mask_src = new HistDataNerr2d;
    hd2d_mask_src->Copy(hd2d_mask);
    for(int iiter = 0; iiter < niter; iiter++){
        double sig_most = hd2d_sig_with_mask->GetOvalArr()->GetValMax();
        double xval_most_sig = hd2d_sig_with_mask->GetXvalAtOvalMax();
        double yval_most_sig = hd2d_sig_with_mask->GetYvalAtOvalMax();
        double sig_most_signed = hd2d_sig_signed->GetOvalElmAtXY(xval_most_sig, yval_most_sig);
        
        if(sig_most < argval->GetSignificance()){
            break;
        }
        MiIolib::Printf2(fp_log, "%3d %e sigma src @ (%e, %e) \n",
                         iiter, sig_most, xval_most_sig, yval_most_sig);
        fprintf(fp_src, "%3d %e sigma src @ (%e, %e) in %s\n",
                iiter, sig_most, xval_most_sig, yval_most_sig, argval->GetInfile().c_str());
        fprintf(fp_src_signed, "%3d %e sigma src @ (%e, %e) in %s\n",
                iiter, sig_most_signed, xval_most_sig, yval_most_sig, argval->GetInfile().c_str());

        // calc radius
        HistDataNerr1d* hd1d_rad = new HistDataNerr1d;
        long nbin_rad = (long) MirMath::GetMin(hd2d->GetXvalFullWidth(), hd2d->GetYvalFullWidth()) / 2.;
        double rad_lo = 0.0;
        double rad_up = (double) nbin_rad;
        hd1d_rad->Init(nbin_rad, rad_lo, rad_up);
        for(long ibin = 0; ibin < hd2d_sig_with_mask->GetNbin(); ibin++){
            if(hd2d_mask_src->GetOvalArr()->GetValElm(ibin) > 0){
                double xval = hd2d_sig_with_mask->GetHi2d()->GetBinCenterXFromIbin(ibin);
                double yval = hd2d_sig_with_mask->GetHi2d()->GetBinCenterYFromIbin(ibin);
                double rad = sqrt( pow(xval - xval_most_sig, 2) +
                                   pow(yval - yval_most_sig, 2) );
                if(fabs(hd2d_sig_with_mask->GetOvalArr()->GetValElm(ibin))
                   > argval->GetSignificance()){
                    if(rad_lo <= rad && rad <= rad_up){
                        hd1d_rad->Fill(rad);
                    }
                }
            }
        }
        double radius = 0.0;
        for(long ibin_rad = 0; ibin_rad < nbin_rad; ibin_rad ++){
            if(hd1d_rad->GetOvalElm(ibin_rad) < 1){
                break;
            }
            radius = (ibin_rad + 1) * 1.0;
        }
        delete hd1d_rad;

        printf("radius = %e\n", radius);
        
        // mask circle area around this src
        for(long ibin = 0; ibin < hd2d_mask_src->GetNbin(); ibin++){
            double xval = hd2d_mask_src->GetHi2d()->GetBinCenterXFromIbin(ibin);
            double yval = hd2d_mask_src->GetHi2d()->GetBinCenterYFromIbin(ibin);
            if(radius > sqrt( pow(xval - xval_most_sig, 2) +
                              pow(yval - yval_most_sig, 2) ) ){
                hd2d_mask_src->SetOvalElm(hd2d_mask_src->GetHi2d()->GetIbinX(ibin),
                                          hd2d_mask_src->GetHi2d()->GetIbinY(ibin),
                                          0);
                hd2d_sig_with_mask->SetOvalElm(hd2d_sig_with_mask->GetHi2d()->GetIbinX(ibin),
                                               hd2d_sig_with_mask->GetHi2d()->GetIbinY(ibin),
                                               0);
            }
        }
    }
    fclose(fp_src);
    fclose(fp_src_signed);
    

    MifFits::OutFitsImageD(argval->GetOutdir(),
                           argval->GetOutfileHead(),
                           "mask_src",
                           naxis,
                           bitpix,
                           img_info->GetNaxesArr(),
                           hd2d_mask_src->GetOvalArr()->GetVal());    
    
    
    delete argval;
    
    return status;
}


