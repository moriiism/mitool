#ifndef MORIIISM_MITOOL_MITIMINGLIB_TELESCOPE_H_
#define MORIIISM_MITOOL_MITIMINGLIB_TELESCOPE_H_

#include "mi_base.h"
#include "mir_physpar.h"

//
// telescope:
//   RXTE
//   ASCA
//   SUZAKU
//   CHANDRA
//   SWIFT
//   MAXI
//
//   MJD_TT
//

namespace Telescope{

    // get
    double GetMjdref(string telescope);
    double GetTimeAccuracy(string telescope,
                           string tunit);
    // convert
    double MjdTTToSCCS(string telescope,
                       double time_mjd_tt); // spacecraft clock seconds
    double SCCSToMjdTT(string telescope,
                       double time_sccs);
}

#endif // MORIIISM_MITOOL_MITIMINGLIB_TELESCOPE_H_
