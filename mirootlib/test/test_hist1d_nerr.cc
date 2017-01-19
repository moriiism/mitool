#include "mi_str.h"
#include "mi_iolib.h"
#include "mir_hist1d_nerr.h"
#include "mir_root_tool.h"

// global variable 
int g_flag_debug = 0;
int g_flag_help = 0;
int g_flag_verbose = 0;

int main(int argc, char* argv[])
{
    int status_prog = kRetNormal;

//    void Init(long nbin_xval,
//              double xval_lo,
//              double xval_up);
    {
        printf("--- test Init;\n");
        HistDataNerr1d* hd1d = new HistDataNerr1d("hd1d");
        long nbin = 10;
        double lo = 0.0;
        double up = 10.0;
        hd1d->Init(nbin, lo, up);
        hd1d->SetConst(10.0);

        MirRootTool* root_tool = new MirRootTool;
        root_tool->InitTCanvas("def");
        
        TH1D* th1d = hd1d->GenTH1D(0.0, 0.0);
        th1d->Draw();
        root_tool->GetTCanvas()->Print("temp.png");

        delete hd1d;
        delete root_tool;
        
        printf("=== \n");
    }


    
//    void Init(const HistInfo1d* const hist_info);
//    HistDataNerr1d* const Clone() const;
//    void Load(string file);
//    const DataArrayNerr1d* const GetOvalArr() const;
//    void PrintData(FILE* fp, string format,
//                   double offset_xval,
//                   double offset_oval) const;
//    HistDataNerr1d* const GenHd1MaxInBin(long nbin_new) const;
//    GraphDataNerr2d* const GenGraph2d() const;
//    TH1D* const GenTH1D(double offset_xval,
//                        double offset_oval) const;
//
//     void FillRandom(const MirFunc* const func,
//                     const MirFuncPar* const func_par,
//                     int rand_seed = 1);
//    void FillRandom(const MirFunc* const func,
//                    const MirFuncPar* const func_par,
//                    const MirFunc* const func_sigma,
//                    const MirFuncPar* const func_par_sigma,
//                    int rand_seed = 1);
//    void FillRandom(const HistData1d* const hist_data,
//                    int rand_seed = 1);


    return status_prog;
}
