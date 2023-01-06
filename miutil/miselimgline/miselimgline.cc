#include "fitsio.h"
#include "mi_str.h"
#include "mi_iolib.h"
#include "mif_fits.h"
#include "mif_img_info.h"
#include "mir_root_tool.h"
#include "mir_hist1d_nerr.h"
#include "mir_hist2d_nerr.h"
#include "arg_miselimgline.h"

// global variable 
int g_flag_debug = 0;
int g_flag_help = 0;
int g_flag_verbose = 0;

int main(int argc, char* argv[])
{
    int status_prog = kRetNormal;
    
    ArgValMiselimgline* argval = new ArgValMiselimgline;
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
    char outfig[kLineSize];
    sprintf(outfig, "%s/%s.png",
            argval->GetOutdir().c_str(),
            argval->GetOutfileHead().c_str());
    hd2d->MkTH2Fig(outfig, root_tool);

    int nline = argval->GetLineEd() - argval->GetLineSt() + 1;
    DataArrayNerr1d** da1d_arr = new DataArrayNerr1d* [nline];
    HistDataNerr1d** hd1d_arr = new HistDataNerr1d* [nline];
    if("row" == argval->GetRowOrCol()){
        for(long iline = 0; iline < nline; iline++){
            long ibiny = argval->GetLineSt() + iline;
            da1d_arr[iline] = new DataArrayNerr1d;
            da1d_arr[iline]->Init(dimx);
            hd1d_arr[iline] = new HistDataNerr1d;
            hd1d_arr[iline]->Init(dimx, 0, dimx);
            for(long ibinx = 0; ibinx < dimx; ibinx ++){
                da1d_arr[iline]->SetValElm(ibinx, hd2d->GetOvalElm(ibinx, ibiny));
                hd1d_arr[iline]->SetOvalElm(ibinx, hd2d->GetOvalElm(ibinx, ibiny));
            }
        }
    } else if("col" == argval->GetRowOrCol()){
        for(long iline = 0; iline < nline; iline++){
            long ibinx = argval->GetLineSt() + iline;
            da1d_arr[iline] = new DataArrayNerr1d;
            da1d_arr[iline]->Init(dimy);
            hd1d_arr[iline] = new HistDataNerr1d;
            hd1d_arr[iline]->Init(dimy, 0, dimy);
            for(long ibiny = 0; ibiny < dimy; ibiny ++){
                da1d_arr[iline]->SetValElm(ibiny, hd2d->GetOvalElm(ibinx, ibiny));
                hd1d_arr[iline]->SetOvalElm(ibiny, hd2d->GetOvalElm(ibinx, ibiny));
            }
        }
    } else {
        printf("bad row_or_col: %s\n", argval->GetRowOrCol().c_str());
        abort();
    }

    for(int iline = 0; iline < nline; iline ++){
        char outfile[kLineSize];
        sprintf(outfile, "%s/%s_%s_da1d_%3.3d.dat",
                argval->GetOutdir().c_str(),
                argval->GetOutfileHead().c_str(),
                argval->GetRowOrCol().c_str(),
                iline);
        printf("%s\n", outfile);
        da1d_arr[iline]->Save(outfile, 1, 0.0);

        char outfile_hist[kLineSize];
        sprintf(outfile_hist, "%s/%s_%s_hd1d_%3.3d.dat",
                argval->GetOutdir().c_str(),
                argval->GetOutfileHead().c_str(),
                argval->GetRowOrCol().c_str(),
                iline);
        printf("%s\n", outfile_hist);
        hd1d_arr[iline]->Save(outfile_hist, "x,y");
    }
    
    return status_prog;
}


