#include "mxkw_iolib.h"
#include "mxkw_hist1d.h"
#include "mxkw_hist1d_serr.h"
#include "mxkw_search_par.h"
#include "mxkw_qdp_tool.h"
#include "mxkw_timing_eph.h"
#include "mxkw_timing_func_pls.h"
#include "mxkw_timing_folding.h"
#include "mxkw_timing_estimate.h"

#include "arg_est_by_lc.h"

// global variable 
int g_flag_debug = 0;
int g_flag_help = 0;
int g_flag_verbose = 0;

int main(int argc, char* argv[]){
    int status = kRetNormal;
  
    ArgValEstByLc* argval = new ArgValEstByLc;
    argval->Init(argc, argv);
    argval->Print(stdout);

    DataArray1d* data_arr = NULL;
    GraphDataSerr2d* g2d  = NULL;

    double time_span = 0.0;
    if("x" == argval->GetLcFormat()){
        data_arr = new DataArray1d;
        data_arr->Load(argval->GetLcFile());
        time_span = data_arr->GetValMax() - data_arr->GetValMin();
    } else {
        g2d = new GraphDataSerr2d;
        g2d->Load(argval->GetLcFile(), argval->GetLcFormat());
        time_span = g2d->GetXvalArr()->GetValAndErrMax()
            - g2d->GetXvalArr()->GetValAndErrMin();
    }

    double time_span_sec = 0.0;    
    if("day" == argval->GetLcTunit()){
        time_span_sec = time_span * kDayToSec;
        printf("time_span     = %e (day)\n",
               time_span);
        printf("time_span_sec = %e (sec)\n",
               time_span_sec);
    } else if("sec" == argval->GetLcTunit()){
        time_span_sec = time_span;
        printf("time_span     = %e (day)\n",
               time_span / kDayToSec);
        printf("time_span_sec = %e (sec)\n",
               time_span_sec);
    } else {
        MPrintErr("bad lc tunit");
        abort();
    }
    
    double delta_nu    = MxkwEstimate::GetDeltaNu(time_span_sec);
    double delta_nudot = MxkwEstimate::GetDeltaNudot(time_span_sec);
    double delta_nudot2 = MxkwEstimate::GetDeltaNudot2(time_span_sec);

    printf("delta_nu     = %e (Hz)\n", delta_nu);
    printf("delta_nudot  = %e (Hz/s)\n", delta_nudot);
    printf("delta_nudot2 = %e (Hz/s2)\n", delta_nudot2);
    
    // cleaning
    delete argval;
    if(NULL != g2d) {delete g2d;}
    if(NULL != data_arr) { delete data_arr;}

    return status;
}

