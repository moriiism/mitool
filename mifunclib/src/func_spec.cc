#include "mifc_spec.h"

// --- FuncSpec

double FuncSpec::FNu(const double* const xval, const double* const par) const
{
    double fnu = Eval(xval, par);
    return fnu;
}

double FuncSpec::NuFNu(const double* const xval, const double* const par) const
{
    double fnu = FNu(xval, par);
    double nufnu = xval[0] * fnu;
    return nufnu;
}

double FuncSpec::PhNu(const double* const xval, const double* const par) const
{
    double fnu = FNu(xval, par);
    double phnu = fnu / xval[0];
    return phnu;
}


TF1* const FuncSpec::GenTF1FNu(double x_low, double x_up) const
{
    string title;
    if("" == GetTitle()){
        title = GetClassName();
    } else {
        title = GetTitle();
    }
    TF1* tf1 = new TF1(title.c_str(), this, &FuncSpec::FNu,
                       x_low, x_up, GetNpar(), GetClassName().c_str(), "FNu");
    if(0 < g_flag_verbose){
        MPrintInfoClass("done.");
    }
    return tf1;
}

void FuncSpec::DrawFuncFNu(const MirFuncPar* const func_par,
                           MirRootTool* const root_tool,
                           double x_low, double x_up, string outfig) const
{
    TF1* tf1 = GenTF1FNu(x_low, x_up);
    MirFuncPar::CopyPar(func_par, tf1);
    tf1->Draw();
    root_tool->GetTCanvas()->Print(outfig.c_str());
    delete tf1;
    if(0 < g_flag_verbose){
        MPrintInfoClass("done.");
    }
}


TF1* const FuncSpec::GenTF1NuFNu(double x_low, double x_up) const
{
    string title;
    if("" == GetTitle()){
        title = GetClassName();
    } else {
        title = GetTitle();
    }
    TF1* tf1 = new TF1(title.c_str(), this, &FuncSpec::NuFNu,
                       x_low, x_up, GetNpar(), GetClassName().c_str(), "NuFNu");
    if(0 < g_flag_verbose){
        MPrintInfoClass("done.");
    }
    return tf1;
}

void FuncSpec::DrawFuncNuFNu(const MirFuncPar* const func_par,
                             MirRootTool* const root_tool,
                             double x_low, double x_up, string outfig) const
{
    TF1* tf1 = GenTF1NuFNu(x_low, x_up);
    MirFuncPar::CopyPar(func_par, tf1);
    tf1->Draw();
    root_tool->GetTCanvas()->Print(outfig.c_str());
    delete tf1;
    if(0 < g_flag_verbose){
        MPrintInfoClass("done.");
    }
}


TF1* const FuncSpec::GenTF1PhNu(double x_low, double x_up) const
{
    string title;
    if("" == GetTitle()){
        title = GetClassName();
    } else {
        title = GetTitle();
    }
    TF1* tf1 = new TF1(title.c_str(), this, &FuncSpec::PhNu,
                       x_low, x_up, GetNpar(), GetClassName().c_str(), "PhNu");
    if(0 < g_flag_verbose){
        MPrintInfoClass("done.");
    }
    return tf1;
}

void FuncSpec::DrawFuncPhNu(const MirFuncPar* const func_par,
                            MirRootTool* const root_tool,
                            double x_low, double x_up, string outfig) const
{
    TF1* tf1 = GenTF1PhNu(x_low, x_up);
    MirFuncPar::CopyPar(func_par, tf1);
    tf1->Draw();
    root_tool->GetTCanvas()->Print(outfig.c_str());
    delete tf1;
    if(0 < g_flag_verbose){
        MPrintInfoClass("done.");
    }
}



//
// --- blackbody function
//

void BlackbodyFunc::Copy(const BlackbodyFunc* const org)
{
    if(this == org) {return;}
    if(NULL == org) {return;}
    
    CopyTitle(org);
}

BlackbodyFunc* const BlackbodyFunc::Clone() const
{
    BlackbodyFunc* obj_new = new BlackbodyFunc;
    obj_new->Copy(this);
    return obj_new;
}

