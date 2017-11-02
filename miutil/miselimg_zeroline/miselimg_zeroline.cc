#include "fitsio.h"
#include "mi_str.h"
#include "mi_iolib.h"
#include "mif_fits.h"
#include "mif_img_info.h"
#include "mir_root_tool.h"
#include "mir_hist1d_nerr.h"
#include "mir_hist2d_nerr.h"
#include "mir_hist2d_ope.h"
#include "arg_miselimg_zeroline.h"

// global variable 
int g_flag_debug = 0;
int g_flag_help = 0;
int g_flag_verbose = 0;

int main(int argc, char* argv[])
{
    int status_prog = kRetNormal;
    
    ArgValMiselimgZeroline* argval = new ArgValMiselimgZeroline;
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

    HistDataNerr2d* hd2d = new HistDataNerr2d;
    hd2d->Init(dimx, 0, dimx, dimy, 0, dimy);
    hd2d->SetOvalArr(dimx * dimy, X_mat);
    char outfig_org[kLineSize];
    sprintf(outfig_org, "%s/%s_org.png",
            argval->GetOutdir().c_str(),
            argval->GetOutfileHead().c_str());
    hd2d->MkTH2Fig(outfig_org, root_tool);

    HistDataNerr1d* hd1d_amean  = new HistDataNerr1d;
    HistDataNerr1d* hd1d_stddev = new HistDataNerr1d;
    if("row" == argval->GetRowOrCol()){
        HistData2dOpe::GetProjectX(hd2d,
                                   0, dimy - 1,
                                   "amean",
                                   hd1d_amean);
        HistData2dOpe::GetProjectX(hd2d,
                                   0, dimy - 1,
                                   "stddev",
                                   hd1d_stddev);
    } else if("col" == argval->GetRowOrCol()){
        HistData2dOpe::GetProjectY(hd2d,
                                   0, dimx - 1,
                                   "amean",
                                   hd1d_amean);
        HistData2dOpe::GetProjectY(hd2d,
                                   0, dimx - 1,
                                   "stddev",
                                   hd1d_stddev);
    } else {
        printf("bad row_or_col: %s\n", argval->GetRowOrCol().c_str());
        abort();
    }

    // mask
    HistDataNerr2d* hd2d_mask = new HistDataNerr2d;
    HistDataNerr1d* hd1d_mask = new HistDataNerr1d;
    hd2d_mask->Init(dimx, 0, dimx, dimy, 0, dimy);
    if("row" == argval->GetRowOrCol()){
        hd1d_mask->Init(dimx, 0, dimx);
        for(long ibinx = 0; ibinx < dimx; ibinx++){
            if( argval->GetStddevThreshold() > hd1d_stddev->GetOvalElm(ibinx) ){
                hd1d_mask->SetOvalElm(ibinx, 0);
                for(long ibiny = 0; ibiny < dimy; ibiny++){
                    hd2d_mask->SetOvalElm(ibinx, ibiny, 0);
                }
            } else{
                hd1d_mask->SetOvalElm(ibinx, 1);
                for(long ibiny = 0; ibiny < dimy; ibiny++){
                    hd2d_mask->SetOvalElm(ibinx, ibiny, 1);
                }
            }
        }
    } else if("col" == argval->GetRowOrCol()){
        hd1d_mask->Init(dimy, 0, dimy);
        for(long ibiny = 0; ibiny < dimy; ibiny++){        
            if( argval->GetStddevThreshold() > hd1d_stddev->GetOvalElm(ibiny) ){
                hd1d_mask->SetOvalElm(ibiny, 0);
                for(long ibinx = 0; ibinx < dimx; ibinx++){
                    hd2d_mask->SetOvalElm(ibinx, ibiny, 0);
                }
            } else{
                hd1d_mask->SetOvalElm(ibiny, 1);
                for(long ibinx = 0; ibinx < dimx; ibinx++){                
                    hd2d_mask->SetOvalElm(ibinx, ibiny, 1);
                }
            }
        }
    } else {
        printf("bad row_or_col: %s\n", argval->GetRowOrCol().c_str());
        abort();
    }

    char outfig_mask2d[kLineSize];
    sprintf(outfig_mask2d, "%s/%s_mask2d.png",
            argval->GetOutdir().c_str(),
            argval->GetOutfileHead().c_str());
    hd2d_mask->MkTH2Fig(outfig_mask2d, root_tool);

    char outfig_mask1d[kLineSize];
    sprintf(outfig_mask1d, "%s/%s_mask1d.png",
            argval->GetOutdir().c_str(),
            argval->GetOutfileHead().c_str());
    hd1d_mask->MkTH1Fig(outfig_mask1d, root_tool, 0.0, 0.0);
    
    char outfig_stddev[kLineSize];
    sprintf(outfig_stddev, "%s/%s_stddev_%s.png",
            argval->GetOutdir().c_str(),
            argval->GetOutfileHead().c_str(),
            argval->GetRowOrCol().c_str());
    hd1d_stddev->MkTH1Fig(outfig_stddev, root_tool, 0.0, 0.0);


    char out_mask1d[kLineSize];
    sprintf(out_mask1d, "%s/%s_mask1d.dat",
            argval->GetOutdir().c_str(),
            argval->GetOutfileHead().c_str());
    hd1d_mask->Save(out_mask1d, "x,y");

    char out_mask1d_da1d[kLineSize];
    sprintf(out_mask1d_da1d, "%s/%s_mask1d_da1d.dat",
            argval->GetOutdir().c_str(),
            argval->GetOutfileHead().c_str());
    hd1d_mask->GetOvalArr()->Save(out_mask1d_da1d, 1, 0.0);
    
    return status_prog;
}


