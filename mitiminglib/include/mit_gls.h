#ifndef MORIIISM_MITOOL_MITIMINGLIB_GLS_H_
#define MORIIISM_MITOOL_MITIMINGLIB_GLS_H_

#include "mi_base.h"
#include "mir_math.h"
#include "mir_hist1d_serr.h"
#include "mit_eph.h"
#include "mit_timeconv.h"

namespace MitGls{

//
// data_arr must be in the unit of sec.
//
    double GetTau(const GraphDataSerr2d* const gd2d,
                  double nu);
    double GetGls(const GraphDataSerr2d* const gd2d,
                  double nu, double tau);
}

#endif // MORIIISM_MITOOL_MITIMINGLIB_GLS_H_
