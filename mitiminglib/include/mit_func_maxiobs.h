#ifndef MORIIISM_MITOOL_MITIMINGLIB_FUNC_MAXIOBS_H_
#define MORIIISM_MITOOL_MITIMINGLIB_FUNC_MAXIOBS_H_

#include "mit_func_pls.h"
#include "mit_telescope.h"

//
// count rate (c/s) functions
//

class MaxiObsFunc : public FuncPls{
public:
    explicit MaxiObsFunc(string title = "") :
        FuncPls("MaxiObsFunc", title),
        func_flux_(NULL),
        func_maxi_sankaku_(NULL)
        {
            SetNpar(0);
            SetNdim(1);
        }
    ~MaxiObsFunc()
        {
            Null();
        }
    void Init(const MirFunc* const func_flux);

    void Copy(const MaxiObsFunc* const org);
    MaxiObsFunc* const Clone() const;
    double Eval(const double* const xval,
                const double* const par) const;

    MirFunc* const GetFuncFlux() const {return func_flux_;};
    MaxiSankakuFunc* const GetFuncMaxiSankaku() const {return func_maxi_sankaku_;};
private:
    MirFunc* func_flux_;  // counts/sec/cm^2
    MaxiSankakuFunc* func_maxi_sankaku_;  // cm^2

    void Null();
};

#endif // MORIIISM_MITOOL_MITIMINGLIB_FUNC_MAXIOBS_H_
