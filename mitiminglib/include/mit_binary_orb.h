#ifndef MORIIISM_MITOOL_MITIMINGLIB_BINARY_ORB_H_
#define MORIIISM_MITOOL_MITIMINGLIB_BINARY_ORB_H_

#include "atFunctions.h"

#include "mi_base.h"
#include "mi_iolib.h"
#include "mir_mathpar.h"
#include "mir_physpar.h"
#include "mir_func.h"
#include "mir_solve.h"

//
// binary orbit
//

class BinaryOrb1;
class BinaryOrbObsTimeFunc;

namespace BinaryOrb
{
    double GetMeanMotion(double period);
    double TimePeriToTime90(double time_peri, double period);
    double Time90ToTimePeri(double time_90, double period);

    double GetMeanAnomaly(double time_mjd, double period, double time_peri);
    double GetEccAnomaly(double time_mjd, double period,
                         double time_peri, double ecc);
    double SolveKeplerEq(double mean_anomaly, double ecc);
    double FuncInKeplerEq(double ecc_anomaly, double ecc, double mean_anomaly);
    double FuncPrimeInKeplerEq(double ecc_anomaly, double ecc);

    double GetMassFunction(double period, double ax_sini, double mass_ratio);
    // mass_ratio: q = m_2 / m_1 = m_x-ray / m_companion

    double GetMu(double mass_companion, double mass_compact);
    double GetSemimajorAxis(double period, double mass_companion, double mass_compact);
    double GetPeriod(double semimajor_axis, double mass_companion, double mass_compact);
    
    double AxToSemimajorAxis(double a_x, double mass_companion, double mass_compact);
    double SemimajorAxisToAx(double semimajor_axis, double mass_companion, double mass_compact);
}

class BinaryOrb1: public MiObject{
public:
    explicit BinaryOrb1(string title = "") :
        MiObject("BinaryOrb1", title),
        period_(0.0), ax_sini_(0.0),
        ecc_(0.0), time_peri_(0.0),
        angle_peri_(0.0) {}
    ~BinaryOrb1() {
        Null();
    }
    void Load(string orbfile);
    void Set(double period, double ax_sini,
             double ecc, double time_peri,
             double angle_peri);
    void Copy(const BinaryOrb1* const org);
    BinaryOrb1* const Clone() const;

    double GetPeriod() const {return period_;};
    double GetAxSini() const {return ax_sini_;};
    double GetEcc() const {return ecc_;};
    double GetTimePeri() const {return time_peri_;};
    double GetAnglePeri() const {return angle_peri_;};
    
    void Print(FILE *fp) const;
    void Save(string file) const;
    void PrintData(FILE *fp) const;
    
    double GetTimeObj(MirFunc* func_bin_orb_obs_time, double time_mjd_obs) const;
    double GetDelayTime(double time_mjd) const;
    double GetDopplerNu(double time_mjd, double nu) const;
    
private:
    // 1: companion star
    // 2: compact star (X-ray source)
    //
    // r_1: position vector of companion star
    // r_2: position vector of compact star
    //
    // r_g: center of mass of the binary system
    //      = (m_1 * r_1 + m_2 * r_2) / (m_1 + m_2)
    // r  : = r_2 - r_1
    // r_x: = r_2 - r_g

    // a_x: semimajor axis of ellipse for r_x
    // i  : inclination angle

    double period_;         // orbital period (day)
    double ax_sini_;        // projected semimajor axis of ellipse for r_x (kidou-chou-hankei) (lt-s)
    // a_x * sin(i)
    double ecc_;            // eccentricity of ellipse   (rishin-ritsu)
    double time_peri_;      // time of periastron (MJD)
    double angle_peri_;     // argument of periastron (deg)

    void Null();    
};


class BinaryOrb2: public MiObject{
public:
    explicit BinaryOrb2(string title = "") :
        MiObject("BinaryOrb2", title),
        semimajor_axis_(0.0),
        ecc_(0.0),
        time_peri_(0.0),
        angle_inc_(0.0),
        angle_lan_(0.0),
        angle_peri_(0.0),
        period_(0.0),
        mass_companion_(0.0),
        mass_compact_(0.0),
        radius_companion_(0.0) {}
    ~BinaryOrb2(){
        Null();
    }

