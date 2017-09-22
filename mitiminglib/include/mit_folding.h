#ifndef MORIIISM_MITOOL_MITIMINGLIB_FOLDING_H_
#define MORIIISM_MITOOL_MITIMINGLIB_FOLDING_H_

#include "mi_base.h"
#include "mir_math.h"
#include "mir_hist1d_serr.h"
#include "mit_eph.h"
#include "mit_timeconv.h"

namespace MitFolding{

    HistDataSerr1d* const GenFoldingBinCenter(const GraphDataSerr2d* const g2d,
                                              double mjdref, string tunit,
                                              const Ephemeris* const eph,
                                              int nphase);
    
    HistDataSerr1d* const GenFoldingBinCenter(const HistDataSerr1d* const h1d,
                                              double mjdref, string tunit,
                                              const Ephemeris* const eph,
                                              int nphase);

    HistDataSerr1d* const GenFolding(const DataArray1d* const data_arr,
                                     double mjdref, string tunit,
                                     const Ephemeris* const eph,
                                     int nphase);
}

#endif // MORIIISM_MITOOL_MITIMINGLIB_FOLDING_H_
