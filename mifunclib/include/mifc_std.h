#ifndef MORIIISM_MITOOL_MIFUNCLIB_STD_H_
#define MORIIISM_MITOOL_MIFUNCLIB_STD_H_

#include "mir_math.h"
#include "mir_func.h"
#include "mifc_functional.h"

// -- simple gaussian fit ---

class Gauss1dFunc : public MirFunc{
public:
    explicit Gauss1dFunc(string title = "") :
        MirFunc("Gauss1dFunc", title)
        {
            SetNpar(3);
            SetNdim(1);            
        }
    ~Gauss1dFunc() {}

    void Copy(const Gauss1dFunc* const org);
    Gauss1dFunc* const Clone() const;
    double Eval(const double* const xval,
                const double* const par) const;
};


class Gauss1dPlusConstFunc : public MirFunc{
public:
    explicit Gauss1dPlusConstFunc(string title = "") :
        MirFunc("Gauss1dPlusConstFunc", title)
        {
            SetNpar(4);
            SetNdim(1);            
        }
    ~Gauss1dPlusConstFunc() {}

    void Copy(const Gauss1dPlusConstFunc* const org);
    Gauss1dPlusConstFunc* const Clone() const;
    double Eval(const double* const xval,
                const double* const par) const;
};


class Gauss1dAsymFunc : public MirFunc{
public:
    explicit Gauss1dAsymFunc(string title = "") :
        MirFunc("Gauss1dAsymFunc", title)
        {
            SetNpar(4);
            SetNdim(1);            
        }
    ~Gauss1dAsymFunc() {}

    void Copy(const Gauss1dAsymFunc* const org);
    Gauss1dAsymFunc* const Clone() const;        
    double Eval(const double* const xval,
                const double* const par) const;
};


class Gauss2dFuncAtZero : public MirFunc{
public:
    explicit Gauss2dFuncAtZero(string title = "") :
        MirFunc("Gauss2dFuncAtZero", title)
        {
            SetNpar(3);
            SetNdim(2);            
        }
    ~Gauss2dFuncAtZero() {}

    void Copy(const Gauss2dFuncAtZero* const org);
    Gauss2dFuncAtZero* const Clone() const;        
    double Eval(const double* const xval,
                const double* const par) const;
};

class Gauss2dFunc : public MirFunc{
public:
    explicit Gauss2dFunc(string title = "") :
        MirFunc("Gauss2dFunc", title),
        gauss2d_func_at_zero_(NULL),
        rotation_func_(NULL),
        parallel_shift_func_(NULL)
        {
            SetNpar(7);
            SetNdim(2);
            Init();
        }
    ~Gauss2dFunc() {
        Null();
    }
    void Init();

    void Copy(const Gauss2dFunc* const org);
    Gauss2dFunc* const Clone() const;        
    double Eval(const double* const xval, const double* const par) const;

    Gauss2dFuncAtZero* const GetGauss2dFuncAtZero() const {return gauss2d_func_at_zero_;};
    RotationFunc* const GetRotationFunc() const {return rotation_func_;};
    ParallelShiftFunc* const GetParallelShiftFunc() const {return parallel_shift_func_;};
    
private:
    Gauss2dFuncAtZero* gauss2d_func_at_zero_;
    RotationFunc* rotation_func_;
    ParallelShiftFunc* parallel_shift_func_;

    void Null();
};


// -- simple function

class Const1dFunc : public MirFunc{
public:
    explicit Const1dFunc(string title = "") :
        MirFunc("Const1dFunc", title)
        {
            SetNpar(1);
            SetNdim(1);            
        }
    ~Const1dFunc() {}

    void Copy(const Const1dFunc* const org);
    Const1dFunc* const Clone() const;        
    double Eval(const double* const xval,
                const double* const par) const;
};

class Const2dFunc : public MirFunc{
public:
    explicit Const2dFunc(string title = "") :
        MirFunc("Const2dFunc", title)
        {
            SetNpar(2);
            SetNdim(1);            
        }
    ~Const2dFunc() {}

    void Copy(const Const2dFunc* const org);
    Const2dFunc* const Clone() const;        
    double Eval(const double* const xval,
                const double* const par) const;
};

