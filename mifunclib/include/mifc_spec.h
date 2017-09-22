#ifndef MORIIISM_MITOOL_MIFUNCLIB_SPEC_H_
#define MORIIISM_MITOOL_MIFUNCLIB_SPEC_H_

#include "TF1.h"

#include "mir_mathpar.h"
#include "mir_physpar.h"
#include "mir_func.h"
#include "mir_func_par.h"
#include "mir_root_tool.h"

class FuncSpec : public MirFunc{
public:
    FuncSpec(string class_name, string title) :
        MirFunc(class_name, title)
        {
            SetNpar(0);
            SetNdim(0);
        }
    virtual ~FuncSpec(){}

    double FNu(const double* const xval, const double* const par) const;   // F_nu (erg/sec/cm^2/Hz)
    double NuFNu(const double* const xval, const double* const par) const; // nu F_nu (Hz * erg/sec/cm^2/Hz)
    double PhNu(const double* const xval, const double* const par) const;  // Photon_nu (photons/sec/cm^2/Hz)

    TF1* const GenTF1FNu(double x_low, double x_up) const;
    void DrawFuncFNu(const MirFuncPar* const func_par,
                     MirRootTool* const root_tool,
                     double x_low, double x_up, string outfig) const;
    TF1* const GenTF1NuFNu(double x_low, double x_up) const;
    void DrawFuncNuFNu(const MirFuncPar* const func_par,
                       MirRootTool* const root_tool,
                       double x_low, double x_up, string outfig) const;
    TF1* const GenTF1PhNu(double x_low, double x_up) const;
    void DrawFuncPhNu(const MirFuncPar* const func_par,
                      MirRootTool* const root_tool,
                      double x_low, double x_up, string outfig) const;
};

//
// functions used for energy spectrum
//
// Eval() must be F_nu in unit of erg/sec/cm^2/Hz
//

class BlackbodyFunc : public FuncSpec{
public:
    explicit BlackbodyFunc(string title = "") :
        FuncSpec("BlackbodyFunc", title)
        {
            SetNpar(3);
            SetNdim(1);
        }
    ~BlackbodyFunc() {}

    void Copy(const BlackbodyFunc* const org);
    BlackbodyFunc* const Clone() const;    
    double Eval(const double* const xval,
                const double* const par) const;
private:
    double B_nu(double nu, double Temp) const;
};

class StdAccDiskFunc : public FuncSpec{
public:
    explicit StdAccDiskFunc(string title = "") :
        FuncSpec("StdAccDiskFunc", title)
        {
            SetNpar(6);
            SetNdim(1);            
        }
    ~StdAccDiskFunc() {}

    void Copy(const StdAccDiskFunc* const org);
    StdAccDiskFunc* const Clone() const;        
    double Eval(const double* const xval,
                const double* const par) const;
private:
    double FuncInnerMineshige(const double* const xval,
                              const double* const par) const;
};

class DustDiskFunc : public FuncSpec{
public:
    explicit DustDiskFunc(string title = "") :
        FuncSpec("DustDiskFunc", title)
        {
            SetNpar(6);
            SetNdim(1);            
        }
    ~DustDiskFunc() {}

    void Copy(const DustDiskFunc* const org);
    DustDiskFunc* const Clone() const;        
    double Eval(const double* const xval,
                const double* const par) const;
private:
    double FuncInnerMineshige(const double* const xval,
                              const double* const par) const;
};


class DustDiskWangFunc : public FuncSpec{
public:
    explicit DustDiskWangFunc(string title = "") :
        FuncSpec("DustDiskWangFunc", title)
        {
            SetNpar(6);
            SetNdim(1);            
        }
    ~DustDiskWangFunc() {}

    void Copy(const DustDiskWangFunc* const org);
    DustDiskWangFunc* const Clone() const;        
    double Eval(const double* const xval,
                const double* const par) const;

    double GetTin(const double* const par) const;
    double GetTout(const double* const par) const;
private:
    double FuncInnerMineshige(const double* const xval,
                              const double* const par) const;
};


class PowerlawSpecFunc : public FuncSpec{
public:
    explicit PowerlawSpecFunc(string title = "") :
        FuncSpec("PowerlawSpecFunc", title)
        {
            SetNpar(3);
            SetNdim(1);
        }
    ~PowerlawSpecFunc() {}

    void Copy(const PowerlawSpecFunc* const org);
    PowerlawSpecFunc* const Clone() const;    
    double Eval(const double* const xval,
                const double* const par) const;
};


#endif // MORIIISM_MITOOL_MIFUNCLIB_SPEC_H_
