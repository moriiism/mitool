#include "mit_eph.h"

// public

void Ephemeris::Set(double nu, double nu_err,
                    double nu_dot, double nu_dot_err,
                    double nu_dot2, double nu_dot2_err,
                    double nu_dot3, double nu_dot3_err,
                    double phase, double phase_err,
                    double epoch_mjd, double t_st_mjd, double t_ed_mjd)
{
    nu_          = nu;
    nu_err_      = nu_err;
    nu_dot_      = nu_dot;
    nu_dot_err_  = nu_dot_err;
    nu_dot2_     = nu_dot2;
    nu_dot2_err_ = nu_dot2_err;
    nu_dot3_     = nu_dot3;
    nu_dot3_err_ = nu_dot3_err;
    phase_       = phase;
    phase_err_   = phase_err;
    epoch_mjd_   = epoch_mjd;
    t_st_mjd_    = t_st_mjd;
    t_ed_mjd_    = t_ed_mjd;
}

void Ephemeris::Load(string ephfile)
{
    Null();
    
    string* line_arr = NULL;
    long nline = 0;
    MiIolib::GenReadFileSkipComment(ephfile, &line_arr, &nline);
    if(13 != nline){
        printf("%s::%s: %s: error: bad ephfile, nline = %ld\n",
               GetClassName().c_str(), __func__, GetTitle().c_str(), nline);
        abort();
    }
  
    int iline = 0;
    nu_          = atof(line_arr[iline].c_str()); iline++;
    nu_err_      = atof(line_arr[iline].c_str()); iline++;
    nu_dot_      = atof(line_arr[iline].c_str()); iline++;
    nu_dot_err_  = atof(line_arr[iline].c_str()); iline++;
    nu_dot2_     = atof(line_arr[iline].c_str()); iline++;
    nu_dot2_err_ = atof(line_arr[iline].c_str()); iline++;
    nu_dot3_     = atof(line_arr[iline].c_str()); iline++;
    nu_dot3_err_ = atof(line_arr[iline].c_str()); iline++;
    phase_       = atof(line_arr[iline].c_str()); iline++;
    phase_err_   = atof(line_arr[iline].c_str()); iline++;
    epoch_mjd_   = atof(line_arr[iline].c_str()); iline++;
    t_st_mjd_    = atof(line_arr[iline].c_str()); iline++;
    t_ed_mjd_    = atof(line_arr[iline].c_str()); iline++;

    MiIolib::DelReadFile(line_arr);
    if(0 < g_flag_verbose){
        MPrintInfoClass("done.");
    }
}



void Ephemeris::Copy(const Ephemeris* const org)
{
    if(this == org) {return;}
    if(NULL == org) {return;}

    CopyTitle(org);
    Null();
    nu_          = org->nu_;
    nu_err_      = org->nu_err_;
    nu_dot_      = org->nu_dot_;
    nu_dot_err_  = org->nu_dot_err_;
    nu_dot2_     = org->nu_dot2_;
    nu_dot2_err_ = org->nu_dot2_err_;
    nu_dot3_     = org->nu_dot3_;
    nu_dot3_err_ = org->nu_dot3_err_;
    phase_       = org->phase_;
    phase_err_   = org->phase_err_;
    epoch_mjd_   = org->epoch_mjd_;
    t_st_mjd_    = org->t_st_mjd_;
    t_ed_mjd_    = org->t_ed_mjd_;
}


Ephemeris* const Ephemeris::Clone() const
{
    Ephemeris* obj_new = new Ephemeris;
    obj_new->Copy(this);
    return obj_new;
}


double Ephemeris::GetPeriod() const
{
    double period = EphemerisCalc::GetPeriod(nu_);
    return period;
}

double Ephemeris::GetPeriodDot() const
{
    double period_dot = EphemerisCalc::GetPeriodDot(nu_, nu_dot_);
    return period_dot;
}

double Ephemeris::GetPeriodDot2() const
{
    double period_dot2 = EphemerisCalc::GetPeriodDot2(nu_,
                                                      nu_dot_,
                                                      nu_dot2_);
    return period_dot2;
}

double Ephemeris::GetPeriodDot3() const
{
    double period_dot3 = EphemerisCalc::GetPeriodDot3(nu_,
                                                      nu_dot_,
                                                      nu_dot2_,
                                                      nu_dot3_);
    return period_dot3;
}

