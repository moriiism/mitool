#include "mit_gti.h"

void MitGti::MkGtiFilter(const Interval* const interval,
                          string telescope, string tunit,
                          string gti_filter_file)
{
    Interval* interval_mjd
        = TimeConv::GenTimeToMjd(interval,
                                 Telescope::GetMjdref(telescope),
                                 tunit);
    Interval* interval_sccs
        = TimeConv::GenMjdToTime(interval_mjd,
                                 Telescope::GetMjdref(telescope),
                                 "sec");
    interval_sccs->Save(gti_filter_file);
    delete interval_mjd;
    delete interval_sccs;
}
