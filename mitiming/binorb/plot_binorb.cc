#include "mit_binary_orb.h"
#include "arg_plot_binorb.h"

// global variable 
int g_flag_debug = 0;
int g_flag_help = 0;
int g_flag_verbose = 0;

void MkQdpXYPlane(const ArgValPlotBinorb* const argval,
                  const BinaryOrb2* const binorb2);
void MkQdpXZPlane(const ArgValPlotBinorb* const argval,
                  const BinaryOrb2* const binorb2);
void MkQdpYZPlane(const ArgValPlotBinorb* const argval,
                  const BinaryOrb2* const binorb2);
void PrintCompanion(FILE* fp, const BinaryOrb2* const binorb2);


int main(int argc, char* argv[]){
    int status = kRetNormal;
    
    ArgValPlotBinorb* argval = new ArgValPlotBinorb;
    argval->Init(argc, argv);
    argval->Print(stdout);
 
    if(MiIolib::TestFileExist(argval->GetOutdir())){
        char cmd[kLineSize];
        sprintf(cmd, "mkdir -p %s", argval->GetOutdir().c_str());
        system(cmd);
    }
//    FILE* fp_log = NULL;
//    fp_log = fopen((argval->GetOutdir() + "/"
//                    + argval->GetProgname() + ".log").c_str(), "w");

    BinaryOrb2* binorb2 = new BinaryOrb2;
    if("A" == argval->GetMode()){
        binorb2->LoadA(argval->GetBinorbFile());
    } else if ("P" == argval->GetMode()){
        binorb2->LoadP(argval->GetBinorbFile());
    } else{
        abort();
    }

    MkQdpXYPlane(argval, binorb2);
    MkQdpXZPlane(argval, binorb2);
    MkQdpYZPlane(argval, binorb2);

    return status;
}

void MkQdpXYPlane(const ArgValPlotBinorb* const argval,
                  const BinaryOrb2* const binorb2)
{
    // x-y plane
    char outfile[kLineSize];
    sprintf(outfile, "%s/%s_x-y.qdp",
            argval->GetOutdir().c_str(),
            argval->GetOutfileHead().c_str());
    FILE* fp = fopen(outfile, "w");
    fprintf(fp, "skip sing\n");
    long nbin = argval->GetNbin();
    double mjd_lo = argval->GetMjdLo();
    double mjd_up = mjd_lo + binorb2->GetPeriod();
    double delta_mjd = (mjd_up - mjd_lo) / nbin;
    fprintf(fp, "! x y  ! collision  eclipse\n");
    for(int ibin = 0; ibin < nbin; ibin ++){
        double mjd = mjd_lo + (ibin + 0.5) * delta_mjd;
        AtVect xyz;
        binorb2->GetXYZByMjd(mjd, xyz);
        int collision = binorb2->Collision(mjd);
        int eclipse = binorb2->Eclipse(mjd);
        fprintf(fp, "%e %e ! %d %d\n",
                xyz[0], xyz[1], collision, eclipse);
    }

    fprintf(fp, "\n");    
    fprintf(fp, "no\n");
    fprintf(fp, "\n");
    PrintCompanion(fp, binorb2);
    fprintf(fp, "\n");    

    fprintf(fp, "lw 5\n");
    fprintf(fp, "col 1 on 1..\n");
    fprintf(fp, "ma 6 on 1\n");
    fprintf(fp, "line on 2\n");    
    fprintf(fp, "la x x\n");
    fprintf(fp, "la y y\n");
    fclose(fp);
}

void MkQdpXZPlane(const ArgValPlotBinorb* const argval,
                  const BinaryOrb2* const binorb2)
{
    // x-z plane
    char outfile[kLineSize];
    sprintf(outfile, "%s/%s_x-z.qdp",
            argval->GetOutdir().c_str(),
            argval->GetOutfileHead().c_str());
    FILE* fp = fopen(outfile, "w");
    fprintf(fp, "skip sing\n");
    long nbin = argval->GetNbin();
    double mjd_lo = argval->GetMjdLo();
    double mjd_up = mjd_lo + binorb2->GetPeriod();
    double delta_mjd = (mjd_up - mjd_lo) / nbin;
    fprintf(fp, "! x z  ! collision  eclipse\n");    
    for(int ibin = 0; ibin < nbin; ibin ++){
        double mjd = mjd_lo + (ibin + 0.5) * delta_mjd;
        AtVect xyz;
        binorb2->GetXYZByMjd(mjd, xyz);
        int collision = binorb2->Collision(mjd);
        int eclipse = binorb2->Eclipse(mjd);
        fprintf(fp, "%e %e ! %d %d\n",
                xyz[0], xyz[2], collision, eclipse);
    }

    fprintf(fp, "\n");    
    fprintf(fp, "no\n");
    fprintf(fp, "\n");
    PrintCompanion(fp, binorb2);
    fprintf(fp, "\n");    

    fprintf(fp, "lw 5\n");        
    fprintf(fp, "col 1 on 1..\n");    
    fprintf(fp, "ma 6 on 1\n");
    fprintf(fp, "line on 2\n");
    fprintf(fp, "la x x\n");
    fprintf(fp, "la y z\n");
    fclose(fp);
}


void MkQdpYZPlane(const ArgValPlotBinorb* const argval,
                  const BinaryOrb2* const binorb2)
{
    // y-z plane
    char outfile[kLineSize];
    sprintf(outfile, "%s/%s_y-z.qdp",
            argval->GetOutdir().c_str(),
            argval->GetOutfileHead().c_str());
    FILE* fp = fopen(outfile, "w");
    fprintf(fp, "skip sing\n");
    long nbin = argval->GetNbin();
    double mjd_lo = argval->GetMjdLo();
    double mjd_up = mjd_lo + binorb2->GetPeriod();
    double delta_mjd = (mjd_up - mjd_lo) / nbin;
    fprintf(fp, "! y z  ! collision  eclipse\n");
    for(int ibin = 0; ibin < nbin; ibin ++){
        double mjd = mjd_lo + (ibin + 0.5) * delta_mjd;
        AtVect xyz;
        binorb2->GetXYZByMjd(mjd, xyz);
        int collision = binorb2->Collision(mjd);
        int eclipse = binorb2->Eclipse(mjd);
        fprintf(fp, "%e %e ! %d %d\n",
                xyz[1], xyz[2], collision, eclipse);
    }

    fprintf(fp, "\n");    
    fprintf(fp, "no\n");
    fprintf(fp, "\n");
    PrintCompanion(fp, binorb2);
    fprintf(fp, "\n");

    fprintf(fp, "lw 5\n");    
    fprintf(fp, "col 1 on 1..\n");
    fprintf(fp, "ma 6 on 1\n");
    fprintf(fp, "line on 2\n");
    fprintf(fp, "la x y\n");
    fprintf(fp, "la y z\n");
    fclose(fp);
}


void PrintCompanion(FILE* fp, const BinaryOrb2* const binorb2)
{
    int ntheta = 100;
    double theta_lo = 0.0;
    double delta_theta = 360.0/ntheta;
    for(int itheta = 0; itheta < ntheta; itheta ++){
        double theta = theta_lo + (itheta + 0.5) * delta_theta;
        double rad_lts = binorb2->GetRadiusCompanion()
            * kSunEqRad / kSpeedOfLight;
        double star_x = rad_lts * cos(theta/180. * kPi);
        double star_y = rad_lts * sin(theta/180. * kPi);
        fprintf(fp, "%e %e\n", star_x, star_y);
    }
}