double Ephemeris::GetPeriodErr() const
{
    double period_err = EphemerisCalc::GetPeriodErr(nu_, nu_err_);
    return period_err;
}

double Ephemeris::GetPeriodDotErr() const
{
    double period_dot_err = EphemerisCalc::GetPeriodDotErr(nu_, nu_err_,
                                                           nu_dot_, nu_dot_err_);
    return period_dot_err;
}

double Ephemeris::GetPeriodDot2Err() const
{
    double period_dot2_err = EphemerisCalc::GetPeriodDot2Err(nu_, nu_err_,
                                                             nu_dot_, nu_dot_err_,
                                                             nu_dot2_, nu_dot2_err_);
    return period_dot2_err;
}

double Ephemeris::GetPeriodDot3Err() const
{
    double period_dot3_err = EphemerisCalc::GetPeriodDot3Err(nu_, nu_err_,
                                                             nu_dot_, nu_dot_err_,
                                                             nu_dot2_, nu_dot2_err_,
                                                             nu_dot3_, nu_dot3_err_);
    return period_dot3_err;
}



double Ephemeris::GetNuAtTimeMjd(double time_mjd) const
{
    double tdiff_mjd = time_mjd - epoch_mjd_;
    double tdiff = tdiff_mjd * kDayToSec;

    double nu
        = nu_
        + nu_dot_  *     tdiff
        + nu_dot2_ * pow(tdiff, 2) / 2.
        + nu_dot3_ * pow(tdiff, 3) / 6.;
    return nu;
}

double Ephemeris::GetNuErrAtTimeMjd(double time_mjd) const
{
    double tdiff_mjd = time_mjd - epoch_mjd_;
    double tdiff = tdiff_mjd * kDayToSec;

    double nu_err
        = sqrt( pow(                     nu_err_     , 2) +
                pow(    tdiff          * nu_dot_err_ , 2) +
                pow(pow(tdiff, 2) / 2. * nu_dot2_err_, 2) +
                pow(pow(tdiff, 3) / 6. * nu_dot3_err_, 2) );
    return nu_err;
}

double Ephemeris::GetNuDotAtTimeMjd(double time_mjd) const
{
    double tdiff_mjd = time_mjd - epoch_mjd_;
    double tdiff = tdiff_mjd * kDayToSec;

    double nu_dot
        = nu_dot_
        + nu_dot2_ *     tdiff
        + nu_dot3_ * pow(tdiff, 2) / 2.;
    return nu_dot;
}

double Ephemeris::GetNuDotErrAtTimeMjd(double time_mjd) const
{
    double tdiff_mjd = time_mjd - epoch_mjd_;
    double tdiff = tdiff_mjd * kDayToSec;

    double nu_dot_err
        = sqrt( pow(                     nu_dot_err_ , 2) +
                pow(    tdiff          * nu_dot2_err_, 2) +
                pow(pow(tdiff, 2) / 2. * nu_dot3_err_, 2) );
    return nu_dot_err;
}

double Ephemeris::GetNuDot2AtTimeMjd(double time_mjd) const
{
    double tdiff_mjd = time_mjd - epoch_mjd_;
    double tdiff = tdiff_mjd * kDayToSec;

    double nu_dot2
        = nu_dot2_
        + nu_dot3_ * tdiff;
    return nu_dot2;
}

double Ephemeris::GetNuDot2ErrAtTimeMjd(double time_mjd) const
{
    double tdiff_mjd = time_mjd - epoch_mjd_;
    double tdiff = tdiff_mjd * kDayToSec;

    double nu_dot2_err
        = sqrt( pow(                     nu_dot2_err_, 2) +
                pow(    tdiff          * nu_dot3_err_, 2) );
    return nu_dot2_err;
}

double Ephemeris::GetNuDot3AtTimeMjd(double time_mjd) const
{
    return nu_dot3_;
}

double Ephemeris::GetNuDot3ErrAtTimeMjd(double time_mjd) const
{
    return nu_dot3_err_;
}


double Ephemeris::GetGphaseAtTimeMjd(double time_mjd) const
{
    double tdiff_mjd = time_mjd - epoch_mjd_;
    double tdiff = tdiff_mjd * kDayToSec;

    double gphase = phase_
        + nu_      *     tdiff
        + nu_dot_  * pow(tdiff, 2) / 2.
        + nu_dot2_ * pow(tdiff, 3) / 6.
        + nu_dot3_ * pow(tdiff, 4) / 24.;
    return gphase;
}

