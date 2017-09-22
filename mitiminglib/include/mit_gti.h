#ifndef MORIIISM_MITOOL_MITIMINGLIB_GTI_H_
#define MORIIISM_MITOOL_MITIMINGLIB_GTI_H_

#include "mir_interval.h"
#include "mir_qdp_tool.h"
#include "mit_telescope.h"
#include "mit_timeconv.h"

namespace MitGti{
    // to be used for xselect    
    void MkGtiFilter(const Interval* const interval,
                     string telescope, string tunit,
                     string gti_filter_file);
}


#endif // MORIIISM_MITOOL_MITIMINGLIB_GTI_H_
