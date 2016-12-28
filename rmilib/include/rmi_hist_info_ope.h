#ifndef MXKWTOOL_MXKWLIB_HIST_INFO_OPE_H_
#define MXKWTOOL_MXKWLIB_HIST_INFO_OPE_H_

#include "mxkw_math.h"
#include "mxkw_iolib.h"
#include "mxkw_interval.h"
#include "mxkw_hist_info.h"

namespace HistInfo1dOpe
{
    // select_type: center, exclusive
    //   center:      select a bin whose center is located in an interval.
    //   exclusive:   select only the full bins,
    //                meaning to exclude bins at the interval edge.
    //   inclusive:   select any bins, even if only a part of a bin is
    //                included in the interval,
    //                meaning to include bins at the interval edge.
    
    void GenSelectHi1dArrByInterval(const HistInfo1d* const hist_info,
                                    const Interval* const interval,
                                    long* nhi1d_sel_ptr,
                                    HistInfo1d*** hi1d_sel_arr_ptr,
                                    Interval** interval_sel_ptr,
                                    string select_type = "exclusive");
}

#endif // MXKWTOOL_MXKWLIB_HIST_INFO_OPE_H_
