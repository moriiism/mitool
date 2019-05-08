#include "mir_binning.h"

void MirBinning::GetPoint(long npoint,
                          double lo,
                          double up,
                          string scale,
                          double* const point_arr)
{
    if("lin" == scale){
        GetPointLin(npoint, lo, up, point_arr);
    } else if ("log" == scale){
        GetPointLog(npoint, lo, up, point_arr);
    } else {
        abort();
    }
}

void MirBinning::GetPointLin(long npoint,
                             double lo,
                             double up,
                             double* const point_arr)
{
    if(npoint > 1){
        double delta = ( up - lo ) / (npoint - 1);
        for(long ipoint = 0; ipoint < npoint; ipoint ++){
            point_arr[ipoint] = lo + ipoint * delta;
        }
    } else if(1 == npoint){
        point_arr[0] = lo;
    } else {
        abort();
    }
}

void MirBinning::GetPointLog(long npoint,
                             double lo,
                             double up,
                             double* const point_arr)
{
    if(npoint > 1){
        double delta = ( log10(up) - log10(lo) ) / (npoint - 1);
        for(long ipoint = 0; ipoint < npoint; ipoint ++){
            point_arr[ipoint] = pow(10.0, log10(lo) + ipoint * delta);
        }
    } else if(1 == npoint){
        point_arr[0] = lo;
    } else {
        abort();
    }
}

// bin center

void MirBinning::GetBin(long nbin,
                        double lo,
                        double up,
                        string scale,
                        double* const bin_arr)
{
    if("lin" == scale){
        GetBinLin(nbin, lo, up, bin_arr);
    } else if ("log" == scale){
        GetBinLog(nbin, lo, up, bin_arr);
    } else {
        abort();
    }
}

void MirBinning::GetBinLin(long nbin,
                           double lo,
                           double up,
                           double* const bin_arr)
{
    if(nbin >= 1){
        double delta = ( up - lo ) / nbin;
        for(long ibin = 0; ibin < nbin; ibin ++){
            bin_arr[ibin] = lo + (ibin + 0.5) * delta;
        }
    } else {
        abort();
    }
}

void MirBinning::GetBinLog(long nbin,
                           double lo,
                           double up,
                           double* const bin_arr)
{
    if(nbin >= 1){
        double delta = ( log10(up) - log10(lo) ) / nbin;
        for(long ibin = 0; ibin < nbin; ibin ++){
            bin_arr[ibin] = pow(10.0, log10(lo) + (ibin + 0.5) * delta);
        }
    } else {
        abort();
    }
}
