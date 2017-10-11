#include "mit_binary_orb.h"

//
// Binary Orbit Basics
//

double BinaryOrb::GetMeanMotion(double period)
{
    double mean_motion = 2 * kPi / period;
    return mean_motion;
}

double BinaryOrb::TimePeriToTime90(double time_peri, double period)
{
    double time_90 = time_peri + period / 4.;
    return time_90;
}


double BinaryOrb::Time90ToTimePeri(double time_90, double period)
{
    double time_peri = time_90 - period / 4.;
    return time_peri;
}

double BinaryOrb::GetMeanAnomaly(double time_mjd, double period, double time_peri)
{
    double mean_anomaly = 2 * kPi / period * (time_mjd - time_peri);
    return mean_anomaly;
}

double BinaryOrb::GetEccAnomaly(double time_mjd, double period,
                                double time_peri, double ecc)
{
    double mean_anomaly = GetMeanAnomaly(time_mjd, period, time_peri);
    double ecc_anomaly = SolveKeplerEq(mean_anomaly, ecc);
    return ecc_anomaly;
}


double BinaryOrb::SolveKeplerEq(double mean_anomaly, double ecc)
{
    string func_name = "BinaryOrb::SolveKeplerEq()";

    double ecc_anomaly_pre = 0.0;    
    double ecc_anomaly = 0.0;    
    if(0 < sin(mean_anomaly) ){
        ecc_anomaly = kPi/2.;
    } else {
        ecc_anomaly = -1 * kPi/2.;
    }
    int iterate = 0;
    while(fabs(ecc_anomaly - ecc_anomaly_pre) > kPi * 0.01){
        ecc_anomaly_pre = ecc_anomaly;
        ecc_anomaly -= FuncInKeplerEq(ecc_anomaly, ecc, mean_anomaly)
            / FuncPrimeInKeplerEq(ecc_anomaly, ecc);
        iterate ++;
        if(iterate > 100){
            printf("! %s: diff = %e\n", func_name.c_str(), fabs(ecc_anomaly - ecc_anomaly_pre));
            break;
        }
    }
    // printf("! %s: iterate = %d\n", func_name.c_str(), iterate);
    return ecc_anomaly;
}

double BinaryOrb::FuncInKeplerEq(double ecc_anomaly, double ecc, double mean_anomaly)
{
    double func = ecc_anomaly - ecc * sin(ecc_anomaly) - mean_anomaly;
    return func;
}

double BinaryOrb::FuncPrimeInKeplerEq(double ecc_anomaly, double ecc)
{
    double func_prime = 1 - ecc * cos(ecc_anomaly);
    return func_prime;
}

// mass ratio: q = m_2 / m_1 = m_x-ray / m_companion
// see morii's lognote (2010.6.10 - ), p135
double BinaryOrb::GetMassFunction(double period, double ax_sini, double mass_ratio)
{
    double period_sec = period * kDayToSec;
    double ax_sini_cm = ax_sini * kSpeedOfLight;
  
    double mass_func = pow(2.0 * kPi / period_sec, 2) * pow(ax_sini_cm, 3) / kGravityConst / kSunMass
        * pow(mass_ratio, 3);
    return mass_func;
}


double BinaryOrb::GetMu(double mass_companion, double mass_compact)
{
    double mu = kGravityConst * (mass_companion + mass_compact) * kSunMass;
    return mu;
}


double BinaryOrb::GetSemimajorAxis(double period, double mass_companion, double mass_compact)
{
    double mu = GetMu(mass_companion, mass_compact);
    double semimajor_axis = pow(pow(period * kDayToSec /(2 * kPi), 2) * mu, 1./3.) / kSpeedOfLight;
    return semimajor_axis;
}

double BinaryOrb::GetPeriod(double semimajor_axis, double mass_companion, double mass_compact)
{
    double mu = GetMu(mass_companion, mass_compact);
    double period = 2 * kPi * sqrt(pow(semimajor_axis * kSpeedOfLight, 3)/ mu);
    return period;
}

