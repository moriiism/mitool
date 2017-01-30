#include "mi_str.h"
#include "mi_iolib.h"
#include "mir_hist2d_serr.h"
#include "mir_root_tool.h"

// global variable 
int g_flag_debug = 0;
int g_flag_help = 0;
int g_flag_verbose = 0;

int main(int argc, char* argv[])
{
    int status_prog = kRetNormal;

//    void Init(long nbin_xval, double xval_lo, double xval_up,
//              long nbin_yval, double yval_lo, double yval_up);
    {
        printf("--- test Init;\n");
        HistDataSerr2d* hd2d = new HistDataSerr2d("hd2d");
        hd2d->Init(2, 0.0, 2.0, 3, 0.0, 3.0);
        hd2d->SetConst(10.0);

        MirRootTool* root_tool = new MirRootTool;
        root_tool->InitTCanvas("pub");
        
        TH2D* th2d = hd2d->GenTH2D(0.0, 0.0, 0.0);
        th2d->Draw("text");
        root_tool->GetTCanvas()->Print("temp.png");

        delete hd2d;
        delete root_tool;
        delete th2d;
        
        printf("=== \n");
    }

//    void Init(const HistInfo2d* const hist_info);
    {
        printf("--- test Init;\n");
        HistDataSerr2d* hd2d = new HistDataSerr2d("hd2d");
        HistInfo2d* hi2d = new HistInfo2d;
        hi2d->InitSetByNbin(0.0, 2.0, 2, 0.0, 3.0, 3);
        hd2d->Init(hi2d);
        hd2d->SetConst(10.0);

        MirRootTool* root_tool = new MirRootTool;
        root_tool->InitTCanvas("pub");
        
        TH2D* th2d = hd2d->GenTH2D(0.0, 0.0, 0.0);
        th2d->Draw("text");
        root_tool->GetTCanvas()->Print("temp.png");
        
        delete hd2d;
        delete hi2d;
        delete root_tool;
        delete th2d;
        
        printf("=== \n");
    }

//    void SetOvalSerrArr(long ndata, const double* const val_serr);
    {
        printf("--- test SetOvalSerrArr(long ndata, const double* const val_serr)\n");
        HistDataSerr2d* hd2d = new HistDataSerr2d("hd2d");
        hd2d->Init(2, 0.0, 2.0, 3, 0.0, 3.0);
        double val[6];
        double val_serr[6];
        val[0] = 1.0;
        val[1] = 2.0;
        val[2] = 3.0;
        val[3] = 4.0;
        val[4] = 5.0;
        val[5] = 6.0;
        val_serr[0] = 0.4;
        val_serr[1] = 0.5;
        val_serr[2] = 0.6;
        val_serr[3] = 0.7;
        val_serr[4] = 0.8;
        val_serr[5] = 0.9;
        hd2d->SetOvalArr(6, val);
        hd2d->SetOvalSerrArr(6, val_serr);

        hd2d->PrintData(stdout, "x,xe,y,ye,z,ze", 0.0, 0.0, 0.0);
        
        MirRootTool* root_tool = new MirRootTool;
        root_tool->InitTCanvas("pub");
        
        TH2D* th2d = hd2d->GenTH2D(0.0, 0.0, 0.0);
        th2d->Draw("text");
        root_tool->GetTCanvas()->Print("temp.png");
        
        delete hd2d;
        delete root_tool;
        delete th2d;
        
        printf("=== \n");
    }

//    void SetOvalSerrArr(vector<double> val_serr);    
    {
        printf("--- test SetOvalSerrArr(vector<double> val_serr)\n");
        HistDataSerr2d* hd2d = new HistDataSerr2d("hd2d");
        hd2d->Init(2, 0.0, 2.0, 3, 0.0, 3.0);
        vector<double> val(6);
        vector<double> val_serr(6);
        val[0] = 1.0;
        val[1] = 2.0;
        val[2] = 3.0;
        val[3] = 4.0;
        val[4] = 5.0;
        val[5] = 6.0;
        val_serr[0] = 0.4;
        val_serr[1] = 0.5;
        val_serr[2] = 0.6;
        val_serr[3] = 0.7;
        val_serr[4] = 0.8;
        val_serr[5] = 0.9;
        hd2d->SetOvalArr(val);
        hd2d->SetOvalSerrArr(val_serr);

        hd2d->PrintData(stdout, "x,xe,y,ye,z,ze", 0.0, 0.0, 0.0);
        
        MirRootTool* root_tool = new MirRootTool;
        root_tool->InitTCanvas("pub");
        
        TH2D* th2d = hd2d->GenTH2D(0.0, 0.0, 0.0);
        th2d->Draw("text");
        root_tool->GetTCanvas()->Print("temp.png");
        
        delete hd2d;
        delete root_tool;
        delete th2d;
        
        printf("=== \n");
    }

//    void SetOvalSerrElm(long ibin_xval, long ibin_yval, double oval_serr);
    {
        printf("--- test SetOvalSerrElm(long ibin_xval, long ibin_yval, double oval_serr)\n");
        HistDataSerr2d* hd2d = new HistDataSerr2d("hd2d");
        hd2d->Init(2, 0.0, 2.0, 3, 0.0, 3.0);
        hd2d->SetOvalElm(0, 0, 10.0);
        hd2d->SetOvalElm(1, 0, 20.0);
        hd2d->SetOvalElm(0, 1, 30.0);
        hd2d->SetOvalElm(1, 1, 40.0);
        hd2d->SetOvalElm(0, 2, 50.0);
        hd2d->SetOvalElm(1, 2, 60.0);
        hd2d->SetOvalSerrElm(0, 0, 1.0);
        hd2d->SetOvalSerrElm(1, 0, 1.5);
        hd2d->SetOvalSerrElm(0, 1, 2.0);
        hd2d->SetOvalSerrElm(1, 1, 2.5);
        hd2d->SetOvalSerrElm(0, 2, 3.0);
        hd2d->SetOvalSerrElm(1, 2, 3.5);
        hd2d->PrintData(stdout, "x,xe,y,ye,z,ze", 0.0, 0.0, 0.0);
        
        delete hd2d;
        
        printf("=== \n");
    }

//    void FillByLarger(double xval, double yval,
//                      double oval,
//                      double oval_serr);
    {
        printf("--- test FillByLarger\n");
        HistDataSerr2d* hd2d = new HistDataSerr2d("hd2d");
        hd2d->Init(2, 0.0, 2.0, 3, 0.0, 3.0);

        hd2d->FillByLarger(1.5, 2.5, 1.0, 0.1);
        hd2d->PrintData(stdout, "x,xe,y,ye,z,ze", 0.0, 0.0, 0.0);                
        
        printf("--- \n");
        hd2d->FillByLarger(1.5, 2.5, 3.0, 0.1);
        hd2d->PrintData(stdout, "x,xe,y,ye,z,ze", 0.0, 0.0, 0.0);        

        printf("--- \n");
        hd2d->FillByLarger(1.5, 2.5, 1.0, 0.2);
        hd2d->PrintData(stdout, "x,xe,y,ye,z,ze", 0.0, 0.0, 0.0);
        
        printf("--- \n");
        hd2d->FillByLarger(1.5, 2.5, 5.0, 0.3);
        hd2d->PrintData(stdout, "x,xe,y,ye,z,ze", 0.0, 0.0, 0.0);
        
        delete hd2d;
        
        printf("=== \n");
    }

//    void FillBySmaller(double xval, double yval,
//                       double oval,
//                       double oval_serr);
    {
        printf("--- test FillBySmaller\n");
        HistDataSerr2d* hd2d = new HistDataSerr2d("hd2d");
        hd2d->Init(2, 0.0, 2.0, 3, 0.0, 3.0);

        hd2d->FillBySmaller(1.5, 2.5, -1.0, 0.1);
        hd2d->PrintData(stdout, "x,xe,y,ye,z,ze", 0.0, 0.0, 0.0);                
        
        printf("--- \n");
        hd2d->FillBySmaller(1.5, 2.5, -3.0, 0.1);
        hd2d->PrintData(stdout, "x,xe,y,ye,z,ze", 0.0, 0.0, 0.0);        

        printf("--- \n");
        hd2d->FillBySmaller(1.5, 2.5, -1.0, 0.2);
        hd2d->PrintData(stdout, "x,xe,y,ye,z,ze", 0.0, 0.0, 0.0);
        
        printf("--- \n");
        hd2d->FillBySmaller(1.5, 2.5, -5.0, 0.3);
        hd2d->PrintData(stdout, "x,xe,y,ye,z,ze", 0.0, 0.0, 0.0);
        
        delete hd2d;
        
        printf("=== \n");
    }
    
//    void SetOvalErrArrByPoissonErr();
    {
        printf("--- test SetOvalErrArrByPoissonErr()\n");
        HistDataSerr2d* hd2d = new HistDataSerr2d("hd2d");
        hd2d->Init(2, 0.0, 2.0, 3, 0.0, 3.0);
        hd2d->SetOvalElm(0, 0, 1.0);
        hd2d->SetOvalElm(1, 0, 2.0);
        hd2d->SetOvalElm(0, 1, 3.0);
        hd2d->SetOvalElm(1, 1, 4.0);
        hd2d->SetOvalElm(0, 2, 5.0);
        hd2d->SetOvalElm(1, 2, 6.0);
        hd2d->SetOvalSerrElm(0, 0, 1.0);
        hd2d->SetOvalSerrElm(1, 0, 1.5);
        hd2d->SetOvalSerrElm(0, 1, 2.0);
        hd2d->SetOvalSerrElm(1, 1, 2.5);
        hd2d->SetOvalSerrElm(0, 2, 3.0);
        hd2d->SetOvalSerrElm(1, 2, 3.5);
        hd2d->SetOvalErrArrByPoissonErr();
        
        hd2d->PrintData(stdout, "x,xe,y,ye,z,ze", 0.0, 0.0, 0.0);
        
        delete hd2d;
        
        printf("=== \n");
    }
    
//    HistDataSerr2d* const Clone() const;
    {
        printf("--- test Clone()\n");
        HistDataSerr2d* hd2d = new HistDataSerr2d("hd2d");
        hd2d->Init(2, 0.0, 2.0, 3, 0.0, 3.0);
        hd2d->SetOvalElm(0, 0, 1.0);
        hd2d->SetOvalElm(1, 0, 2.0);
        hd2d->SetOvalElm(0, 1, 3.0);
        hd2d->SetOvalElm(1, 1, 4.0);
        hd2d->SetOvalElm(0, 2, 5.0);
        hd2d->SetOvalElm(1, 2, 6.0);
        hd2d->SetOvalSerrElm(0, 0, 1.0);
        hd2d->SetOvalSerrElm(1, 0, 1.5);
        hd2d->SetOvalSerrElm(0, 1, 2.0);
        hd2d->SetOvalSerrElm(1, 1, 2.5);
        hd2d->SetOvalSerrElm(0, 2, 3.0);
        hd2d->SetOvalSerrElm(1, 2, 3.5);
        hd2d->PrintData(stdout, "x,xe,y,ye,z,ze", 0.0, 0.0, 0.0);

        HistDataSerr2d* hd2d_new = hd2d->Clone();
        hd2d_new->PrintData(stdout, "x,xe,y,ye,z,ze", 0.0, 0.0, 0.0);
        
        delete hd2d;
        delete hd2d_new;
        
        
        printf("=== \n");
    }

//    void Load(string file);
    {
        printf("--- test Load(string file)\n");
        HistDataSerr2d* hd2d = new HistDataSerr2d("hd2d");
//        hd2d->Init(2, 0.0, 2.0, 3, 0.0, 3.0);
//        hd2d->SetOvalElm(0, 0, 1.0);
//        hd2d->SetOvalElm(1, 0, 2.0);
//        hd2d->SetOvalElm(0, 1, 3.0);
//        hd2d->SetOvalElm(1, 1, 4.0);
//        hd2d->SetOvalElm(0, 2, 5.0);
//        hd2d->SetOvalElm(1, 2, 6.0);
//        hd2d->SetOvalSerrElm(0, 0, 1.0);
//        hd2d->SetOvalSerrElm(1, 0, 1.5);
//        hd2d->SetOvalSerrElm(0, 1, 2.0);
//        hd2d->SetOvalSerrElm(1, 1, 2.5);
//        hd2d->SetOvalSerrElm(0, 2, 3.0);
//        hd2d->SetOvalSerrElm(1, 2, 3.5);
//        hd2d->Save("temp.dat", "x,xe,y,ye,z,ze", 0.0, 0.0, 0.0);
//

        hd2d->Load("data/test_hist2d_serr.dat");
        hd2d->PrintData(stdout, "x,xe,y,ye,z,ze", 0.0, 0.0, 0.0);

        delete hd2d;

        printf("=== \n");
    }

//    const DataArraySerr1d* const GetOvalArr() const;    
    {
        printf("--- test GetOvalArr()\n");
        HistDataSerr2d* hd2d = new HistDataSerr2d("hd2d");
        hd2d->Init(2, 0.0, 2.0, 3, 0.0, 3.0);
        hd2d->SetOvalElm(0, 0, 1.0);
        hd2d->SetOvalElm(1, 0, 2.0);
        hd2d->SetOvalElm(0, 1, 3.0);
        hd2d->SetOvalElm(1, 1, 4.0);
        hd2d->SetOvalElm(0, 2, 5.0);
        hd2d->SetOvalElm(1, 2, 6.0);
        hd2d->SetOvalSerrElm(0, 0, 1.0);
        hd2d->SetOvalSerrElm(1, 0, 1.5);
        hd2d->SetOvalSerrElm(0, 1, 2.0);
        hd2d->SetOvalSerrElm(1, 1, 2.5);
        hd2d->SetOvalSerrElm(0, 2, 3.0);
        hd2d->SetOvalSerrElm(1, 2, 3.5);

        for(long idata = 0; idata < hd2d->GetNbin(); idata ++){
            printf("hd2d->GetOvalArr()->GetValElm(%ld) = %e\n",
                   idata, hd2d->GetOvalArr()->GetValElm(idata));
        }
        for(long idata = 0; idata < hd2d->GetNbin(); idata ++){
            printf("hd2d->GetOvalArr()->GetValSerrElm(%ld) = %e\n",
                   idata, hd2d->GetOvalArr()->GetValSerrElm(idata));
        }
        
        delete hd2d;

        printf("=== \n");
    }

//    double GetOvalSerrElm(long ibin_xval, long ibin_yval) const;
    {
        printf("--- test GetOvalSerrElm(long ibin_xval, long ibin_yval)\n");
        HistDataSerr2d* hd2d = new HistDataSerr2d("hd2d");
        hd2d->Init(2, 0.0, 2.0, 3, 0.0, 3.0);
        hd2d->SetOvalElm(0, 0, 1.0);
        hd2d->SetOvalElm(1, 0, 2.0);
        hd2d->SetOvalElm(0, 1, 3.0);
        hd2d->SetOvalElm(1, 1, 4.0);
        hd2d->SetOvalElm(0, 2, 5.0);
        hd2d->SetOvalElm(1, 2, 6.0);
        hd2d->SetOvalSerrElm(0, 0, 1.0);
        hd2d->SetOvalSerrElm(1, 0, 1.5);
        hd2d->SetOvalSerrElm(0, 1, 2.0);
        hd2d->SetOvalSerrElm(1, 1, 2.5);
        hd2d->SetOvalSerrElm(0, 2, 3.0);
        hd2d->SetOvalSerrElm(1, 2, 3.5);

        for(long idata = 0; idata < hd2d->GetNbin(); idata ++){
            long ibin_xval = hd2d->GetHi2d()->GetIbinX(idata);
            long ibin_yval = hd2d->GetHi2d()->GetIbinY(idata);
            printf("hd2d->GetOvalElm(%ld, %ld) = %e\n",
                   ibin_xval, ibin_yval,
                   hd2d->GetOvalElm(ibin_xval, ibin_yval));
        }
        for(long idata = 0; idata < hd2d->GetNbin(); idata ++){
            long ibin_xval = hd2d->GetHi2d()->GetIbinX(idata);
            long ibin_yval = hd2d->GetHi2d()->GetIbinY(idata);
            printf("hd2d->GetOvalSerrElm(%ld, %ld) = %e\n",
                   ibin_xval, ibin_yval,
                   hd2d->GetOvalSerrElm(ibin_xval, ibin_yval));
        }
        
        delete hd2d;

        printf("=== \n");
    }

//    double GetOvalSerrElmAtXY(double xval, double yval) const;
    {
        printf("--- test GetOvalSerrElmAtXY(double xval, double yval)\n");
        HistDataSerr2d* hd2d = new HistDataSerr2d("hd2d");
        hd2d->Init(2, 0.0, 2.0, 3, 0.0, 3.0);
        hd2d->SetOvalElm(0, 0, 1.0);
        hd2d->SetOvalElm(1, 0, 2.0);
        hd2d->SetOvalElm(0, 1, 3.0);
        hd2d->SetOvalElm(1, 1, 4.0);
        hd2d->SetOvalElm(0, 2, 5.0);
        hd2d->SetOvalElm(1, 2, 6.0);
        hd2d->SetOvalSerrElm(0, 0, 1.0);
        hd2d->SetOvalSerrElm(1, 0, 1.5);
        hd2d->SetOvalSerrElm(0, 1, 2.0);
        hd2d->SetOvalSerrElm(1, 1, 2.5);
        hd2d->SetOvalSerrElm(0, 2, 3.0);
        hd2d->SetOvalSerrElm(1, 2, 3.5);

        printf("hd2d->GetOvalSerrElmAtXY(1.5, 0.5) = %e\n",
               hd2d->GetOvalSerrElmAtXY(1.5, 0.5));
        
        delete hd2d;

        printf("=== \n");
    }

//    void GenOvalSerrArr(double** const oval_serrarr_ptr,
//                        long* const nbin_ptr) const;
    {
        printf("--- test GenOvalSerrArr\n");
        HistDataSerr2d* hd2d = new HistDataSerr2d("hd2d");
        hd2d->Init(2, 0.0, 2.0, 3, 0.0, 3.0);
        hd2d->SetOvalElm(0, 0, 1.0);
        hd2d->SetOvalElm(1, 0, 2.0);
        hd2d->SetOvalElm(0, 1, 3.0);
        hd2d->SetOvalElm(1, 1, 4.0);
        hd2d->SetOvalElm(0, 2, 5.0);
        hd2d->SetOvalElm(1, 2, 6.0);
        hd2d->SetOvalSerrElm(0, 0, 1.0);
        hd2d->SetOvalSerrElm(1, 0, 1.5);
        hd2d->SetOvalSerrElm(0, 1, 2.0);
        hd2d->SetOvalSerrElm(1, 1, 2.5);
        hd2d->SetOvalSerrElm(0, 2, 3.0);
        hd2d->SetOvalSerrElm(1, 2, 3.5);

        long nbin = 0;
        double* oval_serr_arr = NULL;
        hd2d->GenOvalSerrArr(&oval_serr_arr, &nbin);

        for(long ibin = 0; ibin < hd2d->GetNbin(); ibin ++){
            printf("oval_serr_arr[%ld] = %e\n",
                   ibin, oval_serr_arr[ibin]);
        }

        delete [] oval_serr_arr;
        
        delete hd2d;

        printf("=== \n");
    }

//    void PrintData(FILE* fp, string format,
//                   double offset_xval,
//                   double offset_yval,
//                   double offset_oval) const;
    {
        printf("--- test PrintData\n");
        HistDataSerr2d* hd2d = new HistDataSerr2d("hd2d");
        hd2d->Init(2, 0.0, 2.0, 3, 0.0, 3.0);
        hd2d->SetOvalElm(0, 0, 1.0);
        hd2d->SetOvalElm(1, 0, 2.0);
        hd2d->SetOvalElm(0, 1, 3.0);
        hd2d->SetOvalElm(1, 1, 4.0);
        hd2d->SetOvalElm(0, 2, 5.0);
        hd2d->SetOvalElm(1, 2, 6.0);
        hd2d->SetOvalSerrElm(0, 0, 1.0);
        hd2d->SetOvalSerrElm(1, 0, 1.5);
        hd2d->SetOvalSerrElm(0, 1, 2.0);
        hd2d->SetOvalSerrElm(1, 1, 2.5);
        hd2d->SetOvalSerrElm(0, 2, 3.0);
        hd2d->SetOvalSerrElm(1, 2, 3.5);

        hd2d->PrintData(stdout, "x,xe,y,ye,z,ze", 0.0, 0.0, 0.0);
        
        delete hd2d;

        printf("=== \n");
    }

//    TH2D* const GenTH2D(double offset_xval,
//                        double offset_yval,
//                        double offset_oval) const;
    {
        printf("--- test GenTH2D\n");

        MirRootTool* root_tool = new MirRootTool;
        root_tool->InitTCanvas("pub");
        
        HistDataSerr2d* hd2d = new HistDataSerr2d("hd2d");
        hd2d->Init(2, 0.0, 2.0, 3, 0.0, 3.0);
        hd2d->SetOvalElm(0, 0, 1.0);
        hd2d->SetOvalElm(1, 0, 2.0);
        hd2d->SetOvalElm(0, 1, 3.0);
        hd2d->SetOvalElm(1, 1, 4.0);
        hd2d->SetOvalElm(0, 2, 5.0);
        hd2d->SetOvalElm(1, 2, 6.0);
        hd2d->SetOvalSerrElm(0, 0, 1.0);
        hd2d->SetOvalSerrElm(1, 0, 1.5);
        hd2d->SetOvalSerrElm(0, 1, 2.0);
        hd2d->SetOvalSerrElm(1, 1, 2.5);
        hd2d->SetOvalSerrElm(0, 2, 3.0);
        hd2d->SetOvalSerrElm(1, 2, 3.5);

        TH2D* th2d = hd2d->GenTH2D(0.0, 0.0, 0.0);
        th2d->Draw("text");
        root_tool->GetTCanvas()->Print("temp1.png");
        
        delete hd2d;
        delete th2d;

        printf("=== \n");
    }

    
    return status_prog;
}


//    void FillRandom(const MirFunc* const func,
//                    const double* const func_par,
//                    int rand_seed);
//    void FillRandom(const MirFunc* const func,
//                    const double* const func_par,
//                    const MirFunc* const func_sigma,
//                    const double* const func_par_sigma,
//                    int rand_seed);
//    void FillRandom(const HistData2d* const hist_data,
//                    int rand_seed);
