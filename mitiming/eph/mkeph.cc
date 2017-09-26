#include "mit_eph.h"
#include "arg_mkeph.h"

// global variable 
int g_flag_debug = 0;
int g_flag_help = 0;
int g_flag_verbose = 0;

int main(int argc, char *argv[]){
    int status = kRetNormal;

    ArgValMkEph* argval = new ArgValMkEph;
    argval->Init(argc, argv);
    argval->Print(stdout);

    double nu
        = EphemerisCalc::GetNu(argval->GetPeriod());
    double nu_err = 0.0;
    double nu_dot
        = EphemerisCalc::GetNuDot(
            argval->GetPeriod(),
            argval->GetPDot());
    double nu_dot_err = 0.0;
    double nu_dot2 = 0.0;
    double nu_dot2_err = 0.0;
    double nu_dot3 = 0.0;
    double nu_dot3_err = 0.0;
    double phase = 0.0;
    double phase_err = 0.0;
    double epoch_mjd = argval->GetEpochMjd();
    double t_st_mjd = argval->GetStartMjd();
    double t_ed_mjd = argval->GetEndMjd();
    
    Ephemeris* eph = new Ephemeris;
    eph->Set(nu, nu_err,
             nu_dot, nu_dot_err,
             nu_dot2, nu_dot2_err,
             nu_dot3, nu_dot3_err,
             phase, phase_err,
             epoch_mjd, t_st_mjd, t_ed_mjd);
    
    eph->Save(argval->GetEphfileOut());
    eph->Print(stdout);
    eph->PrintRange(stdout);

    delete eph;
    delete argval;

    return status;
}