double BlackbodyFunc::Eval(const double* const xval,
                           const double* const par) const
{
    double nu = xval[0];     // nu (Hz)
    double Temp    = par[0]; // temperature (K)
    double radius  = par[1]; // radius of sphere (cm)
    double dist    = par[2]; // distance (cm)
    // Rybicki & Lightman (1.13)
    double F_nu = kPi * B_nu(nu, Temp) * pow( radius / dist, 2);
    return F_nu;
}

// private

double BlackbodyFunc::B_nu(double nu, double Temp) const
{
    // Rybicki & Lightman (1.51)
    double B_nu = 2 * kPlanckConst * pow(nu, 3) / pow(kSpeedOfLight, 2) /
        ( exp(kPlanckConst * nu / (kBoltzmannConst * Temp) ) - 1.0 );
    return B_nu;
}

//
// --- StdAccDiskFunc
//

void StdAccDiskFunc::Copy(const StdAccDiskFunc* const org)
{
    if(this == org) {return;}
    if(NULL == org) {return;}
    
    CopyTitle(org);
}

StdAccDiskFunc* const StdAccDiskFunc::Clone() const
{
    StdAccDiskFunc* obj_new = new StdAccDiskFunc;
    obj_new->Copy(this);
    return obj_new;
}


double StdAccDiskFunc::Eval(const double* const xval,
                            const double* const par) const
{
    double nu      = xval[0];  // nu (Hz)
    double Tin     = par[0];   // temperature at inner edge (K)
    double Rin     = par[1];   // radius at inner edge (cm)
    double Rout    = par[2];   // radius at inner edge (cm)
    double ang_inc = par[3];   // inclination angle (deg)
    double dist    = par[4];   // distance (cm)
    double index   = par[5];   // index p

    double x_in  = kPlanckConst * nu / (kBoltzmannConst * Tin);
    double x_out = x_in * pow(Rout / Rin, index);

    TF1* tf1 = new TF1("int", this, &StdAccDiskFunc::FuncInnerMineshige,
                       x_in, x_out, 1, "StdAccDiskFunc", "FuncInnerMineshige");
    tf1->SetParameter(0, index);
    double integral = tf1->Integral(x_in, x_out);
    delete tf1;

    double F_nu = cos(ang_inc / 180. * kPi) / pow(dist, 2.0) * 4 * kPi * kPlanckConst
        / pow(kSpeedOfLight, 2) * pow(Rin, 2.0) / index
        * pow( kBoltzmannConst * Tin / (kPlanckConst * nu), 2./index)
        * pow(nu, 3.0) * integral;
    return F_nu;
}

// private

double StdAccDiskFunc::FuncInnerMineshige(const double* const xval,
                                          const double* const par) const
{
    // see Mineshige Book
    double xval0 = xval[0];
    double index = par[0];
    double oval = pow(xval0, (2.0/index) -1.0) / (exp(xval0) - 1.0);
    return oval;
}       

//
// -------- Dust Disk func --------------
//

void DustDiskFunc::Copy(const DustDiskFunc* const org)
{
    if(this == org) {return;}
    if(NULL == org) {return;}
    
    CopyTitle(org);
}

DustDiskFunc* const DustDiskFunc::Clone() const
{
    DustDiskFunc* obj_new = new DustDiskFunc;
    obj_new->Copy(this);
    return obj_new;
}

