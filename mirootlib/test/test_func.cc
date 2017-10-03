#include "mi_str.h"
#include "mi_iolib.h"
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
        printf("--- test GenSelectHi1dArrByInterval\n");
        printf("=== \n");
    }
    
    return status_prog;
}