double BinaryOrb::AxToSemimajorAxis(double a_x,
                                    double mass_companion,
                                    double mass_compact)
{
    double semimajor_axis = a_x * (mass_companion + mass_compact) / mass_companion;
    return semimajor_axis;
}

    
double BinaryOrb::SemimajorAxisToAx(double semimajor_axis,
                                    double mass_companion,
                                    double mass_compact)
{
    double a_x = semimajor_axis * mass_companion / (mass_companion + mass_compact);
    return a_x;
}


//
// BinaryOrb1
//

void BinaryOrb1::Load(string orbfile)
{
    string* line_arr = NULL;
    long nline = 0;
    MiIolib::GenReadFileSkipComment(orbfile, &line_arr, &nline);
    if(5 != nline){
        printf("%s::%s: %s: error: orbfile, nline = %ld\n",
               GetClassName().c_str(), __func__, GetTitle().c_str(), nline);
        abort();
    }
  
    int iline = 0;
    period_      = atof(line_arr[iline].c_str()); iline++;
    ax_sini_     = atof(line_arr[iline].c_str()); iline++;
    ecc_         = atof(line_arr[iline].c_str()); iline++;
    time_peri_   = atof(line_arr[iline].c_str()); iline++;
    angle_peri_  = atof(line_arr[iline].c_str()); iline++;

    MiIolib::DelReadFile(line_arr);
    if(0 < g_flag_verbose){
        MPrintInfoClass("done.");
    }
}

void BinaryOrb1::Set(double period, double ax_sini,
                     double ecc, double time_peri,
                     double angle_peri)
{
    period_      = period;
    ax_sini_     = ax_sini;
    ecc_         = ecc;
    time_peri_   = time_peri;
    angle_peri_  = angle_peri;
}

void BinaryOrb1::Copy(const BinaryOrb1* const org)
{
    if(this == org) {return;}
    if(NULL == org) {return;}
     
    CopyTitle(org);
    
    period_     = org->period_;
    ax_sini_    = org->ax_sini_;
    ecc_        = org->ecc_;
    time_peri_  = org->time_peri_;
    angle_peri_ = org->angle_peri_;
}

BinaryOrb1* const BinaryOrb1::Clone() const
{
    BinaryOrb1* obj_new = new BinaryOrb1;
    obj_new->Copy(this);
    return obj_new;
}

void BinaryOrb1::Print(FILE *fp) const
{
    string func_name = "BinaryOrb1::Print()";
    fprintf(fp, " ---- %s --- \n", func_name.c_str());
    fprintf(fp, "period_           = %f\n", period_);
    fprintf(fp, "ax_sini_          = %f\n", ax_sini_);
    fprintf(fp, "ecc_              = %f\n", ecc_);
    fprintf(fp, "time_peri_        = %f\n", time_peri_);
    fprintf(fp, "angle_peri_       = %f\n", angle_peri_);
    fprintf(fp, " ==== %s === \n", func_name.c_str());
}

void BinaryOrb1::Save(string file) const
{
    FILE *fp = fopen(file.c_str(), "w");
    PrintData(fp);
    fclose(fp);
}

void BinaryOrb1::PrintData(FILE *fp) const
{
    fprintf(fp, "%f\n", period_);
    fprintf(fp, "%f\n", ax_sini_);
    fprintf(fp, "%f\n", ecc_);
    fprintf(fp, "%f\n", time_peri_);
    fprintf(fp, "%f\n", angle_peri_);
}

// time_obj
double BinaryOrb1::GetTimeObj(MirFunc* func_bin_orb_obs_time,
                              double time_mjd_obs,
                              double period)
{
    double epsilon = 1.e-3 / kDayToSec;
    double root_init0 = time_mjd_obs - period/4.0;
    double root_init1 = time_mjd_obs + period/4.0;
    double time_mjd_obj = MirSolve::GetRootBisectionEqC(func_bin_orb_obs_time, NULL,
                                                        root_init0, root_init1, time_mjd_obs, epsilon);
    return time_mjd_obj;
}


// delay time (sec)
// z axis is a vector from us to the center of mass of the binary system

