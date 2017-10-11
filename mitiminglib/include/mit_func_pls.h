#ifndef MORIIISM_MITOOL_MITIMINGLIB_FUNC_PLS_H_
#define MORIIISM_MITOOL_MITIMINGLIB_FUNC_PLS_H_

#include "mir_func.h"
#include "mit_eph.h"
#include "mit_binary_orb.h"
#include "mit_timeconv.h"

class FuncPls : public MirFunc{
public:
    FuncPls(string class_name, string title) :
        MirFunc(class_name, title),
        tunit_(""),
        mjdref_(0.0),
        eph_(NULL),
        binorb_(NULL),
        func_bin_orb_obs_time_(NULL)
        {
            SetNpar(0);
            SetNdim(0); 
        }
    virtual ~FuncPls(){
        NullFuncPls();
    }
    void InitSet(string tunit, double mjdref,
                 const Ephemeris* const eph,
                 const BinaryOrb1* const binorb);
    string GetTunit() const {return tunit_;};
    double GetMjdref() const {return mjdref_;};
    Ephemeris* const GetEph() const {return eph_;};
    BinaryOrb1* const GetBinorb() const {return binorb_;};
    BinaryOrbObsTimeFunc* const GetFuncBinOrbObsTime() const {return func_bin_orb_obs_time_;};

    static FuncPls* GenFuncPls(string func_name);

protected:
    void NullFuncPls();
    void CopyFuncPls(const FuncPls* const org);
    
private:
    string tunit_;    // sec or day
    double mjdref_;   // Time is the elasped time from mjdref_.
    Ephemeris* eph_;
    BinaryOrb1* binorb_;
    BinaryOrbObsTimeFunc* func_bin_orb_obs_time_;
};


//
// pulse profile
//

class SinePlusConstFunc : public FuncPls{
public:
    explicit SinePlusConstFunc(string title = "") :
        FuncPls("SinePlusConstFunc", title)
        {
            SetNpar(2);
            SetNdim(1);
        }
    ~SinePlusConstFunc() {}

    void Copy(const SinePlusConstFunc* const org);
    SinePlusConstFunc* const Clone() const;
    double Eval(const double* const xval,
                const double* const par) const;
};


class MaxiSankakuFunc : public FuncPls{
public:
    explicit MaxiSankakuFunc(string title = "") :
        FuncPls("MaxiSankakuFunc", title)
        {
            SetNpar(0);
            SetNdim(1);
        }
    ~MaxiSankakuFunc() {}

    void Copy(const MaxiSankakuFunc* const org);
    MaxiSankakuFunc* const Clone() const;    
    double Eval(const double* const xval,
                const double* const par) const;
};


//
// binary modulated pulse profile
//

class SinePlusConstBinOrbFunc : public FuncPls{
public:
    explicit SinePlusConstBinOrbFunc(string title = "") :
        FuncPls("SinePlusConstBinOrbFunc", title)
        {
            SetNpar(2);
            SetNdim(1);
        }
    ~SinePlusConstBinOrbFunc() {}

    void Copy(const SinePlusConstBinOrbFunc* const org);
    SinePlusConstBinOrbFunc* const Clone() const;    
    double Eval(const double* const xval,
                const double* const par) const;
};

//
// HistPlsFunc
// 

class HistPlsFunc : public FuncPls{
public:
    explicit HistPlsFunc(string title = "") :
        FuncPls("HistPlsFunc", title),
        hd1d_with_margin_(NULL)
        {
            SetNpar(0);
            SetNdim(1);
        }
    ~HistPlsFunc()
        {
            Null();
        }
    void InitSetHd1d(const HistData1d* const hd1d);
    void Copy(const HistPlsFunc* const org);
    HistPlsFunc* const Clone() const;
    double Eval(const double* const xval,
                const double* const par) const;
    
    const HistData1d* const GetHd1dWithMargin() const {return hd1d_with_margin_;};
private:
    HistData1d* hd1d_with_margin_;

    void Null();
};


//
// GraphPlsFunc
// 

class GraphPlsFunc : public FuncPls{
public:
    explicit GraphPlsFunc(string title = "") :
        FuncPls("GraphPlsFunc", title),
        gd2d_(NULL)
        {
            SetNpar(0);
            SetNdim(1);
        }
    ~GraphPlsFunc()
        {
            Null();
        }
    void InitSetGd2d(const GraphData2d* const gd2d);
    void Copy(const GraphPlsFunc* const org);
    GraphPlsFunc* const Clone() const;        
    double Eval(const double* const xval,
                const double* const par) const;

    const GraphData2d* const GetGd2d() const {return gd2d_;};
private:
    GraphData2d* gd2d_;

    void Null();
};

#endif // MORIIISM_MITOOL_MITIMINGLIB_FUNC_PLS_H_
