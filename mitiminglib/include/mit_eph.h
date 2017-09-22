#ifndef MORIIISM_MITOOL_MITIMINGLIB_EPH_H_
#define MORIIISM_MITOOL_MITIMINGLIB_EPH_H_

#include "mi_iolib.h"
#include "mir_physpar.h"
#include "mit_eph_calc.h"

class Ephemeris: public MiObject{
public:
    explicit Ephemeris(string title = "") :
        MiObject("Ephemeris", title),
        nu_(0.0), nu_err_(0.0),
        nu_dot_(0.0), nu_dot_err_(0.0),
        nu_dot2_(0.0), nu_dot2_err_(0.0),
        nu_dot3_(0.0), nu_dot3_err_(0.0),
        phase_(0.0), phase_err_(0.0),
        epoch_mjd_(0.0), t_st_mjd_(0.0), t_ed_mjd_(0.0) {}
    ~Ephemeris(){
        Null();
    }

    // set
    void Set(double nu, double nu_err,
             double nu_dot, double nu_dot_err,
             double nu_dot2, double nu_dot2_err,
             double nu_dot3, double nu_dot3_err,
             double phase, double phase_err,
             double epoch_mjd, double t_st_mjd, double t_ed_mjd);

    void Load(string ephfile);
    void Copy(const Ephemeris* const org);
    Ephemeris* const Clone() const;
    
    // get
    double GetNu() const {return nu_;};
    double GetNuErr() const {return nu_err_;};
    double GetNuDot() const {return nu_dot_;};
    double GetNuDotErr() const {return nu_dot_err_;};
    double GetNuDot2() const {return nu_dot2_;};
    double GetNuDot2Err() const {return nu_dot2_err_;};
    double GetNuDot3() const {return nu_dot3_;};
    double GetNuDot3Err() const {return nu_dot3_err_;};
    double GetPhase() const {return phase_;};
    double GetPhaseErr() const {return phase_err_;};  

    double GetEpochMjd() const {return epoch_mjd_;};
    double GetTstMjd() const {return t_st_mjd_;};
    double GetTedMjd() const {return t_ed_mjd_;};

    double GetPeriod() const;
    double GetPeriodDot() const;
    double GetPeriodDot2() const;
    double GetPeriodDot3() const;
    double GetPeriodErr() const;
    double GetPeriodDotErr() const;
    double GetPeriodDot2Err() const;
    double GetPeriodDot3Err() const;

    double GetNuAtTimeMjd(double time_mjd) const;
    double GetNuErrAtTimeMjd(double time_mjd) const;
    double GetNuDotAtTimeMjd(double time_mjd) const;
    double GetNuDotErrAtTimeMjd(double time_mjd) const;
    double GetNuDot2AtTimeMjd(double time_mjd) const;
    double GetNuDot2ErrAtTimeMjd(double time_mjd) const;
    double GetNuDot3AtTimeMjd(double time_mjd) const;
    double GetNuDot3ErrAtTimeMjd(double time_mjd) const;

    double GetGphaseAtTimeMjd(double time_mjd) const;
    double GetGphaseErrAtTimeMjd(double time_mjd) const;
    double GetPhaseAtTimeMjd(double time_mjd) const;
  
    Ephemeris* const GenEphemerisAtTimeMjd(double time_mjd) const;

    double GetTimeMjdAtGphase(double gphase) const;
  
  
    // save
    void Save(string ephfile) const;
  
    // output  
    void Print(FILE *fp) const;
    void Print2(FILE *fp) const;
    void MkQdp(string qdpout) const;
    void PrintRange(FILE *fp) const;

    // check
    int CheckNu() const;
   
private:
    double nu_;          // Hz
    double nu_err_;      
    double nu_dot_;      // Hz s^-1
    double nu_dot_err_;
    double nu_dot2_;     // Hz s^-2
    double nu_dot2_err_;
    double nu_dot3_;     // Hz s^-3
    double nu_dot3_err_;

    double phase_;       // 0 -- 1
    double phase_err_;   // 0 -- 1
  
    double epoch_mjd_;   // mjd
    double t_st_mjd_;    // mjd
    double t_ed_mjd_;    // mjd

    void Null();
};

#endif // MORIIISM_MITOOL_MITIMINGLIB_EPH_H_