double BinaryOrb1::GetDelayTime(double time_mjd) const
{
    double ecc_anomaly = BinaryOrb::GetEccAnomaly(time_mjd, period_, time_peri_, ecc_);

    double z_x = ax_sini_ * ( sin(angle_peri_ * DEG2RAD) * ( cos(ecc_anomaly) - ecc_ )
                              + cos(angle_peri_ * DEG2RAD) * sqrt(1.0 - pow(ecc_, 2)) * sin(ecc_anomaly) );
    double delay_time = z_x;
    return delay_time;
}

// Doppler-shifted pulse frequency (Hz)
double BinaryOrb1::GetDopplerNu(double time_mjd, double nu) const
{
    double ecc_anomaly = BinaryOrb::GetEccAnomaly(time_mjd, period_, time_peri_, ecc_);
  
    double vz_x = ax_sini_ * 2 * kPi / (period_ * kDayToSec) / (1.0 - ecc_ * cos(ecc_anomaly))
        * ( -1 * sin(angle_peri_ * DEG2RAD) * sin(ecc_anomaly)
            + cos(angle_peri_ * DEG2RAD) * sqrt(1.0 - pow(ecc_, 2)) * cos(ecc_anomaly) );

    double nu_doppler = nu * (1 - vz_x);
    return nu_doppler;
}

void BinaryOrb1::Null()
{
    period_ = 0.0;
    ax_sini_ = 0.0;
    ecc_ = 0.0;
    time_peri_ = 0.0;
    angle_peri_ = 0.0;
}

//
// BinaryOrbObsTimeFunc
//

void BinaryOrbObsTimeFunc::Init(BinaryOrb1* binorb)
{
    binorb_ = new BinaryOrb1;
    binorb_->Copy(binorb);
}

void BinaryOrbObsTimeFunc::Copy(const BinaryOrbObsTimeFunc* const org)
{
    if(this == org) {return;}
    if(NULL == org) {return;}
    
    CopyTitle(org);
    CopyMirFunc(org);

    Null();
    binorb_ = new BinaryOrb1;
    binorb_->Copy(org->GetBinorb());
}

BinaryOrbObsTimeFunc* const BinaryOrbObsTimeFunc::Clone() const
{
    BinaryOrbObsTimeFunc* obj_new = new BinaryOrbObsTimeFunc;
    obj_new->Copy(this);
    return obj_new;
}

double BinaryOrbObsTimeFunc::Eval(const double* const xval, const double* const par) const
{
    double time_mjd_obj = xval[0];
    double time_mjd_obs = time_mjd_obj + GetBinorb()->GetDelayTime(time_mjd_obj) / kDayToSec;
    return time_mjd_obs;
}

double BinaryOrbObsTimeFunc::Eval1d(double xval, const double* const par) const
{
    double xval_arr[1];
    xval_arr[0] = xval;
    double ans = Eval(xval_arr, par);
    return ans;
}

void BinaryOrbObsTimeFunc::Null()
{
    if(NULL != binorb_){delete binorb_; binorb_ = NULL;}
}


//
// BinaryOrb2
//

// public

void BinaryOrb2::SetA(double semimajor_axis, double ecc, double time_peri,
                      double angle_inc, double angle_peri,
                      double mass_companion, double mass_compact,
                      double radius_companion)
{
    semimajor_axis_  = semimajor_axis;
    period_          = BinaryOrb::GetPeriod(semimajor_axis, mass_companion, mass_compact);
    ecc_             = ecc;   
    time_peri_       = time_peri; 
    angle_inc_       = angle_inc;
    angle_peri_      = angle_peri;
    mass_companion_  = mass_companion;
    mass_compact_    = mass_compact;
    radius_companion_ = radius_companion; 

    // this value never affects timing data
    // owing to the symmetry around the axis of the line of sight.
    angle_lan_       = 0.0;
}

void BinaryOrb2::SetP(double period, double ecc, double time_peri,
                      double angle_inc, double angle_peri,
                      double mass_companion, double mass_compact,
                      double radius_companion)
{
    period_          = period;
    semimajor_axis_  = BinaryOrb::GetSemimajorAxis(period, mass_companion, mass_compact);
    ecc_             = ecc;   
    time_peri_       = time_peri; 
    angle_inc_       = angle_inc;
    angle_peri_      = angle_peri;
    mass_companion_  = mass_companion;
    mass_compact_    = mass_compact;
    radius_companion_ = radius_companion; 

    // this value never affects timing data
    // owing to the symmetry around the axis of the line of sight.
    angle_lan_       = 0.0;
}

