#include "mi_iolib.h"
#include "mir_graph2d_nerr.h"
#include "mir_graph2d_ope.h"
#include "mir_qdp_tool.h"
#include "arg_migetsigda1d.h"

// global variable 
int g_flag_debug = 0;
int g_flag_help = 0;
int g_flag_verbose = 0;

int main(int argc, char* argv[]){
    int status = kRetNormal;
  
    ArgValMigetsigda1d* argval = new ArgValMigetsigda1d;
    argval->Init(argc, argv);
    
    if( MiIolib::TestFileExist(argval->GetOutdir()) ){
        char cmd[kLineSize];
        sprintf(cmd, "mkdir -p %s", argval->GetOutdir().c_str());
        int ret = system(cmd);
        (void) ret;
    }

    //
    // load data
    //
    GraphDataNerr2d* gd2d = new GraphDataNerr2d;
    gd2d->Load(argval->GetInfile());
    DataArrayNerr1d* da1d = new DataArrayNerr1d;
    da1d->Copy(gd2d->GetOvalArr());

    GraphDataNerr2d* gd2d_mask = new GraphDataNerr2d;
    gd2d_mask->Load(argval->GetInfileMask());
    DataArrayNerr1d* da1d_mask = new DataArrayNerr1d;
    da1d_mask->Copy(gd2d_mask->GetOvalArr());
    
    double mean   = MirMath::GetAMean(da1d->GetNdata(), da1d->GetVal());
    double stddev = MirMath::GetSqrtOfUnbiasedVariance(da1d->GetNdata(), da1d->GetVal());
    double median = MirMath::GetMedian(da1d->GetNdata(), da1d->GetVal());
    printf("mean, stddev, median = %e, %e, %e\n", mean, stddev, median);


    DataArrayNerr1d* da1d_mask_bg = new DataArrayNerr1d;
    da1d_mask_bg->Copy(da1d_mask);

    for(int iclip = 0; iclip < argval->GetNclip(); iclip++){
        // get mean, stddev
        vector<double> val_vec;
        for(long idata = 0; idata < da1d->GetNdata(); idata++){
            if( da1d_mask_bg->GetValElm(idata) > 0){
                val_vec.push_back(da1d->GetValElm(idata));
            }
        }
        mean   = MirMath::GetAMean(val_vec);
        stddev = MirMath::GetSqrtOfUnbiasedVariance(val_vec);
        printf("iclip, mean, stddev, nsize = %d, %e, %e, %d\n", iclip, mean, stddev, (int) val_vec.size());

        for(long idata = 0; idata < da1d->GetNdata(); idata++){
            if( da1d_mask_bg->GetValElm(idata) > 0){
                if( da1d->GetValElm(idata) >  mean + argval->GetSignificance() * stddev){
                    da1d_mask_bg->SetValElm(idata, 0);
                } else if( da1d->GetValElm(idata) <  mean - argval->GetSignificance() * stddev){
                    if(da1d->GetValElm(idata) < 0.0){
                        da1d_mask_bg->SetValElm(idata, 0);
                    }
                } else{
                    da1d_mask_bg->SetValElm(idata, 1);
                }
            }
        }

        long nbin_mask_bg = 0;
        for(long idata = 0; idata < da1d->GetNdata(); idata++){
            if( da1d_mask_bg->GetValElm(idata) > 0){
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
    da1d_mask_bg->Save(outfile_mask_bg, 1, 0.0);

    // select
    DataArrayNerr1d* da1d_mask_sel = new DataArrayNerr1d;
    da1d_mask_sel->Copy(da1d_mask);
    
    for(long idata = 0; idata < da1d->GetNdata(); idata++){
        if(da1d_mask->GetValElm(idata) > 0){
            if( fabs(da1d->GetValElm(idata) - mean) < argval->GetSignificance() * stddev){
                da1d_mask_sel->SetValElm(idata, 0);
            }
        }
    }

    char outfile_mask_sel[kLineSize];
    sprintf(outfile_mask_sel, "%s/%s_mask_sel.dat",
            argval->GetOutdir().c_str(),
            argval->GetOutfileHead().c_str());
    da1d_mask_sel->Save(outfile_mask_sel, 1, 0.0);
    
    delete argval;
    
    return status;
}