double Ephemeris::GetGphaseErrAtTimeMjd(double time_mjd) const
{
    double tdiff_mjd = time_mjd - epoch_mjd_;
    double tdiff = tdiff_mjd * kDayToSec;

    double gphase_err = sqrt( pow(phase_err_, 2) +
                              pow(    tdiff           * nu_err_, 2) +
                              pow(pow(tdiff, 2) / 2.  * nu_dot_err_, 2) +
                              pow(pow(tdiff, 3) / 6.  * nu_dot2_err_, 2) +
                              pow(pow(tdiff, 4) / 24. * nu_dot3_err_, 2) );
    return gphase_err;
}

double Ephemeris::GetPhaseAtTimeMjd(double time_mjd) const
{
    double gphase = GetGphaseAtTimeMjd(time_mjd);
    double phase = gphase - floor(gphase);
    return phase;
}

Ephemeris* const Ephemeris::GenEphemerisAtTimeMjd(double time_mjd) const
{
    double nu          = GetNuAtTimeMjd(time_mjd);
    double nu_err      = GetNuErrAtTimeMjd(time_mjd);
    double nu_dot      = GetNuDotAtTimeMjd(time_mjd);
    double nu_dot_err  = GetNuDotErrAtTimeMjd(time_mjd);
    double nu_dot2     = GetNuDot2AtTimeMjd(time_mjd);
    double nu_dot2_err = GetNuDot2ErrAtTimeMjd(time_mjd);
    double nu_dot3     = GetNuDot3AtTimeMjd(time_mjd);
    double nu_dot3_err = GetNuDot3ErrAtTimeMjd(time_mjd);
    double phase       = GetPhaseAtTimeMjd(time_mjd);
    double phase_err   = GetGphaseErrAtTimeMjd(time_mjd);
  
    Ephemeris* eph = new Ephemeris;
    eph->Set(nu, nu_err, nu_dot, nu_dot_err,
             nu_dot2, nu_dot2_err, nu_dot3, nu_dot3_err,
             phase, phase_err,
             time_mjd, t_st_mjd_, t_ed_mjd_);
    return eph;
}


double Ephemeris::GetTimeMjdAtGphase(double gphase) const
{

    // see morii's lognote (2010.06.10 -- ), p2
    // gphase = GetPhase() at eph_->GetEpochMjd()

    double gphase_diff = gphase - GetPhase();
  
    double coeff1 = GetPeriod();
    double coeff2 = GetPeriodDot() * GetPeriod();
    double coeff3
        = GetPeriodDot2() * pow(GetPeriod(), 2)
        + pow(GetPeriodDot(), 2) * GetPeriod();
    double coeff4
        = GetPeriodDot3() * pow(GetPeriod(), 3)
        + 4 * GetPeriodDot2() * GetPeriodDot() * pow(GetPeriod(), 2)
        + pow(GetPeriodDot(), 3) * GetPeriod();
  
    double timediff_sec = coeff1 * gphase_diff
        + coeff2 * pow(gphase_diff, 2) / 2.
        + coeff3 * pow(gphase_diff, 3) / 6.
        + coeff4 * pow(gphase_diff, 4) / 24.;

    double time_mjd = GetEpochMjd() + timediff_sec / kDayToSec;
    return time_mjd;
}


void Ephemeris::Print(FILE *fp) const
{
    fprintf(fp, "! Ephemeris::Print: \n");
    fprintf(fp, "! nu_:            %.15e\n", nu_);
    fprintf(fp, "! nu_err_:        %.15e\n", nu_err_);
    fprintf(fp, "! nu_dot_:        %.15e\n", nu_dot_);
    fprintf(fp, "! nu_dot_err_:    %.15e\n", nu_dot_err_);
    fprintf(fp, "! nu_dot2_:       %.15e\n", nu_dot2_);
    fprintf(fp, "! nu_dot2_err_:   %.15e\n", nu_dot2_err_);
    fprintf(fp, "! nu_dot3_:       %.15e\n", nu_dot3_);
    fprintf(fp, "! nu_dot3_err_:   %.15e\n", nu_dot3_err_);
    fprintf(fp, "! phase_      :   %.15e\n", phase_);
    fprintf(fp, "! phase_err_  :   %.15e\n", phase_err_);
    fprintf(fp, "! epoch_mjd_:     %.15f\n", epoch_mjd_);
    fprintf(fp, "! t_st_mjd_:      %.15f\n", t_st_mjd_);
    fprintf(fp, "! t_ed_mjd_:      %.15f\n", t_ed_mjd_);
    fprintf(fp, "! Ephemeris::Print: DONE.\n");
}

