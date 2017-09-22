#include "sub.h"

HistData1d* const GenHd1dLomb(const DataArray1d* const da1d_sec,
                              long nnu, double nu_lo, double nu_up)
{
    HistData1d* hd1d_lomb = new HistData1d;
    hd1d_lomb->Init(nnu, nu_lo, nu_up);
    double delta_nu = hd1d_lomb->GetBinWidth();
    for(long inu = 0; inu < nnu; inu ++){
        double nu = nu_lo + (inu + 0.5) * delta_nu;
        double tau = MxkwTimingLomb::GetTau(da1d_sec, nu);
        double lomb = MxkwTimingLomb::GetLomb(da1d_sec,
                                              nu, tau);
        hd1d_lomb->SetOvalElm(inu, lomb);
    }
    return hd1d_lomb;
}

HistData1d* const GenHd1dLomb(const GraphData2d* const gd2d_sec,
                              long nnu, double nu_lo, double nu_up)
{
    HistData1d* hd1d_lomb = new HistData1d;
    hd1d_lomb->Init(nnu, nu_lo, nu_up);
    double delta_nu = hd1d_lomb->GetBinWidth();
    for(long inu = 0; inu < nnu; inu ++){
        double nu = nu_lo + (inu + 0.5) * delta_nu;
        double tau = MxkwTimingLomb::GetTau(gd2d_sec->GetXvalArr(), nu);
        double lomb = MxkwTimingLomb::GetLomb(gd2d_sec, nu, tau);
        hd1d_lomb->SetOvalElm(inu, lomb);
    }
    return hd1d_lomb;
}


//
// ratio = nu_dot / nu
//
HistData2d* const GenHd2dLomb(const DataArray1d* const da1d_sec,
                              int nnu, double nu_lo, double nu_up,
                              long nratio, double ratio_lo, double ratio_up,
                              double epoch_sec)
{
     if (ratio_up - ratio_lo < 0){
         printf("bad ratio_lo, ratio_up: %e %e\n", ratio_lo, ratio_up);
         abort();
     }

     HistData2d* hd2d_lomb = new HistData2d;
     hd2d_lomb->Init(nnu, nu_lo, nu_up,
                     nratio, ratio_lo, ratio_up);
     
     double delta_ratio = (ratio_up - ratio_lo) / nratio;
     printf("%s: delta_ratio    = %e\n",
            __func__, delta_ratio);

     for(long iratio = 0; iratio < nratio; iratio ++){
         double ratio = ratio_lo + (iratio + 0.5) * delta_ratio;
         printf(" %ld", iratio);
         fflush(stdout);
         DataArray1d* da1d_sec_shift = new DataArray1d;
         da1d_sec_shift->Init(da1d_sec->GetNdata());
         for(long idata = 0; idata < da1d_sec->GetNdata(); idata ++){
             double time = da1d_sec->GetValElm(idata);
             double time_shift = time + ratio / 2.0 * pow(time - epoch_sec, 2);
             da1d_sec_shift->SetValElm(idata, time_shift);
         }
         HistData1d* hd1d_lomb = GenHd1dLomb(da1d_sec_shift,
                                             nnu, nu_lo, nu_up);
         delete da1d_sec_shift;
         
         //char temp[kLineSize];
         //sprintf(temp, "%s_%2.2d.qdp", "temp", (int) iratio);
         //MxkwQdpTool::MkQdp(hd1d_lomb, temp, "x,xe,y,ye");
         
         for(long inu = 0; inu < nnu; inu ++){
             hd2d_lomb->SetOvalElm(inu, iratio, hd1d_lomb->GetOvalElm(inu));
         }
         delete hd1d_lomb;
     }
     printf("\n");

     return hd2d_lomb;
}

HistData2d* const GenHd2dLomb(const GraphData2d* const gd2d_sec,
                              int nnu, double nu_lo, double nu_up,
                              long nratio, double ratio_lo, double ratio_up,
                              double epoch_sec)
{
     if (ratio_up - ratio_lo < 0){
         printf("bad ratio_lo, ratio_up: %e %e\n", ratio_lo, ratio_up);
         abort();
     }

     HistData2d* hd2d_lomb = new HistData2d;
     hd2d_lomb->Init(nnu, nu_lo, nu_up,
                     nratio, ratio_lo, ratio_up);
     
     double delta_ratio = (ratio_up - ratio_lo) / nratio;
     printf("%s: delta_ratio    = %e\n",
            __func__, delta_ratio);

     for(long iratio = 0; iratio < nratio; iratio ++){
         double ratio = ratio_lo + (iratio + 0.5) * delta_ratio;
         printf(" %ld", iratio);
         fflush(stdout);
         GraphData2d* gd2d_sec_shift = new GraphData2d;
         gd2d_sec_shift->Init();
         for(long idata = 0; idata < gd2d_sec->GetNdata(); idata ++){
             double time = gd2d_sec->GetXvalElm(idata);
             double time_shift = time + ratio / 2.0 * pow(time - epoch_sec, 2);
             gd2d_sec_shift->SetPoint(idata, time_shift, gd2d_sec->GetOvalElm(idata));
         }
         HistData1d* hd1d_lomb = GenHd1dLomb(gd2d_sec_shift,
                                             nnu, nu_lo, nu_up);
         delete gd2d_sec_shift;
         
         //char temp[kLineSize];
         //sprintf(temp, "%s_%2.2d.qdp", "temp", (int) iratio);
         //MxkwQdpTool::MkQdp(hd1d_lomb, temp, "x,xe,y,ye");
         
         for(long inu = 0; inu < nnu; inu ++){
             hd2d_lomb->SetOvalElm(inu, iratio, hd1d_lomb->GetOvalElm(inu));
         }
         delete hd1d_lomb;
     }
     printf("\n");

     return hd2d_lomb;
}
