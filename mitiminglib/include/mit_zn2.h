#ifndef MORIIISM_MITOOL_MITIMINGLIB_ZN2_H_
#define MORIIISM_MITOOL_MITIMINGLIB_ZN2_H_

#include "mi_base.h"
#include "mir_math.h"
#include "mir_hist1d_serr.h"
#include "mit_eph.h"
#include "mit_timeconv.h"

namespace MitZn2{

    double GetZn2(const DataArray1d* const data_arr, double mjdref, string tunit,
                  const Ephemeris* const eph,
                  int nharmonics);
    double GetZn2(const GraphData2d* const g2d, double mjdref, string tunit,
                  const Ephemeris* const eph,
                  int nharmonics);
}

#endif // MORIIISM_MITOOL_MITIMINGLIB_ZN2_H_