void Ephemeris::Save(string ephfile) const
{
    FILE *fp = fopen(ephfile.c_str(), "w");
    fprintf(fp, "%.15e\n", nu_);
    fprintf(fp, "%.15e\n", nu_err_);
    fprintf(fp, "%.15e\n", nu_dot_);
    fprintf(fp, "%.15e\n", nu_dot_err_);
    fprintf(fp, "%.15e\n", nu_dot2_);
    fprintf(fp, "%.15e\n", nu_dot2_err_);
    fprintf(fp, "%.15e\n", nu_dot3_);
    fprintf(fp, "%.15e\n", nu_dot3_err_);
    fprintf(fp, "%.15e\n", phase_);
    fprintf(fp, "%.15e\n", phase_err_);
    fprintf(fp, "%.15f\n", epoch_mjd_);
    fprintf(fp, "%.15f\n", t_st_mjd_);
    fprintf(fp, "%.15f\n", t_ed_mjd_);
    fclose(fp);
}


void Ephemeris::PrintRange(FILE *fp) const
{
    fprintf(fp, "Ephemeris::PrintRange(): nu      = %.15e -- %.15e\n",
            nu_ - nu_err_, nu_ + nu_err_);
    fprintf(fp, "Ephemeris::PrintRange(): nu_dot  = %.15e -- %.15e\n",
            nu_dot_ - nu_dot_err_, nu_dot_ + nu_dot_err_);
    fprintf(fp, "Ephemeris::PrintRange(): nu_dot2 = %.15e -- %.15e\n",
            nu_dot2_ - nu_dot2_err_, nu_dot2_ + nu_dot2_err_);
    fprintf(fp, "Ephemeris::PrintRange(): nu_dot3 = %.15e -- %.15e\n",
            nu_dot3_ - nu_dot3_err_, nu_dot3_ + nu_dot3_err_);
    fprintf(fp, "Ephemeris::PrintRange(): phase   = %.15e -- %.15e\n",
            phase_ - phase_err_, phase_ + phase_err_);

}


void Ephemeris::MkQdp(string qdpout) const
{
    FILE *fp_qdp = fopen(qdpout.c_str(), "w");
    fprintf(fp_qdp, "skip sing\n");
    fprintf(fp_qdp, "read serr 1 2\n");
    fprintf(fp_qdp, "\n");

    int nbin = 100;
    double delta_time = (t_ed_mjd_ - t_st_mjd_)/nbin;

    for(int ibin = 0; ibin < nbin; ibin++){
        double time_mjd = t_st_mjd_ + (ibin + 0.5) * delta_time;
        double nu = GetNuAtTimeMjd(time_mjd);
        double nu_err = GetNuErrAtTimeMjd(time_mjd);
        fprintf(fp_qdp, "%e %e %e %e\n",
                time_mjd, delta_time/2.,
                nu, nu_err);
    }

    fprintf(fp_qdp, "\n");
    fprintf(fp_qdp, "lw 5\n");
    fclose(fp_qdp);
}


int Ephemeris::CheckNu() const
{
    int status = kRetNormal;
    int nbin = 100;
    double delta_time = (t_ed_mjd_ - t_st_mjd_)/nbin;
    for(int ibin = 0; ibin < nbin; ibin++){
        double time_mjd = t_st_mjd_ + (ibin + 0.5) * delta_time;
        double nu = GetNuAtTimeMjd(time_mjd);
        // double nu_err = GetNuErrAtTimeMjd(time_mjd);
        if(nu < 0){
            printf("Ephemeris::CheckNu: bad ephemeris: nu < 0 at MJD %f\n", time_mjd);
            status = kRetError;
            break;
        }
    }
    return status;
}

// private

void Ephemeris::Null()
{
    nu_          = 0.0;
    nu_err_      = 0.0;
    nu_dot_      = 0.0;
    nu_dot_err_  = 0.0;
    nu_dot2_     = 0.0;
    nu_dot2_err_ = 0.0;
    nu_dot3_     = 0.0;
    nu_dot3_err_ = 0.0;

    phase_       = 0.0;
    phase_err_   = 0.0;
  
    epoch_mjd_   = 0.0;
    t_st_mjd_    = 0.0;
    t_ed_mjd_    = 0.0;
}
