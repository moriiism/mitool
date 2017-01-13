#ifndef MORIIISM_MITOOL_MIROOTLIB_FUNC_PAR_H_
#define MORIIISM_MITOOL_MIROOTLIB_FUNC_PAR_H_

#include "TF1.h"
#include "mi_iolib.h"

class MirFuncPar : public MiObject{
public:
    explicit MirFuncPar(string title = "") :
        MiObject("MirFuncPar", title),
        npar_(0),
        par_name_(NULL),
        par_(NULL) {}
    ~MirFuncPar() {
        Null();
    }
    void Init(int npar);
    void Set(int npar,
             const string* const par_name,
             const double* const par);
    void SetElm(int ipar,
                string par_name,
                double par);
    void InitSet(int npar,
                 const string* const par_name,
                 const double* const par);
    
    void Load(string file);

    void Copy(const MirFuncPar* const org);
    MirFuncPar* const Clone() const;

    void Print(FILE* fp) const;

    int GetNpar() const {return npar_;};
    const string* const GetParName() const {return par_name_;};
    const double* const GetPar() const     {return par_;};
    string GetParNameElm(int ipar) const {return par_name_[ipar];};
    double GetParElm(int ipar) const     {return par_[ipar];};
    
    static void CopyPar(const MirFuncPar* const func_par,
                        TF1* const tf1);

private:
    int npar_;
    string* par_name_;
    double* par_;

    void Null();
};

#endif // MORIIISM_MITOOL_MIROOTLIB_FUNC_PAR_H_
