#include "mi_iolib.h"
#include "mir_data1d_serr.h"
#include "mir_graph2d_serr.h"
#include "mir_hist1d_serr.h"
#include "mir_hist2d_serr.h"
#include "mifc_gen.h"
#include "mir_qdp_tool.h"

#include "func_user.h"
#include "arg_test_func_unbin_ks_2d.h"

// global variable 
int g_flag_debug = 0;
int g_flag_help = 0;
int g_flag_verbose = 0;

int main(int argc, char* argv[]){

    int status = kRetNormal;
    
    ArgValTestFuncUnbinKs2d* argval = new ArgValTestFuncUnbinKs2d;
    argval->Init(argc, argv);
    argval->Print(stdout);

    MirRootTool* root_tool = new MirRootTool;
    root_tool->InitTCanvas(argval->GetRootStyle());
    
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

    //
    // data
    //
    GraphData2d* gd2d = new GraphData2d;
    gd2d->Load(argval->GetDataFile());
    gd2d->Sort();
    MirQdpTool::MkQdpMode2(da1d,
                            argval->GetOutdir() + "/" + argval->GetOutfileHead() + "_da1d.qdp",
                            "", 0.0);

    //
    // hist of mask
    //
    HistData1d* hd1d_mask = new HistData1d;
    if("none" == argval->GetHistMask()){
        printf("not supported.\n");
        abort();
    } else if("hist_info=" == argval->GetHistMask().substr(0, 10)){
        string hist_info_file = argval->GetHistMask().substr(10);
        HistInfo1d* hi1d = new HistInfo1d;
        hi1d->Load(hist_info_file);
        hd1d_mask->Init(hi1d);
        hd1d_mask->SetOne();
        delete hi1d;
    } else {
        hd1d_mask->Load(argval->GetHistMask());
    }
    MirQdpTool::MkQdp(hd1d_mask,
                       argval->GetOutdir() + "/" + argval->GetOutfileHead() + "_hd1d_mask.qdp",
                       "x,y");
    //
    // extract data according to hd1d_mask
    //
    DataArray1d* da1d_sel = new DataArray1d;
    vector<double> da1d_sel_vec;
    for(long idata = 0; idata < da1d->GetNdata(); idata ++){
        double xval = da1d->GetValElm(idata);
        if(1 == hd1d_mask->GetOvalElmAtX( xval )){
            da1d_sel_vec.push_back(xval);
        }
    }
    da1d_sel->InitSetVal(da1d_sel_vec);
    MirQdpTool::MkQdpMode2(da1d_sel,
                            argval->GetOutdir() + "/" + argval->GetOutfileHead() + "_da1d_sel.qdp",
                            "", 0.0);
    delete da1d;

    //
    // count rate function (c/sec)
    //
    MirFunc* func = FuncUser::GenFunc(argval->GetFuncName());
    MirFuncPar* func_par = new MirFuncPar;
    func_par->Load(argval->GetFuncPar());
    func_par->Print(stdout);


    // hist of function
    HistData1d* hd1d_func = new HistData1d;
    hd1d_func->Init(argval->GetNpointFunc(),
                    hd1d_mask->GetXvalLo(),
                    hd1d_mask->GetXvalUp());
    hd1d_func->SetByFunc(func, func_par->GetPar());

    // hist of function with mask
    HistData1d* hd1d_func_with_mask = new HistData1d;
    hd1d_func_with_mask->Init(argval->GetNpointFunc(),
                              hd1d_mask->GetXvalLo(),
                              hd1d_mask->GetXvalUp());
    for(long ibin = 0; ibin < hd1d_func_with_mask->GetNbinX(); ibin ++){
        double val = hd1d_func->GetOvalElm(ibin) *
            hd1d_mask->GetOvalElmAtX( hd1d_func_with_mask->GetBinCenterX(ibin) );
        hd1d_func_with_mask->SetOvalElm(ibin, val);
    }
    double integral = hd1d_func_with_mask->GetOvalArr()->GetSum()
        * hd1d_func_with_mask->GetBinWidth();

    // hist of PDF
    HistData1d* hd1d_pdf_with_mask = new HistData1d;
    hd1d_pdf_with_mask->Scale(hd1d_func_with_mask, 1./integral, 0.0);
    MirQdpTool::MkQdp(hd1d_pdf_with_mask,
                       argval->GetOutdir() + "/" + argval->GetOutfileHead() + "_pdf.qdp",
                       "x,y");

    // hist of CDF
    HistData1d* hd1d_cdf = new HistData1d;
    hd1d_cdf->Init(argval->GetNpointFunc(),
                   hd1d_mask->GetXvalLo(),
                   hd1d_mask->GetXvalUp());
    double sum = 0.0;
    for(long ibin = 0; ibin < hd1d_cdf->GetNbinX(); ibin ++){
        sum += hd1d_pdf_with_mask->GetOvalElm(ibin)
            * hd1d_pdf_with_mask->GetBinWidth();
        hd1d_cdf->SetOvalElm(ibin, sum);
    }
    MirQdpTool::MkQdp(hd1d_cdf,
                       argval->GetOutdir() + "/" + argval->GetOutfileHead() + "_cdf.qdp",
                       "x,y");

    // K-S test
    GraphData2d* gd2d_cdf_da1d = new GraphData2d;
    gd2d_cdf_da1d->Init();
    vector<double> cdf_da1d_xval_vec;
    vector<double> cdf_da1d_yval_vec;
    double diff_max = 0.0;
    double val_cdf_da1d_pre = 0.0;
    for(long idata = 0; idata < da1d_sel->GetNdata(); idata ++){
        double val_cdf_da1d = (idata + 1.) / da1d_sel->GetNdata(); // data's CDF after this step
        double val_cdf_func = hd1d_cdf->GetOvalElmAtX( da1d_sel->GetValElm(idata) );
        cdf_da1d_xval_vec.push_back(da1d_sel->GetValElm(idata));
        cdf_da1d_yval_vec.push_back(val_cdf_da1d);
        double diff = MirMath::GetMax(
            fabs( val_cdf_da1d     - val_cdf_func ),
            fabs( val_cdf_da1d_pre - val_cdf_func ));
        if(diff > diff_max){
            diff_max = diff;
        }
        val_cdf_da1d_pre = val_cdf_da1d;
    }
    gd2d_cdf_da1d->SetXvalArrDbl(cdf_da1d_xval_vec);
    gd2d_cdf_da1d->SetOvalArrDbl(cdf_da1d_yval_vec);

    MirQdpTool::MkQdp(gd2d_cdf_da1d,
                       argval->GetOutdir() + "/" + argval->GetOutfileHead() + "_da1d_cdf.qdp",
                       "x,y");
    
    printf("D of KS-test = %e\n", diff_max);
    double z_ks = ( sqrt(da1d_sel->GetNdata()) + 0.12 + 0.11 / sqrt(da1d_sel->GetNdata()) ) * diff_max;
    double p_value = TMath::KolmogorovProb(z_ks);
    printf("p_value of KS-test = %e\n", p_value);


    // compare between CDFs of data and model
    FILE* fp_qdp_comp = fopen(
        (argval->GetOutdir() + "/" + argval->GetOutfileHead() + "_cdf_model+da1d.qdp").c_str(), "w");
    fprintf(fp_qdp_comp, "skip sing\n");
    fprintf(fp_qdp_comp, "\n");
    gd2d_cdf_da1d->PrintData(fp_qdp_comp, "x,y");
    fprintf(fp_qdp_comp, "\n");
    fprintf(fp_qdp_comp, "no\n");
    fprintf(fp_qdp_comp, "\n");
    hd1d_cdf->PrintData(fp_qdp_comp, "x,y");
    fprintf(fp_qdp_comp, "\n");
    fprintf(fp_qdp_comp, "la file\n");
    fprintf(fp_qdp_comp, "time off\n");
    fprintf(fp_qdp_comp, "lw 5\n");
    fprintf(fp_qdp_comp, "csize 1.2\n");
    fprintf(fp_qdp_comp, "la rot\n");
    fclose(fp_qdp_comp);

    
    delete argval;
    delete hd1d_mask;
    delete da1d_sel;
    delete func;
    delete func_par;
    delete hd1d_func;
    delete hd1d_func_with_mask;
    delete hd1d_pdf_with_mask;
    delete hd1d_cdf;
    delete gd2d_cdf_da1d;
    fclose(fp_log);

    
    return status;
}