class LinFunc : public MirFunc{
public:
    explicit LinFunc(string title = "") :
        MirFunc("LinFunc", title)
        {
            SetNpar(2);
            SetNdim(1);            
        }
    ~LinFunc() {}

    void Copy(const LinFunc* const org);
    LinFunc* const Clone() const;        
    double Eval(const double* const xval,
                const double* const par) const;
};

class LinMidFunc : public MirFunc{
public:
    explicit LinMidFunc(string title = "") :
        MirFunc("LinMidFunc", title)
        {
            SetNpar(3);
            SetNdim(1);            
        }
    ~LinMidFunc() {}

    void Copy(const LinMidFunc* const org);
    LinMidFunc* const Clone() const;        
    double Eval(const double* const xval,
                const double* const par) const;
};

class LinMidSlopeFunc : public MirFunc{
public:
    explicit LinMidSlopeFunc(string title = "") :
        MirFunc("LinMidSlopeFunc", title)
        {
            SetNpar(3);
            SetNdim(1);            
        }
    ~LinMidSlopeFunc() {}

    void Copy(const LinMidSlopeFunc* const org);
    LinMidSlopeFunc* const Clone() const;        
    double Eval(const double* const xval,
                const double* const par) const;
};

class LinMidSlopeErrFunc : public MirFunc{
public:
    explicit LinMidSlopeErrFunc(string title = "") :
        MirFunc("LinMidSlopeErrFunc", title)
        {
            SetNpar(3);
            SetNdim(1);            
        }
    ~LinMidSlopeErrFunc() {}

    void Copy(const LinMidSlopeErrFunc* const org);
    LinMidSlopeErrFunc* const Clone() const;        
    double Eval(const double* const xval,
                const double* const par) const;
};


class ParabolaFunc : public MirFunc{
public:
    explicit ParabolaFunc(string title = "") :
        MirFunc("ParabolaFunc", title)
        {
            SetNpar(3);
            SetNdim(1);            
        }
    ~ParabolaFunc() {}

    void Copy(const ParabolaFunc* const org);
    ParabolaFunc* const Clone() const;        
    double Eval(const double* const xval, const double* const par) const;
};


// y = y0 (x - x0)^alpha
// par0: alpha
// par1: x0
// par2: y0
class PowerlawFunc : public MirFunc{
public:
    explicit PowerlawFunc(string title = "") :
        MirFunc("PowerlawFunc", title)
        {
            SetNpar(3);
            SetNdim(1);            
        }
    ~PowerlawFunc() {}

    void Copy(const PowerlawFunc* const org);
    PowerlawFunc* const Clone() const;        
    double Eval(const double* const xval,
                const double* const par) const;
};

// peg power-law
// y = y0 (x - x0)^alpha
// par0: alpha
// par1: x0
// par2: Y = integral between x1 and x2
//       y0 = 
// par3: xval_lo
// par4: xval_up

class PowerlawPegFunc : public MirFunc{
public:
    explicit PowerlawPegFunc(string title = "") :
        MirFunc("PowerlawPegFunc", title),
        xval_lo_(0.0), xval_up_(0.0)
        {
            SetNpar(3);
            SetNdim(1);            
        }
    ~PowerlawPegFunc() {
        Null();
    }

    void SetRange(double xval_lo, double xval_up);
    void Copy(const PowerlawPegFunc* const org);
    PowerlawPegFunc* const Clone() const;        
    double Eval(const double* const xval,
                const double* const par) const;

    double GetXvalLo() const {return xval_lo_;};
    double GetXvalUp() const {return xval_up_;};
    
private:
    double xval_lo_;
    double xval_up_;

    void Null();        
    double GetY0(double pl_index,
                 double xval0,
                 double norm_integral) const;
};

// -- sine function

// par[0] = freq
// par[1] = phase
// par[3] = norm
// par[4] = cons
class SinePlusConstFunc : public MirFunc{
public:
    explicit SinePlusConstFunc(string title = "") :
        MirFunc("SinePlusConstFunc", title)
        {
            SetNpar(4);
            SetNdim(1);            
        }
    ~SinePlusConstFunc() {}

    void Copy(const SinePlusConstFunc* const org);
    SinePlusConstFunc* const Clone() const;
    double Eval(const double* const xval, const double* const par) const;
};



#endif // MORIIISM_MITOOL_MIFUNCLIB_STD_H_