void BinaryOrb2::LoadA(string file)
{
    Null();
    
    string* line_arr = NULL;
    long nline = 0;
    MiIolib::GenReadFileSkipComment(file, &line_arr, &nline);
    if(8 != nline){
        abort();
    }
    long iline = 0;
    double semimajor_axis   = atof(line_arr[iline].c_str()); iline ++;
    double ecc              = atof(line_arr[iline].c_str()); iline ++;
    double time_peri        = atof(line_arr[iline].c_str()); iline ++;
    double angle_inc        = atof(line_arr[iline].c_str()); iline ++;
    double angle_peri       = atof(line_arr[iline].c_str()); iline ++;
    double mass_companion   = atof(line_arr[iline].c_str()); iline ++;
    double mass_compact     = atof(line_arr[iline].c_str()); iline ++;
    double radius_companion = atof(line_arr[iline].c_str()); iline ++;

    MiIolib::DelReadFile(line_arr);

    SetA(semimajor_axis, ecc, time_peri,
         angle_inc, angle_peri,
         mass_companion, mass_compact,
         radius_companion);
}

void BinaryOrb2::LoadP(string file)
{
    Null();
    
    string* line_arr = NULL;
    long nline = 0;
    MiIolib::GenReadFileSkipComment(file, &line_arr, &nline);
    if(8 != nline){
        abort();
    }
    long iline = 0;
    double period           = atof(line_arr[iline].c_str()); iline ++;
    double ecc              = atof(line_arr[iline].c_str()); iline ++;
    double time_peri        = atof(line_arr[iline].c_str()); iline ++;
    double angle_inc        = atof(line_arr[iline].c_str()); iline ++;
    double angle_peri       = atof(line_arr[iline].c_str()); iline ++;
    double mass_companion   = atof(line_arr[iline].c_str()); iline ++;
    double mass_compact     = atof(line_arr[iline].c_str()); iline ++;
    double radius_companion = atof(line_arr[iline].c_str()); iline ++;

    MiIolib::DelReadFile(line_arr);

    SetP(period, ecc, time_peri,
         angle_inc, angle_peri,
         mass_companion, mass_compact,
         radius_companion);
}

void BinaryOrb2::Copy(const BinaryOrb2* const org)
{
    if(this == org) {return;}
    if(NULL == org) {return;}
     
    CopyTitle(org);

    semimajor_axis_ = org->semimajor_axis_;
    ecc_            = org->ecc_;
    time_peri_      = org->time_peri_;
    angle_inc_      = org->angle_inc_;
    angle_lan_      = org->angle_lan_;
    angle_peri_     = org->angle_peri_;
    period_         = org->period_;
    mass_companion_ = org->mass_companion_;
    mass_compact_   = org->mass_compact_;
    radius_companion_ = org->radius_companion_;
}

BinaryOrb2* const BinaryOrb2::Clone() const
{
    BinaryOrb2* obj_new = new BinaryOrb2;
    obj_new->Copy(this);
    return obj_new;
}

void BinaryOrb2::Print(FILE *fp) const
{
    string func_name = "BinaryOrb2::Print()";
    fprintf(fp, " ---- %s --- \n", func_name.c_str());
    fprintf(fp, "semimajor_axis_   = %f\n", semimajor_axis_);
    fprintf(fp, "ecc_              = %f\n", ecc_);
    fprintf(fp, "time_peri_        = %f\n", time_peri_);
    fprintf(fp, "angle_inc_        = %f\n", angle_inc_);
    fprintf(fp, "angle_lan_        = %f\n", angle_lan_);
    fprintf(fp, "angle_peri_       = %f\n", angle_peri_);
    fprintf(fp, "period_           = %f\n", period_);
    fprintf(fp, "mass_companion_   = %f\n", mass_companion_);
    fprintf(fp, "mass_compact_     = %f\n", mass_compact_);
    fprintf(fp, "radius_companion_ = %f\n", radius_companion_);
    fprintf(fp, " ==== %s === \n", func_name.c_str());
}


