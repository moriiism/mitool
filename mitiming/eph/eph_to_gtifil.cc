#include "mxkw_timing.h"
#include "mxkw_util.h"
#include "arg.h"

int main(int argc, char *argv[]){
    int status = kRetNormal;

    ArgValEph *argval = new ArgValEph;
    argval->Init(argc, argv);
    argval->Print(stdout);

    if(MxkwIolib::TestFileExist(argval->GetOutdir())){
        char cmd[kLineSize];
        sprintf(cmd, "mkdir -p %s", argval->GetOutdir().c_str());
        system(cmd);
    }
    FILE *fp_log;
    fp_log = fopen((argval->GetOutdir() + "/" + argval->GetProgname() + ".log").c_str(), "w");

    Telescope *tel = new Telescope;
    tel->Set(argval->GetTelescope());
    printf2(fp_log, "tel::mjdref = %f\n", tel->GetMjdref());

    Ephemeris *eph = new Ephemeris;
    eph->Set(argval->GetEphfile());
    eph->Print2(fp_log);

    Interval *phase_gti = new Interval;
    phase_gti->Load(argval->GetPhaseGti());
    phase_gti->Print2(fp_log);
  
    double gphase_st = eph->GetGphaseAtTimeMjd(argval->GetTimeMjdSt());
    double gphase_ed = eph->GetGphaseAtTimeMjd(argval->GetTimeMjdEd());
    printf("gphase_st, gphase_ed: %f %f \n", gphase_st, gphase_ed);

    int nperiod = (int)(floor(gphase_ed) - ceil(gphase_st));

    int nterm = nperiod * phase_gti->GetNterm();
    double *tstart_gti = new double [nterm]; 
    double *tstop_gti = new double [nterm]; 

    int iterm = 0;
    for(int iperiod = 0; iperiod < nperiod; iperiod ++){
        for(int iphase = 0; iphase < phase_gti->GetNterm(); iphase ++){
            double gphase;
            gphase = ceil(gphase_st) + iperiod + phase_gti->GetTstart()[iphase];
            tstart_gti[iterm] = tel->MjdToSCCS(eph->GetTimeMjdAtGphase(gphase));

            printf("gphase: %f\n", gphase);
            gphase = ceil(gphase_st) + iperiod + phase_gti->GetTstop()[iphase];

            tstop_gti[iterm] = tel->MjdToSCCS(eph->GetTimeMjdAtGphase(gphase));
            printf("gphase: %f\n", gphase);

            printf("%f %f\n", tstart_gti[iterm], tstop_gti[iterm]);
      
            iterm ++;
        }
    }

    Gti *gti = new Gti;
    gti->SetGti("sec", tel->GetMjdref());
    gti->SetData(nterm, tstart_gti, tstop_gti);

    double offset = gti->GetOffset(argval->GetOffsetArg());
    printf2(fp_log, "gti->GetNterm(): %d\n", gti->GetNterm());
    gti->MkQdp(argval->GetOutdir() + "/" +
               argval->GetOutfileHead() + "_" +
               argval->GetProgname() + ".qdp");
    gti->MkQdp(argval->GetOutdir() + "/" +
               argval->GetOutfileHead() + "_" +
               argval->GetProgname() + "_offset.qdp",
               offset);
    gti->MkGtiFilter(argval->GetOutdir() + "/" + argval->GetOutfileHead() + ".gti",
                     argval->GetTelescope());
  
    return status;
}

