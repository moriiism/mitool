#include "mit_eph.h"
#include "arg_ephatt.h"

// global variable 
int g_flag_debug = 0;
int g_flag_help = 0;
int g_flag_verbose = 0;

int main(int argc, char *argv[]){
    int status = kRetNormal;

    ArgValEphatt* argval = new ArgValEphatt;
    argval->Init(argc, argv);
    argval->Print(stdout);
  
    Ephemeris* eph = new Ephemeris;
    eph->Load(argval->GetEphfileIn());
    eph->Print(stdout);
    eph->PrintRange(stdout);
  
    Ephemeris* eph_new = eph->GenEphemerisAtTimeMjd(argval->GetTimeMjd());
    eph_new->Save(argval->GetEphfileOut());
    eph_new->Print(stdout);
    eph_new->PrintRange(stdout);

    delete eph;
    delete eph_new;
    delete argval;

    return status;
}