void BinaryOrb2::GetXYZByMjd(double time_mjd, AtVect xyz_out) const
{
    double ecc_anomaly = BinaryOrb::GetEccAnomaly(time_mjd, period_,
                                                  time_peri_, ecc_);
    GetXYZ(ecc_anomaly, xyz_out);
}

void BinaryOrb2::GetVXYZByMjd(double time_mjd, AtVect vxyz_out) const
{
    double ecc_anomaly = BinaryOrb::GetEccAnomaly(time_mjd, period_,
                                                  time_peri_, ecc_);
    GetVXYZ(ecc_anomaly, vxyz_out);

}


void BinaryOrb2::GetXYZOrbPlaneByMjd(double time_mjd, AtVect xyz_orb_plane_out) const
{
    double ecc_anomaly = BinaryOrb::GetEccAnomaly(time_mjd, period_,
                                                  time_peri_, ecc_);
    GetXYZOrbPlane(ecc_anomaly, xyz_orb_plane_out);
}

void BinaryOrb2::GetVXYZOrbPlaneByMjd(double time_mjd, AtVect vxyz_orb_plane_out) const
{
    double ecc_anomaly = BinaryOrb::GetEccAnomaly(time_mjd, period_,
                                                  time_peri_, ecc_);
    GetVXYZOrbPlane(ecc_anomaly, vxyz_orb_plane_out);

}


// delay time (sec) from center of mass (r_G)
double BinaryOrb2::GetDelayTimeCompact(double time_mjd) const
{
    double ecc_anomaly = BinaryOrb::GetEccAnomaly(time_mjd, period_,
                                                  time_peri_, ecc_);
    AtVect xyz;
    GetXYZ(ecc_anomaly, xyz);

    double z_X = mass_companion_ / (mass_companion_ + mass_compact_) * xyz[2];
    double delay = z_X;
    return delay;
}


// Doppler-shifted pulse frequency (Hz)
double BinaryOrb2::GetDopplerNuCompact(double time_mjd, double nu) const
{
    double ecc_anomaly = BinaryOrb::GetEccAnomaly(time_mjd, period_,
                                                  time_peri_, ecc_);
    AtVect vxyz;
    GetVXYZ(ecc_anomaly, vxyz);
    double vz_X = mass_companion_ / (mass_companion_ + mass_compact_) * vxyz[2];

    printf("vz_X = %e\n", vz_X);
    
    double nu_doppler = nu * (1 - vz_X);
    return nu_doppler;
}


int BinaryOrb2::Eclipse(double time_mjd) const
{
    double ecc_anomaly = BinaryOrb::GetEccAnomaly(time_mjd,
                                                  period_, time_peri_, ecc_);
    AtVect xyz;
    GetXYZ(ecc_anomaly, xyz);
    double rad_companion_lts = radius_companion_ * kSunEqRad / kSpeedOfLight;

    int flag_eclipse = 0;
    if(xyz[2] > 0 &&
       pow(xyz[0], 2) + pow(xyz[1], 2) < pow(rad_companion_lts, 2)){
        flag_eclipse = 1;
    }
    return flag_eclipse;
}

int BinaryOrb2::Collision(double time_mjd) const
{
    double ecc_anomaly = BinaryOrb::GetEccAnomaly(time_mjd,
                                                  period_, time_peri_, ecc_);
    AtVect xyz;
    GetXYZ(ecc_anomaly, xyz);
    double rad_companion_lts = radius_companion_ * kSunEqRad / kSpeedOfLight;

    int flag_collision = 0;
    if(pow(xyz[0], 2) + pow(xyz[1], 2) + pow(xyz[2], 2) < pow(rad_companion_lts, 2)){
        flag_collision = 1;
    }
    return flag_collision;
}

//
// private
//

void BinaryOrb2::Null()
{
    semimajor_axis_ = 0.0;
    ecc_ = 0.0;
    time_peri_ = 0.0;
    angle_inc_ = 0.0;
    angle_lan_ = 0.0;
    angle_peri_ = 0.0;
    period_ = 0.0;
    mass_companion_ = 0.0;
    mass_compact_ = 0.0;
    radius_companion_ = 0.0;
}