    void SetA(double semimajor_axis, double ecc, double time_peri,
              double angle_inc, double angle_peri,
              double mass_companion, double mass_compact,
              double radius_companion);

    void SetP(double period, double ecc, double time_peri,
              double angle_inc, double angle_peri,
              double mass_companion, double mass_compact,
              double radius_companion);

    void LoadA(string file);
    void LoadP(string file);

    BinaryOrb2* const Clone() const;
    
    double GetSemimajorAxis() const {return semimajor_axis_;};
    double GetEcc() const {return ecc_;};
    double GetTimePeri() const {return time_peri_;};
    double GetAngleInc() const {return angle_inc_;};
    double GetAngleLan() const {return angle_lan_;};
    double GetAnglePeri() const {return angle_peri_;};
    double GetPeriod() const {return period_;};

    double GetMassCompanion() const {return mass_companion_;};
    double GetMassCompact() const {return mass_compact_;};    
    double GetRadiusCompanion() const {return radius_companion_;};    

    void Print(FILE *fp) const;
    
    void GetXYZByMjd(double time_mjd, AtVect xyz_out) const;
    void GetVXYZByMjd(double time_mjd, AtVect vxyz_out) const;
    void GetXYZOrbPlaneByMjd(double time_mjd, AtVect xyz_orb_plane_out) const;
    void GetVXYZOrbPlaneByMjd(double time_mjd, AtVect vxyz_orb_plane_out) const;

    double GetDelayTimeCompact(double time_mjd) const;
    double GetDopplerNuCompact(double time_mjd, double nu) const;
    int Eclipse(double time_mjd) const;
    int Collision(double time_mjd) const;

private:
    //
    // The following parameters are for "r" = r_2 - r_1
    // 
    double semimajor_axis_; // semimajor axis of ellipse (kidou-chou-hankei) (lt-s) (= a)
    double ecc_;            // eccentricity of ellipse   (rishin-ritsu) (= epsilon)
    double time_peri_;      // time of periastron (MJD) (= t_0)
    double angle_inc_;      // inclination angle  (deg) (= i)
    double angle_lan_;      // longitude of ascending node (shoukou-ten keido) (deg) (= Omega)
    // must be 0, because photon timing cannot measure this value.
    double angle_peri_;     // argument of periastron (deg) (= omega)
    double period_;         // orbital period (day) (= P)

    double mass_companion_;  // mass of companion star (solar mass unit)
    double mass_compact_;    // mass of compact star (solar mass unit)
    double radius_companion_; // radius of companion star (solar radius unit)

    void Null();
    
    void RotVect(AtVect xyz_orb_plane, AtVect xyz) const;
    
    double GetXOrbPlane(double ecc_anomaly) const;
    double GetYOrbPlane(double ecc_anomaly) const;
    double GetVXOrbPlane(double ecc_anomaly) const;
    double GetVYOrbPlane(double ecc_anomaly) const;

    void GetXYZ(double ecc_anomaly, AtVect xyz_out) const;
    void GetVXYZ(double ecc_anomaly, AtVect vxyz_out) const;
    void GetXYZOrbPlane(double ecc_anomaly, AtVect xyz_orb_plane_out) const;
    void GetVXYZOrbPlane(double ecc_anomaly, AtVect vxyz_orb_plane_out) const;
};

class BinaryOrbObsTimeFunc : public MirFunc{
public:
    explicit BinaryOrbObsTimeFunc(string title = "") :
        MirFunc("BinaryOrbObsTimeFunc", title),
        binorb_(NULL)
        {
            SetNpar(0);
            SetNdim(1);
        }
    ~BinaryOrbObsTimeFunc(){
        Null();
    }
    void Init(BinaryOrb1* binorb);
    void Copy(const BinaryOrbObsTimeFunc* const org);
    BinaryOrbObsTimeFunc* const Clone() const;
    double Eval(const double* const xval, const double* const par) const;
    double Eval1d(double xval, const double* const par) const;

    const BinaryOrb1* const GetBinorb() const {return binorb_;};
        
private:
    BinaryOrb1* binorb_;
    void Null();
};

#endif // MORIIISM_MITOOL_MITIMINGLIB_BINARY_ORB_H_
