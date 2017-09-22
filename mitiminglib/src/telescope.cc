#include "mit_telescope.h"

double Telescope::GetMjdref(string telescope)
{
    // MJDREF : reference time of time column
    //          then, time column is the elasped sec (day) from MJDREF
    //          MJDREF is TT.

    double mjdref = 0.0;
    if("RXTE" == telescope){
        mjdref = 49353.000696574074;
        printf("! MJDREF(RXTE) = %20.12f\n", mjdref);

    } else if ("SUZAKU" == telescope){
        // MJDREFI =                51544 / MJD reference day
        // MJDREFF = 7.428703703703700E-04 / MJD reference (fraction of day)
        mjdref = 51544 + 7.428703703703700E-04;
        printf("! MJDREF(SUZAKU) = %20.12f\n", mjdref);

    } else if ("SWIFT" == telescope){
        mjdref = 51910.00074287037;
        printf("! MJDREF(SWIFT) = %20.12f\n", mjdref);

    } else if ("MAXI" == telescope){
        //MJDREFI =                51544 / MJD reference day
        //MJDREFF =  0.00074287037037037 / MJD reference(fraction of day)
        mjdref = 51544.00074287037037037;
        printf("! MJDREF(MAXI) = %20.12f\n", mjdref);

    } else if ("MJD_TT" == telescope){
        mjdref = 0.;
        printf("! MJDREF(MJD_TT) = %f\n", mjdref);

    } else {
        char msg[kLineSize];
        sprintf(msg, "unknown telescope: %s", telescope.c_str());
        MPrintErr(msg);
        abort();
    }

//} else if ("ASCA" == telescope){
  // mjdref = 4.89880000E+04;
  //  printf("! MJDREF(ASCA) = %20.12f\n", mjdref);
 //    } else if ("CHANDRA" == telescope){
  //mjdref = 5.0814000000000E+04;
  // printf("! MJDREF(CHANDRA) = %20.12f\n", mjdref);
//    } else if ("SUBARU" == telescope){
//        // MJD (TT), See /raid/morii/Hawaii/ana/4U0142+61/Subaru/hhmmss2sec.pl
//        mjdref = 52891.5337175637;
//        printf("! MJDREF(SUBARU) = %20.12f\n", mjdref);
    
    return mjdref;
}


double Telescope::GetTimeAccuracy(string telescope,
                                  string tunit)
{
    string func_name = "Telescope::GetTimeAccuracy()";
    printf("%s: tunit = %s\n", func_name.c_str(), tunit.c_str());
    if("none" == tunit){
        return 0.0;
    }
  
    double time_accuracy;
    if ("MAXI" == telescope){
        // if difference < 0.1 msec, same.
        // 0.1 msec / sec = 1.e-4
        //  // 0.1 msec / day = 1.15740740740741e-09
        if(tunit == "sec"){
            time_accuracy = 1.e-4;
        } else if (tunit == "day"){
            time_accuracy = 1.e-9;
        } else {
            printf("error: bad tunit\n");
            exit(1);
        }
    } else if ("RXTE" == telescope) {
        // if difference < 1.0 microsec (PCA), same.
        // 1.0 microsec / sec = 1.e-6
        // 1.0 microsec / day = 1.157407407e-11
        if(tunit == "sec"){
            time_accuracy = 1.e-6;
        } else if (tunit == "day"){
            time_accuracy = 1.2e-11;
        } else {
            printf("error: bad tunit\n");
            exit(1);
        }
    } else if ("SUZAKU" == telescope) {
        // if difference < 61.0 microsec (HXD), same.
        // 61.0 microsec / sec = 6.1e-05
        // 61.0 microsec / day = 7.06018518518519e-10
        if(tunit == "sec"){
            time_accuracy = 6.1e-05;
        } else if (tunit == "day"){
            time_accuracy = 7.1e-10;
        } else {
            printf("error: bad tunit\n");
            exit(1);
        }
    } else if ("ASCA" == telescope) {
        // if difference < 25.0 microsec (GIS), same.
        // 25.0 microsec / sec = 2.5e-5
        // 25.0 microsec / day = 2.893518519e-10
        if(tunit == "sec"){
            time_accuracy = 2.5e-5;
        } else if (tunit == "day"){
            time_accuracy = 3.e-10;
        } else {
            printf("error: bad tunit\n");
            exit(1);
        }
    } else if ("CHANDRA" == telescope) {
        // if difference < 10 microsec (HRC), same.
        // 10.0 microsec / sec = 1.e-5
        // 10.0 microsec / day = 1.157407407e-10
        if(tunit == "sec"){
            time_accuracy = 1.e-5;
        } else if (tunit == "day"){
            time_accuracy = 1.2e-10;
        } else {
            printf("error: bad tunit\n");
            exit(1);
        }
    } else if ("SWIFT" == telescope) {
        // if difference < 1.7 msec (WT mode), same.
        // 1.7 msec / sec = 1.7e-3
        // 1.7 msec / day = 1.967592593e-8
        if(tunit == "sec"){
            time_accuracy = 1.7e-3;
        } else if (tunit == "day"){
            time_accuracy = 2.e-8;
        } else {
            printf("error: bad tunit\n");
            exit(1);
        }
    } else if ("MJD_TT" == telescope) {
        // if difference < 1 msec , same.
        // 1 msec / sec = 1e-6
        // 1 msec / day = 1.157407407e-11
        if(tunit == "sec"){
            time_accuracy = 1.e-6;
        } else if (tunit == "day"){
            time_accuracy = 1.2e-11;
        } else {
            printf("error: bad tunit\n");
            exit(1);
        }
    } else {
        printf("! error: unknown telescope : %s\n", telescope.c_str());
        exit(1);
    }
    return time_accuracy;
}

double Telescope::MjdTTToSCCS(string telescope,
                              double time_mjd_tt)
{
    // spacecraft clock seconds
    double time_sccs = (time_mjd_tt - GetMjdref(telescope)) * kDayToSec;
    return time_sccs;
}

double Telescope::SCCSToMjdTT(string telescope,
                              double time_sccs)
{
    double time_mjd_tt = GetMjdref(telescope) + time_sccs / kDayToSec;
    return time_mjd_tt;
}
