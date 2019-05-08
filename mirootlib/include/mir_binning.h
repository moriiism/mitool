#ifndef MORIIISM_MITOOL_MIROOTLIB_BINNING_H_
#define MORIIISM_MITOOL_MIROOTLIB_BINNING_H_

#include "mir_math.h"

namespace MirBinning
{
    // bin edge
    void GetPoint(long npoint, double lo, double up, string scale, double* const point_arr);
    void GetPointLin(long npoint, double lo, double up, double* const point_arr);
    void GetPointLog(long npoint, double lo, double up, double* const point_arr);

    // bin center
    void GetBin(long nbin, double lo, double up, string scale, double* const bin_arr);
    void GetBinLin(long nbin, double lo, double up, double* const bin_arr);
    void GetBinLog(long nbin, double lo, double up, double* const bin_arr);
    
} //  namespace MirBinning

#endif // MORIIISM_MITOOL_MIROOTLIB_BINNING_H_
