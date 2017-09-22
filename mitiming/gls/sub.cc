#include "sub.h"

HistData1d* const GenHd1dGls(const GraphDataSerr2d* const gd2d_sec,
                             long nnu, double nu_lo, double nu_up)
{
    HistData1d* hd1d_gls = new HistData1d;
    hd1d_gls->Init(nnu, nu_lo, nu_up);
    double delta_nu = hd1d_gls->GetBinWidth();
    for(long inu = 0; inu < nnu; inu ++){
        double nu = nu_lo + (inu + 0.5) * delta_nu;
        double tau = MxkwTimingGls::GetTau(gd2d_sec, nu);
        double gls = MxkwTimingGls::GetGls(gd2d_sec, nu, tau);
        hd1d_gls->SetOvalElm(inu, gls);
    }
    return hd1d_gls;
}


//
// ratio = nu_dot / nu
//
HistData2d* const GenHd2dGls(const GraphDataSerr2d* const gd2d_sec,
                             int nnu, double nu_lo, double nu_up,
                             long nratio, double ratio_lo, double ratio_up,
                             double epoch_sec)
{
     if (ratio_up - ratio_lo < 0){
         printf("bad ratio_lo, ratio_up: %e %e\n", ratio_lo, ratio_up);
         abort();
     }

     HistData2d* hd2d_gls = new HistData2d;
     hd2d_gls->Init(nnu, nu_lo, nu_up,
                    nratio, ratio_lo, ratio_up);
     
     double delta_ratio = (ratio_up - ratio_lo) / nratio;
     printf("%s: delta_ratio    = %e\n",
            __func__, delta_ratio);

     for(long iratio = 0; iratio < nratio; iratio ++){
         double ratio = ratio_lo + (iratio + 0.5) * delta_ratio;
         printf(" %ld", iratio);
         fflush(stdout);
         GraphDataSerr2d* gd2d_sec_shift = new GraphDataSerr2d;
         gd2d_sec_shift->Init();
         for(long idata = 0; idata < gd2d_sec->GetNdata(); idata ++){
             double time = gd2d_sec->GetXvalElm(idata);
             double time_shift = time + ratio / 2.0 * pow(time - epoch_sec, 2);
             gd2d_sec_shift->SetPoint(idata, time_shift, 0.0,
                                      gd2d_sec->GetOvalElm(idata),
                                      gd2d_sec->GetOvalSerrElm(idata));
         }
         HistData1d* hd1d_gls = GenHd1dGls(gd2d_sec_shift,
                                           nnu, nu_lo, nu_up);
         delete gd2d_sec_shift;
         
         //char temp[kLineSize];
         //sprintf(temp, "%s_%2.2d.qdp", "temp", (int) iratio);
         //MxkwQdpTool::MkQdp(hd1d_gls, temp, "x,xe,y,ye");
         
         for(long inu = 0; inu < nnu; inu ++){
             hd2d_gls->SetOvalElm(inu, iratio, hd1d_gls->GetOvalElm(inu));
         }
         delete hd1d_gls;
     }
     printf("\n");

     return hd2d_gls;
}
