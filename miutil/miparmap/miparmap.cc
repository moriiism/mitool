#include "mi_iolib.h"
#include "mir_root_tool.h"
#include "mir_hist2d_nerr.h"
#include "mir_qdp_tool.h"
#include "arg_miparmap.h"
#include "TColor.h"

// global variable 
int g_flag_debug = 0;
int g_flag_help = 0;
int g_flag_verbose = 0;

int main(int argc, char* argv[]){
    int status = kRetNormal;
  
    ArgValMiparmap* argval = new ArgValMiparmap;
    argval->Init(argc, argv);

    MirRootTool* root_tool = new MirRootTool;
    root_tool->InitTCanvas("pub");
    if( MiIolib::TestFileExist(argval->GetOutdir()) ){
        char cmd[kLineSize];
        sprintf(cmd, "mkdir -p %s", argval->GetOutdir().c_str());
        system(cmd);
    }


    string* lines_arr = NULL;
    long nline = 0;
    MiIolib::GenReadFileSkipComment(argval->GetInfile(),
                                    &lines_arr,
                                    &nline);
    double* mu_arr = new double [nline];
    double* beta_arr = new double [nline];
    double* ave_arr = new double [nline];
    for(long iline = 0; iline < nline; iline ++){
        int nsplit = 0;
        string* split_arr = NULL;
        MiStr::GenSplit(lines_arr[iline], &nsplit, &split_arr);

        mu_arr[iline]   = atof(split_arr[0].c_str());
        beta_arr[iline] = atof(split_arr[1].c_str());
        ave_arr[iline]  = atof(split_arr[2].c_str());
        MiStr::DelSplit(split_arr);

        printf("%e %e %e\n", mu_arr[iline], beta_arr[iline], ave_arr[iline]);
    }

    double ave_min = 1.0e10;
    double mu_min  = 0.0;
    double beta_min  = 0.0;
    HistInfo2d* hi2d = new HistInfo2d;
    hi2d->Load(argval->GetHistInfoFile());
    HistDataNerr2d* hd2d = new HistDataNerr2d;
    hd2d->Init(hi2d);
    for(long iline = 0; iline < nline; iline ++){
        hd2d->Fill(mu_arr[iline], beta_arr[iline], ave_arr[iline]);

        if(ave_arr[iline] < ave_min){
            ave_min = ave_arr[iline];
            mu_min = mu_arr[iline];
            beta_min = beta_arr[iline];
        }
        
    }

    //printf("min at (%e, %e)\n",
    //       hd2d->GetXvalAtOvalMin(),
    //       hd2d->GetYvalAtOvalMin());
    printf("min at (mu, beta) = (%e, %e)\n", mu_min, beta_min);
    
    double zrange_lo = argval->GetZrangeLo();
    double zrange_up = argval->GetZrangeUp();
    
    TH2D* th2d = hd2d->GenTH2D(0, 0, 0);
    th2d->SetAxisRange(zrange_lo, zrange_up, "Z");
    gStyle->SetPalette(53);
    // TColor::InvertPalette();
    th2d->Draw("COLZ");
    
    
    gPad->Update();
    // TPaletteAxis* palette = (TPaletteAxis*) th2d->GetListOfFunctions()->FindObject("palette");
//    palette->SetX1NDC(0.86);
//    palette->SetX2NDC(0.89);
    th2d->GetXaxis()->SetTitleSize(0.05);
    th2d->GetYaxis()->SetTitleSize(0.05);
    th2d->GetXaxis()->SetLabelSize(0.05);
    th2d->GetYaxis()->SetLabelSize(0.05);

    char outfig[kLineSize];
    sprintf(outfig, "%s/%s.png",
            argval->GetOutdir().c_str(),
            argval->GetOutfileHead().c_str());
//    hd2d->MkTH2FigZrange(outfig, root_tool,
//                         2.27e-2, 2.300e-2,
//                         //7.2e-2, 7.3e-2,
//                         0.0, 0.0, 0.0,
//                         "mu", "beta", "ave");

    root_tool->GetTCanvas()->Print(outfig);
    
    delete argval;
    
    return status;
}


