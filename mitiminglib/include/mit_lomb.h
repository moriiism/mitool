#ifndef MORIIISM_MITOOL_MITIMINGLIB_LOMB_H_
#define MORIIISM_MITOOL_MITIMINGLIB_LOMB_H_

#include "mi_base.h"
#include "mir_math.h"
#include "mir_hist1d_serr.h"
#include "mit_eph.h"
#include "mit_timeconv.h"

namespace MitLomb{

//
// data_arr must be in the unit of sec.
//
    double GetTau(const DataArray1d* const data_arr,
                  double nu);
    double GetLomb(const GraphData2d* const gd2d,
                   double nu, double tau);
    double GetLomb(const DataArray1d* const da1d,
                   double nu, double tau);
}

#endif // MORIIISM_MITOOL_MITIMINGLIB_LOMB_H_
