#ifndef MORIIISM_MITOOL_MITIMINGLIB_PULSEPROF_STAT_H_
#define MORIIISM_MITOOL_MITIMINGLIB_PULSEPROF_STAT_H_

#include "mir_hist1d_serr.h"

namespace PulseProfStat{
    
    double GetChi2(const HistDataSerr1d* const h1d);

}

#endif // MORIIISM_MITOOL_MITIMINGLIB_PULSEPROF_STAT_H_