double DustDiskFunc::Eval(const double* const xval,
                          const double* const par) const
{
    double nu      = xval[0];  // nu (Hz)
    double Rin     = par[0];   // radius at inner edge (cm)
    double Rout    = par[1];   // radius at inner edge (cm)
    double ang_inc = par[2];   // inclination angle (deg)
    double dist    = par[3];   // distance (cm)
    double albedo  = par[4];   // albedo (ita_disk)
    double flux_x  = par[5];   // Unabsorbed X-ray flux (erg/s/cm2)

    double lumi_x  = flux_x * 4 * kPi * pow(dist, 2);

    // double f1 = 1.0;
    double f1 = 0.15;
        
    double f2 = 1 - albedo;
    double mu = 0.5; // for proton-electron plasma
    double M_NS = kSunMass * 1.4; // neutron star mass
    double index = 3./7.;
    
    // temperature at outer edge (K)    
    double Tout    = pow( sqrt( f1 * kBoltzmannConst /
                                (mu * kProtonMass * kGravityConst * M_NS)) /
                          (14 * kPi * kStefanBoltzmannConst), 2./7.) * 
        pow( f2 * lumi_x, 2./7.) * pow(Rout, -3./7.);

    // printf("Tout = %e\n", Tout);
    
    double x_in  = kPlanckConst * nu / (kBoltzmannConst * Tout) * pow(Rout / Rin, -1 * index);
    double x_out = kPlanckConst * nu / (kBoltzmannConst * Tout);

    TF1* tf1 = new TF1("int", this, &DustDiskFunc::FuncInnerMineshige,
                       x_in, x_out, 1, "DustDiskFunc", "FuncInnerMineshige");
    tf1->SetParameter(0, index);
    double integral = tf1->Integral(x_in, x_out);
    delete tf1;

    //printf("in, out = %e %e\n", x_in, x_out);
    //printf("integral = %e\n", integral);
    
    
    double F_nu = cos(ang_inc / 180. * kPi) / pow(dist, 2.0) * 4 * kPi * kPlanckConst
        / pow(kSpeedOfLight, 2) * pow(Rout, 2.0) / index
        * pow( kBoltzmannConst * Tout / (kPlanckConst * nu), 2./index)
        * pow(nu, 3.0) * integral;
    return F_nu;
}

// private

double DustDiskFunc::FuncInnerMineshige(const double* const xval,
                                        const double* const par) const
{
    // see Mineshige Book
    double xval0 = xval[0];
    double index = par[0];
    double oval = pow(xval0, (2.0/index) -1.0) / (exp(xval0) - 1.0);

//    printf("mine = %e, xval, index = %e %e\n", oval, xval0, index);
    
    return oval;
}       


//
// -------- Dust Disk func in Wang et al.--------------
//

void DustDiskWangFunc::Copy(const DustDiskWangFunc* const org)
{
    if(this == org) {return;}
    if(NULL == org) {return;}
    
    CopyTitle(org);
}

DustDiskWangFunc* const DustDiskWangFunc::Clone() const
{
    DustDiskWangFunc* obj_new = new DustDiskWangFunc;
    obj_new->Copy(this);
    return obj_new;
}

double DustDiskWangFunc::Eval(const double* const xval,
                              const double* const par) const
{
    double nu      = xval[0];  // nu (Hz)
    double Rin     = par[0];   // radius at inner edge (cm)
    double Rout    = par[1];   // radius at inner edge (cm)
    double ang_inc = par[2];   // inclination angle (deg)
    double dist    = par[3];   // distance (cm)
    double albedo  = par[4];   // albedo (ita_disk)
    double flux_x  = par[5];   // Unabsorbed X-ray flux (erg/s/cm2)

    double lumi_x  = flux_x * 4 * kPi * pow(dist, 2);

    double mu = 0.5; // for proton-electron plasma
    double M_NS = kSunMass * 1.4; // neutron star mass
    
    // double f1 = 1.0;

    double flux_x_4p8em10 = 4.8e-10;
    double distance_3p9kpc = 3.9e3 * kCmPerPc;
    double f1 = mu * kProtonMass / kBoltzmannConst * pow(14 * kPi * kStefanBoltzmannConst, 2)
        * kGravityConst * M_NS / pow(flux_x_4p8em10 * 4 * kPi * pow(distance_3p9kpc, 2), 2)
        * pow(kSunEqRad, 3) * pow(5030, 7);
    printf("f1 = %e\n", f1);
    
    double f2 = 1 - albedo;
    double index = 3./7.;
    
    // temperature at outer edge (K)    
    double Tout    = pow( sqrt( f1 * kBoltzmannConst /
                                (mu * kProtonMass * kGravityConst * M_NS)) /
                          (14 * kPi * kStefanBoltzmannConst), 2./7.) * 
        pow( f2 * lumi_x, 2./7.) * pow(Rout, -3./7.);

    double Tin = Tout * pow(Rin / Rout, -3./7.);
    printf("Tin = %e, Tout = %e\n", Tin, Tout);
    
    double x_in  = kPlanckConst * nu / (kBoltzmannConst * Tout) * pow(Rout / Rin, -1 * index);
    double x_out = kPlanckConst * nu / (kBoltzmannConst * Tout);

    TF1* tf1 = new TF1("int", this, &DustDiskWangFunc::FuncInnerMineshige,
                       x_in, x_out, 1, "DustDiskWangFunc", "FuncInnerMineshige");
    tf1->SetParameter(0, index);
    double integral = tf1->Integral(x_in, x_out);
    delete tf1;

    //printf("in, out = %e %e\n", x_in, x_out);
    //printf("integral = %e\n", integral);
    
    
    double F_nu = cos(ang_inc / 180. * kPi) / pow(dist, 2.0) * 4 * kPi * kPlanckConst
        / pow(kSpeedOfLight, 2) * pow(Rout, 2.0) / index
        * pow( kBoltzmannConst * Tout / (kPlanckConst * nu), 2./index)
        * pow(nu, 3.0) * integral;
    return F_nu;
}