void BinaryOrb2::RotVect(AtVect xyz_orb_plane, AtVect xyz) const
{
    AtVect x_axis = {1.0, 0.0, 0.0};
    AtVect z_axis = {0.0, 0.0, 1.0};

    AtRotMat rm_lan;
    AtRotMat rm_inc;
    AtRotMat rm_peri;
    AtRotMat rm_tmp;
    AtRotMat rm_all;
  
    atSetRotMat(z_axis, -1 * angle_lan_ * DEG2RAD, rm_lan);
    atSetRotMat(x_axis, -1 * angle_inc_ * DEG2RAD, rm_inc);
    atSetRotMat(z_axis, -1 * angle_peri_ * DEG2RAD, rm_peri);

    // rm_tmp = rm_inc * rm_peri
    // rm_all = rm_lan * rm_tmp
    //        = rm_lan * rm_inc * rm_peri
    atRMProd(rm_peri, rm_inc, rm_tmp);
    atRMProd(rm_tmp, rm_lan, rm_all);

    atRotVect(rm_all, xyz_orb_plane, xyz);
}


// lt-s
double BinaryOrb2::GetXOrbPlane(double ecc_anomaly) const
{
    double x_orb_plane = semimajor_axis_ * (cos(ecc_anomaly) - ecc_);
    return x_orb_plane;
}

// lt-s
double BinaryOrb2::GetYOrbPlane(double ecc_anomaly) const
{
    double y_orb_plane = semimajor_axis_ * sqrt(1 - pow(ecc_, 2)) * sin(ecc_anomaly);
    return y_orb_plane;
}

// lt-s / s
double BinaryOrb2::GetVXOrbPlane(double ecc_anomaly) const
{
    double vx_orb_plane = -1 * BinaryOrb::GetMeanMotion(period_) * semimajor_axis_ * sin(ecc_anomaly) /
        (1 - ecc_ * cos(ecc_anomaly));
    return vx_orb_plane;
}

// lt-s / s
double BinaryOrb2::GetVYOrbPlane(double ecc_anomaly) const
{
    double vy_orb_plane = BinaryOrb::GetMeanMotion(period_) * semimajor_axis_
        * sqrt(1 - pow(ecc_, 2)) * cos(ecc_anomaly) /
        (1 - ecc_ * cos(ecc_anomaly));
    return vy_orb_plane;
}


void BinaryOrb2::GetXYZ(double ecc_anomaly, AtVect xyz_out) const
{
    AtVect xyz_orb_plane;
    xyz_orb_plane[0] = GetXOrbPlane(ecc_anomaly);
    xyz_orb_plane[1] = GetYOrbPlane(ecc_anomaly);
    xyz_orb_plane[2] = 0.0;

    RotVect(xyz_orb_plane, xyz_out);
}

void BinaryOrb2::GetVXYZ(double ecc_anomaly, AtVect vxyz_out) const
{
    AtVect vxyz_orb_plane;
    vxyz_orb_plane[0] = GetVXOrbPlane(ecc_anomaly);
    vxyz_orb_plane[1] = GetVYOrbPlane(ecc_anomaly);
    vxyz_orb_plane[2] = 0.0;

    RotVect(vxyz_orb_plane, vxyz_out);
}


void BinaryOrb2::GetXYZOrbPlane(double ecc_anomaly, AtVect xyz_orb_plane_out) const
{
    xyz_orb_plane_out[0] = GetXOrbPlane(ecc_anomaly);
    xyz_orb_plane_out[1] = GetYOrbPlane(ecc_anomaly);
    xyz_orb_plane_out[2] = 0.0;
}

void BinaryOrb2::GetVXYZOrbPlane(double ecc_anomaly, AtVect vxyz_orb_plane_out) const
{
    vxyz_orb_plane_out[0] = GetVXOrbPlane(ecc_anomaly);
    vxyz_orb_plane_out[1] = GetVYOrbPlane(ecc_anomaly);
    vxyz_orb_plane_out[2] = 0.0;
}

