#include "mi_str.h"
#include "mi_iolib.h"
#include "mir_interval.h"
#include "mir_hist_info.h"
#include "mir_hist_info_ope.h"

// global variable 
int g_flag_debug = 0;
int g_flag_help = 0;
int g_flag_verbose = 0;

int main(int argc, char* argv[])
{
    int status_prog = kRetNormal;

//    void GenSelectHi1dArrByInterval(const HistInfo1d* const hist_info,
//                                    const Interval* const interval,
//                                    long* nhi1d_sel_ptr,
//                                    HistInfo1d*** hi1d_sel_arr_ptr,
//                                    Interval** interval_sel_ptr,
//                                    string select_type = "exclusive");
    {
        printf("--- test GenSelectHi1dArrByInterval, exclusive\n");
        
        HistInfo1d* hi1d = new HistInfo1d;
        double lo = 0.0;
        double up = +10.0;
        long nbin = 10;
        hi1d->InitSetByNbin(lo, up, nbin);
        
        Interval* interval = new Interval;
        long nterm = 3;
        interval->Init(nterm);
        double* st_arr = new double[nterm];
        double* ed_arr = new double[nterm];
        st_arr[0] =  0.5; ed_arr[0] =  1.0;
        st_arr[1] =  2.0; ed_arr[1] =  5.0;
        st_arr[2] =  7.5; ed_arr[2] =  9.5;
        interval->Set(nterm, st_arr, ed_arr);

        long nhi1d_sel = 0;
        HistInfo1d** hi1d_sel_arr = NULL;
        Interval* interval_sel = NULL;
        string select_type = "exclusive";
        HistInfo1dOpe::GenSelectHi1dArrByInterval(hi1d, interval,
                                                  &nhi1d_sel,
                                                  &hi1d_sel_arr,
                                                  &interval_sel,
                                                  select_type);
        printf("nhi1d_sel = %ld\n", nhi1d_sel);
        interval_sel->Print(stdout);
        for(long isel = 0; isel < nhi1d_sel; isel ++){
            hi1d_sel_arr[isel]->Print(stdout);
        }
        
        printf("=== \n");
    }


    {
        printf("--- test GenSelectHi1dArrByInterval, center\n");
        
        HistInfo1d* hi1d = new HistInfo1d;
        double lo = 0.0;
        double up = +10.0;
        long nbin = 10;
        hi1d->InitSetByNbin(lo, up, nbin);
        
        Interval* interval = new Interval;
        long nterm = 3;
        interval->Init(nterm);
        double* st_arr = new double[nterm];
        double* ed_arr = new double[nterm];
        st_arr[0] =  0.5; ed_arr[0] =  1.0;
        st_arr[1] =  2.0; ed_arr[1] =  5.0;
        st_arr[2] =  7.5; ed_arr[2] =  9.5;
        interval->Set(nterm, st_arr, ed_arr);

        long nhi1d_sel = 0;
        HistInfo1d** hi1d_sel_arr = NULL;
        Interval* interval_sel = NULL;
        string select_type = "center";
        HistInfo1dOpe::GenSelectHi1dArrByInterval(hi1d, interval,
                                                  &nhi1d_sel,
                                                  &hi1d_sel_arr,
                                                  &interval_sel,
                                                  select_type);
        printf("nhi1d_sel = %ld\n", nhi1d_sel);
        interval_sel->Print(stdout);
        for(long isel = 0; isel < nhi1d_sel; isel ++){
            hi1d_sel_arr[isel]->Print(stdout);
        }
        
        printf("=== \n");
    }


    
    
    return status_prog;
}