double DustDiskWangFunc::FuncInnerMineshige(const double* const xval,
                                            const double* const par) const
{
    // see Mineshige Book
    double xval0 = xval[0];
    double index = par[0];
    double oval = pow(xval0, (2.0/index) -1.0) / (exp(xval0) - 1.0);

//    printf("mine = %e, xval, index = %e %e\n", oval, xval0, index);
    
    return oval;
}       

double DustDiskWangFunc::GetTout(const double* const par) const
{
    //double Rin     = par[0];   // radius at inner edge (cm)
    double Rout    = par[1];   // radius at inner edge (cm)
    //double ang_inc = par[2];   // inclination angle (deg)
    double dist    = par[3];   // distance (cm)
    double albedo  = par[4];   // albedo (ita_disk)
    double flux_x  = par[5];   // Unabsorbed X-ray flux (erg/s/cm2)

    double lumi_x  = flux_x * 4 * kPi * pow(dist, 2);

    double mu = 0.5; // for proton-electron plasma
    double M_NS = kSunMass * 1.4; // neutron star mass
    
    // double f1 = 1.0;

    double flux_x_4p8em10 = 4.8e-10;
    double distance_3p9kpc = 3.9e3 * kCmPerPc;
    double f1 = mu * kProtonMass / kBoltzmannConst * pow(14 * kPi * kStefanBoltzmannConst, 2)
        * kGravityConst * M_NS / pow(flux_x_4p8em10 * 4 * kPi * pow(distance_3p9kpc, 2), 2)
        * pow(kSunEqRad, 3) * pow(5030, 7);
    printf("f1 = %e\n", f1);
    
    double f2 = 1 - albedo;
    // double index = 3./7.;

    // temperature at outer edge (K)    
    double Tout    = pow( sqrt( f1 * kBoltzmannConst /
                                (mu * kProtonMass * kGravityConst * M_NS)) /
                          (14 * kPi * kStefanBoltzmannConst), 2./7.) * 
        pow( f2 * lumi_x, 2./7.) * pow(Rout, -3./7.);

    return Tout;
}


double DustDiskWangFunc::GetTin(const double* const par) const
{
    double Rin     = par[0];   // radius at inner edge (cm)
    double Rout    = par[1];   // radius at inner edge (cm)
    double Tin = GetTout(par) * pow(Rin / Rout, -3./7.);

    return Tin;
}


//
// Powerlaw function
//

void PowerlawSpecFunc::Copy(const PowerlawSpecFunc* const org)
{
    if(this == org) {return;}
    if(NULL == org) {return;}
    
    CopyTitle(org);
}

PowerlawSpecFunc* const PowerlawSpecFunc::Clone() const
{
    PowerlawSpecFunc* obj_new = new PowerlawSpecFunc;
    obj_new->Copy(this);
    return obj_new;
}

double PowerlawSpecFunc::Eval(const double* const xval,
                              const double* const par) const
{
    double nu = xval[0];     // nu (Hz)
    double index   = par[0]; // index
    double freq0   = par[1]; // pivot frequency (Hz)
    double norm    = par[2]; // normalization at pivot freq.

    double F_nu = norm * pow(nu/freq0, index);
    return F_nu;
}




