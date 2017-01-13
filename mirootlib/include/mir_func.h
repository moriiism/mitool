#ifndef MORIIISM_MITOOL_MIROOTLIB_FUNC_H_
#define MORIIISM_MITOOL_MIROOTLIB_FUNC_H_

#include "TRandom3.h"
#include "TF1.h"
#include "TF2.h"
#include "mir_func_par.h"

class MirFunc : public MiObject{
public:
    MirFunc(string class_name, string title) :
        MiObject(class_name, title),
        npar_(0), ndim_(0) {}
    virtual ~MirFunc(){
        NullMirFunc();
    }
    void SetNpar(int npar) {npar_ = npar;};
    void SetNdim(int ndim) {ndim_ = ndim;};
   
    //
    // const functions
    //
    
    int GetNpar() const {return npar_;};
    int GetNdim() const {return ndim_;};

    virtual double Eval(const double* const xval,
                        const double* const par) const = 0;
    double operator()(const double* const xval,
                      const double* const par) const
        {return Eval(xval, par);};
    
    double Eval1d(double xval,
                  const double* const par) const;
    double Eval2d(double xval, double yval,
                  const double* const par) const;

private:
    int npar_;
    int ndim_;
    void NullMirFunc();
};

#endif // MORIIISM_MITOOL_MIROOTLIB_FUNC_H_

