#include "mi_iolib.h"
#include "mir_graph2d_nerr.h"
#include "mir_graph2d_ope.h"
#include "mir_qdp_tool.h"
#include "arg_migetsighd1d.h"

// global variable 
int g_flag_debug = 0;
int g_flag_help = 0;
int g_flag_verbose = 0;

int main(int argc, char* argv[]){
    int status = kRetNormal;
  
    ArgValMigetsighd1d* argval = new ArgValMigetsighd1d;
    argval->Init(argc, argv);
    
    if( MiIolib::TestFileExist(argval->GetOutdir()) ){
        char cmd[kLineSize];
        sprintf(cmd, "mkdir -p %s", argval->GetOutdir().c_str());
        int ret = system(cmd);
        (void) ret;
    }
    char logfile[kLineSize];
    sprintf(logfile, "%s/%s_%s.log",
            argval->GetOutdir().c_str(),
            argval->GetOutfileHead().c_str(),
            argval->GetProgname().c_str());
    FILE* fp_log = fopen(logfile, "w");
    MiIolib::Printf2(fp_log, "-----------------------------\n");
    argval->Print(fp_log);

    //
    // load data
    //
    HistDataNerr1d* hd1d = new HistDataNerr1d;
    hd1d->Load(argval->GetInfile());
    HistDataNerr1d* hd1d_mask = new HistDataNerr1d;
    hd1d_mask->Load(argval->GetInfileMask());
    
    double mean   = 0.0;
    double stddev = 0.0;
    HistDataNerr1d* hd1d_mask_bg = new HistDataNerr1d;
    hd1d_mask_bg->Copy(hd1d_mask);
    
    for(int iclip = 0; iclip < argval->GetNclip(); iclip++){
        // get mean, stddev
        vector<double> val_vec;
        for(long ibin = 0; ibin < hd1d->GetNbinX(); ibin++){
            if( hd1d_mask_bg->GetOvalElm(ibin) > 0){
                val_vec.push_back(hd1d->GetOvalElm(ibin));
            }
        }
        mean   = MirMath::GetAMean(val_vec);
        stddev = MirMath::GetSqrtOfUnbiasedVariance(val_vec);
        printf("iclip, mean, stddev, nsize = %d, %e, %e, %d\n", iclip, mean, stddev, (int) val_vec.size());

        for(long ibin = 0; ibin < hd1d->GetNbinX(); ibin++){
            if( hd1d_mask_bg->GetOvalElm(ibin) > 0){
                if( fabs(hd1d->GetOvalElm(ibin) - mean) > argval->GetSignificanceBg() * stddev){
                    hd1d_mask_bg->SetOvalElm(ibin, 0);
                } else{
                    hd1d_mask_bg->SetOvalElm(ibin, 1);
                }
            }
        }

        long nbin_mask_bg = 0;
        for(long ibin = 0; ibin < hd1d->GetNbinX(); ibin++){
            if( hd1d_mask_bg->GetOvalElm(ibin) > 0){
                nbin_mask_bg ++;
            }
        }
        if(nbin_mask_bg == (int) val_vec.size()){
            break;
        }
    }

    char outfile_mask_bg[kLineSize];
    sprintf(outfile_mask_bg, "%s/%s_mask_bg.dat",
            argval->GetOutdir().c_str(),
            argval->GetOutfileHead().c_str());
    hd1d_mask_bg->Save(outfile_mask_bg, "x,y");

    // select
    HistDataNerr1d* hd1d_mask_sel = new HistDataNerr1d;
    hd1d_mask_sel->Copy(hd1d_mask);
    for(long ibin = 0; ibin < hd1d->GetNbinX(); ibin++){
        if(hd1d_mask->GetOvalElm(ibin) > 0){
            if( fabs(hd1d->GetOvalElm(ibin) - mean) < argval->GetSignificanceBg() * stddev){
                hd1d_mask_sel->SetOvalElm(ibin, 0);
            }
        }
    }

    // make significance hist
    HistDataNerr1d* hd1d_sig = new HistDataNerr1d;
    hd1d_sig->Init(hd1d->GetHi1d());
    for(long ibin = 0; ibin < hd1d_sig->GetNbinX(); ibin++){
        if( hd1d_mask->GetOvalArr()->GetValElm(ibin) > 0){
            double sig = fabs( hd1d->GetOvalArr()->GetValElm(ibin) - mean) / stddev;
            hd1d_sig->SetOvalElm(ibin, sig);
        }
    }

    HistDataNerr1d* hd1d_sig_signed = new HistDataNerr1d;
    hd1d_sig_signed->Init(hd1d->GetHi1d());
    for(long ibin = 0; ibin < hd1d_sig_signed->GetNbinX(); ibin++){
        if( hd1d_mask->GetOvalArr()->GetValElm(ibin) > 0){
            double sig = (hd1d->GetOvalArr()->GetValElm(ibin) - mean) / stddev;
            hd1d_sig_signed->SetOvalElm(ibin, sig);
        }
    }

    char outfile_sig[kLineSize];
    sprintf(outfile_sig, "%s/%s_sig.dat",
            argval->GetOutdir().c_str(),
            argval->GetOutfileHead().c_str());
    hd1d_sig->Save(outfile_sig, "x,y");

    char outfile_sig_signed[kLineSize];
    sprintf(outfile_sig_signed, "%s/%s_sig_signed.dat",
            argval->GetOutdir().c_str(),
            argval->GetOutfileHead().c_str());
    hd1d_sig_signed->Save(outfile_sig_signed, "x,y");
    
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
    HistDataNerr1d* hd1d_sig_with_mask = new HistDataNerr1d;
    hd1d_sig_with_mask->Copy(hd1d_sig);
    HistDataNerr1d* hd1d_mask_src = new HistDataNerr1d;
    hd1d_mask_src->Copy(hd1d_mask);
    for(int iiter = 0; iiter < niter; iiter++){
        double sig_most = hd1d_sig_with_mask->GetOvalArr()->GetValMax();
        double xval_most_sig = hd1d_sig_with_mask->GetXvalAtOvalMax();
        double sig_most_signed = hd1d_sig_signed->GetOvalElmAtX(xval_most_sig);
        if(sig_most < argval->GetSignificanceSrc()){
            break;
        }
        MiIolib::Printf2(fp_log, "%3d %e sigma src @ %e \n",
                         iiter, sig_most, xval_most_sig);
        fprintf(fp_src, "%3d %e sigma src @ %e in %s\n",
                iiter, sig_most, xval_most_sig, argval->GetInfile().c_str());
        fprintf(fp_src_signed, "%3d %e sigma src @ %e in %s\n",
                iiter, sig_most_signed, xval_most_sig, argval->GetInfile().c_str());
        
        // calc half width
        HistDataNerr1d* hd1d_hwidth = new HistDataNerr1d;
        long nbin_hwidth = (long) hd1d->GetXvalFullWidth() / 2.;
        double hwidth_lo = 0.0;
        double hwidth_up = (double) nbin_hwidth;
        hd1d_hwidth->Init(nbin_hwidth, hwidth_lo, hwidth_up);
        for(long ibin = 0; ibin < hd1d_sig_with_mask->GetNbinX(); ibin++){
            if(hd1d_mask_src->GetOvalElm(ibin) > 0){
                double xval = hd1d_sig_with_mask->GetHi1d()->GetBinCenter(ibin);
                double hwidth = fabs(xval - xval_most_sig);
                if(fabs(hd1d_sig_with_mask->GetOvalElm(ibin))
                   > argval->GetSignificanceSrc()){
                    if(hwidth_lo <= hwidth && hwidth <= hwidth_up){
                        hd1d_hwidth->Fill(hwidth);
                    }
                }
            }
        }
        double hwidth = 0.0;
        for(long ibin_hwidth = 0; ibin_hwidth < nbin_hwidth; ibin_hwidth ++){
            if(hd1d_hwidth->GetOvalElm(ibin_hwidth) < 1){
                break;
            }
            hwidth = (ibin_hwidth + 1) * 1.0;
        }
        delete hd1d_hwidth;

        // mask half width area around this src
        for(long ibin = 0; ibin < hd1d_mask_src->GetNbinX(); ibin++){
            double xval = hd1d_mask_src->GetHi1d()->GetBinCenter(ibin);
            if(hwidth > fabs(xval - xval_most_sig) ){
                hd1d_mask_src->SetOvalElm(hd1d_mask_src->GetHi1d()->GetIbin(ibin), 0);
                hd1d_sig_with_mask->SetOvalElm(hd1d_sig_with_mask->GetHi1d()->GetIbin(ibin), 0);
            }
        }
    }
    fclose(fp_src);
    fclose(fp_src_signed);

    char outfile_mask_src[kLineSize];
    sprintf(outfile_mask_src, "%s/%s_mask_src.dat",
            argval->GetOutdir().c_str(),
            argval->GetOutfileHead().c_str());
    hd1d_mask_src->Save(outfile_mask_src, "x,y");
    
    delete argval;
    
    return status;
}


